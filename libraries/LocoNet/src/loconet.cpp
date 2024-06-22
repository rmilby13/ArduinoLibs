#include "loconet.h"
#include "lnconst.h"
#if defined(DEBUGLOCONET) || defined(TRACELOCONET)
#define LNDEBUG(...) Serial.printf("%s:%d:\t",__FILE__,__LINE__); Serial.print(__VA_ARGS__)
#define LNDEBUGLN(...) Serial.printf("%s:%d:\t",__FILE__,__LINE__); Serial.println(__VA_ARGS__)
#else
#define LNDEBUG(...)
#define LNDEBUGLN(...)
#endif
#ifdef TRACELOCONET
#define LNTRACE(...) LNDEBUG(__VA_ARGS__)
#define LNTRACELN(...) LNDEBUGLN(__VA_ARGS__)
#else
#define LNTRACE(...)
#define LNTRACELN(...)
#endif
#ifndef SKIPMUTEX
#define LOCK(...) mutex_enter_blocking (__VA_ARGS__)
#define UNLOCK(...) mutex_exit (__VA_ARGS__)
#else
#define LOCK(...)
#define UNLOCK(...)
#endif

//#include "hardware/gpio.h"

LocoNet::LocoNet::LocoNet () {
  this->lastCD = micros ();
  this->NetPri = DigiTraxInitPriority;
  this->rx_pin = LOCONET_RX_PIN;
  this->tx_pin = LOCONET_TX_PIN;
  this->rx_sm = 0;
  this->tx_sm = 0;
  this->rx_pio = pio0_hw;
  this->tx_pio = pio0_hw;
  mutex_init (&this->rxbufferlock);
  mutex_init (&this->txbufferlock);
  mutex_init (&this->lastCDlock);
}
;

uint LocoNet::LocoNet::sendQSize () {
  return this->txbuffer.size ();
}
;
void LocoNet::LocoNet::setRxPin (unsigned char rx_pin) {
  this->rx_pin = rx_pin;
}
;
unsigned char LocoNet::LocoNet::getRxPin () {
  return this->rx_pin;
}
;
void LocoNet::LocoNet::setTxPin (unsigned char tx_pin) {
  this->tx_pin = tx_pin;
}
;
unsigned char LocoNet::LocoNet::getTxPin () {
  return this->tx_pin;
}
;
void LocoNet::LocoNet::setRxSm (uint rx_sm) {
  this->rx_sm = rx_sm;
}
;
uint LocoNet::LocoNet::getRxSm () {
  return this->rx_sm;
}
;
void LocoNet::LocoNet::setTxSm (uint tx_sm) {
  this->tx_sm = tx_sm;
}
;
uint LocoNet::LocoNet::getTxSm () {
  return this->tx_sm;
}

void LocoNet::LocoNet::begin () {
  this->begin (this->tx_pin, this->rx_pin);
}
;

