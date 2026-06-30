#include "ln_consist_func.h"
#include <arduino.h>

namespace LocoNet {
	LN_CONSIST_FUNC::LN_CONSIST_FUNC() : LNPacket (4) {
		this->data[0] = DigiTraxOpcConsistFunc;
		this->setCheckSum ();
	}

	LN_CONSIST_FUNC::LN_CONSIST_FUNC( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_CONSIST_FUNC::LN_CONSIST_FUNC( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_CONSIST_FUNC::toString() {
		return LNPacket::toString () + "CONSIST_FUNC";
	}

	byte LN_CONSIST_FUNC::getSlot(){
		return this->data.size() > 1 ? this->data[1] : 0;
	}

	byte LN_CONSIST_FUNC::getDirF(){
		return this->data.size() > 2 ? this->data[2] : 0;
	}

	void LN_CONSIST_FUNC::setSlot(byte s){
		if(this->data.size() > 1) this->data[1] = s;
		this->setCheckSum();
	}

	void LN_CONSIST_FUNC::setDirF(byte df){
		if(this->data.size() > 2) this->data[2] = df;
		this->setCheckSum();
	}
}
