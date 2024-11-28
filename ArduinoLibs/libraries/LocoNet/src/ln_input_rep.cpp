#include "ln_input_rep.h"
#include "lnconst.h"
#include <Arduino.h>

//#define DEBUGLNINPUTREP
//#define TRACELNINPUTREP

#ifdef TRACELNINPUTREP
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNINPUTREP
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNINPUTREP
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif
namespace LocoNet {

	LN_INPUT_REP::LN_INPUT_REP() : LNPacket (4) {
		this->data[0] = DigiTraxOpcSwReq;
		this->setAddr (1);
		this->setCheckSum ();
	}

	LN_INPUT_REP::LN_INPUT_REP( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_INPUT_REP::LN_INPUT_REP( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_INPUT_REP::toString() {
		return LNPacket::toString () + "Input Report from Address " + arduino::String (this->getAddr ()) + " currently "
		        + (this->getActive () ? "High" : "Low");
	}

	lnaddr LN_INPUT_REP::getAddr() {
		return ((this->data.at (2) & 0x0F) << 8) + ((this->data.at (1) & 0x7F) << 1) + ((this->data.at (2) & 0x20) >> 5)
		        + 1;
	}

	void LN_INPUT_REP::setAddr( lnaddr address ) {
		TRACE("OLD DATA [ %2X %2X ]\n", this->data.at (1), this->data.at (2));
		lnaddr LNaddr = address - 1;
		TRACE("LNaddr %d %4X\n", LNaddr, LNaddr);
		byte b1, b2;
		b1 = (LNaddr & 0xFE) >> 1;
		TRACE("b1 = %04X\n", b1);
		b2 = (LNaddr & 0x0F00) >> 8;
		TRACE("b2 = %04X\n", b2);
		b2 = b2 | ((LNaddr & 0x01) << 5);
		TRACE("b2 = %04X\n", b2);
		b2 = (this->data.at (2) & 0x50) | b2;
		TRACE("b2 = %04X\n", b2);
		this->data.at (1) = b1;
		this->data.at (2) = b2;
		this->setCheckSum ();
	}

	bool LN_INPUT_REP::getActive() {
		byte b = this->data[2] & 0x10;
		DEBUG("b = %04X", b);
		return (b == 0x10);
	}

	void LN_INPUT_REP::setActive( bool active ) {
		//this->data[2] = this->data & 0xEF;
		if (active) {
			DEBUG("Before Setting Active %02X", this->data[2]);
			bitSet (this->data[2], 4);
			DEBUG("Setting Active %02X", this->data[2]);
		} else {
			bitClear (this->data[2], 4);
		}
		this->setCheckSum ();
	}
}
