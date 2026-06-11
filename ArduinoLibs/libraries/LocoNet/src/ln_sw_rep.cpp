/*
 * LNSWREP.cpp
 *
 *  Created on: Nov 2, 2024
 *      Author: rmilb
 */

#include "ln_sw_rep.h"
#include <Arduino.h>

//#define DEBUGLNSWREP
//#define TRACELNSWREP

#ifdef TRACELNSWREP
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNSWREP
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNSWREP
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

namespace LocoNet {
	LN_SW_REP::LN_SW_REP() : LNPacket (4) {
		this->data[0] = DigiTraxOpcSwRep;
		this->setCheckSum ();
	}

	LN_SW_REP::LN_SW_REP( lnaddr address, bool closed, bool active ) : LNPacket (4) {
		this->data[0] = DigiTraxOpcSwRep;
		this->setClosed (closed);
		this->setAddress (address);
		this->setActive (active);
		this->setCheckSum ();
	}

	LN_SW_REP::LN_SW_REP( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_SW_REP::LN_SW_REP( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_SW_REP::toString() {
		return LNPacket::toString () + "Reporting Switch at " + arduino::String (this->getAddress ()) + " to "
		        + (this->getClosed () ? "Closed" : "Thrown") + " Output " + (this->getActive () ? "Active" : "Inactive");
	}

	lnaddr LN_SW_REP::getAddress() {
		return ((this->data[2] & 0x0F) << 7) + (this->data[1] & 0x7F) + 1;
	}

	void LN_SW_REP::setAddress( lnaddr address ) {
		lnaddr addr = address - 1;
		this->data[1] = addr & 0x7F;
		addr = addr >> 7;
		addr = addr & 0x0F;
		this->data[2] = addr | (this->data[2] & 0xF0);
		this->setCheckSum ();
	}

	void LN_SW_REP::setClosed( bool closed ) {
		if (closed) {
			bitSet (this->data.at (2), 5);
		} else {
			bitClear (this->data.at (2), 5);
		}
		this->setCheckSum ();
	}

	bool LN_SW_REP::getClosed() {
		return (bitRead (this->data.at (2), 5) == 1 ? true : false);
	}

	void LN_SW_REP::setActive( bool active ) {
		if (active) {
			bitSet (this->data.at (2), 4);
		} else {
			bitClear (this->data.at (2), 4);
		}
		this->setCheckSum ();
	}

	bool LN_SW_REP::getActive() {
		return (bitRead (this->data.at (2), 4) == 1 ? true : false);
	}
}
