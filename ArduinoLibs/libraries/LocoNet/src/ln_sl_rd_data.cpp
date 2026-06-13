#include "ln_sl_rd_data.h"
#include <arduino.h>

namespace LocoNet {
	LN_SL_RD_DATA::LN_SL_RD_DATA() : LNPacket (14) {
		this->data[0] = DigiTraxOpcSlRdData;
		this->setCheckSum ();
	}

	LN_SL_RD_DATA::LN_SL_RD_DATA( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_SL_RD_DATA::LN_SL_RD_DATA( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_SL_RD_DATA::toString() {
		return LNPacket::toString () + "SL_RD_DATA";
	}

	byte LN_SL_RD_DATA::getSlot(){
		return this->data.size() > 2 ? this->data[2] : 0;
	}

	byte LN_SL_RD_DATA::getStat1(){
		return this->data.size() > 3 ? this->data[3] : 0;
	}

	byte LN_SL_RD_DATA::getAddrLow(){
		return this->data.size() > 4 ? this->data[4] : 0;
	}

	byte LN_SL_RD_DATA::getSpeed(){
		return this->data.size() > 5 ? this->data[5] : 0;
	}

	byte LN_SL_RD_DATA::getDirF(){
		return this->data.size() > 6 ? this->data[6] : 0;
	}

	byte LN_SL_RD_DATA::getTrk(){
		return this->data.size() > 7 ? this->data[7] : 0;
	}

	byte LN_SL_RD_DATA::getSs2(){
		return this->data.size() > 8 ? this->data[8] : 0;
	}

	byte LN_SL_RD_DATA::getAddrHigh(){
		return this->data.size() > 9 ? this->data[9] : 0;
	}

	byte LN_SL_RD_DATA::getSound(){
		return this->data.size() > 10 ? this->data[10] : 0;
	}

	byte LN_SL_RD_DATA::getId1(){
		return this->data.size() > 11 ? this->data[11] : 0;
	}

	byte LN_SL_RD_DATA::getId2(){
		return this->data.size() > 12 ? this->data[12] : 0;
	}
}
