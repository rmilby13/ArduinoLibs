#include <ln_packet.h>
#include "Arduino.h"
//
#include "ln_packets.h"
//#define TRACELNPACKET
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

LocoNet::LNPacket::LNPacket( uint len ) {
	this->data.resize (len, 0);
}

LocoNet::LNPacket::LNPacket( packet_data &pdata ) {
	LNPDEBUG("Building Packet from packet data [");
	for (packet_data::iterator it = pdata.begin (); it != pdata.end (); ++it) {
		LNPDEBUG(" ");
		LNPDEBUG(*it, HEX);
		this->data.push_back (*it);
	};
	LNPDEBUGLN(" ]");
}
/*
LocoNet::LNPacket::LNPacket( byte dataArray[], uint len ) {
	LNPDEBUG("Building LN Packet from dataArray of length %d", len);
	for (uint it = 0; it < len; it++) {
		LNPDEBUG(" ");
		LNPDEBUG(dataArray[it], HEX);
		this->data.push_back (dataArray[it]);
	};
	LNPDEBUGLN(" ]");
}
*/
LocoNet::LNPacket::LNPacket( LN_OP_CODE opc ) {
	uint packetLen = this->getLen (opc);
	this->data.resize (packetLen);
	for (uint i = 1; i < packetLen; i++) {
		this->data.at (i) = 0;
	}
	;
	switch (opc) {
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
		case LN_OPC_SW_REP:
			this->data.at (0) = DigiTraxOpcSwRep;
			break;
		case LN_OPC_SW_STATE:
			this->data[0] = DigiTraxOpcSwState;
			break;
		case LN_OPC_SW_ACK:
			this->data[0] = DigiTraxOpcSwAck;
			break;
		case LN_OPC_LONG_ACK:
			this->data[0] = DigiTraxOpcLongAck;
			break;
		default:
			LNPDEBUGLN("Unknown OpCode");
			this->data.at (0) = DigiTraxOpcNoOp;
			break;
	};
	this->setCheckSum ();
	LNPDEBUGLN(this->toString().c_str ());
}
;

LocoNet::LNPacket::~LNPacket() {
	LNPDEBUGLN("Freeing Packet:" + this->toString ());
}
;

void LocoNet::LNPacket::setCheckSum() {
	byte chksum = 0xFF;
	for (uint i = 0; i < this->data.size () - 1; i++) {
		chksum ^= this->data.at (i);
	}
	this->data.at (this->data.size () - 1) = chksum;
}
;

LocoNet::LN_OP_CODE LocoNet::LNPacket::get_opcode() {
	return this->get_opcode(this->data.at(0));
}

LocoNet::LN_OP_CODE LocoNet::LNPacket::get_opcode(byte firstByte){
	LocoNet::LN_OP_CODE oc;
	switch (firstByte){
		case DigiTraxOpcNoOp:
			oc = LN_OPC_NOOP;
			break;
		case DigiTraxOpcBusy:
			oc = LN_OPC_BUSY;
			break;
		case DigiTraxOpcGpoff:
			oc = LN_OPC_GPOFF;
			break;
		case DigiTraxOpcGpon:
			oc = LN_OPC_GPON;
			break;
		case DigiTraxOpcSwReq:
			oc = LN_OPC_SW_REQ;
			break;
		case DigiTraxOpcSwRep:
			oc = LN_OPC_SW_REP;
			break;
		case DigiTraxOpcInputRep:
			oc = LN_OPC_INPUT_REP;
			break;
		case DigiTraxOpcMultiSense:
			oc = LN_OPC_MULTI_SENSE;
			break;
		case DigiTraxOpcImmPacket:
			oc = LN_OPC_IMM_PACKET;
			break;
		case DigiTraxOpcSwState:
			oc = LN_OPC_SW_STATE;
			break;
		case DigiTraxOpcSwAck:
			oc = LN_OPC_SW_ACK;
			break;
		case DigiTraxOpcLongAck:
			oc = LN_OPC_LONG_ACK;
			break;
		case DigiTraxOpcWrSlData:
			oc = LN_OPC_WR_SL_DATA;
			break;
		default:
			oc = LocoNet::LN_OPC_UNKNOWN;
			break;
	}
	return oc;
}

