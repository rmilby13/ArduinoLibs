#ifndef LIBRARIES_LOCONET_SRC_LN_SL_RD_DATA_H_
#define LIBRARIES_LOCONET_SRC_LN_SL_RD_DATA_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_SL_RD_DATA : public LNPacket {
	public:
		LN_SL_RD_DATA();
		LN_SL_RD_DATA( packet_data &pdata );
		LN_SL_RD_DATA( LNPacket &packet );
		arduino::String toString();
	};
}

#endif
