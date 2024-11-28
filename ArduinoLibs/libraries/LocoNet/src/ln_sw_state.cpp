/*
 * LNSWState.cpp
 *
 *  Created on: Nov 5, 2024
 *      Author: rmilb
 */

#include "ln_sw_state.h"

//#define DEBUGLNSWState
//#define TRACELNSWState

#ifdef TRACELNSWState
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNSWState
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNSWState
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

namespace LocoNet {

	LN_SW_State::LN_SW_State() : LNPacket (4) {
		// TODO Auto-generated constructor stub
		this->data[0] = 0xBC;
		this->setCheckSum ();
	}

	LN_SW_State::LN_SW_State( packet_data &pdata ) : LNPacket (pdata) {

	}
	LN_SW_State::LN_SW_State( LNPacket &packet ) : LNPacket (packet) {

	}

	LN_SW_State::~LN_SW_State() {
		// TODO Auto-generated destructor stub
	}

	arduino::String LN_SW_State::toString() {
		return LNPacket::toString () + "Request State of Switch " + arduino::String (this->getAddr ());
	}

	lnaddr LN_SW_State::getAddr() {
		return ((this->data[2] & 0x0F) << 7) + (this->data[1] & 0x7F) + 1;
	}

	void LN_SW_State::setAddr( lnaddr address ) {
		lnaddr addr = address;
		this->data[1] = addr & 0x7F;
		addr = addr >> 7;
		addr = addr & 0x0F;
		this->data[2] = addr | (this->data[2] & 0xF0);
		this->setCheckSum ();
	}
} /* namespace LocoNet */
