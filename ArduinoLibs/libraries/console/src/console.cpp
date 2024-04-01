/*
 * console.cpp
 *
 *  Created on: Aug 8, 2023
 *      Author: rmilb
 */

#include "console.h"
#include <Arduino.h>

#ifndef SKIPMUTEX
#define LOCK(...) mutex_enter_blocking (__VA_ARGS__)
#define UNLOCK(...) mutex_exit (__VA_ARGS__)
#else
#define LOCK(...)
#define UNLOCK(...)
#endif

void Console::initConsole (arduino::Stream *stream) {
  this->cmdBuffer = "";
  this->pendingCommands.clear ();
//  mutex_init (&this->bufferLock);
  mutex_init (&this->commandLock);
  this->consoleStreams.push_back (stream);
}

Console::Console () {
  this->initConsole (&Serial);
}

Console::Console (arduino::Stream *stream) {
  this->initConsole (stream);
}

void Console::addStream (arduino::Stream *stream) {
  this->consoleStreams.push_back (stream);
}

void Console::check () {
  for (auto const &stream : consoleStreams) {
//    if (stream->available ()) {
//      LOCK(&this->bufferLock);
    while (stream->available ()) {
      char c = (char) stream->read ();
      if ((int (c) == 10) || (int (c) == 13)) {
	if (this->cmdBuffer != String ("")) {
	  //Serial.printf("cmdbuffer = %s\n", this->cmdBuffer.c_str());
	  ConsoleCommand cmd (this->cmdBuffer);
	  LOCK(&this->commandLock);
	  this->pendingCommands.push_back (cmd);
	  UNLOCK(&this->commandLock);
	  this->cmdBuffer = "";
	}
      } else {
	this->cmdBuffer += c;
      }
    }
//      UNLOCK(&this->bufferLock);
  }
//  }
}

ConsoleCommand::ConsoleCommand (arduino::String cmdBuffer) {
  arduino::String cmd = cmdBuffer;
  cmd.trim ();
  while (cmd.length () > 0) {
    this->args.push_back (cmd.substring (0, cmd.indexOf (" ")));
    cmd = cmd.substring (cmd.indexOf (" "));
    cmd.trim ();
  }
}
arduino::String ConsoleCommand::command () {
  return this->args.front ();
}

int ConsoleCommand::argCount () {
  return this->args.size () - 1;
}

arduino::String ConsoleCommand::arg (unsigned int pos) {
  unsigned int p = 0;
  arduino::String ret = "";
  for (auto const &arg : this->args) {
    if (p == pos) {
      ret = arg;
    }
    p++;
  }
  return ret;
}

bool Console::cmdAvailable () {
  /*  if (!this->pendingCommands.empty ()) {
   Serial.printf ("Console commands available %d\n", this->pendingCommands.size ());
   }*/
  return !this->pendingCommands.empty ();
}
ConsoleCommand Console::getCommand () {
  LOCK(&this->commandLock);
  ConsoleCommand cmd = this->pendingCommands.front ();
  this->pendingCommands.pop_back ();
  UNLOCK(&this->commandLock);
  return cmd;
}
