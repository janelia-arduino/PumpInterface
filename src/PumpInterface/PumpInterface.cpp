// ----------------------------------------------------------------------------
// PumpInterface.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../PumpInterface.h"


using namespace pump_interface;

PumpInterface::PumpInterface()
{
}

void PumpInterface::setup()
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

  modular_server::Property & write_line_endings_property = modular_server_.property(serial_interface::constants::write_line_endings_property_name);
  write_line_endings_property.setDefaultValue(constants::write_line_endings_default);
  write_line_endings_property.setSubset(constants::write_line_ending_ptr_subset);

  modular_server::Property & read_line_endings_property = modular_server_.property(serial_interface::constants::read_line_endings_property_name);
  read_line_endings_property.setDefaultValue(constants::read_line_endings_default);
  read_line_endings_property.setSubset(constants::read_line_ending_ptr_subset);

  modular_server::Property & timeouts_property = modular_server_.property(serial_interface::constants::timeouts_property_name);
  timeouts_property.setDefaultValue(constants::timeouts_default);

  // Parameters

  // Functions
  modular_server::Function & get_current_conditions_function = modular_server_.createFunction(constants::get_current_conditions_function_name);
  get_current_conditions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PumpInterface::getCurrentConditionsHandler));
  get_current_conditions_function.setResultTypeObject();

  // Callbacks
}

bool PumpInterface::communicating()
{
  const char command[] = "CC";
  return sendCommandGetResponse(command);
}

bool PumpInterface::getCurrentConditions(int & pressure,
  float & flow)
{
  char * current_conditions_string = response_data_;
  const char command[] = "CC";
  bool success = sendCommandGetResponse(command);

  if (success)
  {
    char * ch_ptr;
    ch_ptr = strtok(current_conditions_string,",");
    if (ch_ptr != NULL)
    {
      pressure = atoi(ch_ptr);
      ch_ptr = strtok(NULL, ",");
    }
    if (ch_ptr != NULL)
    {
      flow = atof(ch_ptr);
    }
  }
  return success;
}

char PumpInterface::lineEndingToChar(const ConstantString * line_ending_ptr)
{
  char line_ending_char = SerialInterface::lineEndingToChar(line_ending_ptr);
  if (line_ending_ptr == &constants::line_ending_forward_slash)
  {
    line_ending_char = '/';
  }
  return line_ending_char;
}

bool PumpInterface::sendCommandGetResponse(const char command[])
{
  initializeRequestAndResponse();
  strcat(request_,command);
  writeRead(request_,response_,constants::RESPONSE_SIZE_MAX);
  strncpy(response_status_,response_,constants::RESPONSE_STATUS_SIZE);
  // Serial << "command = " << command << "\n";
  // Serial << "request_ = " << request_ << "\n";
  // Serial << "response_ = " << response_ << "\n";
  // Serial << "response_status_ = " << response_status_ << "\n";
  // Serial << "response_data_ = " << response_data_ << "\n";
  bool success = false;
  if (strcmp("OK",response_status_) == 0)
  {
    success = true;
  }
  else if (strcmp("Er",response_status_) == 0)
  {
    write("#"); // clears any characters in the pump command buffer
  }
  return success;
}

size_t PumpInterface::getResponseLength()
{
  return strlen(response_);
}

void PumpInterface::initializeRequestAndResponse()
{
  request_[0] = '\0';
  response_[0] = '\0';
  response_status_[0] = '\0';
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

void PumpInterface::getCurrentConditionsHandler()
{
  if (!communicating())
  {
    modular_server_.response().returnError(constants::pump_not_communicating_error);
    return;
  }

  int pressure;
  float flow;
  bool success = getCurrentConditions(pressure,flow);

  if (success)
  {
    modular_server_.response().writeResultKey();

    modular_server_.response().beginObject();

    modular_server_.response().write(constants::pressure_constant_string,pressure);
    modular_server_.response().write(constants::flow_constant_string,flow);

    modular_server_.response().endObject();
  }
  else
  {
    modular_server_.response().returnError(constants::invalid_command_error);
  }
}
