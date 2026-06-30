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

void ConfigInfo::saveJson (File filehandle) {
  TRACE("Starting ConfigInfo::save");
  serializeJson (this->createJsonDoc (), filehandle);
}

void ConfigInfo::loadJson (File filehandle) {
  TRACE("Starting ConfigInfo::load");
  jsondoc doc;
  deserializeJson (doc, filehandle);
  this->loadJsonDoc(doc);
}

void ConfigInfo::loadJson (arduino::String jsonString) {
  DEBUG("Starting ConfigInfo::load");
  jsondoc doc;
  deserializeJson (doc, jsonString);
  DEBUG("Configuring application");
  this->loadJsonDoc(doc);
}
