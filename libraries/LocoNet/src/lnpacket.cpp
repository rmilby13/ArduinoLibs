#include "lnpacket.h"
#include "Arduino.h"
#ifdef DEBUGLNPACKET
#define LNPDEBUG(...) Serial.printf("%s:%d:\t",__FILE__,__LINE__); Serial.print(__VA_ARGS__)
#define LNPDEBUGLN(...) Serial.printf("%s:%d:\t",__FILE__,__LINE__); Serial.println(__VA_ARGS__)
#define LNPDEBUGF(...) Serial.printf("%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__)
#else
#define LNPDEBUG(...)
#define LNPDEBUGLN(...)
#define LNPDEBUGF(...)
#endif
#ifdef TRACELNPACKET
#define LNPTRACE(...) Serial.printf("%s:%d:\t",__FILE__,__LINE__); Serial.print(__VA_ARGS__)
#define LNPTRACELN(...) Serial.printf("%s:%d:\t",__FILE__,__LINE__); Serial.println(__VA_ARGS__)
#define LNPTRACEF(...) Serial.printf("%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__)
#else
#define LNPTRACE(...)
#define LNPTRACELN(...)
#define LNPTRACEF(...)
#endif

LocoNet::LNPacket::LNPacket (uint len) {
  this->data.resize (len, 0);
}

LocoNet::LNPacket::LNPacket (byte dataArray[], uint len) {
  LNPDEBUG("Creating Packet:");
  this->data.resize (0);
  for (uint i = 0; i < len; i++) {
    LNPDEBUG("*");
    LNPDEBUG(dataArray[i], HEX);
    this->data.push_back (dataArray[i]);
  };
  this->setCheckSum ();
  LNPDEBUGLN(";");
}
;

LocoNet::LNPacket::LNPacket (packet_data &pdata) {
  LNPDEBUG("Building Packet from packet data [");
  for (packet_data::iterator it = pdata.begin (); it != pdata.end (); ++it) {
    LNPDEBUG(" ");
    LNPDEBUG(*it, HEX);
    this->data.push_back (*it);
  }LNPDEBUGLN(" ]");
}

LocoNet::LNPacket::LNPacket (LN_OP_CODE opc) {
  uint packetLen = this->getLen (opc);
  this->data.resize (packetLen);
  for (uint i = 1; i < packetLen; i++) {
    this->data.at (i) = 0;
  };
  switch (opc)
    {
    case LN_OPC_NOOP:
      this->data.at (0) = DigiTraxOpcNoOp;
      break;
    case LN_OPC_BUSY:
      this->data.at (0) = DigiTraxOpcBusy;
      break;
    case LN_OPC_GPOFF:
      this->data.at (0) = DigiTraxOpcGpoff;
      break;
    case LN_OPC_GPON:
      this->data.at (0) = DigiTraxOpcGpon;
      break;
    case LN_OPC_SW_REQ:
      this->data.at (0) = DigiTraxOpcSwReq;
      break;
    case LN_OPC_IMM_PACKET:
      this->data.at (0) = DigiTraxOpcImmPacket;
      this->data.at (1) = 0x0B;
      this->data.at (2) = 0x7F;
      break;
    case LN_OPC_INPUT_REP:
      this->data.at (0) = DigiTraxOpcInputRep;
      this->data.at (1) = 0;
      this->data.at (2) = 0x40;
      break;
    default:
      LNPDEBUGLN("Unknown OpCode");
      this->data.at (0) = DigiTraxOpcNoOp;
      break;
    };
  this->setCheckSum ();
  LNPDEBUGLN(this->repr ().c_str ());
}
;

//LNPacket::LNPacket (const LNPacket &packet) {
//  LNPDEBUGLN("Creating Packet with Packet:");
//LNPDEBUGLN(packet->repr ());
//this->data = packet->data;
//LNPDEBUGLN(this->repr());
//}

LocoNet::LNPacket::~LNPacket () {
  //LNPDEBUGLN("Freeing Packet:" + this->repr ());
}
;

void LocoNet::LNPacket::setCheckSum () {
  byte chksum = 0xFF;
  for (uint i = 0; i < this->data.size () - 1; i++) {
    chksum ^= this->data.at (i);
  }
  this->data.at (this->data.size () - 1) = chksum;
}
;

uint LocoNet::LNPacket::len () {
  return this->data.size ();
}
;

