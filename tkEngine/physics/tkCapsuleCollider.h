/*!
 * @brief	�J�v�Z���R���C�_�[�B
 */

#pragma once

#include "tkEngine/Physics/tkICollider.h"


namespace tkEngine{
	class CCapsuleCollider : public ICollider
	{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CCapsuleCollider();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CCapsuleCollider();
		/*!
		* @brief	�쐬�B
		*/
		void Create(float radius, float height)
		{
			shape = new btCapsuleShape(radius, height);
			this->radius = radius;
			this->height = height;
		}
		btCollisionShape* GetBody() const override
		{
			return shape;
		}
		float GetRadius() const
		{
			return radius;
		}
		float GetHeight() const
		{
			return height;
		}
	private:
		btCapsuleShape*		shape = nullptr;
		float radius = 0.0f;
		float height = 0.0f;
	};
}