void LocoNet::LocoNet::begin (unsigned char lnTxPin, unsigned char lnRxPin) {

  if (pio_can_add_program (pio0_hw, &loconet_tx_program)) {
    this->tx_pio = pio0_hw;
    this->tx_sm = pio_claim_unused_sm (this->tx_pio, false);
    if (this->tx_sm < 1) {
      this->tx_pio = pio1_hw;
      this->tx_sm = pio_claim_unused_sm (this->tx_pio, true);
    }
  } else if (pio_can_add_program (pio1_hw, &loconet_tx_program) || (this->tx_sm < 1)) {
    this->tx_pio = pio1_hw;
    this->tx_sm = pio_claim_unused_sm (this->tx_pio, true);
  }
  uint offset = pio_add_program (this->tx_pio, &loconet_tx_program);
  pio_sm_set_pins_with_mask (this->tx_pio, this->tx_sm, 1u << lnTxPin, 1u << lnTxPin);
  pio_sm_set_pindirs_with_mask (this->tx_pio, this->tx_sm, 1u << lnTxPin, 1u << lnTxPin);
  pio_gpio_init (this->tx_pio, lnTxPin);
  //pio_gpio_init(this->tx_pio,25);
  gpio_pull_up (lnTxPin);
  pio_sm_config c = loconet_tx_program_get_default_config (offset);
  sm_config_set_out_shift (&c, true, false, 8);
  sm_config_set_out_pins (&c, lnTxPin, 1);
  sm_config_set_sideset_pins (&c, lnTxPin);
  sm_config_set_fifo_join (&c, PIO_FIFO_JOIN_TX);
  sm_config_set_clkdiv (&c, LOCONET_PIO_CLK_DIV);
  pio_sm_init (this->tx_pio, this->tx_sm, offset, &c);
  pio_sm_set_enabled (this->tx_pio, this->tx_sm, true);

  if (pio_can_add_program (pio0_hw, &loconet_rx_program)) {
    this->rx_pio = pio0_hw;
    this->rx_sm = pio_claim_unused_sm (this->rx_pio, false);
    if (this->rx_sm < 1) {
      this->rx_pio = pio1_hw;
      this->rx_sm = pio_claim_unused_sm (this->rx_pio, true);
    }
  } else if (pio_can_add_program (pio1_hw, &loconet_rx_program) || (this->rx_sm < 1)) {
    this->rx_pio = pio1_hw;
    this->rx_sm = pio_claim_unused_sm (this->rx_pio, true);
  }
  offset = pio_add_program (this->rx_pio, &loconet_rx_program);
  pio_sm_set_pins_with_mask (this->rx_pio, this->rx_sm, 1u << lnRxPin, 1u << lnRxPin);
  pio_sm_set_pindirs_with_mask (this->rx_pio, this->rx_sm, 1u << lnRxPin, 1u << lnRxPin);
  pio_gpio_init (this->rx_pio, lnRxPin);
  gpio_pull_up (rx_pin);
  pio_sm_config crx = loconet_rx_program_get_default_config (offset);
  sm_config_set_in_pins (&crx, lnRxPin);
  sm_config_set_in_shift (&crx, true, false, 8);
  sm_config_set_sideset_pins (&crx, 25);
  sm_config_set_fifo_join (&crx, PIO_FIFO_JOIN_RX);
  sm_config_set_clkdiv (&crx, LOCONET_PIO_CLK_DIV);
  pio_sm_init (this->rx_pio, this->rx_sm, offset, &crx);
  pio_sm_set_enabled (this->rx_pio, this->rx_sm, true);
}
;

void LocoNet::LocoNet::send (LNPacket &packet) {
  //LNPacket p = LNPacket(packet.len());
  //this->NetPri = (this->txbuffer.size()==0) ? DigiTraxInitPriority : this->NetPri;
  LNDEBUG("Queuing Packet to send, queue size = ");
  LNDEBUG(this->txbuffer.size ());
  LNDEBUG(" - ");
  LNDEBUGLN(packet.repr ());
  if (packet.valid ()) {
#ifndef SKIPMUTEX
    mutex_enter_blocking (&this->txbufferlock);
#endif
    this->txbuffer.push_back (packet);
#ifndef SKIPMUTEX
    mutex_exit (&this->txbufferlock);
#endif
  };
}
;

void LocoNet::LocoNet::recieve (LNPacket &packet) {
  LOCK(&this->rxbufferlock);
  for (uint i = 0; i < packet.len (); i++) {
    this->rxbuffer.push_back (packet.getByte (i));
  }
  UNLOCK(&this->rxbufferlock);
  this->showRxBuffer ();
}
;

void LocoNet::LocoNet::process () {
  this->getBytes ();
  this->sendBytes ();
  this->getBytes ();
}
;

