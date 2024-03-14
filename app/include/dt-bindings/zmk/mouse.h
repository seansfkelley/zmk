/*
 * Copyright (c) 2023 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include <zephyr/dt-bindings/dt-util.h>

/* Mouse press behavior */
/* Left click */
#define MB1 BIT(0)
#define LCLK (MB1)

/* Right click */
#define MB2 BIT(1)
#define RCLK (MB2)

/* Middle click */
#define MB3 BIT(2)
#define MCLK (MB3)

#define MB4 BIT(3)
#define MB5 BIT(4)

#ifndef ZMK_MOUSE_DEFAULT_MOVE_VAL
#define ZMK_MOUSE_DEFAULT_MOVE_VAL 600
#endif

#ifndef ZMK_MOUSE_DEFAULT_SCRL_VAL
#define ZMK_MOUSE_DEFAULT_SCRL_VAL 16
#endif

/* Mouse move behavior */
#define MOVE_Y(vert) ((vert)&0xFFF0)
#define MOVE_Y_DECODE(encoded) (int16_t)((encoded)&0x0000FFF0)
#define MOVE_X(hor) (((hor)&0xFFF0) << 16)
#define MOVE_X_DECODE(encoded) (int16_t)(((encoded)&0xFFF00000) >> 16)
// Note that we pack these values into the last 4 bits of what used to be the least significant part
// of the already-packed-bit movement numbers. This means a few things:
// - the values here cannot go above 16, so choose the `base-multiplier` property accordingly
// - movement/scroll values must be multiples of 16 (and remainders are truncated)
//
// Note also that these multipliers can only be applied per-behavior, so if it's desired to have one
// key set the speed for e.g. scroll and move, a wrapper macro must be used to do both.
#define MOVE_MULT(factor) ((factor)&0xF)
#define MOVE_MULT_DECODE(encoded) (uint8_t)((encoded)&0x0000000F)
#define MOVE_DIV(factor) (((factor)&0xF) << 16)
#define MOVE_DIV_DECODE(encoded) (uint8_t)(((encoded)&0x000F0000) >> 16)

#define MOVE(hor, vert) (MOVE_X(hor) + MOVE_Y(vert))

#define MOVE_UP MOVE_Y(-ZMK_MOUSE_DEFAULT_MOVE_VAL)
#define MOVE_DOWN MOVE_Y(ZMK_MOUSE_DEFAULT_MOVE_VAL)
#define MOVE_LEFT MOVE_X(-ZMK_MOUSE_DEFAULT_MOVE_VAL)
#define MOVE_RIGHT MOVE_X(ZMK_MOUSE_DEFAULT_MOVE_VAL)

#define SCRL_UP MOVE_Y(ZMK_MOUSE_DEFAULT_SCRL_VAL)
#define SCRL_DOWN MOVE_Y(-ZMK_MOUSE_DEFAULT_SCRL_VAL)
#define SCRL_LEFT MOVE_X(-ZMK_MOUSE_DEFAULT_SCRL_VAL)
#define SCRL_RIGHT MOVE_X(ZMK_MOUSE_DEFAULT_SCRL_VAL)
