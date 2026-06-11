#ifndef LIBRARIES_LOCONET_SRC_LN_SW_REQ_H_
#define LIBRARIES_LOCONET_SRC_LN_SW_REQ_H_
#pragma once

#include <ln_packet.h>
#include <Arduino.h>
namespace LocoNet {
	class LN_SW_REQ : public LNPacket {
	public:
		LN_SW_REQ();
		/*
		 LN_SW_REQ( byte dataArray[], uint len );
		 */
		LN_SW_REQ( packet_data &pdata );
		LN_SW_REQ( LNPacket &packet );
		arduino::String toString();

		lnaddr getAddress();
		void setAddress( lnaddr address );
		void setClosed( bool closed );
		bool getClosed();
		void setActive( bool active );
		bool getActive();
	protected:
	private:
	};
}

#endif
