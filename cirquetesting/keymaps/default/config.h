// Copyright 2023 Eric (@erico009)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
#define CIRQUE_PINNACLE_RELATIVE_MODE 0
#define CIRQUE_PINNACLE_DIAMETER_MM 23	
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#define POINTING_DEVICE_ROTATION_270
#define ENCODERS_PAD_A { F4, F4 }
#define ENCODERS_PAD_B { F5, F6 }
#define ENCODER_RESOLUTION 4
#define ENCODER_DEFAULT_POS 3
