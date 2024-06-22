/*
 * TCPLoconet.cpp
 *
 *  Created on: Aug 11, 2023
 *      Author: rmilb
 */
#include "TCPLoconet.h"

#include <Arduino.h>
#include <WiFi.h>

TCPLocoNet::TCPLocoNet (arduino::String server, int port) {
  this->server = server;
  this->port = port;
}

TCPLocoNet::TCPLocoNet (arduino::String server) {
  this->server = server;
  this->port = 1234;
}

TCPLocoNet::TCPLocoNet () {
  this->server = "";
  this->port = 1234;
}

int TCPLocoNet::available () {
  return client.available ();
}

int TCPLocoNet::peek () {
  return client.peek ();
}

int TCPLocoNet::read () {
  return client.read ();
}

size_t TCPLocoNet::write (uint8_t i) {
  return client.write (i);
}

size_t TCPLocoNet::write (const uint8_t *buffer, size_t size) {
  return client.write (buffer, size);
}

int TCPLocoNet::availableForWrite () {
  return client.availableForWrite ();
}
void TCPLocoNet::flush () {
  client.flush ();
}

void TCPLocoNet::connect () {
  if (WiFi.status () == WL_CONNECTED) {
    if (!client.connect (server.c_str(), port)) {
      IPAddress ip((arduino::IPAddress)WiFi.localIP ());
      IPAddress subnetmask = (arduino::IPAddress)WiFi.subnetMask ();
      IPAddress hostmask = (arduino::IPAddress)WiFi.subnetMask ();
      IPAddress gateway = (arduino::IPAddress)WiFi.gatewayIP ();
      IPAddress network = (arduino::IPAddress)WiFi.localIP ();
      IPAddress broadcast = (arduino::IPAddress)WiFi.localIP ();
      network[0] = ip[0] & subnetmask[0];
      network[1] = ip[1] & subnetmask[1];
      network[2] = ip[2] & subnetmask[2];
      network[3] = ip[3] & subnetmask[3];
      hostmask[0] = 0xFF ^ subnetmask[0];
      hostmask[1] = 0xFF ^ subnetmask[1];
      hostmask[2] = 0xFF ^ subnetmask[2];
      hostmask[3] = 0xFF ^ subnetmask[3];
      broadcast[0] = (ip[0] & subnetmask[0]) | hostmask[0];
      broadcast[1] = (ip[1] & subnetmask[1]) | hostmask[1];
      broadcast[2] = (ip[2] & subnetmask[2]) | hostmask[2];
      broadcast[3] = (ip[3] & subnetmask[3]) | hostmask[3];
      Serial.printf (
	  "Connected to Wifi\nIP:\t\t%s\nSubnet:\t%s\nGateway:\t%s\nNetwork:\t%s\nBroadcast:\t%s\nAttempting to connect to Loconet over TCP/IP\n",
	  (ip.toString ()).c_str (), subnetmask.toString ().c_str (), gateway.toString ().c_str (),
	  network.toString ().c_str (), broadcast.toString ().c_str ());
      IPAddress server = network;
      bool foundserver = false;
      //WiFiClient client;
      while ((server[0] <= broadcast[0]) && (server[1] <= broadcast[1]) && (server[2] <= broadcast[2])
	  && (server[3] <= broadcast[3]) && !foundserver) {
	Serial.printf ("Attempting server:\t%s\n", server.toString ().c_str ());
	if (client.connect (server, 1234)) {
	  foundserver = true;
	} else {
	  if (server[3] == 255) {
	    if (server[2] == 255) {
	      if (server[1] == 255) {
		server[0]++;
	      }
	      server[1]++;
	    }
	    server[2]++;
	  }
	  server[3]++;
	}
      }
      Serial.printf ("server:\t%s\n", server.toString ().c_str ());
    }
  }
}

bool TCPLocoNet::connected(){
  return client.connected();
}
