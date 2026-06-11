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
namespace LocoNet {

	LN_IMM_Packet::LN_IMM_Packet() : LNPacket (11) {
		this->data[0] = DigiTraxOpcImmPacket;
		this->data[1] = 0x0B;
		this->data[2] = 0x7F;
		this->data[6] = 0x01;
		this->setAddress (1);
		this->setCheckSum ();
	}

	LN_IMM_Packet::LN_IMM_Packet( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_IMM_Packet::LN_IMM_Packet( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_IMM_Packet::toString() {
		arduino::String s;
		switch (this->getAspect ()) {
			case SignalHeadRed:
				s = "Red";
				break;
			case SignalHeadYellow:
				s = "Yellow";
				break;
			case SignalHeadGreen:
				s = "Green";
				break;
			case SignalHeadLunar:
				s = "Lunar";
				break;
			case SignalHeadFlashingRed:
				s = "Flashing Red";
				break;
			case SignalHeadFlashingYellow:
				s = "Flashing Yellow";
				break;
			case SignalHeadFlashingGreen:
				s = "Flashing Green";
				break;
			case SignalHeadFlashingLunar:
				s = "Flashing Lunar";
				break;
			case SignalHeadDark:
				s = "Dark";
				break;
			default:
				s = "unknown";
		}
		return LNPacket::toString () + " IMM Packet address: " + arduino::String (this->getAddress ()) + " - " + s;
	}

	LocoNet::SignalHeadAspect LN_IMM_Packet::getAspect() {
		DEBUG("Get Aspect from data 7 %d" , this->data[7]);
		return (SignalHeadAspect) this->data[7];
	}


	void LN_IMM_Packet::setAspect( SignalHeadAspect aspect ) {
		DEBUG("Set Aspect to %d", aspect);
		if (aspect < SignalHeadRed || aspect > SignalHeadFlashingLunar) {
			DEBUG("Invalid aspect %d", aspect);
			return;
		}
		this->data[7] = (byte) aspect;
		this->setCheckSum ();
	}

	lnaddr LN_IMM_Packet::getAddress() {
		TRACE("%X %X", this->data[5], this->data[6]);
		lnaddr ret = 1;
		lnaddr t;
		TRACE("ret = %d(%#04x)", ret, ret);
		t = (lnaddr) ((this->data[6] & 0x06) >> 1);
		TRACE("ret = %d(%#04x) : t = %d(%#04x)", ret, ret, t, t);
		ret = ret + t;
		t = (lnaddr) ((this->data[5] & 0x3F) << 2);
		TRACE("ret = %d(%#04x) : t = %d(%#04x)", ret, ret, t, t);
		ret = ret + t;
		t = (lnaddr) (((this->data[6] & 0x70) ^ 0x70) << 4);
		TRACE("ret = %d(%#04x) : t = %d(%#06x)", ret, ret, t, t);
		ret = ret + t;
		TRACE("ret = %d(%#04x)", ret, ret);
		return ret;
	}

	void LN_IMM_Packet::setAddress( lnaddr address ) {
		TRACE("Setting address to %d", address);
		lnaddr addr = address - 1;
		byte im1 = (this->data[5] & 0x40) | ((addr & 0xFC) >> 2);
		byte im2 = (this->data[6] & 0x09) | ((addr & 0x03) << 1) | (((addr & 0x0700) >> 4) ^ 0x70);
		this->data[5] = im1;
		this->data[6] = im2;
		this->setCheckSum ();
	}


}
