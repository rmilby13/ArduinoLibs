/*
 * config.cpp
 *
 *  Created on: Aug 8, 2023
 *      Author: rmilb
 */

#include "config.h"

ConfigInfo::ConfigInfo () {
  Serial.printf("%s:%d\n",__FILE__,__LINE__);
}

ConfigInfo::~ConfigInfo() {
  Serial.printf("%s:%d\n",__FILE__,__LINE__);
}

arduino::String ConfigInfo::display () {
  arduino::String ret;
  serializeJsonPretty (this->createJsonDoc (), ret);
  return ret;
}

jsondoc ConfigInfo::createJsonDoc () {
  jsondoc doc;
  //Serial.printf("%s:%d\n",__FILE__,__LINE__);
  return doc;
}

void ConfigInfo::save (File filehandle) {
  serializeJson (this->createJsonDoc (), filehandle);
}

jsondoc ConfigInfo::load (File filehandle) {
  jsondoc doc;
  deserializeJson (doc, filehandle);
  return doc;
}
