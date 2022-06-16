#pragma once

#include "Types.h"
#include "Point.h"

namespace Quartz
{
	/*====================================================
	|                 QUARTZMATH BOUNDS2                 |
	=====================================================*/

	template<typename IntType>
	struct Bounds2
	{
		Point2<IntType> start;
		Point2<IntType> end;

		constexpr Bounds2() {};

		constexpr Bounds2(IntType x, IntType y, IntType width, IntType height)
			: start(x, y), end(x + width, y + height) { }

		constexpr Bounds2(const Point2<IntType>& point1, const Point2<IntType>& point2)
			: start(Min(point1, point2)), end(Max(point1, point2)) { }

		constexpr Bounds2(const Bounds2& bounds2)
			: start(bounds2.start), end(bounds2.end) { }

		constexpr Bounds2& Extend(const Point2<IntType>& point)
		{
			start = Min(start, point);
			end = Max(end, point);
			return *this;
		}

		constexpr Bounds2 Extended(const Point2<IntType>& point) const
		{
			Bounds2 result;
			result.start = Min(start, point);
			result.end = Max(end, point);
			return result;
		}

		constexpr Bounds2& Translate(const Vector2<IntType>& vec2)
		{
			start += vec2;
			end += vec2;
			return *this;
		}

		constexpr Bounds2 Translated(const Vector2<IntType>& vec2) const
		{
			Bounds2 result;
			result.x = start + vec2;
			result.y = end + vec2;
			return result;
		}
		
		constexpr Point2<IntType> TopLeft() const
		{
			return Point2<IntType>(start.x, end.y);
		}

		constexpr Point2<IntType> TopRight() const
		{
			return end;
		}

		constexpr Point2<IntType> BottomLeft() const
		{
			return start;
		}

		constexpr Point2<IntType> BottomRight() const
		{
			return Point2<IntType>(start.y, end.x);
		}

		constexpr Vector2<IntType> Extent() const
		{
			return Vector2<IntType>(end - start);
		}

		constexpr IntType Width() const
		{
			return end.x - start.x;
		}

		constexpr IntType Height() const
		{
			return end.y - start.y;
		}

		constexpr bool IsNull() const
		{
			return start == end;
		}
	};

	typedef Bounds2<int8>	Bounds2i8;
	typedef Bounds2<int16>	Bounds2i16;
	typedef Bounds2<int32>	Bounds2i32;
	typedef Bounds2<int64>	Bounds2i64;

	typedef Bounds2<uInt8>  Bounds2u8;
	typedef Bounds2<uInt16> Bounds2u16;
	typedef Bounds2<uInt32> Bounds2u32;
	typedef Bounds2<uInt64> Bounds2u64;

	typedef Bounds2<sSize>	Bounds2i;
	typedef Bounds2<uSize>	Bounds2u;

	typedef Bounds2<float>	Bounds2f;
	typedef Bounds2<double>	Bounds2d;

	/*====================================================
	|                QUARTZMATH BOUNDS3                  |
	=====================================================*/

	template<typename IntType>
	struct Bounds3
	{
		Point3<IntType> start;
		Point3<IntType> end;

		constexpr Bounds3() {};

		constexpr Bounds3(IntType x, IntType y, IntType z, IntType width, IntType height, IntType depth)
			: start(x, y, z), end(x + width, y + height, z + depth) { }

		constexpr Bounds3(const Point3<IntType>& point1, const Point3<IntType>& point2)
			: start(Min(point1, point2)), end(Max(point1, point2)) { }

		constexpr Bounds3(const Bounds3& bounds3)
			: start(bounds3.start), end(bounds3.end) { }

		constexpr Bounds3& Extend(const Point3<IntType>& point)
		{
			start = Min(start, point);
			end = Max(end, point);
			return *this;
		}

		constexpr Bounds3 Extended(const Point3<IntType>& point) const
		{
			Bounds3 result;
			result.start = Min(start, point);
			result.end = Max(end, point);
			return result;
		}

		constexpr Bounds3& Translate(const Vector2<IntType>& vec2)
		{
			start += vec2;
			end += vec2;
			return *this;
		}

		constexpr Bounds3 Translated(const Vector2<IntType>& vec2) const
		{
			Bounds3 result;
			result.x = start + vec2;
			result.y = end + vec2;
			return result;
		}

		constexpr Point3<IntType> TopLeftFront() const
		{
			return Point3<IntType>(start.x, end.y, start.z);
		}

		constexpr Point3<IntType> TopRightFront() const
		{
			return Point3<IntType>(end.x, end.y, start.z);
		}

		constexpr Point3<IntType> BottomLeftFront() const
		{
			return start;
		}

		constexpr Point3<IntType> BottomRightFront() const
		{
			return Point3<IntType>(end.x, start.y, start.z);
		}

		constexpr Point3<IntType> TopLeftBack() const
		{
			return Point3<IntType>(start.x, end.y, end.y);
		}

		constexpr Point3<IntType> TopRightBack() const
		{
			return end;
		}

		constexpr Point3<IntType> BottomLeftBack() const
		{
			return Point3<IntType>(start.x, start.y, end.z);
		}

		constexpr Point3<IntType> BottomRightBack() const
		{
			return Point3<IntType>(end.x, start.y, end.z);
		}

		constexpr Vector3<IntType> Extent() const
		{
			return Vector3<IntType>(end - start);
		}

		constexpr IntType Width() const
		{
			return end.x - start.x;
		}

		constexpr IntType Height() const
		{
			return end.y - start.y;
		}

		constexpr IntType Depth() const
		{
			return end.z - start.z;
		}

		constexpr bool IsNull() const
		{
			return start == end;
		}
	};

	typedef Bounds3<int8>	Bounds3i8;
	typedef Bounds3<int16>	Bounds3i16;
	typedef Bounds3<int32>	Bounds3i32;
	typedef Bounds3<int64>	Bounds3i64;

	typedef Bounds3<uInt8>  Bounds3u8;
	typedef Bounds3<uInt16> Bounds3u16;
	typedef Bounds3<uInt32> Bounds3u32;
	typedef Bounds3<uInt64> Bounds3u64;

	typedef Bounds3<sSize>	Bounds3i;
	typedef Bounds3<uSize>	Bounds3u;

	typedef Bounds3<float>	Bounds3f;
	typedef Bounds3<double>	Bounds3d;

	/*====================================================
	|                   BOUNDS UTILITY                   |
	=====================================================*/

	template<typename IntType>
	bool PointInBounds(Point2<IntType> point, Bounds2<IntType> bounds)
	{
		return point.x > bounds.start.x && point.x < bounds.end.x&&
			point.y > bounds.start.y && point.y < bounds.end.y;
	}

	template<typename IntType>
	bool PointInBounds(Point3<IntType> point, Bounds3<IntType> bounds)
	{
		return point.x > bounds.start.x && point.x < bounds.end.x&&
			point.y > bounds.start.y && point.y < bounds.end.y&&
			point.z > bounds.start.z && point.z < bounds.end.z;
	}
}