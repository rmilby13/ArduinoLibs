#include "ln_slot_stat1.h"
#include <arduino.h>

namespace LocoNet {
	LN_SLOT_STAT1::LN_SLOT_STAT1() : LNPacket (4) {
		this->data[0] = DigiTraxOpcSlotStat1;
		this->setCheckSum ();
	}

	LN_SLOT_STAT1::LN_SLOT_STAT1( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_SLOT_STAT1::LN_SLOT_STAT1( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_SLOT_STAT1::toString() {
		return LNPacket::toString () + "SLOT_STAT1";
	}

	byte LN_SLOT_STAT1::getSlot(){
		return this->data.size() > 1 ? this->data[1] : 0;
	}

	byte LN_SLOT_STAT1::getStat1(){
		return this->data.size() > 2 ? this->data[2] : 0;
	}

	void LN_SLOT_STAT1::setSlot(byte s){
		if(this->data.size() > 1) this->data[1] = s;
		this->setCheckSum();
	}

	void LN_SLOT_STAT1::setStat1(byte s1){
		if(this->data.size() > 2) this->data[2] = s1;
		this->setCheckSum();
	}
}
