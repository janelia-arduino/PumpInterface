// ----------------------------------------------------------------------------
// PumpController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../PumpController.h"


using namespace pump_controller;

PumpController::PumpController()
{
}

void PumpController::setup()
{
  // Parent Setup
  SerialInterface::setup();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & bauds_property = modular_server_.property(serial_interface::constants::bauds_property_name);
  bauds_property.setDefaultValue(constants::bauds_default);
  bauds_property.setSubset(constants::baud_subset);

  modular_server::Property & formats_property = modular_server_.property(serial_interface::constants::formats_property_name);
  formats_property.setDefaultValue(constants::formats_default);
  formats_property.setSubset(constants::format_ptr_subset);

  modular_server::Property & line_endings_property = modular_server_.property(serial_interface::constants::line_endings_property_name);
  line_endings_property.setDefaultValue(constants::line_endings_default);
  line_endings_property.setSubset(constants::line_ending_ptr_subset);

  modular_server::Property & timeouts_property = modular_server_.property(serial_interface::constants::timeouts_property_name);
  timeouts_property.setDefaultValue(constants::timeouts_default);

  // Parameters

  // Functions

  // Callbacks
}

bool UltravioletDetectorInterface::sendCommandGetResponse(const char command[])
{
  initializeRequestAndResponse();
  strcat(request_,constants::line_beginning);
  strcat(request_,command);
  writeRead(request_,response_,constants::RESPONSE_SIZE_MAX);
  strncpy(request_key_,command,constants::KEY_SIZE);
  strncpy(response_key_,response_,constants::KEY_SIZE);
  // Serial << "command = " << command << "\n";
  // Serial << "request_ = " << request_ << "\n";
  // Serial << "request_key_ = " << request_key_ << "\n";
  // Serial << "response_ = " << response_ << "\n";
  // Serial << "response_key_ = " << response_key_ << "\n";
  // Serial << "response_data_ = " << response_data_ << "\n";
  bool success = false;
  error_ptr_ = &constants::no_error;
  if (strcmp("???",response_key_) == 0)
  {
    error_ptr_ = &constants::invalid_command_error;
  }
  else if (strcmp(request_key_,response_key_) != 0)
  {
    error_ptr_ = &constants::not_communicating_error;
  }
  else if (strcmp("ERR2",response_data_) == 0)
  {
    error_ptr_ = &constants::invalid_parameter_error;
  }
  else if (strcmp("ERR4",response_data_) == 0)
  {
    error_ptr_ = &constants::invalid_mode_error;
  }
  else if (strcmp("ERR5",response_data_) == 0)
  {
    error_ptr_ = &constants::operation_error;
  }
  else
  {
    success = true;
  }
  return success;
}

size_t UltravioletDetectorInterface::getResponseLength()
{
  return strlen(response_);
}

void UltravioletDetectorInterface::initializeRequestAndResponse()
{
  request_[0] = '\0';
  request_key_[0] = '\0';
  response_[0] = '\0';
  response_key_[0] = '\0';
  response_data_[0] = '\0';
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type
