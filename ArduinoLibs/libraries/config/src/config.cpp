/*
 * config.cpp
 *
 *  Created on: Aug 8, 2023
 *      Author: rmilb
 */

#include "config.h"
//#define DEBUGCONFIG 1
#ifdef TRACECONFIG
#define DEBUGCONFIG 1
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__) ; Serial.println()
#else
#define TRACE(...)
#endif
#ifdef DEBUGCONFIG
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__) ; Serial.println()
#else
#define DEBUG(...)
#endif
ConfigInfo::ConfigInfo () {
  TRACE("Creating configuration");
}

ConfigInfo::~ConfigInfo() {
  TRACE("Destroying configuration");
}

arduino::String ConfigInfo::display () {
  TRACE("Starting ConfigInfo::display\n");
  arduino::String ret;
  serializeJsonPretty (this->createJsonDoc (), ret);
  TRACE("Finished ConfigInfo::display\n");
  return ret;
}

jsondoc ConfigInfo::createJsonDoc () {
  TRACE("Starting ConfigInfo::createJsonDoc");
  jsondoc doc;
  return doc;
}

void ConfigInfo::save (File filehandle) {
  TRACE("Starting ConfigInfo::save");
  serializeJson (this->createJsonDoc (), filehandle);
}

jsondoc ConfigInfo::load (File filehandle) {
  TRACE("Starting ConfigInfo::load");
  jsondoc doc;
  deserializeJson (doc, filehandle);
  return doc;
}
