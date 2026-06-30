/*
 * LNWRSLDATA.h
 *
 *  Created on: Jun 17, 2025
 *      Author: rmilb
 */

#ifndef LIBRARIES_LOCONET_SRC_LN_WR_SL_DATA_H_
#define LIBRARIES_LOCONET_SRC_LN_WR_SL_DATA_H_

#include <ln_packet.h>
#include <Arduino.h>
namespace LocoNet {
	class LN_WR_SL_DATA: public LNPacket {
	public:
		LN_WR_SL_DATA();
		LN_WR_SL_DATA( LNPacket &packet );
		LN_WR_SL_DATA( packet_data &pdata );
		virtual arduino::String toString();
		virtual ~LN_WR_SL_DATA();
	};
}
#endif /* LIBRARIES_LOCONET_SRC_LN_WR_SL_DATA_H_ */
