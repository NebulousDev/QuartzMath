#pragma once

#include "Types.h"
#include "Util.h"

namespace Quartz
{
	/*====================================================
	|	             QUARTZMATH VECTOR2                  |
	=====================================================*/

	template<typename IntType>
	struct Vector2
	{
		union
		{
			IntType e[2];

			struct
			{
				IntType x;
				IntType y;
			};

		};

		/** Construct an uninitialized Vector2 */
		constexpr Vector2()
			: x(0), y(0) { }

		/** Construct an filled Vector2 */
		constexpr Vector2(IntType fill)
			: x(fill), y(fill) { }

		/** Construct a Vector2 from values */
		constexpr Vector2(IntType x, IntType y)
			: x(x), y(y) { }

		constexpr Vector2(const Vector2& vec2)
			: x(vec2.x), y(vec2.y) { }

		/** Set component values */
		constexpr Vector2& Set(IntType x, IntType y)
		{
			this->x = x;
			this->y = y;
		}

		/** Set component values */
		constexpr Vector2& Set(const Vector2& vec2)
		{
			this->x = vec2.x;
			this->y = vec2.y;
		}

		/** Get the magnitude this vector */
		constexpr IntType Magnitude() const
		{
			return 1.0f / FastInvsereSquare(MagnitudeSquared());
		}

		/** Get the squared magnitude this vector */
		constexpr IntType MagnitudeSquared() const
		{
			return (x * x) + (y * y);
		}

		/** Normalize this vector */
		constexpr Vector2& Normalize()
		{
			IntType fastInv = FastInvsereSquare(MagnitudeSquared());
			this->x *= fastInv;
			this->y *= fastInv;
			return *this;
		}

		/** Get the normalized vector */
		constexpr Vector2 Normalized() const
		{
			Vector2 result;
			IntType fastInv = FastInvsereSquare(MagnitudeSquared());
			result.x = x * fastInv;
			result.y = y * fastInv;
			return result;
		}

		/** Get the dot product of two vectors */
		constexpr friend IntType Dot(const Vector2& veca, const Vector2& vecb)
		{
			return veca.x * vecb.x + veca.y * vecb.y;
		}

		/** Get a component by index */
		constexpr IntType& operator[](int index)
		{
			return e[index];
		}

		/** Get a component by index */
		constexpr IntType operator[](int index) const
		{
			return e[index];
		}

		/** Get the negated vector */
		constexpr Vector2 operator-() const
		{
			return Vector2(-x, -y);
		}

		/** Add a vector to this */
		constexpr Vector2 operator+(const Vector2& vec2) const
		{
			return Vector2(x + vec2.x, y + vec2.y);
		}
		
		/** Add a vector to this */
		constexpr void operator+=(const Vector2& vec2)
		{
			x += vec2.x;
			y += vec2.y;
		}

		/** Subtract a vector to this */
		constexpr Vector2 operator-(const Vector2& vec2) const
		{
			return Vector2(x - vec2.x, y - vec2.y);
		}

		/** Subtract a vector to this */
		constexpr void operator-=(const Vector2& vec2)
		{
			x -= vec2.x;
			y -= vec2.y;
		}

		/** Multiply a vector to this */
		constexpr Vector2 operator*(const Vector2& vec2) const
		{
			return Vector2(x * vec2.x, y * vec2.y);
		}

		/** Multiply a vector to this */
		constexpr void operator*=(const Vector2& vec2)
		{
			x *= vec2.x;
			y *= vec2.y;
		}

		/** Multiply a IntType to this */
		constexpr Vector2 operator*(IntType value) const
		{
			return Vector2(x * value, y * value);
		}

		/** Multiply a IntType to this */
		constexpr friend Vector2 operator*(IntType value, const Vector2& vec2)
		{
			return Vector2(value * vec2.x, value * vec2.y);
		}

		/** Multiply a IntType to this */
		constexpr Vector2 operator*=(IntType value)
		{
			x *= value;
			y *= value;
		}

		/** Divide a vector from this */
		constexpr Vector2 operator/(const Vector2& vec2) const
		{
			return Vector2(x / vec2.x, y / vec2.y);
		}

