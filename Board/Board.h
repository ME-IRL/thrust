#ifndef __BOARD_USER_H__
#define __BOARD_USER_H__

	/* Includes: */
		// TODO: Add any required includes here
		#include <LUFA/Common/Common.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_BOARD_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Board.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
			/** Indicates the board has hardware LEDs mounted if defined. */
			#define BOARD_HAS_LEDS

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

