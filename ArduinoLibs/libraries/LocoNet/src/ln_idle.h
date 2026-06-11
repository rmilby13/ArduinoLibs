#ifndef LIBRARIES_LOCONET_SRC_LN_IDLE_H_
#define LIBRARIES_LOCONET_SRC_LN_IDLE_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_IDLE : public LNPacket {
	public:
		LN_IDLE();
		LN_IDLE( packet_data &pdata );
		LN_IDLE( LNPacket &packet );
		arduino::String toString();
	protected:
	private:
	};
}

#endif
