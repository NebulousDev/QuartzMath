#pragma once

#include "Vector.h"

namespace Quartz
{
	/*====================================================
	|                 QUARTZMATH MATRIX4                 |
	=====================================================*/

	struct Quaternion;

	template<typename IntType>
	struct Matrix4
	{
		union
		{
			// Row major: accessed m[row][column]
			IntType m[4][4];

			// Row major: accessed e[row + column * 4]
			IntType e[16];

			// Row major
			struct
			{
				IntType m00, m01, m02, m03; // Left
				IntType m10, m11, m12, m13; // Up
				IntType m20, m21, m22, m23; // Forward
				IntType m30, m31, m32, m33; // Position
			};
		};

		/** Construct an uninitialized Matrix4 */
		constexpr Matrix4() {};

		/** Construct a Matrix4 from values */
		constexpr Matrix4(
			IntType m00, IntType m01, IntType m02, IntType m03,
			IntType m10, IntType m11, IntType m12, IntType m13,
			IntType m20, IntType m21, IntType m22, IntType m23,
			IntType m30, IntType m31, IntType m32, IntType m33)
		{
			this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
			this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
			this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
			this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
		}

		/** Construct a Matrix4 from vectors */
		constexpr Matrix4(
			const Vector4<IntType>& vecX, const Vector4<IntType>& vecY, 
			const Vector4<IntType>& vecZ, const Vector4<IntType>& vecW)
		{
			this->m00 = vecX.x; this->m01 = vecX.y; this->m02 = vecX.z; this->m03 = vecX.w;
			this->m10 = vecY.x; this->m11 = vecY.y; this->m12 = vecY.z; this->m13 = vecY.w;
			this->m20 = vecZ.x; this->m21 = vecZ.y; this->m22 = vecZ.z; this->m23 = vecZ.w;
			this->m30 = vecW.x; this->m31 = vecW.y; this->m32 = vecW.z; this->m33 = vecW.w;
		}

		/** Set to the identity matrix */
		constexpr Matrix4& SetZero()
		{
			for (int i = 0; i < 16; i++)
				e[i] = 0.0f;

			return *this;
		}

		/** Set to the identity matrix */
		constexpr Matrix4& SetIdentity()
		{
			m00 = 1; m01 = 0; m02 = 0; m03 = 0;
			m10 = 0; m11 = 1; m12 = 0; m13 = 0;
			m20 = 0; m21 = 0; m22 = 1; m23 = 0;
			m30 = 0; m31 = 0; m32 = 0; m33 = 1;
			return *this;
		}

		/** Set to a translation matrix */
		constexpr Matrix4& SetTranslation(const Vector3<IntType>& translation)
		{
			m00 = 1; m01 = 0; m02 = 0; m03 = 0;
			m10 = 0; m11 = 1; m12 = 0; m13 = 0;
			m20 = 0; m21 = 0; m22 = 1; m23 = 0;
			m30 = translation.x;
			m31 = translation.y;
			m32 = translation.z;
			m33 = 1;
			return *this;
		}

		/** Set to a rotation matrix */
		constexpr Matrix4& SetRotation(const Quaternion& rotation)
		{
			float qx = rotation.x;
			float qy = rotation.y;
			float qz = rotation.z;
			float qw = rotation.w;

			m00 = 1.0f - 2.0f * ((qy * qy) + (qz * qz));
			m01 =		 2.0f * ((qx * qy) + (qz * qw));
			m02 =		 2.0f * ((qx * qz) - (qy * qw));
			m03 =		 0.0f;

			m10 =		 2.0f * ((qx * qy) - (qz * qw));
			m11 = 1.0f - 2.0f * ((qx * qx) + (qz * qz));
			m12 =		 2.0f * ((qy * qz) + (qx * qw));
			m13 =		 0.0f;

			m20 =		 2.0f * ((qx * qz) + (qy * qw));
			m21 =		 2.0f * ((qy * qz) - (qx * qw));
			m22 = 1.0f - 2.0f * ((qx * qx) + (qy * qy));
			m23 =		 0.0f;

			m30 = 0.0f;
			m31 = 0.0f;
			m32 = 0.0f;
			m33 = 1.0f;

			return *this;
		}

		/** Set to a scale matrix */
		constexpr Matrix4& SetScale(const Vector3<IntType>& scale)
		{
			m00 = scale.x;	m01 = 0;		m02 = 0;		m03 = 0;
			m10 = 0;		m11 = scale.y;	m12 = 0;		m13 = 0;
			m20 = 0;		m21 = 0;		m22 = scale.z;	m23 = 0;
			m30 = 0;		m31 = 0;		m32 = 0;		m33 = 1;
			return *this;
		}

