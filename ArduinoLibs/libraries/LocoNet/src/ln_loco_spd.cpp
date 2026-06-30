#include "ln_loco_spd.h"
#include <arduino.h>

namespace LocoNet {
	LN_LOCO_SPD::LN_LOCO_SPD() : LNPacket (4) {
		this->data[0] = DigiTraxOpcLocoSpd;
		this->setCheckSum ();
	}

	LN_LOCO_SPD::LN_LOCO_SPD( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_LOCO_SPD::LN_LOCO_SPD( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_LOCO_SPD::toString() {
		return LNPacket::toString () + "LOCO_SPD";
	}

	byte LN_LOCO_SPD::getSlot(){
		return this->data.size() > 1 ? this->data[1] : 0;
	}

	byte LN_LOCO_SPD::getSpeed(){
		return this->data.size() > 2 ? this->data[2] : 0;
	}

	void LN_LOCO_SPD::setSlot(byte s){
		if(this->data.size() > 1) this->data[1] = s;
		this->setCheckSum();
	}

	void LN_LOCO_SPD::setSpeed(byte sp){
		if(this->data.size() > 2) this->data[2] = sp;
		this->setCheckSum();
	}
}
