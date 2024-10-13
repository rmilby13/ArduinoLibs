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
  	//LNPacket();
  	LNPacket(uint len);
  	LNPacket(byte dataArray[], uint len);
  	LNPacket(packet_data& pdata);
  	static LNPacket* factory(packet_data& pdata);
    //LNPacket(packet_data dataArray, uint len);
  	//LNPacket(const LNPacket &packet);
  	LNPacket(LN_OP_CODE opc);
    //static LNPacket* factory(byte dataArray[], uint len);
  	virtual ~LNPacket();
  	virtual arduino::String toString();
  	uint static getLen(byte b);
  	uint len();
  	virtual LN_OP_CODE get_opcode();
  	static LN_OP_CODE get_opcode(byte firstByte);
  	bool valid();
  	byte getByte(uint pos);
  	//uint getaddr();
  	//void setaddr(uint addr);
  	//bool getClosed();
  	//void setClosed(bool closed);
  	//bool getActive();
  	//void setActive(bool active);
protected:
  	void setByte(uint pos, byte b);
  	void setData(byte dataArray[], uint len);
  	void setCheckSum();
  	packet_data data;
  private:
  	//byte data[LOCONET_MAX_PACKET_SIZE];
//  	uint len;
  	//byte getLen(byte b);
  	byte getLen(LN_OP_CODE opc);
  };
}
#endif
