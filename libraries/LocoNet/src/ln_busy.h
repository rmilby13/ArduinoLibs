#ifndef LIBRARIES_LOCONET_SRC_LN_BUSY_H_
#define LIBRARIES_LOCONET_SRC_LN_BUSY_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_BUSY : public LNPacket {
	public:
		LN_BUSY();
		LN_BUSY( packet_data &pdata );
		LN_BUSY( LNPacket &packet );
		arduino::String toString();
	protected:
	private:
	};
}

#endif
