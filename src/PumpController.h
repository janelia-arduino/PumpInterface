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

  // Handlers

};

#endif
