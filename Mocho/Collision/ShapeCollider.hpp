/*
 * RigidBody.hpp
 *
 *  Created on: Oct 14, 2017
 *      Author: santiago
 */

#pragma once
#include "../Collision/collision.hpp"
#include "Mocho/definitions.hpp"
namespace mch {


class ShapeCollider{
	public:
		void* getUserData();
		void setUserData(void*);

		void setShapeType(ShapeType type);
		ShapeType getShapeType();

		void setCircle(const Circle& circle);
		const Circle& getCircle();

		void setAABB(const AABB& size);
		const AABB& getAABB();

		void setPosition(Vec2f position);
		const Vec2f& getPosition();

		void setRotation(float radians);
		float getRotation(float rotation);

		const std::vector<ShapeCollider*>& getCollisions();

	private:

		void* user_data;
		std::vector<ShapeCollider*> collisions;

		ShapeType type;
		union{
			AABB aabb;
			Circle circle;
		}shape;

		float rotation;
		Vec2f position;

		bool need_update_shape;
};

} /* namespace mch */
