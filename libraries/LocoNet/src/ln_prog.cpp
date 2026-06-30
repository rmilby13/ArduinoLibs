#include "ln_prog.h"
#include <arduino.h>

namespace LocoNet {
	LN_PROG::LN_PROG() : LNPacket (16) {
		this->data[0] = DigiTraxOpcProg;
		this->setCheckSum ();
	}

	LN_PROG::LN_PROG( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_PROG::LN_PROG( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_PROG::toString() {
		return LNPacket::toString () + "PROG";
	}

	byte LN_PROG::getByte(int idx){
		int pos = 1 + idx;
		return this->data.size() > pos ? this->data[pos] : 0;
	}

	void LN_PROG::setByte(int idx, byte v){
		int pos = 1 + idx;
		if(this->data.size() > pos) this->data[pos] = v;
		this->setCheckSum();
	}
}
