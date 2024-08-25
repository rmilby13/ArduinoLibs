/*
 * console.h
 *
 *  Created on: Aug 8, 2023
 *      Author: rmilb
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_
#pragma once

#include <Arduino.h>
#include <Stream.h>
#include <list>
//g#include "Stream.h"

typedef std::list<arduino::String> argList;
class ConsoleCommand {
public:
  ConsoleCommand(arduino::String cmdBuffer);
  arduino::String command();
  int argCount();
  arduino::String arg(unsigned int pos);
  arduino::String fullLine();
private:
  argList args;
};

typedef std::list<ConsoleCommand> pendingCommandList;
typedef std::list<arduino::Stream*> consoleStreamList;

class Console {
public:
  Console();
  Console(arduino::Stream *stream);
  void addStream(arduino::Stream *stream);
  void check();
  bool cmdAvailable();
  ConsoleCommand getCommand();
private:
  void initConsole(arduino::Stream *stream);
  arduino::String cmdBuffer;
  pendingCommandList pendingCommands;
//  mutex bufferLock;
  mutex commandLock;
  //arduino::Stream *consoleStream;
  consoleStreamList consoleStreams;
};
#endif /* CONSOLE_H_ */
