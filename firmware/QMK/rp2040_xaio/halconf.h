#pragma once

// 1. Force Enable FIRST (Before include_next)
#define HAL_USE_USB_MSD   TRUE
#define HAL_USE_RTC       TRUE

// 2. Load Defaults
#include_next <halconf.h>

// 3. Clear & Re-Enable (Safety)
#undef HAL_USE_USB_MSD
#define HAL_USE_USB_MSD TRUE

#undef HAL_USE_COMMUNITY
#define HAL_USE_COMMUNITY TRUE