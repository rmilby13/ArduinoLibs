/*
 * config.h
 *
 *  Created on: Aug 8, 2023
 *      Author: rmilby
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#pragma once

#include <Arduino.h>
#include <FS.h>
#include <ArduinoJson.h>

typedef StaticJsonDocument<1024> jsondoc;

class ConfigInfo {
public:
  ConfigInfo();
  virtual ~ConfigInfo();
  arduino::String display();
  void save(File filehandle);
  virtual jsondoc load(File filehandle);
protected:
  virtual jsondoc createJsonDoc();
};
//extern ConfigInfo config; // = new ConfigInfo();

#endif /* CONFIG_H_ */
