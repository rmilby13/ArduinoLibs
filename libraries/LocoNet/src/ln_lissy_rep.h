#ifndef LIBRARIES_LOCONET_SRC_LN_LISSY_REP_H_
#define LIBRARIES_LOCONET_SRC_LN_LISSY_REP_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_LISSY_REP : public LNPacket {
	public:
		LN_LISSY_REP();
		LN_LISSY_REP( packet_data &pdata );
		LN_LISSY_REP( LNPacket &packet );
		arduino::String toString();

		byte getFlag();
		byte getUnitHigh();
		byte getUnitLow();
		byte getAddrHigh();
		byte getAddrLow();
	};
}

#endif
