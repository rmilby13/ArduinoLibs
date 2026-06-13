#ifndef LIBRARIES_LOCONET_SRC_LN_LOCO_SPD_H_
#define LIBRARIES_LOCONET_SRC_LN_LOCO_SPD_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_LOCO_SPD : public LNPacket {
	public:
		LN_LOCO_SPD();
		LN_LOCO_SPD( packet_data &pdata );
		LN_LOCO_SPD( LNPacket &packet );
		arduino::String toString();
	};
}

#endif