		/** Divide a vector from this */
		constexpr void operator/=(const Vector2& vec2)
		{
			x /= vec2.x;
			y /= vec2.y;
		}

		/** Check if two matrices are equal */
		constexpr bool operator==(const Vector2& vec2) const
		{
			return x == vec2.x && y == vec2.y;
		}

		/** Check if two matrices are not equal */
		constexpr bool operator!=(const Vector2& vec2) const
		{
			return !(*this == vec2);
		}

		constexpr friend Vector2 Max(const Vector2& veca, const Vector2& vecb)
		{
			Vector2 result;
			result.x = veca.x > vecb.x ? veca.x : vecb.x;
			result.y = veca.y > vecb.y ? veca.y : vecb.y;
			return result;
		}

		constexpr friend Vector2 Min(const Vector2& veca, const Vector2& vecb)
		{
			Vector2 result;
			result.x = veca.x < vecb.x ? veca.x : vecb.x;
			result.y = veca.y < vecb.y ? veca.y : vecb.y;
			return result;
		}

		constexpr bool IsZero() const
		{
			return x == y == 0;
		}
	};

	typedef Vector2<uInt8>	Vec2u8;
	typedef Vector2<uInt16>	Vec2u16;
	typedef Vector2<uInt32>	Vec2u32;
	typedef Vector2<uInt64>	Vec2u64;

	typedef Vector2<int8>	Vec2i8;
	typedef Vector2<int16>	Vec2i16;
	typedef Vector2<int32>	Vec2i32;
	typedef Vector2<int64>	Vec2i64;

	typedef Vector2<uSize>	Vec2u;
	typedef Vector2<sSize>	Vec2i;

	typedef Vector2<float>	Vec2f;
	typedef Vector2<double>	Vec2d;

	/*====================================================
	|	             QUARTZMATH VECTOR3                  |
	=====================================================*/

	template<typename IntType>
	struct Vector3
	{
		union
		{
			IntType e[3];

			struct
			{
				IntType x;
				IntType y;
				IntType z;
			};

		};

		/** Construct an uninitialized Vector3 */
		constexpr Vector3()
			: x(0), y(0), z(0) { }

		/** Construct an filled Vector3 */
		constexpr Vector3(IntType fill)
			: x(fill), y(fill), z(fill) { }

		/** Construct a Vector3 from values */
		constexpr Vector3(IntType x, IntType y, IntType z)
			: x(x), y(y), z(z) { }

		constexpr Vector3(const Vector2<IntType>& vec2, float z)
			: x(vec2.x), y(vec2.y), z(z) { }

		constexpr Vector3(const Vector3& vec3)
			: x(vec3.x), y(vec3.y), z(vec3.z) { }

