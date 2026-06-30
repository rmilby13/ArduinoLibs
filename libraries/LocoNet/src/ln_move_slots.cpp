#include "ln_move_slots.h"
#include <arduino.h>

namespace LocoNet {
	LN_MOVE_SLOTS::LN_MOVE_SLOTS() : LNPacket (4) {
		this->data[0] = DigiTraxOpcMoveSlots;
		this->setCheckSum ();
	}

	LN_MOVE_SLOTS::LN_MOVE_SLOTS( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_MOVE_SLOTS::LN_MOVE_SLOTS( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_MOVE_SLOTS::toString() {
		return LNPacket::toString () + "MOVE_SLOTS";
	}

	byte LN_MOVE_SLOTS::getSrc(){
		return this->data.size() > 1 ? this->data[1] : 0;
	}

	byte LN_MOVE_SLOTS::getDst(){
		return this->data.size() > 2 ? this->data[2] : 0;
	}

	void LN_MOVE_SLOTS::setSrc(byte s){
		if(this->data.size() > 1) this->data[1] = s;
		this->setCheckSum();
	}

	void LN_MOVE_SLOTS::setDst(byte d){
		if(this->data.size() > 2) this->data[2] = d;
		this->setCheckSum();
	}
}
