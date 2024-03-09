#pragma once

#ifndef MY_ASSERT
#include <assert.h>
#define MY_ASSERT(_EXPR)            assert(_EXPR)                               // You can override the default assert handler by editing imconfig.h
#endif

#define True                1
#define False               0

#define MULT_X  0.00052083333f  // 1 / 1920
#define MULT_Y  0.00092592592f  // 1 / 1080
