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
  //	LNPacket(packet_data dataArray, uint len);
  	//LNPacket(const LNPacket &packet);
  	LNPacket(LN_OP_CODE opc);
  	~LNPacket();
  	uint len();
  	arduino::String repr();
  	uint static getLen(byte b);
  	LN_OP_CODE get_opcode();
  	uint getaddr();
  	void setaddr(uint addr);
  	bool valid();
  	bool getClosed();
  	void setClosed(bool closed);
  	bool getActive();
  	void setActive(bool active);
  	byte getByte(uint pos);

  private:
  	//byte data[LOCONET_MAX_PACKET_SIZE];
  	packet_data data;
  	void setCheckSum();
  	//byte getLen(byte b);
  	byte getLen(LN_OP_CODE opc);
  };
}
#endif
