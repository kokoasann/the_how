/*!
 * @brief	�X�L�����f�������_���[
 */

#pragma once


namespace tkEngine{
namespace prefab{
	class CSkinModelRender : public IGameObject {
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CSkinModelRender() {}
		/*!
		* @brief	�������B
		*@param[in]	filePath	�t�@�C���p�X�B
		*@param[in]	animationClips		�A�j���[�V�����N���b�v�B
		*@param[in]	numAnimClip			�A�j���[�V�����N���b�v�̐��B
		*@param[in]	enUpdateAxis		fbx�̏�����B
		*/
		void Init(const wchar_t* filePath,
			CAnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			CSkinModel::EnFbxUpAxis fbxUpAxis = CSkinModel::enFbxUpAxisZ);
		
		/*!
		 * @brief	�X�V�O�ɌĂ΂��֐��B
		 */
		bool Start() override final;
		/*!
		 * @brief	�X�V�B
		 */
		void Update() override final;
		/*!
		 * @brief	�`��B
		 */
		void Render(CRenderContext& rc) override final;
		/*!
		* @brief	�A�j���[�V�������Đ��B
		*@param[in]	clipNo	�A�j���[�V�����N���b�v�̔ԍ��B�R���X�g���N�^�ɓn����animClipList�̕��тƂȂ�B
		*@param[in]	interpolateTime		�⊮����(�P�ʁF�b)
		*/
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		/*!
		* @brief	�A�j���[�V�����̍Đ����H
		*/
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}
		/*!
		* @brief	�V���h�E�L���X�^�[�̃t���O��ݒ�B
		*@param[in]	flag	�V���h�E�L���X�^�[�̃t���O�B
		*/
		void SetShadowCasterFlag(bool flag)
		{
			m_skinModel.SetShadowCasterFlag(flag);
		}
		/*!
		* @brief	�V���h�E���V�[�o�[�̃t���O��ݒ�B
		*@param[in]	flag	�V���h�E���V�[�o�[�̃t���O�B
		*/
		void SetShadowReceiverFlag(bool flag)
		{
			m_skinModel.SetShadowReceiverFlag(flag);
		}
		/*!
		*@brief	�t���[�Y�����Ă���{�[���̕��s�ړ��ʂ��擾�B
		*@details
		* �ŏI�|�[�Y�̃A�j���[�V���������B
		*/
		CVector3 GetFreezeBoneTranslate() const
		{
			return m_animation.GetFreezeBoneTranslate();
		}
		/*!
		*@brief	�A�j���[�V�����C�x���g���X�i�[��o�^�B
		*@return
		* �o�^���ꂽ���X�i�[�B
		*/
		void AddAnimationEventListener(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}
		/*!
		*@brief	���W��ݒ�B
		*/
		void SetPosition(const CVector3& position)
		{
			m_position = position;
		}
		const CVector3& GetPosition() const 
		{
			return m_position;
		}
		/*!
		*@brief	��]��ݒ�B
		*/
		void SetRotation(const CQuaternion& rotation)
		{
			m_rotation = rotation;
		}
		const CQuaternion& GetRotation() const
		{
			return m_rotation;
		}
		/*!
		*@brief	�g�嗦��ݒ�B
		*/
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
		const CVector3& GetScale() const
		{
			return m_scale;
		}
		/*!
		*@brief	�X�L�����f���f�[�^���擾�B
		*/
		CSkinModelData& GetSkinModelData() 
		{
			return m_skinModelData;
		}
		const CSkinModelData& GetSkinModelData() const
		{
			return m_skinModelData;
		}
		/*!
		*@brief	�X�L�����f���擾�B
		*/
		CSkinModel& GetSkinModel()
		{
			return m_skinModel;
		}
		const CSkinModel& GetSkinModel() const
		{
			return m_skinModel;
		}
		/*!
		*@brief	���f���}�e���A���̌����B
		*@param[in]	findEffect		�}�e���A�������������ɌĂ΂��R�[���o�b�N�֐�
		*/
		void FindMaterial(CSkinModelData::OnFindMaterial findMaterial) const
		{
			m_skinModel.FindMaterial(findMaterial);
		}
		/*!
		*@brief	�A�j���[�V�����̍X�V�t���O��ݒ�B
		*/
		void SetUpdateAnimationFlag(bool flag)
		{
			m_isUpdateAnimation = flag;
		}
		/*!
		* @brief	�A�j���[�V�����̏������B
		*/
		void InitAnimation(CAnimationClip* animationClips, int numAnimationClips);
	private:
		CAnimationClip*				m_animationClips = nullptr;			//!<�A�j���[�V�����N���b�v�B
		int							m_numAnimationClips = 0;			//!<�A�j���[�V�����N���b�v�̐��B
		CVector3 					m_position = CVector3::Zero;		//!<���W�B
		CQuaternion	 				m_rotation = CQuaternion::Identity;	//!<��]�B
		CVector3					m_scale = CVector3::One;			//!<�g�嗦�B
		CSkinModel::EnFbxUpAxis		m_enFbxUpAxis = CSkinModel::enFbxUpAxisZ;	//!<FBX�̏�����B
		CAnimation					m_animation;						//!<�A�j���[�V�����B
		CSkinModel					m_skinModel;						//!<�X�L�����f���B
		CSkinModelData				m_skinModelData;					//!<�X�L�����f���f�[�^�B
		const std::wstring			m_filePath;							//!<�t�@�C���p�X�B
		bool						m_isUpdateAnimation = true;			//!<�A�j���[�V�������X�V����H
	};
}
}