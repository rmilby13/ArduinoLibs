#ifndef LIBRARIES_LOCONET_SRC_LN_GPOFF_H_
#define LIBRARIES_LOCONET_SRC_LN_GPOFF_H_


#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_GPOFF : public LNPacket {
	public:
		LN_GPOFF();
		LN_GPOFF( packet_data &pdata );
		LN_GPOFF( LNPacket &packet );
		arduino::String toString();
	protected:
	private:
	};
}

#endif
