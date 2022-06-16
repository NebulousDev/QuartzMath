#pragma once

#include "Types.h"

#define QMATH_USE_FAST_SQRT_2ND_PASS 0

namespace Quartz
{
	/*====================================================
	|                QUARTZMATH UTILITY                  |
	=====================================================*/

	// Fast inverse square root
	template<typename IntType>
	inline IntType FastInvsereSquare(IntType number);

	// Fast inverse square root
	// https://en.wikipedia.org/wiki/Fast_inverse_square_root
	template<typename IntType>
	inline IntType FastInvsereSquare(IntType number)
	{
		float y		= (float)number;
		float x2	= y * 0.5f;
		uInt32 i	= *(uInt32*)&y;

		i = 0x5f3759df - (i >> 1);
		y = *(float*)&i;
		y = y * (1.5f - (x2 * y * y));

	#if QMATH_USE_FAST_SQRT_2ND_PASS
		y = y * (1.5f - (x2 * y * y));
	#endif

		return y;
	}

	// Fast inverse square root (64bit) - double
	// https://stackoverflow.com/questions/11644441/fast-inverse-square-root-on-x64
	template<>
	inline double FastInvsereSquare<double>(double number)
	{
		double y	= number;
		double x2	= y * 0.5;
		int64 i		= *(int64*)&y;

		i = 0x5fe6eb50c7b537a9 - (i >> 1);
		y = *(double*)&i;
		y = y * (1.5 - (x2 * y * y));

	#if QMATH_USE_FAST_SQRT_2ND_PASS
		y = y * (1.5 - (x2 * y * y));
	#endif

		return y;
	}

	// Fast inverse square root (64bit) - int64
	// https://stackoverflow.com/questions/11644441/fast-inverse-square-root-on-x64
	template<>
	inline int64 FastInvsereSquare<int64>(int64 number)
	{
		double y	= (double)number;
		double x2	= y * 0.5;
		uInt64 i	= *(uInt64*)&y;

		i = 0x5fe6eb50c7b537a9 - (i >> 1);
		y = *(double*)&i;
		y = y * (1.5 - (x2 * y * y));

	#if QMATH_USE_FAST_SQRT_2ND_PASS
		y = y * (1.5 - (x2 * y * y));
	#endif

		return y;
	}

	// Fast inverse square root (64bit) - uInt64
	// https://stackoverflow.com/questions/11644441/fast-inverse-square-root-on-x64
	template<>
	inline uInt64 FastInvsereSquare<uInt64>(uInt64 number)
	{
		double y = (double)number;
		double x2 = y * 0.5;
		uInt64 i = *(uInt64*)&y;

		i = 0x5fe6eb50c7b537a9 - (i >> 1);
		y = *(double*)&i;
		y = y * (1.5 - (x2 * y * y));

#if QMATH_USE_FAST_SQRT_2ND_PASS
		y = y * (1.5 - (x2 * y * y));
#endif

		return y;
	}

	inline float ToRadians(float degrees)
	{
		return degrees * (3.14159265f / 180.0f);
	}

	inline float ToDegrees(float radians)
	{
		return radians * (180.0f / 3.14159265f);
	}
}