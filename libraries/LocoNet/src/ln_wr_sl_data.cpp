/*
 * LNWRSLDATA.cpp
 *
 *  Created on: Jun 17, 2025
 *      Author: rmilb
 */

#include "lnconst.h"
#include <Arduino.h>
#include "ln_wr_sl_data.h"

namespace LocoNet {
	LN_WR_SL_DATA::LN_WR_SL_DATA() :
			LNPacket(14) {
		this->data[0] = DigiTraxOpcWrSlData;
		this->data[1] = 0x0E;
		this->setCheckSum();
	}
	LN_WR_SL_DATA::LN_WR_SL_DATA(LNPacket &packet) :
			LNPacket(packet) {

	}

	LN_WR_SL_DATA::LN_WR_SL_DATA(packet_data &pdata) :
			LNPacket(pdata) {

	}

	LN_WR_SL_DATA::~LN_WR_SL_DATA() {
		// TODO Auto-generated destructor stub
	}

	arduino::String LN_WR_SL_DATA::toString() {
		return LNPacket::toString();

	}
}
