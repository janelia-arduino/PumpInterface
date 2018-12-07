// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef PUMP_INTERFACE_CONSTANTS_H
#define PUMP_INTERFACE_CONSTANTS_H
#include <ConstantVariable.h>
#include <SerialInterface.h>


namespace pump_interface
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=2};
enum{CALLBACK_COUNT_MAX=3};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

enum{REQUEST_SIZE_MAX=20};
enum{RESPONSE_SIZE_MAX=3000};
enum{RESPONSE_STATUS_SIZE=2};
enum{RESPONSE_STATUS_BUFFER_SIZE=4};
enum{PRESSURE_UNITS_SIZE=3};
enum{PRESSURE_UNITS_BUFFER_SIZE=4};

extern ConstantString pressure_constant_string;
extern ConstantString flow_constant_string;
extern ConstantString upper_pressure_limit_constant_string;
extern ConstantString lower_pressure_limit_constant_string;
extern ConstantString pressure_units_constant_string;
extern ConstantString is_running_constant_string;

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
enum{BAUD_SUBSET_LENGTH=1};
extern modular_server::SubsetMemberType baud_subset[BAUD_SUBSET_LENGTH];
extern const long & baud_default;

enum{FORMAT_SUBSET_LENGTH=1};
extern modular_server::SubsetMemberType format_ptr_subset[FORMAT_SUBSET_LENGTH];
extern const ConstantString * const format_ptr_default;

enum{LINE_ENDING_SUBSET_LENGTH=1};

extern modular_server::SubsetMemberType write_line_ending_ptr_subset[LINE_ENDING_SUBSET_LENGTH];
extern const ConstantString * const write_line_ending_ptr_default;

extern ConstantString line_ending_forward_slash;
extern modular_server::SubsetMemberType read_line_ending_ptr_subset[LINE_ENDING_SUBSET_LENGTH];
extern const ConstantString * const read_line_ending_ptr_default;

extern const long timeout_default;

// Parameters

// Functions
extern ConstantString get_current_conditions_function_name;
extern ConstantString get_current_status_function_name;

// Callbacks
extern ConstantString clear_faults_callback_name;
extern ConstantString run_pump_callback_name;
extern ConstantString stop_pump_callback_name;

// Errors
extern ConstantString pump_not_communicating_error;
extern ConstantString invalid_command_error;
}
}
#include "5x3.h"
#include "3x2.h"
#endif
