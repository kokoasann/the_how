/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
 */

#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

namespace tkEngine{
	/*!
	 * @brief	�ÓI�����I�u�W�F�N�g
	 */
	class CPhysicsStaticObject{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CPhysicsStaticObject();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CPhysicsStaticObject();
		/*!
		 * @brief	���b�V���̐ÓI�I�u�W�F�N�g���쐬�B
		 *@param[in]	skinModel	�X�L�����f���B
		 *@param[in]	pos			���W�B
		 *@param[in]	rot			��]�B
		 */
		void CreateMeshObject(CSkinModel& skinModel, CVector3 pos, CQuaternion rot);
		void CreateMeshObject(prefab::CSkinModelRender* skinModelRender, CVector3 pos, CQuaternion rot);
	private:
		CMeshCollider m_meshCollider;		//!<���b�V���R���C�_�[�B
		CRigidBody m_rigidBody;				//!<���́B
	};
}