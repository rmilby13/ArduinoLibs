#ifndef LIBRARIES_LOCONET_SRC_LN_SW_REQ_H_
#define LIBRARIES_LOCONET_SRC_LN_SW_REQ_H_
#pragma once

#include "lnpacket.h"
#include "Arduino.h"
namespace LocoNet {
	class LN_SW_REQ : public LocoNet::LNPacket {
	public:
		LN_SW_REQ();
		LN_SW_REQ( byte dataArray[], uint len );
		LN_SW_REQ( packet_data &pdata );
		lnaddr getAddr();
		void setAddr(lnaddr address);
	protected:
	private:
	};
}

#endif
