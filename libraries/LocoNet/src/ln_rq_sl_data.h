#ifndef LIBRARIES_LOCONET_SRC_LN_RQ_SL_DATA_H_
#define LIBRARIES_LOCONET_SRC_LN_RQ_SL_DATA_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_RQ_SL_DATA : public LNPacket {
	public:
		LN_RQ_SL_DATA();
		LN_RQ_SL_DATA( packet_data &pdata );
		LN_RQ_SL_DATA( LNPacket &packet );
		arduino::String toString();

		byte getSlot();
		void setSlot(byte s);
	};
}

#endif
