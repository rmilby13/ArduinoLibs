#ifndef LIBRARIES_LOCONET_SRC_LN_LOCO_DIRF_H_
#define LIBRARIES_LOCONET_SRC_LN_LOCO_DIRF_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_LOCO_DIRF : public LNPacket {
	public:
		LN_LOCO_DIRF();
		LN_LOCO_DIRF( packet_data &pdata );
		LN_LOCO_DIRF( LNPacket &packet );
		arduino::String toString();
	};
}

#endif