		/** Set component values */
		constexpr Vector3& Set(IntType x, IntType y, IntType z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/** Set component values */
		constexpr Vector3& Set(const Vector3& vec3)
		{
			this->x = vec3.x;
			this->y = vec3.y;
			this->z = vec3.z;
		}

		/** Get the magnitude this vector */
		constexpr IntType Magnitude() const
		{
			return 1.0f / FastInvsereSquare(MagnitudeSquared());
		}

		/** Get the squared magnitude this vector */
		constexpr IntType MagnitudeSquared() const
		{
			return (x * x) + (y * y) + (z * z);
		}

		/** Normalize this vector */
		constexpr Vector3& Normalize()
		{
			IntType fastInv = FastInvsereSquare(MagnitudeSquared());
			this->x *= fastInv;
			this->y *= fastInv;
			this->z *= fastInv;
			return *this;
		}

		/** Get the normalized vector */
		constexpr Vector3 Normalized() const
		{
			Vector3 result;
			IntType fastInv = FastInvsereSquare(MagnitudeSquared());
			result.x = x * fastInv;
			result.y = y * fastInv;
			result.z = z * fastInv;
			return result;
		}

		/** Get the dot product of two vectors */
		constexpr friend IntType Dot(const Vector3& veca, const Vector3& vecb)
		{
			return veca.x * vecb.x + veca.y * vecb.y + veca.z * vecb.z;
		}

		/** Get the cross product of two vectors */
		constexpr friend Vector3 Cross(const Vector3& veca, const Vector3& vecb)
		{
			IntType x = veca.y * vecb.z - veca.z * vecb.y;
			IntType y = veca.z * vecb.x - veca.x * vecb.z;
			IntType z = veca.x * vecb.y - veca.y * vecb.x;
			return Vector3(-x, -y, -z);
		}

		/** Get a component by index */
		constexpr IntType& operator[](int index)
		{
			return e[index];
		}

		/** Get a component by index */
		constexpr IntType operator[](int index) const
		{
			return e[index];
		}

		/** Get the negated vector */
		constexpr Vector3 operator-() const
		{
			return Vector3(-x, -y, -z);
		}

		/** Add a vector to this */
		constexpr Vector3 operator+(const Vector3& vec3) const
		{
			return Vector3(x + vec3.x, y + vec3.y, z + vec3.z);
		}

		/** Add a vector to this */
		constexpr void operator+=(const Vector3& vec3)
		{
			x += vec3.x;
			y += vec3.y;
			z += vec3.z;
		}

		/** Subtract a vector to this */
		constexpr Vector3 operator-(const Vector3& vec3) const
		{
			return Vector3(x - vec3.x, y - vec3.y, z - vec3.z);
		}

		/** Subtract a vector to this */
		constexpr void operator-=(const Vector3& vec3)
		{
			x -= vec3.x;
			y -= vec3.y;
			z -= vec3.z;
		}

		/** Multiply a vector to this */
		constexpr Vector3 operator*(const Vector3& vec3) const
		{
			return Vector3(x * vec3.x, y * vec3.y, z * vec3.z);
		}

		/** Multiply a vector to this */
		constexpr void operator*=(const Vector3& vec3)
		{
			x *= vec3.x;
			y *= vec3.y;
			z *= vec3.z;
		}

		/** Multiply a IntType to this */
		constexpr Vector3 operator*(IntType value) const
		{
			return Vector3(x * value, y * value, z * value);
		}

		/** Multiply a IntType to this */
		constexpr friend Vector3 operator*(IntType value, const Vector3& vec3)
		{
			return Vector3(value * vec3.x, value * vec3.y, value * vec3.z);
		}

		/** Multiply a IntType to this */
		constexpr Vector3 operator*=(IntType value)
		{
			x *= value;
			y *= value;
			z *= value;
		}

		/** Divide a vector from this */
		constexpr Vector3 operator/(const Vector3& vec3) const
		{
			return Vector3(x / vec3.x, y / vec3.y, z / vec3.z);
		}

		/** Divide a vector from this */
		constexpr void operator/=(const Vector3& vec3)
		{
			x /= vec3.x;
			y /= vec3.y;
			z /= vec3.z;
		}

		/** Check if two matrices are equal */
		constexpr bool operator==(const Vector3& vec3) const
		{
			return x == vec3.x && y == vec3.y && z == vec3.z;
		}

		/** Check if two matrices are not equal */
		constexpr bool operator!=(const Vector3& vec3) const
		{
			return !(*this == vec3);
		}

		constexpr friend Vector3 Max(const Vector3& veca, const Vector3& vecb)
		{
			Vector3 result;
			result.x = veca.x > vecb.x ? veca.x : vecb.x;
			result.y = veca.y > vecb.y ? veca.y : vecb.y;
			result.z = veca.z > vecb.z ? veca.z : vecb.z;
			return result;
		}

		constexpr friend Vector3 Min(const Vector3& veca, const Vector3& vecb)
		{
			Vector3 result;
			result.x = veca.x < vecb.x ? veca.x : vecb.x;
			result.y = veca.y < vecb.y ? veca.y : vecb.y;
			result.z = veca.z < vecb.z ? veca.z : vecb.z;
			return result;
		}

		constexpr Vector2<IntType> xy() const
		{
			return Vector2<IntType>(x, y);
		}

		constexpr bool IsZero() const
		{
			return x == y == z == 0;
		}
	};

