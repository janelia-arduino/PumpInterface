// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace pump_interface
{
namespace constants
{
// Pins

// Units

// Properties
const long bauds_default[serial_interface::constants::SERIAL_STREAM_COUNT] =
{
  baud_default,
};

const ConstantString * const formats_default[serial_interface::constants::SERIAL_STREAM_COUNT] =
{
  format_ptr_default,
};

const ConstantString * const write_line_endings_default[serial_interface::constants::SERIAL_STREAM_COUNT] =
{
  write_line_ending_ptr_default,
};

const ConstantString * const read_line_endings_default[serial_interface::constants::SERIAL_STREAM_COUNT] =
{
  read_line_ending_ptr_default,
};

const long timeouts_default[serial_interface::constants::SERIAL_STREAM_COUNT] =
{
  timeout_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