std::unique_ptr<LocoNet::LNPacket> LocoNet::LNPacket::factory(packet_data &pdata){
    switch (LNPacket::get_opcode(pdata.at(0))){
        case LN_OPC_NOOP:
            return std::make_unique<LN_NOP>(pdata);
        case LN_OPC_SW_REQ:
            return std::make_unique<LN_SW_REQ>(pdata);
        case LN_OPC_SW_REP:
            return std::make_unique<LN_SW_REP>(pdata);
        case LN_OPC_IMM_PACKET:
            return std::make_unique<LN_IMM_Packet>(pdata);
        case LN_OPC_INPUT_REP:
            return std::make_unique<LN_INPUT_REP>(pdata);
        case LN_OPC_SW_STATE:
            return std::make_unique<LN_SW_State>(pdata);
        case LN_OPC_SW_ACK:
            return std::make_unique<LN_SW_ACK>(pdata);
        case LN_OPC_LONG_ACK:
            return std::make_unique<LN_Long_Ack>(pdata);
        case LN_OPC_WR_SL_DATA:
            switch (pdata[2]) {
                case 0x7B: // Fast Clock Slot Data
                    return std::make_unique<LN_FAST_CLOCK_SLOT_DATA>(pdata);
                default:
                    LNPDEBUGLN("Unknown SL Data Packet, using generic LN_WR_SL_DATA");
                    return std::make_unique<LN_WR_SL_DATA>(pdata);
            }
        default:
            return std::make_unique<LNPacket>(pdata);
    }
}

std::unique_ptr<LocoNet::LNPacket> LocoNet::LNPacket::factory( LNPacket& packet){
    switch (packet.get_opcode()){
        case LN_OPC_NOOP:
            return std::make_unique<LN_NOP>(packet);
        case LN_OPC_SW_REQ:
            return std::make_unique<LN_SW_REQ>(packet);
        case LN_OPC_SW_REP:
            return std::make_unique<LN_SW_REP>(packet);
        case LN_OPC_IMM_PACKET:
            return std::make_unique<LN_IMM_Packet>(packet);
        case LN_OPC_INPUT_REP:
            return std::make_unique<LN_INPUT_REP>(packet);
        case LN_OPC_SW_STATE:
            return std::make_unique<LN_SW_State>(packet);
        case LN_OPC_SW_ACK:
            return std::make_unique<LN_SW_ACK>(packet);
        case LN_OPC_LONG_ACK:
            return std::make_unique<LN_Long_Ack>(packet);
        case LN_OPC_WR_SL_DATA:
            switch (packet.data.at(2)) {
                case 0x7B: // Fast Clock Slot Data
                    return std::make_unique<LN_FAST_CLOCK_SLOT_DATA>(packet);
                default:
                    LNPDEBUGLN("Unknown SL Data Packet, using generic LN_WR_SL_DATA");
                    return std::make_unique<LN_WR_SL_DATA>(packet);
            }
        default:
            return std::make_unique<LNPacket>(packet);
    }
}

uint LocoNet::LNPacket::len() {
	return this->data.size ();
}
;

void LocoNet::LNPacket::setByte(uint pos, byte b) {
	this->data[pos] = b;
}

