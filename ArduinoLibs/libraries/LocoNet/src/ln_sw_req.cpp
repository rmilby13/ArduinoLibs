#include "ln_sw_req.h"
#include "lnconst.h"
#include <Arduino.h>

//#define DEBUGLNSWREQ
//#define TRACELNSWREQ

#ifdef TRACELNSWREQ
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNSWREQ
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNSWREQ
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

namespace LocoNet {
	LN_SW_REQ::LN_SW_REQ() : LNPacket (4) {
		this->data[0] = DigiTraxOpcSwReq;
		this->setAddr (1);
		this->setCheckSum ();
	}

	LN_SW_REQ::LN_SW_REQ( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_SW_REQ::LN_SW_REQ( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_SW_REQ::toString() {
		return LNPacket::toString () + "Requesting Switch at " + arduino::String (this->getAddr ()) + " to "
		        + (this->getClosed () ? "Closed" : "Thrown") + " Output " + (this->getActive () ? "Active" : "Inactive");
	}

	lnaddr LN_SW_REQ::getAddr() {
		return ((this->data[2] & 0x0F) << 7) + (this->data[1] & 0x7F) + 1;
	}

	void LN_SW_REQ::setAddr( lnaddr address ) {
		lnaddr addr = address;
		this->data[1] = addr & 0x7F;
		addr = addr >> 7;
		addr = addr & 0x0F;
		this->data[2] = addr | (this->data[2] & 0xF0);
		this->setCheckSum ();
	}

	void LN_SW_REQ::setClosed( bool closed ) {
		if (closed) {
			bitSet (this->data.at (2), 5);
		} else {
			bitClear (this->data.at (2), 5);
		}
		this->setCheckSum ();
	}

	bool LN_SW_REQ::getClosed() {
		return (bitRead (this->data.at (2), 5) == 1 ? true : false);
	}

	void LN_SW_REQ::setActive( bool active ) {
		if (active) {
			bitSet (this->data.at (2), 4);
		} else {
			bitClear (this->data.at (2), 4);
		}
		this->setCheckSum ();
	}

	bool LN_SW_REQ::getActive() {
		return (bitRead (this->data.at (2), 4) == 1 ? true : false);
	}
}
