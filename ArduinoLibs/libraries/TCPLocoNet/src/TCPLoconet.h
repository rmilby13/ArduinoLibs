/*
 * TCPLoconet.h
 *
 *  Created on: Aug 11, 2023
 *      Author: rmilb
 */

#ifndef TCPLOCONET_H_
#define TCPLOCONET_H_
#include <arduino.h>
#include <WiFi.h>

class TCPLocoNet : public arduino::Stream  { // @suppress("Class has a virtual method and non-virtual destructor")
public:
  TCPLocoNet ();
  TCPLocoNet (arduino::String server);
  TCPLocoNet (arduino::String server, int port);
  void connect ();
  bool connected();
  int available ();
  int read ();
  int peek ();
  size_t write(uint8_t);
  size_t write(const uint8_t *buffer, size_t size);
  int availableForWrite();
  void flush();
private:
  arduino::String server;
  unsigned short int port;
  WiFiClient client;
};
extern TCPLocoNet tcploco;
#endif /* TCPLOCONET_H_ */
