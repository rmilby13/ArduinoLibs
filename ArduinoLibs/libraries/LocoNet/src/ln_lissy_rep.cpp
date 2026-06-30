#include "ln_lissy_rep.h"
#include <arduino.h>

namespace LocoNet {
	LN_LISSY_REP::LN_LISSY_REP() : LNPacket (8) {
		this->data[0] = DigiTraxOpcLissyRep;
		this->setCheckSum ();
	}

	LN_LISSY_REP::LN_LISSY_REP( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_LISSY_REP::LN_LISSY_REP( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_LISSY_REP::toString() {
		return LNPacket::toString () + "LISSY_REP";
	}

	byte LN_LISSY_REP::getFlag(){
		return this->data.size() > 2 ? this->data[2] : 0;
	}

	byte LN_LISSY_REP::getUnitHigh(){
		return this->data.size() > 3 ? this->data[3] : 0;
	}

	byte LN_LISSY_REP::getUnitLow(){
		return this->data.size() > 4 ? this->data[4] : 0;
	}

	byte LN_LISSY_REP::getAddrHigh(){
		return this->data.size() > 5 ? this->data[5] : 0;
	}

	byte LN_LISSY_REP::getAddrLow(){
		return this->data.size() > 6 ? this->data[6] : 0;
	}
}