		/** Set to a view matrix */
		constexpr Matrix4& SetView(
			const Vector3<IntType>& right, const Vector3<IntType>& up, 
			const Vector3<IntType>& forward, const Vector3<IntType>& position)
		{
			m00 = right.x;		m01 = right.y;		m02 = right.z;		m03 = 0.0f;
			m10 = up.x;			m11 = up.y;			m12 = up.z;			m13 = 0.0f;
			m20 = forward.x;	m21 = forward.y;	m22 = forward.z;	m23 = 0.0f;
			m30 = position.x;	m31 = position.y;	m32 = position.z;	m33 = 1.0f;
			return *this;
		}

		/** Set to a lookat matrix */
		constexpr Matrix4& SetLookAt(
			const Vector3<IntType>& eye, const Vector3<IntType>& target, const Vector3<IntType>& up)
		{
			Vector3<IntType> forward	= (target - eye).Normalize();
			Vector3<IntType> right		= Cross(globalUp, forward).Normalize();
			Vector3<IntType> up			= Cross(forward, right);

			Vector3<IntType> position(Dot(right, eye), Dot(up, eye), Dot(forward, eye));

			return SetView(-right, up, forward, -position);
		}

		/** Set to a orthographic matrix */
		constexpr Matrix4& SetOrthographic(
			IntType left, IntType right, IntType top, 
			IntType bottom, IntType near, IntType far)
		{
			// TODO: Implement
			SetZero();
			return *this;
		}

		/** Set to a perspective matrix */
		constexpr Matrix4& SetPerspective(IntType fov, IntType aspect, IntType zNear, IntType zFar)
		{
			IntType fovY = 1.0f / tanf(fov * 0.5f);
			IntType range = (zFar - zNear);

			SetZero();
			m00 = fovY / aspect;
			m11 = fovY;
			m22 = -(zNear + zFar) / range;
			m23 = -1.0f;
			m32 = (-2.0f * zFar * zNear) / range;
			return *this;
		}

		/** Transpose this matrix */
		constexpr Matrix4& Transpose()
		{
			return *this = Transposed();
		}

		/** Get the transposed matrix */
		constexpr Matrix4 Transposed() const
		{
			Matrix4 result;
			result.m00 = m00; result.m01 = m10; result.m02 = m20; result.m03 = m30;
			result.m10 = m01; result.m11 = m11; result.m12 = m21; result.m13 = m31;
			result.m20 = m02; result.m21 = m12; result.m22 = m22; result.m23 = m32;
			result.m30 = m03; result.m31 = m13; result.m32 = m23; result.m33 = m33;
			return result;
		}

		/** Get the IntTypeing-point determinant */
		constexpr IntType Determinant() const
		{
			return	
				  m00 * ( m11 * (m22 * m33 - m23 * m32) - m21 * (m12 * m33 - m13 * m32) + m31 * (m12 * m23 - m13 * m22))
				- m10 * ( m01 * (m22 * m33 - m23 * m32) - m21 * (m02 * m33 - m03 * m32) + m31 * (m02 * m23 - m03 * m22))
				+ m20 * ( m01 * (m12 * m33 - m13 * m32) - m11 * (m02 * m33 - m03 * m32) + m31 * (m02 * m13 - m03 * m12))
				- m30 * ( m01 * (m12 * m23 - m13 * m22) - m11 * (m02 * m23 - m03 * m22) + m21 * (m02 * m13 - m03 * m12));
		}

