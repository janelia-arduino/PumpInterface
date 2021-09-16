// ----------------------------------------------------------------------------
// PumpInterface.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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
  modular_server::Pin & btn_a_pin = modular_server_.pin(modular_device_base::constants::btn_a_pin_name);

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
  modular_server::Parameter & flow_rate_parameter = modular_server_.createParameter(constants::flow_rate_parameter_name);
  flow_rate_parameter.setRange(constants::flow_rate_min,constants::flow_rate_max);

  // Functions
  modular_server::Function & get_current_conditions_function = modular_server_.createFunction(constants::get_current_conditions_function_name);
  get_current_conditions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PumpInterface::getCurrentConditionsHandler));
  get_current_conditions_function.setResultTypeObject();

  modular_server::Function & get_current_status_function = modular_server_.createFunction(constants::get_current_status_function_name);
  get_current_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PumpInterface::getCurrentStatusHandler));
  get_current_status_function.setResultTypeObject();

  modular_server::Function & pump_is_running_function = modular_server_.createFunction(constants::pump_is_running_function_name);
  pump_is_running_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PumpInterface::pumpIsRunningHandler));
  pump_is_running_function.setResultTypeBool();

  modular_server::Function & set_flow_rate_function = modular_server_.createFunction(constants::set_flow_rate_function_name);
  set_flow_rate_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PumpInterface::setFlowRateHandler));
  set_flow_rate_function.addParameter(flow_rate_parameter);

  // Callbacks
  modular_server::Callback & clear_faults_callback = modular_server_.createCallback(constants::clear_faults_callback_name);
  clear_faults_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&PumpInterface::clearFaultsHandler));

  modular_server::Callback & run_pump_callback = modular_server_.createCallback(constants::run_pump_callback_name);
  run_pump_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&PumpInterface::runPumpHandler));

  modular_server::Callback & stop_pump_callback = modular_server_.createCallback(constants::stop_pump_callback_name);
  stop_pump_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&PumpInterface::stopPumpHandler));
  stop_pump_callback.attachTo(btn_a_pin,modular_server::constants::pin_mode_interrupt_falling);

}

bool PumpInterface::communicating()
{
  const char command[] = "CC";
  return sendCommandGetResponse(command);
}

bool PumpInterface::getCurrentConditions(int & pressure,
  float & flow_rate)
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
      flow_rate = atof(ch_ptr);
    }
  }
  return success;
}