arduino::String LocoNet::LNPacket::repr () {
  LNPDEBUGLN("Building representation of LoconetPacket");
  String ret = "[ ";
  for (uint i = 0; i < this->len (); i++) {
    ret = ret + (this->data.at (i) < 16 ? "0" : "") + String (this->data.at (i), HEX) + " ";
  }
  ret += "] ";
  LNPTRACELN(ret);
  if (this->valid ()) {
    switch (this->get_opcode ())
      {
      case LN_OPC_NOOP:
	ret += "No Op";
	break;
      case LN_OPC_BUSY:
	ret += "Master Busy";
	break;
      case LN_OPC_GPOFF:
	ret += "Global Power Off";
	break;
      case LN_OPC_GPON:
	ret += "Global Power On";
	break;
      case LN_OPC_SW_REQ:
	ret += "Switch Request ";
	ret += arduino::String (this->getaddr ());
	ret += (this->getClosed () ? " Closed" : " Thrown");
	ret += (this->getActive () ? " Active" : " Inactive");
	break;
      case LN_OPC_INPUT_REP:
	ret += "General sensor input codes ";
	ret += arduino::String (this->getaddr ());
	ret += " state ";
	ret += (this->getActive () ? "Active" : "Inactive");
	break;
      default:
	ret += "Unknown";
      }
  } else {
    ret += "Invalid";
  }
  LNPDEBUGLN(ret);
  return ret;
}
;

bool LocoNet::LNPacket::getClosed () {
  return (bitRead (this->data.at (2), 5) == 1 ? true : false);
}

bool LocoNet::LNPacket::getActive () {
  //b &= 0x10;
  bool ret = false;
  switch (this->get_opcode ())
    {
    case LN_OPC_SW_REQ:
//      ret = (bitRead (this->data.at (2), 4) == 1 ? true : false);
//      break;
    case LN_OPC_INPUT_REP:
#ifdef TRACELNPACKET
      for (int i = 0; i < 8; i++) {
	Serial.printf ("Bit %d = %d\n", i, bitRead (this->data.at (1), i));
      }
      for (int i = 0; i < 8; i++) {
	Serial.printf ("Bit %d = %d\n", i, bitRead (this->data.at (2), i));
      }
#endif
      ret = (bitRead (this->data.at (2), 4) == 1 ? true : false);
      break;
    default:
      ret = false;
    }
  return ret;
}

uint LocoNet::LNPacket::getaddr () {
  uint ret;
  switch (this->get_opcode ())
    {
    case LN_OPC_SW_REQ:
      ret = ((this->data.at (2) & 0x0F) << 7) + (this->data.at (1) & 0x7F);
      break;
    case LN_OPC_INPUT_REP:
      ret = ((this->data.at (2) & 0x0F) << 8) + ((this->data.at (1) & 0x7F) << 1) + ((this->data.at (2) & 0x20) >> 5)
	  + 1;
      break;
    default:
      ret = 0;
      break;
    };
  return ret;
}
;

void LocoNet::LNPacket::setaddr (uint addr) {
  switch (this->get_opcode ())
    {
    case LN_OPC_SW_REQ:
      {
	this->data.at (1) = addr & 0x7F;
	addr = addr >> 7;
	addr = addr & 0x0F;
	this->data.at (2) = addr | (this->data.at (2) & 0xF0);
	break;
      }
    case LN_OPC_INPUT_REP:
      {
	LNPTRACEF("OLD DATA [ %2X %2X ]\n", this->data.at (1), this->data.at (2));
	uint LNaddr = addr - 1;
	LNPTRACEF("LNaddr %d %4X\n", LNaddr, LNaddr);
	byte b1, b2;
	b1 = (LNaddr & 0xFE) >> 1;
	LNPTRACE("b1 = ");
	LNPTRACELN(b1, BIN);
	b2 = (LNaddr & 0x0F00) >> 8;
	LNPTRACE("b2 = ");
	LNPTRACELN(b2, BIN);
	b2 = b2 | ((LNaddr & 0x01) << 5);
	LNPTRACE("b2 = ");
	LNPTRACELN(b2, BIN);
	b2 = (this->data.at (2) & 0x50) | b2;
	LNPTRACE("b2 = ");
	LNPTRACELN(b2, BIN);
	this->data.at (1) = b1;
	this->data.at (2) = b2;
	break;
      }
    default:
      this->setCheckSum ();
      break;
    }
  this->setCheckSum ();
  LNPDEBUGF("Address to %d should be %d\n", this->getaddr (), addr);
  LNPDEBUGLN(this->repr ().c_str ());
}
;