LocoNet::LNPacket LocoNet::LocoNet::getPacket () {
#ifdef TRACELOCONET
  this->showRxBuffer ();
#endif
  while ((!this->rxbuffer.empty ()) && (this->rxbuffer.front () < 128)) { // Find the start of the next packet
    LNTRACELN("Skipping byte from non-packet start");
    LOCK(&this->rxbufferlock);
    this->rxbuffer.pop_front ();
    UNLOCK(&this->rxbufferlock);
  }
  if (this->rxbuffer.size () < 2) { // Minimum packet size is 2 bytes, if there there are not at least two bytes, break fast.
    //LNDEBUG()
    return LNPacket (LN_OPC_NOOP);
  }
  uint plen = LNPacket::getLen (this->rxbuffer.front ());
  if (this->rxbuffer.size () == LOCONET_MAX_PACKET_SIZE) { // if the packet size isn't 2, 4, or 6 byes, get the packet size from the packet
    LNTRACELN("Need to get size of buffer from first byte");
    LOCK(&this->rxbufferlock);
    unsigned char opc = this->rxbuffer.front ();
    this->rxbuffer.pop_front ();
    plen = this->rxbuffer.front ();
    this->rxbuffer.push_front (opc);
    UNLOCK(&this->rxbufferlock);
  }
  if (this->rxbuffer.size () < plen) { // fast exit if the queue is empty or not long enough
    LNTRACE("Rxbuffer not long enough for this packet yet buffer length : ");LNTRACE(this->rxbuffer.size ());LNTRACE(" expected ");LNTRACELN(plen);

    return LNPacket (LN_OPC_NOOP);
  }

  packet_data packbytes;
  LNTRACE("getting Packet Data - Packet length : ");LNTRACE(plen);LNTRACE(" - Packet Data : *[");
  LOCK(&this->rxbufferlock);
  for (uint i = 0; i < plen; i++) {
    packbytes.push_back (this->rxbuffer.front ());
    LNTRACE(" *");LNTRACE(i);LNTRACE(":");LNTRACE(this->rxbuffer.front (), HEX);
    this->rxbuffer.pop_front ();
  }
  UNLOCK(&this->rxbufferlock);LNTRACELN("]*");LNTRACELN("Returning Packet");
  processPacket (LNPacket (packbytes));
  return LNPacket (packbytes);
}
;

void LocoNet::LocoNet::showTxBuffer () {
#if defined(DEBUGLOCONET) || defined(TRACELOCONET)
  //LocoNet::packet_queue squeue = this->txbuffer;
  Serial.print ("txbuffer:");
  LOCK(&this->txbufferlock);
  for (auto it : this->txbuffer) {
    LNDEBUG(" * ");
    LNDEBUGLN(it.repr ());
  }
  UNLOCK(&this->txbufferlock);
  LNDEBUGLN("");
#endif
}
void LocoNet::LocoNet::showRxBuffer () {
#if defined(DEBUGLOCONET) || defined(TRACELOCONET)
  //std::deque<byte>::iterator it;
  LNDEBUG("rxbuffer = [");
  LOCK(&this->rxbufferlock);
  for (auto it : this->rxbuffer) {
    LNDEBUG(" ");
    LNDEBUG(it, HEX);
  }
  UNLOCK(&this->rxbufferlock);
  LNDEBUGLN(" ]");
#endif
}
;
bool LocoNet::LocoNet::pioRxFIFOEmpty () {
  return pio_sm_is_rx_fifo_empty (this->rx_pio, this->rx_sm);
}
;

unsigned char LocoNet::LocoNet::getByte () {
  //Serial.println("---Getting Byte");
  io_rw_8 *rxfifo_shift = (io_rw_8*) &this->rx_pio->rxf[this->rx_sm] + 3;
  return (unsigned char) * rxfifo_shift;
}
;

void LocoNet::LocoNet::getBytes () {
  while (!pioRxFIFOEmpty ()) {
    unsigned char b = this->getByte ();
    LOCK(&this->rxbufferlock);
    this->rxbuffer.push_back (b);
    UNLOCK(&this->rxbufferlock);
    LOCK(&this->lastCDlock);
    this->lastCD = micros ();
    UNLOCK(&this->lastCDlock);LNTRACE("Getting Byte From PIO : ");LNTRACELN(b, HEX);
#ifdef TRACELOCONET
    this->showRxBuffer ();
#endif
  }
}
;

