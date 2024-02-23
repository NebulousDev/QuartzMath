#pragma once

#include "Vector.h"
#include <cmath>

namespace Quartz
{
	inline Vec2f RandomGradient2D(int64 x, int64 y)
	{
		const uInt64 w = 8 * sizeof(uInt64);
		const uInt64 s = w / 2;

		uInt64 a = x, b = y;
		a *= 3284157443;

		b ^= a << s | a >> w - s;
		b *= 1911520717;

		a ^= b << s | b >> w - s;
		a *= 2048419325;

		float random = a * (3.14159265 / ~(~0u >> 1));

		Vec2f result;
		result.x = sin(random);
		result.y = cos(random);

		return result;
	}

	inline float PerlinNoise2D(float x, float y)
	{
		int64 ix0 = (int64)x;
		int64 iy0 = (int64)y;
		int64 ix1 = (int64)x + 1;
		int64 iy1 = (int64)y + 1;

		float sx0 = x - (float)ix0;
		float sy0 = y - (float)iy0;
		float sx1 = x - (float)ix1;
		float sy1 = y - (float)iy1;

		Vec2f downLeft	= RandomGradient2D(ix0, iy0);
		Vec2f downRight = RandomGradient2D(ix1, iy0);
		Vec2f upLeft	= RandomGradient2D(ix0, iy1);
		Vec2f upRight	= RandomGradient2D(ix1, iy1);

		float dotDownLeft	= Dot(downLeft,  { sx0, sy0 });
		float dotDownRight	= Dot(downRight, { sx1, sy0 });
		float dotUpLeft		= Dot(upLeft,    { sx0, sy1 });
		float dotUpRight	= Dot(upRight,   { sx1, sy1 });

		float intrpDown = Cerp(dotDownLeft, dotDownRight, sx0);
		float intrpUp	= Cerp(dotUpLeft, dotUpRight, sx0);
		float value		= Cerp(intrpDown, intrpUp, sy0);

		return value;
	}
}