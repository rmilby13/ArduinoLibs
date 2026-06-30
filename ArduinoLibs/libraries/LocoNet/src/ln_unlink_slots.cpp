#include "ln_unlink_slots.h"
#include <arduino.h>

namespace LocoNet {
	LN_UNLINK_SLOTS::LN_UNLINK_SLOTS() : LNPacket (4) {
		this->data[0] = DigiTraxOpcUnlinkSlots;
		this->setCheckSum ();
	}

	LN_UNLINK_SLOTS::LN_UNLINK_SLOTS( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_UNLINK_SLOTS::LN_UNLINK_SLOTS( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_UNLINK_SLOTS::toString() {
		return LNPacket::toString () + "UNLINK_SLOTS";
	}

	byte LN_UNLINK_SLOTS::getSlotA(){
		return this->data.size() > 1 ? this->data[1] : 0;
	}

	byte LN_UNLINK_SLOTS::getSlotB(){
		return this->data.size() > 2 ? this->data[2] : 0;
	}

	void LN_UNLINK_SLOTS::setSlotA(byte a){
		if(this->data.size() > 1) this->data[1] = a;
		this->setCheckSum();
	}

	void LN_UNLINK_SLOTS::setSlotB(byte b){
		if(this->data.size() > 2) this->data[2] = b;
		this->setCheckSum();
	}
}
