#ifndef LIBRARIES_LOCONET_SRC_LN_IMM_Packet_H_
#define LIBRARIES_LOCONET_SRC_LN_IMM_Packet_H_
#pragma once

#include "ln_packet.h"
#include <Arduino.h>
namespace LocoNet {
	class LN_IMM_Packet : public LNPacket {
	public:
		LN_IMM_Packet();
		/*
		 LN_SW_REQ( byte dataArray[], uint len );
		 */
		LN_IMM_Packet( LNPacket &packet );
		LN_IMM_Packet( packet_data &pdata );
		arduino::String toString();
		lnaddr getAddress();
		void setAddress( lnaddr address );
		SignalHeadAspect getAspect();
		void setAspect( SignalHeadAspect aspect );
	protected:
	private:
	};
}

#endif