		/** Get the inverse of the matrix */
		constexpr Matrix4 Inverse() const
		{
			// Modified from https://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform

			Matrix4 result;

			IntType s0 = m00 * m11 - m10 * m01;
			IntType s1 = m00 * m12 - m10 * m02;
			IntType s2 = m00 * m13 - m10 * m03;
			IntType s3 = m01 * m12 - m11 * m02;
			IntType s4 = m01 * m13 - m11 * m03;
			IntType s5 = m02 * m13 - m12 * m03;

			IntType c5 = m22 * m33 - m32 * m23;
			IntType c4 = m21 * m33 - m31 * m23;
			IntType c3 = m21 * m32 - m31 * m22;
			IntType c2 = m20 * m33 - m30 * m23;
			IntType c1 = m20 * m32 - m30 * m22;
			IntType c0 = m20 * m31 - m30 * m21;

			// TODO: Should check for 0 determinant
			IntType invdet = 1.0 / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

			result.m00 = ( m11 * c5 - m12 * c4 + m13 * c3) * invdet;
			result.m01 = (-m01 * c5 + m02 * c4 - m03 * c3) * invdet;
			result.m02 = ( m31 * s5 - m32 * s4 + m33 * s3) * invdet;
			result.m03 = (-m21 * s5 + m22 * s4 - m23 * s3) * invdet;

			result.m10 = (-m10 * c5 + m12 * c2 - m13 * c1) * invdet;
			result.m11 = ( m00 * c5 - m02 * c2 + m03 * c1) * invdet;
			result.m12 = (-m30 * s5 + m32 * s2 - m33 * s1) * invdet;
			result.m13 = ( m20 * s5 - m22 * s2 + m23 * s1) * invdet;

			result.m20 = ( m10 * c4 - m11 * c2 + m13 * c0) * invdet;
			result.m21 = (-m00 * c4 + m01 * c2 - m03 * c0) * invdet;
			result.m22 = ( m30 * s4 - m31 * s2 + m33 * s0) * invdet;
			result.m23 = (-m20 * s4 + m21 * s2 - m23 * s0) * invdet;

			result.m30 = (-m10 * c3 + m11 * c1 - m12 * c0) * invdet;
			result.m31 = ( m00 * c3 - m01 * c1 + m02 * c0) * invdet;
			result.m32 = (-m30 * s3 + m31 * s1 - m32 * s0) * invdet;
			result.m33 = ( m20 * s3 - m21 * s1 + m22 * s0) * invdet;

			return result;
		}

		/** Devide each column by a vector */
		constexpr Matrix4 DivideColumns(
			const Vector4<IntType>& col1, const Vector4<IntType>& col2, 
			const Vector4<IntType>& col3, const Vector4<IntType>& col4)
		{
			// TODO: probably flipped

			Matrix4 result;

			result.m00 = m00 / col1.x;
			result.m10 = m10 / col1.y;
			result.m20 = m20 / col1.z;
			result.m30 = m30 / col1.w;

			result.m01 = m01 / col2.x;
			result.m11 = m11 / col2.y;
			result.m21 = m21 / col2.z;
			result.m31 = m31 / col2.w;

			result.m02 = m02 / col3.x;
			result.m12 = m12 / col3.y;
			result.m22 = m22 / col3.z;
			result.m32 = m32 / col3.w;

			result.m03 = m03 / col4.x;
			result.m13 = m13 / col4.y;
			result.m23 = m23 / col4.z;
			result.m33 = m33 / col4.w;

			return result;
		}

		/** Get the origin vector */
		constexpr Vector3<IntType> GetTranslation() const
		{
			return Vector3<IntType>(m30, m31, m32);
		}

		/** Get the normalized up vector */
		constexpr Vector3<IntType> GetUp() const
		{
			return Vector3<IntType>(m10, m11, m12).Normalize();
		}

		/** Get the normalized down vector */
		constexpr Vector3<IntType> GetDown() const
		{
			return Vector3<IntType>(-m10, -m11, -m12).Normalize();
		}

		/** Get the normalized right vector */
		constexpr Vector3<IntType> GetRight() const
		{
			return Vector3<IntType>(m00, m01, m02).Normalize();
		}

		/** Get the normalized left vector */
		constexpr Vector3<IntType> GetLeft() const
		{
			return Vector3<IntType>(-m00, -m01, -m02).Normalize();
		}

		/** Get the normalized forward vector */
		constexpr Vector3<IntType> GetForward() const
		{
			return Vector3<IntType>(m20, m21, m22).Normalize();
		}

		/** Get the normalized backward vector */
		constexpr Vector3<IntType> GetBackward() const
		{
			return Vector3<IntType>(-m20, -m21, -m22).Normalize();
		}

		/** Get the scaled up vector */
		constexpr Vector3<IntType> GetScaledUp() const
		{
			return Vector3<IntType>(m10, m11, m12);
		}

		/** Get the scaled down vector */
		constexpr Vector3<IntType> GetScaledDown() const
		{
			return Vector3<IntType>(-m10, -m11, -m12);
		}

		/** Get the scaled right vector */
		constexpr Vector3<IntType> GetScaledRight() const
		{
			return Vector3<IntType>(m00, m01, m02);
		}

		/** Get the scaled left vector */
		constexpr Vector3<IntType> GetScaledLeft() const
		{
			return Vector3<IntType>(-m00, -m01, -m02);
		}

		/** Get the scaled forward vector */
		constexpr Vector3<IntType> GetScaledForward() const
		{
			return Vector3<IntType>(m20, m21, m22);
		}

