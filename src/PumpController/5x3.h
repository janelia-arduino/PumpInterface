// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef PUMP_CONTROLLER_5X3_CONSTANTS_H
#define PUMP_CONTROLLER_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__MK64FX512__)

namespace pump_controller
{
namespace constants
{
// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long bauds_default[serial_interface::constants::SERIAL_STREAM_COUNT];

extern const ConstantString * const formats_default[serial_interface::constants::SERIAL_STREAM_COUNT];

extern const ConstantString * const line_endings_default[serial_interface::constants::SERIAL_STREAM_COUNT];

extern const long timeouts_default[serial_interface::constants::SERIAL_STREAM_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