	typedef Vector3<uInt8>	Vec3u8;
	typedef Vector3<uInt16>	Vec3u16;
	typedef Vector3<uInt32>	Vec3u32;
	typedef Vector3<uInt64>	Vec3u64;

	typedef Vector3<int8>	Vec3i8;
	typedef Vector3<int16>	Vec3i16;
	typedef Vector3<int32>	Vec3i32;
	typedef Vector3<int64>	Vec3i64;

	typedef Vector3<uSize>	Vec3u;
	typedef Vector3<sSize>	Vec3i;

	typedef Vector3<float>	Vec3f;
	typedef Vector3<double>	Vec3d;

	/*====================================================
	|	             QUARTZMATH VECTOR4                  |
	=====================================================*/

	template<typename IntType>
	struct Vector4
	{
		union
		{
			IntType e[4];

			struct
			{
				IntType x;
				IntType y;
				IntType z;
				IntType w;
			};

		};

		/** Construct an uninitialized Vector4 */
		constexpr Vector4()
			: x(0), y(0), z(0), w(0) { }

		/** Construct an filled Vector4 */
		constexpr Vector4(IntType fill)
			: x(fill), y(fill), z(fill), w(fill) { }

		/** Construct a Vector4 from values */
		constexpr Vector4(IntType x, IntType y, IntType z)
			: x(x), y(y), z(z) { }

		constexpr Vector4(const Vector2<IntType>& vec2, float z, float w)
			: x(vec2.x), y(vec2.y), z(z), w(w) { }

		constexpr Vector4(const Vector3<IntType>& vec3, float w)
			: x(vec3.x), y(vec3.y), z(vec3.z), w(w) { }

		constexpr Vector4(const Vector4& vec4)
			: x(vec4.x), y(vec4.y), z(vec4.z), w(vec4.w) { }

		/** Set component values */
		constexpr Vector4& Set(IntType x, IntType y, IntType z, IntType w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->z = w;
		}

		/** Set component values */
		constexpr Vector4& Set(const Vector4& vec4)
		{
			this->x = vec4.x;
			this->y = vec4.y;
			this->z = vec4.z;
			this->w = vec4.w;
		}

		/** Get the magnitude this vector */
		IntType Magnitude() const
		{
			return 1.0f / FastInvsereSquare(MagnitudeSquared());
		}

		/** Get the squared magnitude this vector */
		IntType MagnitudeSquared() const
		{
			return (x * x) + (y * y) + (z * z) + (w * w);
		}

		/** Normalize this vector */
		Vector4& Normalize()
		{
			IntType fastInv = FastInvsereSquare(MagnitudeSquared());
			this->x *= fastInv;
			this->y *= fastInv;
			this->z *= fastInv;
			this->w *= fastInv;
			return *this;
		}

		/** Get the normalized vector */
		Vector4 Normalized() const
		{
			Vector4 result;
			IntType fastInv = FastInvsereSquare(MagnitudeSquared());
			result.x = x * fastInv;
			result.y = y * fastInv;
			result.z = z * fastInv;
			result.w = w * fastInv;
			return result;
		}

		/** Get the dot product of two vectors */
		constexpr friend IntType Dot(const Vector4& veca, const Vector4& vecb)
		{
			return veca.x * vecb.x + veca.y * vecb.y + veca.z * vecb.z + veca.w * vecb.w;
		}

		/** Get a component by index */
		constexpr IntType& operator[](int index)
		{
			return e[index];
		}

		/** Get a component by index */
		constexpr IntType operator[](int index) const
		{
			return e[index];
		}

		/** Get the negated vector */
		constexpr Vector4 operator-() const
		{
			return Vector4(-x, -y, -z, -w);
		}

		/** Add a vector to this */
		constexpr Vector4 operator+(const Vector4& vec4) const
		{
			return Vector4(x + vec4.x, y + vec4.y, z + vec4.z, w + vec4.w);
		}

		/** Add a vector to this */
		constexpr void operator+=(const Vector4& vec4)
		{
			x += vec4.x;
			y += vec4.y;
			z += vec4.z;
			w += vec4.w;
		}

