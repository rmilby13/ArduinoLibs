#ifndef LIBRARIES_LOCONET_SRC_LN_GPON_H_
#define LIBRARIES_LOCONET_SRC_LN_GPON_H_
#pragma once

#include "lnpacket.h"
#include "Arduino.h"
namespace LocoNet {
	class LN_GPON : public LocoNet::LNPacket {
	public:
		LN_GPON();
		LN_GPON( packet_data &pdata );
		arduino::String toString();
	protected:
	private:
	};
}

#endif
