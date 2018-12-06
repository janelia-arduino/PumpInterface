// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef PUMP_INTERFACE_3X2_CONSTANTS_H
#define PUMP_INTERFACE_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace pump_interface
{
namespace constants
{
// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long bauds_default[serial_interface::constants::SERIAL_STREAM_COUNT];

extern const ConstantString * const formats_default[serial_interface::constants::SERIAL_STREAM_COUNT];

extern const ConstantString * const write_line_endings_default[serial_interface::constants::SERIAL_STREAM_COUNT];

extern const ConstantString * const read_line_endings_default[serial_interface::constants::SERIAL_STREAM_COUNT];

extern const long timeouts_default[serial_interface::constants::SERIAL_STREAM_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
