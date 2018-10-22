/*!
 *@brief	�t���X�^���J�����O�����B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/culling/tkObjectFrustumCulling.h"

namespace tkEngine{
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	CObjectFrustumCulling::CObjectFrustumCulling()
	{
	}
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	CObjectFrustumCulling::~CObjectFrustumCulling()
	{
	}
	/*!
	 *@brief	�J�����O�A���S���Y���̎��s�B
	 */
	void CObjectFrustumCulling::Execute(const CAabb& aabb)
	{
		if (m_camera != nullptr) {
			const CMatrix& viewProjMatrix = m_camera->GetViewProjectionMatrix();
			SetCullingFlag(true);
			//AABB�̂W���_���X�N���[����Ԃ̐��K�����W�n�ɕϊ�����B
			//x�Ay��1.0�`-1.0�Az��0.0�`1.0�͈͓̔��ɂ������ʓ��ɂ���Ƃ������ƂɂȂ�B
			//8���_���ׂĂ���ʂ̊O�Ȃ�J�����O����B
			for (int i = 0; i < 8; i++) {
				CVector4 vertPos(aabb.GetVertexPosition(i));
				viewProjMatrix.Mul(vertPos);
				vertPos.x /= vertPos.w;
				vertPos.y /= vertPos.w;
				vertPos.z /= vertPos.w;
				if (vertPos.x >= -1.0f
					&& vertPos.x <= 1.0f
					&& vertPos.y >= -1.0f
					&& vertPos.y <= 1.0f
					&& vertPos.z >= 0.0f
					&& vertPos.z <= 1.0f
					) {
					//��ʓ��ɂ���
					SetCullingFlag(false);
					break;
				}
			}
		}
	}
}
