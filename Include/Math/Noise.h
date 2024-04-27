#pragma once

#include "Vector.h"
#include <cmath>

namespace Quartz
{
	inline Vec2f RandomGradient2D(uInt64 seed, int64 x, int64 y)
	{
		const int64 w = 8 * sizeof(int64);
		const int64 s = w / 2;

		int64 a = x, b = y;
		a *= 3284157443;
		b ^= a << s | a >> w - s;
		b *= 1911520717;
		a ^= b << s | b >> w - s;
		a *= 2048419325;

		float random = a * (3.14159265 / ~(~0u >> 1));

		Vec2f result;
		result.x = sinf(random);
		result.y = cosf(random);

		return result;
	}

	inline Vec2f RandomGradient2D(uInt64 seed, Vec2i pos)
	{
		const int64 w = 8 * sizeof(int64);
		const int64 s = w / 2;

		int64 a = (int64)pos.x, b = (int64)pos.y;
		a *= 3284157443;
		b ^= a << s | a >> w - s;
		b *= 1911520717;
		a ^= b << s | b >> w - s;
		a *= 2048419325;

		float random = a * (3.14159265 / ~(~0u >> 1));

		Vec2f result;
		result.x = sinf(random);
		result.y = cosf(random);

		return result;
	}

	inline float PerlinNoise2D(uInt64 seed, float x, float y)
	{
		int64 x0 = (int64)floor(x);
		int64 y0 = (int64)floor(y);
		int64 x1 = x0 + 1;
		int64 y1 = y0 + 1;

		Vec2f downLeft	= RandomGradient2D(seed, x0, y0);
		Vec2f downRight = RandomGradient2D(seed, x1, y0);
		Vec2f upLeft	= RandomGradient2D(seed, x0, y1);
		Vec2f upRight	= RandomGradient2D(seed, x1, y1);

		float dx0 = x - (float)x0;
		float dy0 = y - (float)y0;
		float dx1 = x - (float)x1;
		float dy1 = y - (float)y1;

		float dotDownLeft	= Dot(downLeft,  { dx0, dy0 });
		float dotDownRight	= Dot(downRight, { dx1, dy0 });
		float dotUpLeft		= Dot(upLeft,	 { dx0, dy1 });
		float dotUpRight	= Dot(upRight,	 { dx1, dy1 });

		float intrpDown = Cerp(dotDownLeft, dotDownRight, Fade(dx0));
		float intrpUp	= Cerp(dotUpLeft, dotUpRight, Fade(dx0));
		float value		= Cerp(intrpDown, intrpUp, Fade(dy0));

		return value;
	}

	// Inigo Quilez https://www.shadertoy.com/view/XdXBRH
	inline Vec3f PerlinNoise2DDeriv(uInt64 seed, float x, float y)
	{
		Vec2i flpos0 = Vec2i(floor(x), floor(y));
		Vec2f fractPos = Vec2f(x, y) - flpos0;

		Vec2f downLeft	= RandomGradient2D(seed, flpos0 + Vec2i(0, 0));
		Vec2f downRight = RandomGradient2D(seed, flpos0 + Vec2i(1, 0));
		Vec2f upLeft	= RandomGradient2D(seed, flpos0 + Vec2i(0, 1));
		Vec2f upRight	= RandomGradient2D(seed, flpos0 + Vec2i(1, 1));

		float dotDownLeft	= Dot(downLeft,  fractPos - Vec2i(0, 0));
		float dotDownRight	= Dot(downRight, fractPos - Vec2i(1, 0));
		float dotUpLeft		= Dot(upLeft,	 fractPos - Vec2i(0, 1));
		float dotUpRight	= Dot(upRight,	 fractPos - Vec2i(1, 1));

		Vec2f quintIntrp		= Fade(fractPos);
		Vec2f quintIntrpDeriv	= FadeDeriv(fractPos);

		float value =
			dotDownLeft + quintIntrp.x * (dotDownRight - dotDownLeft) +
			quintIntrp.y * (dotUpLeft - dotDownLeft) +
			quintIntrp.x * quintIntrp.y *
			(dotDownLeft - dotDownRight - dotUpLeft + dotUpRight);

		//Vec2f deriv = 
		//	downLeft + quintIntrp.x * (downRight - downLeft) +
		//	quintIntrp.y * (upLeft - downLeft) +
		//	quintIntrp.x * quintIntrp.y * (downLeft - downRight - upLeft + upRight) +
		//	quintIntrpDeriv * (Vec2f(quintIntrp.y, quintIntrp.x) * 
		//	(dotDownLeft - dotDownRight - dotUpLeft + dotUpRight) +
		//	Vec2f(dotDownRight, dotDownRight) - dotDownLeft);

		Vec2f deriv = quintIntrpDeriv * (Vec2f(dotDownRight - dotDownLeft, dotUpLeft - dotDownLeft) +
			Vec2f(quintIntrp.y, quintIntrp.x) * (dotDownLeft - dotDownRight - dotUpLeft + dotUpRight));

		return Vec3f(value, deriv.x, deriv.y);
	}
}