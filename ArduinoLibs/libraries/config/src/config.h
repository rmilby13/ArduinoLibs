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

typedef JsonDocument jsondoc;

class ConfigInfo {
public:
  ConfigInfo();
  virtual ~ConfigInfo();
  arduino::String display();
  void saveJson(File filehandle);
  void loadJson(File filehandle);
  void loadJson(arduino::String jsonString);
protected:
  virtual jsondoc createJsonDoc();
  virtual void loadJsonDoc(jsondoc configjsondoc) = 0;
};

#endif /* CONFIG_H_ */
