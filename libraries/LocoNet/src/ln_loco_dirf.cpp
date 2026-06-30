#include "ln_loco_dirf.h"
#include <arduino.h>

namespace LocoNet {
	LN_LOCO_DIRF::LN_LOCO_DIRF() : LNPacket (4) {
		this->data[0] = DigiTraxOpcLocoDirF;
		this->setCheckSum ();
	}

	LN_LOCO_DIRF::LN_LOCO_DIRF( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_LOCO_DIRF::LN_LOCO_DIRF( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_LOCO_DIRF::toString() {
		return LNPacket::toString () + "LOCO_DIRF";
	}

	byte LN_LOCO_DIRF::getSlot(){
		return this->data.size() > 1 ? this->data[1] : 0;
	}

	byte LN_LOCO_DIRF::getDirF(){
		return this->data.size() > 2 ? this->data[2] : 0;
	}

	void LN_LOCO_DIRF::setSlot(byte s){
		if(this->data.size() > 1) this->data[1] = s;
		this->setCheckSum();
	}

	void LN_LOCO_DIRF::setDirF(byte df){
		if(this->data.size() > 2) this->data[2] = df;
		this->setCheckSum();
	}
}
