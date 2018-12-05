// ----------------------------------------------------------------------------
// PumpController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef PUMP_CONTROLLER_H
#define PUMP_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <SerialInterface.h>

#include "PumpController/Constants.h"


class PumpController : public SerialInterface
{
public:
  PumpController();
  virtual void setup();

private:
  modular_server::Property properties_[pump_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[pump_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[pump_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[pump_controller::constants::CALLBACK_COUNT_MAX];

  char request_[pump_controller::constants::REQUEST_SIZE_MAX];
  char request_key_[pump_controller::constants::KEY_BUFFER_SIZE];
  char response_[pump_controller::constants::RESPONSE_SIZE_MAX];
  char response_key_[pump_controller::constants::KEY_BUFFER_SIZE];
  char * const response_data_ = response_ + pump_controller::constants::KEY_SIZE;

  bool sendCommandGetResponse(const char command[]);
  size_t getResponseLength();
  void initializeRequestAndResponse();

  // Handlers

};

#endif
