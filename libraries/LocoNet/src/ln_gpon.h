#ifndef LIBRARIES_LOCONET_SRC_LN_GPON_H_
#define LIBRARIES_LOCONET_SRC_LN_GPON_H_
#pragma once

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_GPON : public LNPacket {
	public:
		LN_GPON();
		LN_GPON( packet_data &pdata );
		LN_GPON( LNPacket &packet );
		arduino::String toString();
	protected:
	private:
	};
}

#endif