		/** Get the scaled backward vector */
		constexpr Vector3<IntType> GetScaledBackward() const
		{
			return Vector3<IntType>(-m20, -m21, -m22);
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

		/** Multiply a matrix to this */
		constexpr Matrix4 operator*(const Matrix4& mat4) const
		{
			Matrix4 result;

			result.m00 = m00 * mat4.m00 + m01 * mat4.m10 + m02 * mat4.m20 + m03 * mat4.m30;
			result.m01 = m00 * mat4.m01 + m01 * mat4.m11 + m02 * mat4.m21 + m03 * mat4.m31;
			result.m02 = m00 * mat4.m02 + m01 * mat4.m12 + m02 * mat4.m22 + m03 * mat4.m32;
			result.m03 = m00 * mat4.m03 + m01 * mat4.m13 + m02 * mat4.m23 + m03 * mat4.m33;

			result.m10 = m10 * mat4.m00 + m11 * mat4.m10 + m12 * mat4.m20 + m13 * mat4.m30;
			result.m11 = m10 * mat4.m01 + m11 * mat4.m11 + m12 * mat4.m21 + m13 * mat4.m31;
			result.m12 = m10 * mat4.m02 + m11 * mat4.m12 + m12 * mat4.m22 + m13 * mat4.m32;
			result.m13 = m10 * mat4.m03 + m11 * mat4.m13 + m12 * mat4.m23 + m13 * mat4.m33;

			result.m20 = m20 * mat4.m00 + m21 * mat4.m10 + m22 * mat4.m20 + m23 * mat4.m30;
			result.m21 = m20 * mat4.m01 + m21 * mat4.m11 + m22 * mat4.m21 + m23 * mat4.m31;
			result.m22 = m20 * mat4.m02 + m21 * mat4.m12 + m22 * mat4.m22 + m23 * mat4.m32;
			result.m23 = m20 * mat4.m03 + m21 * mat4.m13 + m22 * mat4.m23 + m23 * mat4.m33;

			result.m30 = m30 * mat4.m00 + m31 * mat4.m10 + m32 * mat4.m20 + m33 * mat4.m30;
			result.m31 = m30 * mat4.m01 + m31 * mat4.m11 + m32 * mat4.m21 + m33 * mat4.m31;
			result.m32 = m30 * mat4.m02 + m31 * mat4.m12 + m32 * mat4.m22 + m33 * mat4.m32;
			result.m33 = m30 * mat4.m03 + m31 * mat4.m13 + m32 * mat4.m23 + m33 * mat4.m33;

			return result;
		}

		/** Multiply this by a matrix */
		constexpr void operator*=(const Matrix4& mat4)
		{
			*this = this * mat4;
		}

		/** Multiply a Vector4<IntType> to this */
		constexpr Vector4<IntType> operator*(const Vector4<IntType>& vec4) const
		{
			Vector4<IntType> result;

			result.x = m00 * vec4.x + m10 * vec4.y + m20 * vec4.z + m30 * vec4.w;
			result.y = m01 * vec4.x + m11 * vec4.y + m21 * vec4.z + m31 * vec4.w;
			result.z = m02 * vec4.x + m12 * vec4.y + m22 * vec4.z + m32 * vec4.w;
			result.w = m03 * vec4.x + m13 * vec4.y + m23 * vec4.z + m33 * vec4.w;

			return result;
		}

		/** Multiply a IntType to this */
		constexpr Matrix4 operator*(IntType value) const
		{
			Matrix4 result;
			for (int i = 0; i < 16; i++)
				result.e[i] = e[i] * value;
			return result;
		}

		/** Multiply a IntType to this */
		friend constexpr Matrix4 operator*(IntType value, const Matrix4& mat4)
		{
			return mat4 * value;
		}

		/** Multiply a IntType to this */
		constexpr void operator*=(IntType value)
		{
			for (int i = 0; i < 16; i++)
				e[i] = e[i] * value;
		}

		/** Check if two matrices are equal */
		constexpr bool operator==(const Matrix4& mat4) const
		{
			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					if (m[row][col] != mat4.m[row][col])
					{
						return false;
					}
				}
			}

			return true;
		}

		/** Check if two matrices are not equal */
		constexpr bool operator!=(const Matrix4& mat4) const
		{
			return !(*this == mat4);
		}
	};

	typedef Matrix4<sSize>	Mat4i;
	typedef Matrix4<uSize>	Mat4u;
	typedef Matrix4<float>	Mat4f;
	typedef Matrix4<double>	Mat4d;
}