/*!
 *@brief	�X�L�����f���B
 */

#pragma once

#include "tkEngine/graphics/preRender/tkShadowCaster.h"

namespace tkEngine{
	class CSkinModelData;
	/*!
	 *@brief	�X�L�����f���B
	 *@details
	 * �X�L������A�Ȃ����f���̕\�����T�|�[�g����N���X�B</br>
	 * �����̃C���X�^���X����x�̊֐��R�[���ŕ`�悷�邱�Ƃ��ł���C���X�^���V���O�`����T�|�[�g���Ă���B</br>
	 */
	class CSkinModel : Noncopyable{
	public:
		/*!
		*@brief	FBX�̏�����B
		*/
		enum EnFbxUpAxis {
			enFbxUpAxisY,		//Y-up
			enFbxUpAxisZ,		//Z-up
		};
		typedef std::function<void(CSkeleton&)>		OnPostUpdateSkeleton;

		/*!
		*@brief QueryEffects�����s�����Ƃ��̃R�[���o�b�N�ɓn���������\���́B
		*/
		struct SQuerryEffectsCbArg {
			DirectX::ModelMeshPart*	meshPart;		//���݂̃G�t�F�N�g�B
		};
		CSkinModel();
		~CSkinModel();
		/*!
		*@brief	������
		*@param[in]	modelData		���f���f�[�^�B
		*@param[in] maxInstance		�C���X�^���X�̍ő吔�B1���傫���ꍇ�C���X�^���V���O�`�悪�s���܂��B
		*							�C���X�^���V���O�`����s���ꍇ�́AUpdateInstance�֐����g�p���āA
		*							�C���X�^���X�ŗL�̃f�[�^���X�V����K�v������܂��B
		*/
		void Init(CSkinModelData& modelData, int maxInstance = 1);
		/*!
		*@brief	�X�V�B
		*@details
		* �ʏ�`��̏ꍇ�̍s��X�V�͂�������g�p����B
		* �C���X�^���V���O�`��̏ꍇ��UpdateInstancingData���g�p����B
		*@param[in]		trans		���s�ړ��B
		*@param[in]		rot			��]�B
		*@param[in]		scale		�g��B
		*@param[in]		enUpdateAxis	fbx�̏�����B
		*/
		void Update(
			const CVector3& trans, 
			const CQuaternion& rot, 
			const CVector3& scale,
			EnFbxUpAxis enUpdateAxis = enFbxUpAxisZ
		);
		/*!
		 *@brief	�C���X�^���V���O�p�̃f�[�^�̍X�V�B
		 *@details
		 * �C���X�^���V���O�`��̏ꍇ�̍s��X�V�͂�������g�p����B
		 * �S�ẴC���X�^���X�̍s��X�V�����������̂��APostUpadteInstancingData���Ăяo���悤�ɁB
		 *@param[in]		trans		���s�ړ��B
		 *@param[in]		rot			��]�B
		 *@param[in]		scale		�g��B
		 *@param[in]		enUpdateAxis	fbx�̏�����B

		 */
		void UpdateInstancingData(
			const CVector3& trans,
			const CQuaternion& rot,
			const CVector3& scale,
			EnFbxUpAxis enUpdateAxis = enFbxUpAxisZ
		);
		/*!
		*@brief	�C���X�^���X�f�[�^�̍X�V�J�n���ɌĂяo���Ă��������B
		*/
		void BeginUpdateInstancingData()
		{
			m_numInstance = 0;
		}
		/*!
		 *@brief	�S�ẴC���X�^���X�f�[�^�̍X�V�I�������Ăяo���Ă��������B
		 */
		void EndUpdateInstancingData();
		/*!
		*@brief	�`��
		*@param[in] renderContext	�����_�����O�R���e�L�X�g�B
		*/
		void Draw(CRenderContext& renderContext);
		/*!
		*@brief	�`��
		*@param[in] renderContext	�����_�����O�R���e�L�X�g�B
		*@param[in]	viewMatrix		�r���[�s��B
		*@param[in]	projMatrix		�v���W�F�N�V�����s��B
		*@param[in]	isUpdateAnimation	�A�j���[�V�������X�V����H
		*/
		void Draw(
			CRenderContext& renderContext, 
			const CMatrix& viewMatrix, 
			const CMatrix& projMatrix,
			bool isUpdateAnimation = true
		);
		/*!
		*@brief	���b�V���̌����B
		*@param[in]	findMesh		���b�V�������������ɌĂ΂��R�[���o�b�N�֐�
		*/
		void FindMesh(CSkinModelData::OnFindMesh findMesh) const
		{
			if (m_skinModelData != nullptr) {
				m_skinModelData->FindMesh(findMesh);
			}
		}
		/*!
		*@brief	���f���}�e���A���̌����B
		*@param[in]	findEffect		�}�e���A�������������ɌĂ΂��R�[���o�b�N�֐�
		*/
		void FindMaterial(CSkinModelData::OnFindMaterial findMaterial) const
		{
			FindMesh([&](auto& mesh) {
				CModelEffect* effect = reinterpret_cast<CModelEffect*>(mesh->effect.get());
				findMaterial(effect);
			});
		}
		/*!
		* @brief	�V���h�E�L���X�^�[�̃t���O��ݒ�B
		*@param[in]	flag	�V���h�E�L���X�^�[�̃t���O�B
		*/
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}
		/*!
		* @brief	�V���h�E���V�[�o�[�̃t���O��ݒ�B
		*@param[in]	flag	�V���h�E���V�[�o�[�̃t���O�B
		*/
		void SetShadowReceiverFlag(bool flag)
		{
			m_isShadowReceiver = flag;
		}
		/*!
		 *@brief	���[���h�s����擾�B
		 */
		const CMatrix& GetWorldMatrix() const
		{
			return m_worldMatrix;
		}
		/*!
		*@brief	�X�L�����f���f�[�^���擾�B
		*/
		CSkinModelData* GetSkinModelData() const
		{
			return m_skinModelData;
		}
		/*!
		*@brief	�A�j���[�V������ݒ�B
		*@details
		* �G���W�������Ŏg�p����Ă��܂��B���[�U�[�͎g�p���Ȃ��ł��������B
		*/
		void SetAnimation(CAnimation* animation)
		{
			m_animation = animation;
		}
	private:
		/*!
		 *@brief	���[���h�s��̍X�V�B
		 */
		void UpdateWorldMatrix(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, EnFbxUpAxis enUpdateAxis);
	private:
		struct SVSConstantBuffer {
			CMatrix mWorld;
			CMatrix mView;
			CMatrix mProj;
			CVector4 screenParam;
			int isShadowReceiver;
		};
		CAnimation* m_animation = nullptr;
		CSkinModelData*	m_skinModelData = nullptr;
		CMatrix m_worldMatrix = CMatrix::Identity;
		CConstantBuffer m_cb;			//�萔�o�b�t�@�B
		CShadowCaster_SkinModel m_shadowCaster;	//!<�V���h�E�L���X�^�[�B
		bool m_isShadowCaster = false;		//!<�V���h�E�L���X�^�[�H
		bool m_isShadowReceiver = false;	//!<�V���h�E���V�[�o�[�H
		CSamplerState m_samplerState;		//!<�T���v���X�e�[�g�B@todo �ЂƂ܂Ƃ߂ɂ������������B
		std::unique_ptr<CMatrix[]>	m_instancingData;		//!<�C���X�^���V���O�`��p�̃f�[�^�B
		CStructuredBuffer	m_instancingDataSB;				//!<�C���X�^���V���O�`��p�̃X�g���N�`���[�o�b�t�@�B
		int m_maxInstance = 1;								//!<�C���X�^���X�̍ő吔
		int m_numInstance = 0;								//!<�C���X�^���X�̐��B
	};
}