bool PumpInterface::clearFaults()
{
  const char command[] = "CF";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool PumpInterface::getCurrentStatus(float & flow_rate,
  int & upper_pressure_limit,
  int & lower_pressure_limit,
  char * pressure_units,
  bool & pump_is_running)
{
  char * current_status_string = response_data_;
  const char command[] = "CS";
  bool success = sendCommandGetResponse(command);

  if (success)
  {
    char * ch_ptr;
    ch_ptr = strtok(current_status_string,",");
    if (ch_ptr != NULL)
    {
      flow_rate = atof(ch_ptr);
      ch_ptr = strtok(NULL, ",");
    }
    if (ch_ptr != NULL)
    {
      upper_pressure_limit = atoi(ch_ptr);
      ch_ptr = strtok(NULL, ",");
    }
    if (ch_ptr != NULL)
    {
      lower_pressure_limit = atoi(ch_ptr);
      ch_ptr = strtok(NULL, ",");
    }
    if (ch_ptr != NULL)
    {
      strncpy(pressure_units,ch_ptr,constants::PRESSURE_UNITS_SIZE);
      pressure_units[constants::PRESSURE_UNITS_SIZE] = '\0';
      ch_ptr = strtok(NULL, ",");
    }
    if (ch_ptr != NULL)
    {
      ch_ptr = strtok(NULL, ",");
    }
    if (ch_ptr != NULL)
    {
      pump_is_running = atoi(ch_ptr);
    }
  }
  return success;
}

bool PumpInterface::runPump()
{
  const char command[] = "RU";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool PumpInterface::stopPump()
{
  const char command[] = "ST";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool PumpInterface::pumpIsRunning(bool & pump_is_running)
{
  float flow_rate;
  int upper_pressure_limit;
  int lower_pressure_limit;
  char pressure_units[constants::PRESSURE_UNITS_BUFFER_SIZE];
  pressure_units[0] = '\0';
  bool success = getCurrentStatus(flow_rate,
    upper_pressure_limit,
    lower_pressure_limit,
    pressure_units,
    pump_is_running);
  return success;
}

bool PumpInterface::setFlowRate(float flow_rate)
{
  size_t flow_rate_scaled = flow_rate * constants::flow_rate_scale_factor;
  char flow_rate_scaled_string[constants::FLOW_RATE_SCALED_BUFFER_SIZE];
  snprintf(flow_rate_scaled_string,constants::FLOW_RATE_SCALED_BUFFER_SIZE,"%05d",flow_rate_scaled);

  char command[constants::FLOW_RATE_COMMAND_BUFFER_SIZE];
  strcpy(command,"FI");
  strcat(command,flow_rate_scaled_string);

  bool success = sendCommandGetResponse(command);
  char * flow_rate_response_string = response_data_;

  if (success)
  {
    char * ch_ptr;
    ch_ptr = strtok(flow_rate_response_string,":");
    if (ch_ptr != NULL)
    {
      ch_ptr = strtok(NULL, "");
    }
    if (ch_ptr != NULL)
    {
      if (strcmp(ch_ptr,flow_rate_scaled_string) != 0)
      {
        success = false;
      }
    }
  }
  return success;
}

// Protected

char PumpInterface::lineEndingToChar(const ConstantString * line_ending_ptr)
{
  char line_ending_char = SerialInterface::lineEndingToChar(line_ending_ptr);
  if (line_ending_ptr == &constants::line_ending_forward_slash)
  {
    line_ending_char = '/';
  }
  return line_ending_char;
}

// Private

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
// ArduinoJson::JsonArray
// ArduinoJson::JsonObject
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
  float flow_rate;
  bool success = getCurrentConditions(pressure,
    flow_rate);

  if (success)
  {
    modular_server_.response().writeResultKey();

    modular_server_.response().beginObject();

    modular_server_.response().write(constants::pressure_constant_string,pressure);
    modular_server_.response().write(constants::flow_rate_constant_string,flow_rate);

    modular_server_.response().endObject();
  }
  else
  {
    modular_server_.response().returnError(constants::invalid_command_error);
  }
}

void PumpInterface::clearFaultsHandler(modular_server::Pin * pin_ptr)
{
  clearFaults();
}

void PumpInterface::getCurrentStatusHandler()
{
  if (!communicating())
  {
    modular_server_.response().returnError(constants::pump_not_communicating_error);
    return;
  }

  float flow_rate;
  int upper_pressure_limit;
  int lower_pressure_limit;
  char pressure_units[constants::PRESSURE_UNITS_BUFFER_SIZE];
  pressure_units[0] = '\0';
  bool pump_is_running;
  bool success = getCurrentStatus(flow_rate,
    upper_pressure_limit,
    lower_pressure_limit,
    pressure_units,
    pump_is_running);

  if (success)
  {
    modular_server_.response().writeResultKey();

    modular_server_.response().beginObject();

    modular_server_.response().write(constants::flow_rate_constant_string,flow_rate);
    modular_server_.response().write(constants::upper_pressure_limit_constant_string,upper_pressure_limit);
    modular_server_.response().write(constants::lower_pressure_limit_constant_string,lower_pressure_limit);
    modular_server_.response().write(constants::pressure_units_constant_string,pressure_units);
    modular_server_.response().write(constants::pump_is_running_constant_string,pump_is_running);

    modular_server_.response().endObject();
  }
  else
  {
    modular_server_.response().returnError(constants::invalid_command_error);
  }
}

void PumpInterface::runPumpHandler(modular_server::Pin * pin_ptr)
{
  runPump();
}

void PumpInterface::stopPumpHandler(modular_server::Pin * pin_ptr)
{
  stopPump();
}

void PumpInterface::pumpIsRunningHandler()
{
  if (!communicating())
  {
    modular_server_.response().returnError(constants::pump_not_communicating_error);
    return;
  }

  bool pump_is_running;
  bool success = pumpIsRunning(pump_is_running);
  if (!success)
  {
    modular_server_.response().returnError(constants::invalid_command_error);
  }
  modular_server_.response().returnResult(pump_is_running);
}

void PumpInterface::setFlowRateHandler()
{
  if (!communicating())
  {
    modular_server_.response().returnError(constants::pump_not_communicating_error);
    return;
  }

  double flow_rate;
  modular_server_.parameter(constants::flow_rate_parameter_name).getValue(flow_rate);
  bool success = setFlowRate(flow_rate);
  if (!success)
  {
    modular_server_.response().returnError(constants::invalid_command_error);
  }
}
