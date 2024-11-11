#ifndef LIBRARIES_LOCONET_SRC_LNPACKET_H_
#define LIBRARIES_LOCONET_SRC_LNPACKET_H_
#pragma once

#include "Arduino.h"
#include <mutex>
#include "lnconst.h"
//#define DEBUGLNPACKET 1
//#define TRACELNPACKET 1
namespace LocoNet {

	typedef std::vector<byte> packet_data;

	class LNPacket {
	public:
		LNPacket( uint len );
		LNPacket( packet_data &pdata );
		LNPacket( LN_OP_CODE opc );
		static LNPacket* factory( packet_data &pdata );
		static LNPacket* factory( LNPacket& packet);
		virtual ~LNPacket();
		virtual arduino::String toString();
		uint static getLen( byte b );
		uint len();
		virtual LN_OP_CODE get_opcode();
		static LN_OP_CODE get_opcode( byte firstByte );
		static LN_OP_CODE get_opcode( packet_data &pdata );
		bool valid();
		byte getByte( uint pos );
	protected:
		void setByte( uint pos, byte b );
		void setData( byte dataArray[], uint len );
		void setCheckSum();
		packet_data data;
	private:
		//byte data[LOCONET_MAX_PACKET_SIZE];
//  	uint len;
		//byte getLen(byte b);
		byte getLen( LN_OP_CODE opc );
	};
}

#include "ln_nop.h"
#include "ln_idle.h"
#include "ln_busy.h"
#include "ln_gpoff.h"
#include "ln_gpon.h"
#include "LNSWREP.h"
#include "ln_sw_req.h"
#include "ln_imm_packet.h"
#include "ln_input_rep.h"
#include "LNSWState.h"
#include "LNSWACK.h"
#include "LNLongAck.h"
#endif
