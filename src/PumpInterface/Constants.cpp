// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace pump_interface
{
namespace constants
{
CONSTANT_STRING(device_name,"pump_interface");

CONSTANT_STRING(firmware_name,"PumpInterface");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=0,
  .version_patch=0,
};

CONSTANT_STRING(pressure_constant_string,"pressure");
CONSTANT_STRING(flow_constant_string,"flow");
CONSTANT_STRING(upper_pressure_limit_constant_string,"upper_pressure_limit");
CONSTANT_STRING(lower_pressure_limit_constant_string,"lower_pressure_limit");
CONSTANT_STRING(pressure_units_constant_string,"pressure_units");
CONSTANT_STRING(is_running_constant_string,"is_running");

// Pins

// Units

// Properties
modular_server::SubsetMemberType baud_subset[BAUD_SUBSET_LENGTH] =
{
  {.l=9600},
};
const long & baud_default = baud_subset[0].l;

modular_server::SubsetMemberType format_ptr_subset[FORMAT_SUBSET_LENGTH] =
{
  {.cs_ptr=&serial_interface::constants::format_8n1},
};
const ConstantString * const format_ptr_default = &serial_interface::constants::format_8n1;

modular_server::SubsetMemberType write_line_ending_ptr_subset[LINE_ENDING_SUBSET_LENGTH] =
{
  {.cs_ptr=&serial_interface::constants::line_ending_cr},
};
const ConstantString * const write_line_ending_ptr_default = &serial_interface::constants::line_ending_cr;

CONSTANT_STRING(line_ending_forward_slash,"FORWARD_SLASH");
modular_server::SubsetMemberType read_line_ending_ptr_subset[LINE_ENDING_SUBSET_LENGTH] =
{
  {.cs_ptr=&line_ending_forward_slash},
};
const ConstantString * const read_line_ending_ptr_default = &line_ending_forward_slash;

const long timeout_default = 100;

// Parameters

// Functions
CONSTANT_STRING(get_current_conditions_function_name,"getCurrentConditions");
CONSTANT_STRING(get_current_status_function_name,"getCurrentStatus");

// Callbacks
CONSTANT_STRING(clear_faults_callback_name,"clearFaults");
CONSTANT_STRING(run_pump_callback_name,"runPump");
CONSTANT_STRING(stop_pump_callback_name,"stopPump");

// Errors
CONSTANT_STRING(pump_not_communicating_error,"Pump not communicating. Check power and connections.");
CONSTANT_STRING(invalid_command_error,"Invalid command. It does not exist or it has an invalid pattern.");
}
}