void LocoNet::LocoNet::send (unsigned char write) {
  pio_sm_put_blocking (this->tx_pio, this->tx_sm, (uint32_t) write);
}
;

void LocoNet::LocoNet::sendBytes () {
  if (!this->txbuffer.empty ()) {
    LOCK(&this->lastCDlock);
    this->lastCD = this->lastCD > micros () ? micros () : this->lastCD;
    UNLOCK(&this->lastCDlock);
    unsigned long currentDelay = micros () - this->lastCD;
    unsigned long requiredDelay = DigiTractCDBackOffuS + (DigiTraxBituS * 6) + (this->NetPri * DigiTraxBituS);
    if (currentDelay > requiredDelay) {
      //LNDEBUGLN("Loconet network CD Backoff met");
      if (random (1, this->NetPri--) <= 3) {
	this->showTxBuffer ();
	LNDEBUG("Loconet network backoff random check passed. TX buffer size = ");
	LNDEBUG(this->txbuffer.size ());
	LNDEBUG(" - Transmitting : ");
	LNPacket p = this->txbuffer.front ();
	LNDEBUGLN(p.repr ());
	for (uint i = 0; i < p.len (); i++) {
	  unsigned char send = p.getByte (i);
	  this->send (send);
	  this->getBytes ();
	}
	LOCK(&this->txbufferlock);
	this->txbuffer.pop_front ();
	UNLOCK(&this->txbufferlock);
	this->NetPri = DigiTraxInitPriority;
      } else {
	LOCK(&this->lastCDlock);
	this->lastCD = micros ();
	UNLOCK(&this->lastCDlock);
      }
    } else {
      this->NetPri--;
    }
  }
}
;

void LocoNet::LocoNet::processPacket (LNPacket packet) {
  switch (packet.get_opcode ())
    {
    case LN_OPC_INPUT_REP:
      this->ssm[packet.getaddr ()] = packet.getActive () ? LN_SEN_ACTIVE : LN_SEN_INACTIVE;
      break;
    case LN_OPC_SW_REQ:
      this->swsm[packet.getaddr()] = packet.getClosed() ? packet.getActive() ? LN_SW_CLOSED_ACTIVE : LN_SW_CLOSED_INACTIVE : packet.getActive() ? LN_SW_THROWN_ACTIVE : LN_SW_THROWN_INACTIVE;
      break;
    default:
      packet.get_opcode ();
    }
}

LocoNet::LN_SENSOR_STATUS LocoNet::LocoNet::getSensorStatus (uint address) {
  return (this->ssm.count (address) > 0) ? this->ssm[address] : LN_SEN_UNDEF;
}

LocoNet::LN_SWITCH_STATUS LocoNet::LocoNet::getSwitchStatus (uint address) {
  return (this->swsm.count (address) > 0) ? this->swsm[address] : LN_SW_UNDEF;
}

arduino::String LocoNet::LocoNet::repr () {
  arduino::String ret = "";
  ret += "\n ----\nSensor status:\n";
  for (auto it : this->ssm) {
    ret += "Sensor: ";
    ret += it.first;
    ret += " Status: ";
    ret += it.second ? "Active" : "Inactive";
    ret += "\n";
  }
  ret += "Switch status:\n";
  for (auto it : this->swsm) {
    ret += "Switch: ";
    ret += it.first;
    ret += " Status: ";
    ret += it.second ==LN_SW_CLOSED_INACTIVE ? "Closed & Inactive" : it.second ==LN_SW_CLOSED_ACTIVE ? "Closed & Active" : it.second==LN_SW_THROWN_INACTIVE?"Thrown & Inactive" : it.second==LN_SW_THROWN_ACTIVE ?"Thrown & Active" : "Unknown";
    ret += "\n";
  }
  ret += " ----\n\n";
  return ret;
}