		/** Subtract a vector to this */
		constexpr Vector4 operator-(const Vector4& vec4) const
		{
			return Vector4(x - vec4.x, y - vec4.y, z - vec4.z, w - vec4.w);
		}

		/** Subtract a vector to this */
		constexpr void operator-=(const Vector4& vec4)
		{
			x -= vec4.x;
			y -= vec4.y;
			z -= vec4.z;
			w -= vec4.w;
		}

		/** Multiply a vector to this */
		constexpr Vector4 operator*(const Vector4& vec4) const
		{
			return Vector4(x * vec4.x, y * vec4.y, z * vec4.z, w * vec4.w);
		}

		/** Multiply a vector to this */
		constexpr void operator*=(const Vector4& vec4)
		{
			x *= vec4.x;
			y *= vec4.y;
			z *= vec4.z;
			w *= vec4.w;
		}

		/** Multiply a IntType to this */
		constexpr Vector4 operator*(IntType value) const
		{
			return Vector4(x * value, y * value, z * value, w * value);
		}

		/** Multiply a IntType to this */
		constexpr friend Vector4 operator*(IntType value, const Vector4& vec4)
		{
			return Vector4(value * vec4.x, value * vec4.y, value * vec4.z, value * vec4.w);
		}

		/** Multiply a IntType to this */
		constexpr Vector4 operator*=(IntType value)
		{
			x *= value;
			y *= value;
			z *= value;
			w *= value;
		}

		/** Divide a vector from this */
		constexpr Vector4 operator/(const Vector4& vec4) const
		{
			return Vector4(x / vec4.x, y / vec4.y, z / vec4.z, w / vec4.w);
		}

		/** Divide a vector from this */
		constexpr void operator/=(const Vector4& vec4)
		{
			x /= vec4.x;
			y /= vec4.y;
			z /= vec4.z;
			w /= vec4.w;
		}

		/** Check if two matrices are equal */
		constexpr bool operator==(const Vector4& vec4) const
		{
			return x == vec4.x && y == vec4.y && z == vec4.z && w == vec4.w;
		}

		/** Check if two matrices are not equal */
		constexpr bool operator!=(const Vector4& vec4) const
		{
			return !(*this == vec4);
		}

		constexpr friend Vector4 Max(const Vector4& veca, const Vector4& vecb)
		{
			Vector4 result;
			result.x = veca.x > vecb.x ? veca.x : vecb.x;
			result.y = veca.y > vecb.y ? veca.y : vecb.y;
			result.z = veca.z > vecb.z ? veca.z : vecb.z;
			result.w = veca.w > vecb.w ? veca.w : vecb.w;
			return result;
		}

		constexpr friend Vector4 Min(const Vector4& veca, const Vector4& vecb)
		{
			Vector4 result;
			result.x = veca.x < vecb.x ? veca.x : vecb.x;
			result.y = veca.y < vecb.y ? veca.y : vecb.y;
			result.z = veca.z < vecb.z ? veca.z : vecb.z;
			result.w = veca.w < vecb.w ? veca.w : vecb.w;
			return result;
		}

		constexpr Vector2<IntType> xy() const
		{
			return Vector2<IntType>(x, y);
		}

		constexpr Vector3<IntType> xyz() const
		{
			return Vector3<IntType>(x, y, z);
		}

		constexpr bool IsZero() const
		{
			return x == y == z == w == 0;
		}
	};

	typedef Vector4<uInt8>	Vec4u8;
	typedef Vector4<uInt16>	Vec4u16;
	typedef Vector4<uInt32>	Vec4u32;
	typedef Vector4<uInt64>	Vec4u64;

	typedef Vector4<int8>	Vec4i8;
	typedef Vector4<int16>	Vec4i16;
	typedef Vector4<int32>	Vec4i32;
	typedef Vector4<int64>	Vec4i64;

	typedef Vector4<uSize>	Vec4u;
	typedef Vector4<sSize>	Vec4i;

	typedef Vector4<float>	Vec4f;
	typedef Vector4<double>	Vec4d;
}