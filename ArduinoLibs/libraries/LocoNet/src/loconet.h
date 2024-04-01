#ifndef LIBRARIES_LOCONET_SRC_LOCONET_H_
#define LIBRARIES_LOCONET_SRC_LOCONET_H_
#pragma once

#if !defined(ARDUINO_ARCH_MBED_RP2040) && !defined(ARDUINO_ARCH_RP2040)
#pragma message("Unsupported platform")
#endif

//#define DEBUGLOCONET 1
//#define TRACELOCONET 1
//#define SKIPMUTEX 1

#include <arduino.h>
#include <lnconst.h>
#include <lnpacket.h>
#include <map>
#include <deque>

#ifdef ARDUINO_ARCH_RP2040
#define LOCONET_RX_PIN 14
#define LOCONET_RX_SM 0
#define LOCONET_RX_PIO pio0
#define LOCONET_TX_PIN 15

#define LOCONET_TX_SM 1
#define LOCONET_TX_PIO pio0
#define LOCONET_PIO_CLK_DIV 100000
#define LOCONET_RX_BUFFER_SIZE 255
#define LOCONET_TX_BUFFER_SIZE 40
#include "loconet.pio.h"
#endif
namespace LocoNet {

  typedef std::deque<LNPacket> packet_queue;
  typedef std::deque<unsigned char> rx_byte_queue;
  typedef std::map<unsigned short int,LocoNet::LN_SENSOR_STATUS> sensor_status_map;
  typedef std::map<unsigned short int,LocoNet::LN_SWITCH_STATUS> switch_status_map;
  class LocoNet {
  public:
    LocoNet ();
    void begin ();
    void begin (unsigned char lnTxPin, unsigned char lnRxPin);
    void process ();
    void send (LNPacket& packet);
    void recieve(LNPacket& packet);
    LNPacket getPacket ();
    void setRxPin (unsigned char rx_pin);
    unsigned char getRxPin ();
    void setTxPin (unsigned char tx_pin);
    unsigned char getTxPin ();
    void setRxSm (uint rx_sm);
    uint getRxSm ();
    void setTxSm (uint tx_sm);
    uint getTxSm ();
    uint sendQSize();
    arduino::String repr();
    LN_SENSOR_STATUS getSensorStatus(uint address);
    LN_SWITCH_STATUS getSwitchStatus(uint address);
  private:
    PIO tx_pio;
    PIO rx_pio;
    uint tx_sm;
    uint rx_sm;
    unsigned char tx_pin;
    unsigned char rx_pin;
    uint NetPri;
    uint32_t lastCD;
    rx_byte_queue rxbuffer;
    mutex rxbufferlock;
    packet_queue txbuffer;
    mutex txbufferlock;
    mutex lastCDlock;
    sensor_status_map ssm;
    switch_status_map swsm;

    unsigned char getByte ();
    void getBytes ();
    void sendBytes ();
    LNPacket noop ();
    void send (unsigned char write);
    void showTxBuffer ();
    void showRxBuffer ();
    bool pioRxFIFOEmpty ();
    void processPacket(LNPacket packet);
  };
}
;

//extern LocoNet::LocoNet loconet;

#endif