arduino::String LocoNet::LNPacket::toString() {
	LNPDEBUGLN("Building representation of LoconetPacket");
	String ret = "[ ";
	for (uint i = 0; i < this->len (); i++) {
//		Serial.printf ("%08b ", this->data.at(i));
		ret = ret + (this->data.at (i) < 16 ? "0" : "") + String (this->data.at (i), HEX) + " ";
	}
	ret += "] ";
	LNPTRACELN(ret);
	if (!this->valid ()) {
		ret += "*Invalid* ";
	};
	LNPDEBUGLN(ret);
	return ret;
}
;
/*
bool LocoNet::LNPacket::getClosed() {
	return (bitRead (this->data.at (2), 5) == 1 ? true : false);
}

bool LocoNet::LNPacket::getActive() {
	//b &= 0x10;
	bool ret = false;
	switch (this->get_opcode ()) {
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

uint LocoNet::LNPacket::getaddr() {
	uint ret;
	switch (this->get_opcode ()) {
		case LN_OPC_SW_REQ:
			ret = ((this->data.at (2) & 0x0F) << 7) + (this->data.at (1) & 0x7F);
			break;
		case LN_OPC_INPUT_REP:
			ret = ((this->data.at (2) & 0x0F) << 8) + ((this->data.at (1) & 0x7F) << 1)
			        + ((this->data.at (2) & 0x20) >> 5) + 1;
			break;
		default:
			ret = 0;
			break;
	};
	return ret;
}
;

void LocoNet::LNPacket::setaddr( uint addr ) {
	switch (this->get_opcode ()) {
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
				LNPTRACE("b1 = "); LNPTRACELN(b1, BIN);
				b2 = (LNaddr & 0x0F00) >> 8;
				LNPTRACE("b2 = "); LNPTRACELN(b2, BIN);
				b2 = b2 | ((LNaddr & 0x01) << 5);
				LNPTRACE("b2 = "); LNPTRACELN(b2, BIN);
				b2 = (this->data.at (2) & 0x50) | b2;
				LNPTRACE("b2 = "); LNPTRACELN(b2, BIN);
				this->data.at (1) = b1;
				this->data.at (2) = b2;
				break;
			}
		default:
			this->setCheckSum ();
			break;
	}
	this->setCheckSum ();
	LNPDEBUGF("Address to %d should be %d\n", this->getaddr (), addr); LNPDEBUGLN(this->toString ().c_str ());
}
;

void LocoNet::LNPacket::setClosed( bool closed ) {
	switch (this->get_opcode ()) {
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

void LocoNet::LNPacket::setActive( bool active ) {
	switch (this->get_opcode ()) {
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
*/


bool LocoNet::LNPacket::valid() {
	byte chksum = 0XFF;
	for (uint i = 0; i < (this->len () - 1); i++) {
		LNPTRACE("valid? i = "); LNPTRACE(i); LNPTRACE("; chksum = "); LNPTRACE(chksum, HEX); LNPTRACE("; byte = "); LNPTRACELN(this->data.at (i), HEX);
		chksum ^= this->data.at (i);
	}; LNPTRACE("valid? chksum = "); LNPTRACE(chksum, HEX); LNPTRACE("; byte = "); LNPTRACELN(this->data.at (this->len () - 1), HEX);
	return (chksum == this->data.at (this->len () - 1));
}
;

byte LocoNet::LNPacket::getByte( uint pos ) {
	byte ret = 0;
	if (pos < this->len ()) {
		ret = this->data.at (pos);
	}
	return ret;
}
;

uint LocoNet::LNPacket::getLen( byte b ) {
	byte ret;
	byte h = b & 224;
	switch (h) {
		case 0:
			ret = 0;
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
			switch (b) {
				case DigiTraxOpcImmPacket:
					ret = 11;
					break;
				case DigiTraxOpcWrSlData:
					ret = 14;
					break;
				default:
					ret = LOCONET_MAX_PACKET_SIZE;
					LNPDEBUGLN("unknown PacketSize");
					break;
			}
	}
	return ret;
}
;

byte LocoNet::LNPacket::getLen( LN_OP_CODE opc ) {
	byte ret;
	switch (opc) {
		case LN_OPC_NOOP:
			ret = LNPacket::getLen (DigiTraxOpcNoOp);
			break;
		case LN_OPC_BUSY:
			ret = LNPacket::getLen (DigiTraxOpcBusy);
			break;
		case LN_OPC_GPOFF:
			ret = LNPacket::getLen (DigiTraxOpcGpoff);
			break;
		case LN_OPC_GPON:
			ret = LNPacket::getLen (DigiTraxOpcGpon);
			break;
		case LN_OPC_SW_REQ:
			ret = LNPacket::getLen (DigiTraxOpcSwReq);
			break;
		case LN_OPC_SW_REP:
			ret = LNPacket::getLen (DigiTraxOpcSwRep);
			break;
		case LN_OPC_INPUT_REP:
			ret = LNPacket::getLen (DigiTraxOpcInputRep);
			break;
		case LN_OPC_IMM_PACKET:
			ret = LNPacket::getLen (DigiTraxOpcImmPacket);
			break;
		case LN_OPC_SW_STATE:
			ret = LNPacket::getLen (DigiTraxOpcWrSlData);
			break;
		default:
			ret = LOCONET_MAX_PACKET_SIZE;
			break;
	}
	return ret;
}
;