/*
 * LNSWACK.cpp
 *
 *  Created on: Nov 5, 2024
 *      Author: rmilb
 */

#include "ln_sw_ack.h"
#include "lnconst.h"
#include <Arduino.h>

//#define DEBUGLNSWACK
//#define TRACELNSWACK

#ifdef TRACELNSWACK
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNSWACK
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNSWACK
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

namespace LocoNet {

	LN_SW_ACK::LN_SW_ACK() : LNPacket (4) {
		// TODO Auto-generated constructor stub
		this->data[0] = DigiTraxOpcSwAck;
		this->setCheckSum ();
	}
	LN_SW_ACK::LN_SW_ACK( packet_data &pdata ) : LNPacket (pdata) {

	}
	LN_SW_ACK::LN_SW_ACK( LNPacket &packet ) : LNPacket (packet) {

	}

	LN_SW_ACK::~LN_SW_ACK() {
		// TODO Auto-generated destructor stub
	}

	arduino::String LN_SW_ACK::toString(){
		return LNPacket::toString() + "Requesting Switch at " + arduino::String(this->getAddress()) + " to " + (this->getClosed()? "Closed" : "Thrown") + " Output " + (this->getActive() ? "Active" : "Inactive") + " with acknowledgment.";
	}


	lnaddr LN_SW_ACK::getAddress() {
		return ((this->data[2] & 0x0F) << 7) + (this->data[1] & 0x7F) + 1;
	}

	void LN_SW_ACK::setAddress( lnaddr address ) {
		lnaddr addr = address;
		this->data[1] = addr & 0x7F;
		addr = addr >> 7;
		addr = addr & 0x0F;
		this->data[2] = addr | (this->data[2] & 0xF0);
		this->setCheckSum ();
	}

	void LN_SW_ACK::setClosed( bool closed ) {
		if (closed) {
			bitSet (this->data.at (2), 5);
		} else {
			bitClear (this->data.at (2), 5);
		}
		this->setCheckSum ();
	}

	bool LN_SW_ACK::getClosed() {
		return (bitRead (this->data.at (2), 5) == 1 ? true : false);
	}

	void LN_SW_ACK::setActive( bool active ) {
		if (active) {
			bitSet (this->data.at (2), 4);
		} else {
			bitClear (this->data.at (2), 4);
		}
		this->setCheckSum ();
	}

	bool LN_SW_ACK::getActive() {
		return (bitRead (this->data.at (2), 4) == 1 ? true : false);
	}

} /* namespace LocoNet */
