#ifndef LIBRARIES_LOCONET_SRC_LNPACKET_H_
#define LIBRARIES_LOCONET_SRC_LNPACKET_H_
#include "Arduino.h"
#include <vector>
#include <mutex>
#include <memory>
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
		static std::unique_ptr<LNPacket> factory( packet_data &pdata );
		static std::unique_ptr<LNPacket> factory( LNPacket& packet);
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
		byte static getLen( LN_OP_CODE opc );
	};
}

#endif
