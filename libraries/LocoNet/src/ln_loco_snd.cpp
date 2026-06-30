#include "ln_loco_snd.h"
#include <arduino.h>

namespace LocoNet {
	LN_LOCO_SND::LN_LOCO_SND() : LNPacket (4) {
		this->data[0] = DigiTraxOpcLocoSnd;
		this->setCheckSum ();
	}

	LN_LOCO_SND::LN_LOCO_SND( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_LOCO_SND::LN_LOCO_SND( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_LOCO_SND::toString() {
		return LNPacket::toString () + "LOCO_SND";
	}

	byte LN_LOCO_SND::getSlot(){
		return this->data.size() > 1 ? this->data[1] : 0;
	}

	byte LN_LOCO_SND::getSound(){
		return this->data.size() > 2 ? this->data[2] : 0;
	}

	void LN_LOCO_SND::setSlot(byte s){
		if(this->data.size() > 1) this->data[1] = s;
		this->setCheckSum();
	}

	void LN_LOCO_SND::setSound(byte snd){
		if(this->data.size() > 2) this->data[2] = snd;
		this->setCheckSum();
	}
}
