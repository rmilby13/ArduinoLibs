#include "ln_imm_packet.h"
#include "lnconst.h"
#include <Arduino.h>

//#define DEBUGLNIMM
//#define TRACELNIMM

#ifdef TRACELNIMM
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNIMM
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNIMM
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

LocoNet::LN_IMM_Packet::LN_IMM_Packet() : LNPacket (11) {
	this->data[0] = DigiTraxOpcImmPacket;
	this->data[1] = 0x0B;
	this->data[2] = 0x7F;
	this->data[6] = 0x01;
	this->setAddr (1);
	this->setCheckSum ();
}

LocoNet::LN_IMM_Packet::LN_IMM_Packet(packet_data& pdata) : LNPacket(pdata) {

}

LocoNet::LN_IMM_Packet::LN_IMM_Packet( LNPacket& packet) : LNPacket (packet) {

}

arduino::String LocoNet::LN_IMM_Packet::toString() {
	arduino::String s;
	switch (this->getAspect()) {
		case LocoNet::SignalHeadRed:
			s = "Red";
			break;
		case LocoNet::SignalHeadYellow:
			s = "Yellow";
			break;
		case LocoNet::SignalHeadGreen:
			s = "Green";
			break;
		case LocoNet::SignalHeadLunar:
			s = "Lunar";
			break;
		case LocoNet::SignalHeadFlashingRed:
			s = "Flashing Red";
			break;
		case LocoNet::SignalHeadFlashingYellow:
			s = "Flashing Yellow";
			break;
		case LocoNet::SignalHeadFlashingGreen:
			s = "Flashing Green";
			break;
		case LocoNet::SignalHeadFlashingLunar:
			s = "Flashing Lunar";
			break;
		case LocoNet::SignalHeadDark:
			s = "Dark";
			break;
		default:
			s = "unknown";
	}
	return LNPacket::toString() + " IMM Packet address: " + arduino::String(this->getAddr()) + " - " + s;
}

LocoNet::SignalHeadAspect LocoNet::LN_IMM_Packet::getAspect(){
	DEBUG("Get Aspect from data 7 %d" , this->data[7]);
	return (LocoNet::SignalHeadAspect) this->data[7];
}

lnaddr LocoNet::LN_IMM_Packet::getAddr() {
	TRACE("%X %X", this->data[5], this->data[6]);
	lnaddr ret = 1;
	lnaddr t;
	TRACE("ret = %d(%#04x)", ret, ret);
	t = (lnaddr)((this->data[6] & 0x06) >> 1);
	TRACE("ret = %d(%#04x) : t = %d(%#04x)", ret, ret, t, t);
	ret = ret + t;
	t = (lnaddr)((this->data[5] & 0x3F) << 2);
	TRACE("ret = %d(%#04x) : t = %d(%#04x)", ret, ret, t, t);
	ret = ret + t;
	t = (lnaddr)(((this->data[6] & 0x70) ^ 0x70)<< 4);
	TRACE("ret = %d(%#04x) : t = %d(%#06x)", ret, ret, t, t);
	ret = ret + t;
	TRACE("ret = %d(%#04x)", ret, ret);
	return ret;
}

void LocoNet::LN_IMM_Packet::setAddr( lnaddr address ) {
	TRACE("Setting address to %d", address);
	lnaddr addr = address-1;
	byte im1 = (this->data[5] & 0x40) | ((addr & 0xFC)>>2);
	byte im2 = (this->data[6] & 0x09) | ((addr & 0x03)<<1) | (((addr & 0x0700)>>4) ^ 0x70);
	this->data[5] = im1;
	this->data[6] = im2;
	this->setCheckSum();
}

/*
void LocoNet::LN_SW_REQ::setClosed( bool closed ) {
	if (closed) {
		bitSet (this->data.at (2), 5);
	} else {
		bitClear (this->data.at (2), 5);
	}
}

bool LocoNet::LN_SW_REQ::getClosed() {
	return (bitRead (this->data.at (2), 5) == 1 ? true : false);
}

void LocoNet::LN_SW_REQ::setActive(bool active) {
	if (active) {
		bitSet (this->data.at (2), 4);
	} else {
		bitClear (this->data.at (2), 4);
	}
}

bool LocoNet::LN_SW_REQ::getActive() {
	return (bitRead (this->data.at (2), 4) == 1 ? true : false);
}
*/
