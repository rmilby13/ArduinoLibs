#include "ln_link_slots.h"
#include <arduino.h>

namespace LocoNet {
	LN_LINK_SLOTS::LN_LINK_SLOTS() : LNPacket (4) {
		this->data[0] = DigiTraxOpcLinkSlots;
		this->setCheckSum ();
	}

	LN_LINK_SLOTS::LN_LINK_SLOTS( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_LINK_SLOTS::LN_LINK_SLOTS( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_LINK_SLOTS::toString() {
		return LNPacket::toString () + "LINK_SLOTS";
	}

	byte LN_LINK_SLOTS::getSlotA(){
		return this->data.size() > 1 ? this->data[1] : 0;
	}

	byte LN_LINK_SLOTS::getSlotB(){
		return this->data.size() > 2 ? this->data[2] : 0;
	}

	void LN_LINK_SLOTS::setSlotA(byte a){
		if(this->data.size() > 1) this->data[1] = a;
		this->setCheckSum();
	}

	void LN_LINK_SLOTS::setSlotB(byte b){
		if(this->data.size() > 2) this->data[2] = b;
		this->setCheckSum();
	}
}
