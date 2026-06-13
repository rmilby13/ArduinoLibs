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
}
