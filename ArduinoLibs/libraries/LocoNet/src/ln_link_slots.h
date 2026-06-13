#ifndef LIBRARIES_LOCONET_SRC_LN_LINK_SLOTS_H_
#define LIBRARIES_LOCONET_SRC_LN_LINK_SLOTS_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_LINK_SLOTS : public LNPacket {
	public:
		LN_LINK_SLOTS();
		LN_LINK_SLOTS( packet_data &pdata );
		LN_LINK_SLOTS( LNPacket &packet );
		arduino::String toString();
	};
}

#endif
