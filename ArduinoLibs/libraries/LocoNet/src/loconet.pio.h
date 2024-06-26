// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ---------- //
// loconet_rx //
// ---------- //

#define loconet_rx_wrap_target 0
#define loconet_rx_wrap 4

static const uint16_t loconet_rx_program_instructions[] =
  {
              //     .wrap_target
      0xf827, //  0: set    x, 7            side 1
      0x2720, //  1: wait   0 pin, 0               [7]
      0x5001, //  2: in     pins, 1         side 0
      0x0442, //  3: jmp    x--, 2                 [4]
      0x8020, //  4: push   block
	      //     .wrap
    };

#if !PICO_NO_HARDWARE
static const struct pio_program loconet_rx_program =
  { .instructions = loconet_rx_program_instructions, .length = 5, .origin = -1, };

static inline pio_sm_config
loconet_rx_program_get_default_config (uint offset)
{
  pio_sm_config c = pio_get_default_sm_config ();
  sm_config_set_wrap (&c, offset + loconet_rx_wrap_target, offset + loconet_rx_wrap);
  sm_config_set_sideset (&c, 2, true, false);
  return c;
}

#endif

// ---------- //
// loconet_tx //
// ---------- //

#define loconet_tx_wrap_target 0
#define loconet_tx_wrap 4

static const uint16_t loconet_tx_program_instructions[] =
  {
              //     .wrap_target
      0xe027, //  0: set    x, 7
      0x9da0, //  1: pull   block           side 1 [5]
      0xf500, //  2: set    pins, 0         side 0 [5]
      0x6001, //  3: out    pins, 1
      0x0443, //  4: jmp    x--, 3                 [4]
	      //     .wrap
    };

#if !PICO_NO_HARDWARE
static const struct pio_program loconet_tx_program =
  { .instructions = loconet_tx_program_instructions, .length = 5, .origin = -1, };

static inline pio_sm_config
loconet_tx_program_get_default_config (uint offset)
{
  pio_sm_config c = pio_get_default_sm_config ();
  sm_config_set_wrap (&c, offset + loconet_tx_wrap_target, offset + loconet_tx_wrap);
  sm_config_set_sideset (&c, 2, true, false);
  return c;
}

#endif

