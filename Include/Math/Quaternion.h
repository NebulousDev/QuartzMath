#pragma once

#include "Vector.h"

#include <cmath>

namespace Quartz
{
	/*====================================================
	|                QUARTZMATH QUATERNION               |
	=====================================================*/

	template<typename IntType>
	struct Quaternion
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

		/** Construct an uninitialized Quaternion */
		constexpr Quaternion()
			: x(0), y(0), z(0), w(1) {}

		/** Construct a Quaternion from axis and angle */
		constexpr Quaternion(const Vector3<IntType>& axis, IntType angle)
		{
			SetAxisAngle(axis, angle);
		}

		/** Construct a Quaternion from euler angles */
		constexpr Quaternion(const Vector3<IntType>& euler)
		{
			SetEuler(euler);
		}

		/** Construct a Quaternion from values */
		constexpr Quaternion(IntType x, IntType y, IntType z, IntType w)
			: x(x), y(y), z(z), w(w) {}

		/** Set component values */
		constexpr Quaternion& Set(IntType x, IntType y, IntType z, IntType w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;

			return *this;
		}

		/** Set a Quaternion from axis and angle */
		constexpr Quaternion& SetAxisAngle(const Vector3<IntType>& axis, IntType angle)
		{
			IntType sinHalfAngle = sinf(angle * 0.5f);
			IntType cosHalfAngle = cosf(angle * 0.5f);

			this->x = axis.x * sinHalfAngle;
			this->y = axis.y * sinHalfAngle;
			this->z = axis.z * sinHalfAngle;
			this->w = cosHalfAngle;

			return *this;
		}

		/** Set a Quaternion from euler angles */
		constexpr Quaternion& SetEuler(const Vector3<IntType>& euler)
		{
			IntType cx = cosf(x * 0.5f);
			IntType cy = cosf(y * 0.5f);
			IntType cz = cosf(z * 0.5f);
			IntType sx = sinf(x * 0.5f);
			IntType sy = sinf(y * 0.5f);
			IntType sz = sinf(z * 0.5f);

			this->x = cx * sy * sz + cy * cz * sx;
			this->y = cx * cz * sy - cy * sx * sz;
			this->z = cx * cy * sz - cz * sx * sy;
			this->w = sx * sy * sz + cx * cy * cz;

			return *this;
		}

		/** Get the magnitude of this quaternion */
		IntType Magnitude() const
		{
			return 1.0f / FastInvsereSquare(MagnitudeSquared());
		}

		/** Get the inverse of the magnitude of this quaternion */
		IntType InverseMagnitude() const
		{
			return FastInvsereSquare(MagnitudeSquared());
		}

		/** Get the squared magnitude of this quaternion */
		constexpr IntType MagnitudeSquared() const
		{
			return (x * x) + (y * y) + (z * z) + (w * w);
		}

		/** Normalize this quaternion */
		Quaternion& Normalize()
		{
			IntType inverse = InverseMagnitude();
			this->x *= inverse;
			this->y *= inverse;
			this->z *= inverse;
			this->w *= inverse;
			return *this;
		}

		/** Get the normalized quaternion */
		constexpr Quaternion Normalized() const
		{
			IntType inverse = InverseMagnitude();
			IntType rx = x * inverse;
			IntType ry = y * inverse;
			IntType rz = z * inverse;
			IntType rw = w * inverse;
			return Quaternion(rx, ry, rz, rw);
		}

		/** Get the dot product of two quaternion */
		constexpr friend IntType Dot(const Quaternion& quat1, const Quaternion& quat2)
		{
			return quat1.x * quat2.x + quat1.y * quat2.y + quat1.z * quat2.z + quat1.w * quat2.w;
		}

		/** Get the conjugate of the quaternion */
		constexpr Quaternion Conjugate() const
		{
			return Quaternion(-x, -y, -z, w);
		}

		/** Get the inverse of the quaternion */
		Quaternion Inverse() const
		{
			IntType mag = Magnitude();
			IntType rx = -x / mag;
			IntType ry = -y / mag;
			IntType rz = -z / mag;
			IntType rw = w / mag;
			return Quaternion(rx, ry, rz, rw);
		}

		/** Multiply a quaternion to this */
		constexpr Quaternion operator*(const Quaternion& quat) const
		{
			IntType rx = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
			IntType ry = w * quat.y + y * quat.w + z * quat.x - x * quat.z;
			IntType rz = w * quat.z + z * quat.w + x * quat.y - y * quat.x;
			IntType rw = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
			return Quaternion(rx, ry, rz, rw);
		}

		/** Multiply a quaternion to this */
		constexpr void operator*=(const Quaternion& quat)
		{
			*this = *this * quat;
		}

		/** Multiply a quaternion to a Vector3<IntType> */
		constexpr Vector3<IntType> operator*(const Vector3<IntType>& vec3) const
		{
			Vector3<IntType> quatVec(x, y, z);
			return 2.0 * Dot(quatVec, vec3) * quatVec +
				(w * w - Dot(quatVec, quatVec)) * vec3 +
				2.0f * w * Cross(quatVec, vec3);
		}

		/** Multiply a Vector3<IntType> by a quaternion */
		constexpr friend Vector3<IntType> operator*(const Vector3<IntType>& vec3, const Quaternion& quat)
		{
			return quat * vec3;
		}

		/** Multiply a IntType to this */
		constexpr Quaternion operator*(IntType value) const
		{
			return Quaternion(x * value, y * value, z * value, w * value);
		}

		/** Multiply a IntType to this */
		constexpr Quaternion operator*=(IntType value)
		{
			x *= value;
			y *= value;
			z *= value;
			w *= value;
		}

		/** Multiply a IntType to this */
		friend constexpr Quaternion operator*(IntType value, const Quaternion& quat)
		{
			return quat * value;
		}

		/** Divide a quaternion from this */
		constexpr Quaternion operator/(const Quaternion& quat) const
		{
			return *this * quat.Inverse();
		}

		/** Divide a quaternion from this */
		constexpr void operator/=(const Quaternion& quat)
		{
			*this = *this * quat.Inverse();
		}

		/** Check if two matrices are equal */
		constexpr bool operator==(const Quaternion& quat) const
		{
			return x == quat.x && y == quat.y && z == quat.z && w == quat.w;
		}

		/** Check if two matrices are not equal */
		constexpr bool operator!=(const Quaternion& quat) const
		{
			return !(*this == quat);
		}
	};

	typedef Quaternion<sSize>	Quati;
	typedef Quaternion<uSize>	Quatu;
	typedef Quaternion<float>	Quatf;
	typedef Quaternion<double>	Quatd;
}