void LocoNet::LNPacket::setClosed (bool closed) {
  switch (this->get_opcode ())
    {
    case LN_OPC_SW_REQ:
      if (closed) {
	bitSet (this->data.at (2), 5);
      } else {
	bitClear (this->data.at (2), 5);
      }
      break;
    case LN_OPC_INPUT_REP:
      if (closed) {
	bitSet (this->data.at (2), 4);
      } else {
	bitClear (this->data.at (2), 4);
      }
      break;
    default:
      this->setCheckSum ();
    }
  this->setCheckSum ();
}
;

void LocoNet::LNPacket::setActive (bool active) {
  switch (this->get_opcode ())
    {
    case LN_OPC_SW_REQ:
    case LN_OPC_INPUT_REP:
      if (active) {
	bitSet (this->data.at (2), 4);
      } else {
	bitClear (this->data.at (2), 4);
      }
      break;
    default:
      this->setCheckSum ();
    };
  this->setCheckSum ();
}
;

LocoNet::LN_OP_CODE LocoNet::LNPacket::get_opcode () {
  LocoNet::LN_OP_CODE ret;
  LNPTRACE("Getting OpCode for ");
  LNPTRACE(this->data.at (0), HEX);
  LNPTRACE(" - ");
  switch (this->data.at (0))
    {
    case DigiTraxOpcNoOp:
      LNPTRACELN("DigiTraxOpcNoOp");
      ret = LN_OPC_NOOP;
      break;
    case DigiTraxOpcBusy:
      LNPTRACELN("DigiTraxOpcBusy");
      ret = LN_OPC_BUSY;
      break;
    case DigiTraxOpcGpoff:
      LNPTRACELN("DigiTraxOpcGpoff");
      ret = LN_OPC_GPOFF;
      break;
    case DigiTraxOpcSwReq:
      LNPTRACELN("DigiTraxOpcSwReq");
      ret = LN_OPC_SW_REQ;
      break;
    case DigiTraxOpcInputRep:
      LNPTRACELN("DigiTraxOpcInputRep");
      ret = LN_OPC_INPUT_REP;
      break;
    default:
      LNPTRACELN("UNKNOWN");
      ret = LN_OPC_UNKNOWN;
      break;
    };
  return ret;
}
;

bool LocoNet::LNPacket::valid () {
  byte chksum = 0XFF;
  for (uint i = 0; i < (this->len () - 1); i++) {
    LNPTRACE("valid? i = ");
    LNPTRACE(i);
    LNPTRACE("; chksum = ");
    LNPTRACE(chksum, HEX);
    LNPTRACE("; byte = ");
    LNPTRACELN(this->data.at (i), HEX);
    chksum ^= this->data.at (i);
  };
  LNPTRACE("valid? chksum = ");
  LNPTRACE(chksum, HEX);
  LNPTRACE("; byte = ");
  LNPTRACELN(this->data.at (this->len () - 1), HEX);
  return (chksum == this->data.at (this->len () - 1));
}
;

byte LocoNet::LNPacket::getByte (uint pos) {
  byte ret = 0;
  if (pos < this->len ()) {
    ret = this->data.at (pos);
  }
  return ret;
}
;

uint LocoNet::LNPacket::getLen (byte b) {
  byte ret;
  byte h = b & 224;
  switch (h)
    {
    case 0:
      ret = LOCONET_MAX_PACKET_SIZE;
      break;
    case 128:
      ret = 2;
      break;
    case 160:
      ret = 4;
      break;
    case 192:
      ret = 6;
      break;
    default:
      ret = LOCONET_MAX_PACKET_SIZE;
      LNPDEBUGLN("unknown PacketSize");
      break;
    }
  return ret;
}
;

byte LocoNet::LNPacket::getLen (LN_OP_CODE opc) {
  byte ret;
  switch (opc)
    {
    case LN_OPC_NOOP:
      ret = this->getLen (DigiTraxOpcNoOp);
      break;
    case LN_OPC_BUSY:
      ret = this->getLen (DigiTraxOpcBusy);
      break;
    case LN_OPC_GPOFF:
      ret = this->getLen (DigiTraxOpcGpoff);
      break;
    case LN_OPC_GPON:
      ret = this->getLen (DigiTraxOpcGpon);
      break;
    case LN_OPC_SW_REQ:
      ret = this->getLen (DigiTraxOpcSwReq);
      break;
    case LN_OPC_INPUT_REP:
      ret = this->getLen (DigiTraxOpcInputRep);
      break;
    case LN_OPC_IMM_PACKET:
      ret = 0xB;
      break;
    default:
      ret = LOCONET_MAX_PACKET_SIZE;
      break;
    }
  return ret;
}

