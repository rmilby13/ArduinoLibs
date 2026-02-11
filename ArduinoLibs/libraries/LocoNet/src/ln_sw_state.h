/*
 * LNSWState.h
 *
 *  Created on: Nov 5, 2024
 *      Author: rmilb
 */

#ifndef LIBRARIES_LOCONET_SRC_LNSWSTATE_H_
#define LIBRARIES_LOCONET_SRC_LNSWSTATE_H_

#include <ln_packet.h>
#include <Arduino.h>
namespace LocoNet {

	class LN_SW_State : public LNPacket {
	public:
		LN_SW_State();
		LN_SW_State( packet_data &pdata );
		LN_SW_State( LNPacket &packet );
		virtual ~LN_SW_State();
		arduino::String toString();
		lnaddr getAddress();
		void setAddress( lnaddr address );
	};

} /* namespace LocoNet */

#endif /* LIBRARIES_LOCONET_SRC_LNSWSTATE_H_ */
