#include "ln_rq_sl_data.h"
#include <arduino.h>

namespace LocoNet {
	LN_RQ_SL_DATA::LN_RQ_SL_DATA() : LNPacket (4) {
		this->data[0] = DigiTraxOpcRqSlData;
		this->setCheckSum ();
	}

	LN_RQ_SL_DATA::LN_RQ_SL_DATA( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_RQ_SL_DATA::LN_RQ_SL_DATA( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_RQ_SL_DATA::toString() {
		return LNPacket::toString () + "RQ_SL_DATA";
	}

	byte LN_RQ_SL_DATA::getSlot(){
		return this->data.size() > 1 ? this->data[1] : 0;
	}

	void LN_RQ_SL_DATA::setSlot(byte s){
		if(this->data.size() > 1) this->data[1] = s;
		this->setCheckSum();
	}
}
