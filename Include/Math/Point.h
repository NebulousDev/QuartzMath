#pragma once

#include "Vector.h"

namespace Quartz
{
	/*====================================================
	|	              QUARTZMATH POINT2                  |
	=====================================================*/

	template<typename IntType>
	using Point2 = Vector2<IntType>;

	typedef Point2<int8>	Point2i8;
	typedef Point2<int16>	Point2i16;
	typedef Point2<int32>	Point2i32;
	typedef Point2<int64>	Point2i64;

	typedef Point2<uInt8>  Point2u8;
	typedef Point2<uInt16> Point2u16;
	typedef Point2<uInt32> Point2u32;
	typedef Point2<uInt64> Point2u64;

	typedef Point2<sSize>	Point2i;
	typedef Point2<uSize>	Point2u;

	typedef Point2<float>	Point2f;
	typedef Point2<double>	Point2d;

	/*====================================================
	|	              QUARTZMATH POINT3                  |
	=====================================================*/

	template<typename IntType>
	using Point3 = Vector3<IntType>;

	typedef Point3<int8>	Point3i8;
	typedef Point3<int16>	Point3i16;
	typedef Point3<int32>	Point3i32;
	typedef Point3<int64>	Point3i64;

	typedef Point3<uInt8>  Point3u8;
	typedef Point3<uInt16> Point3u16;
	typedef Point3<uInt32> Point3u32;
	typedef Point3<uInt64> Point3u64;

	typedef Point3<sSize>	Point3i;
	typedef Point3<uSize>	Point3u;

	typedef Point3<float>	Point3f;
	typedef Point3<double>	Point3d;

	/*====================================================
	|	              QUARTZMATH POINT4                  |
	=====================================================*/

	template<typename IntType>
	using Point4 = Vector4<IntType>;

	typedef Point4<int8>	Point4i8;
	typedef Point4<int16>	Point4i16;
	typedef Point4<int32>	Point4i32;
	typedef Point4<int64>	Point4i64;

	typedef Point4<uInt8>	Point4u8;
	typedef Point4<uInt16>	Point4u16;
	typedef Point4<uInt32>	Point4u32;
	typedef Point4<uInt64>	Point4u64;

	typedef Point4<sSize>	Point4i;
	typedef Point4<uSize>	Point4u;

	typedef Point4<float>	Point4f;
	typedef Point4<double>	Point4d;
}