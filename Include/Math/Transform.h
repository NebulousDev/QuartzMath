#pragma once

#include "Vector.h"
#include "Quaternion.h"
#include "Matrix.h"

namespace Quartz
{
	struct Transform
	{
		Vec3f position;
		Quatf rotation;
		Vec3f scale;

		inline Transform() :
			position{ 0.0f, 0.0f, 0.0f },
			rotation{ 0.0f, 0.0f, 0.0f, 1.0f },
			scale{ 1.0f, 1.0f, 1.0f } { }

		inline Transform(const Vec3f& position, const Quatf& rotation, const Vec3f& scale) :
			position(position),
			rotation(rotation),
			scale(scale) { }

		inline Vec3f GetForward() const
		{
			return rotation * Vec3f(0.0f, 0.0f, 1.0f);
		}

		inline Vec3f GetBackward() const
		{
			return rotation * Vec3f(0.0f, 0.0f, -1.0f);
		}

		inline Vec3f GetLeft() const
		{
			return rotation * Vec3f(-1.0f, 0.0f, 0.0f);
		}

		inline Vec3f GetRight() const
		{
			return rotation * Vec3f(1.0f, 0.0f, 0.0f);
		}

		inline Vec3f GetUp() const
		{
			return rotation * Vec3f(0.0f, 1.0f, 1.0f);
		}

		inline Vec3f GetDown() const
		{
			return rotation * Vec3f(0.0f, -1.0f, 1.0f);
		}

		inline Mat4f GetMatrix() const
		{
			return
				Mat4f().SetScale(scale) *
				Mat4f().SetRotation(rotation) *
				Mat4f().SetTranslation(position);
		}

		inline Mat4f GetViewMatrix() const
		{
			return
				Mat4f().SetTranslation(-position) *
				Mat4f().SetRotation(rotation);

		}
	};
}