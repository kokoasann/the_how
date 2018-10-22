/*!
 * @brief	�X�L�����f�������_���[
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelRender.h"

#include "tkEngine/graphics/tkPresetRenderState.h"


namespace tkEngine{
namespace prefab{

	void CSkinModelRender::Init(
		const wchar_t* filePath,
		CAnimationClip* animationClips,
		int numAnimationClips ,
		CSkinModel::EnFbxUpAxis fbxUpAxis)
	{
		m_enFbxUpAxis = fbxUpAxis;
		m_skinModelData.Load(filePath);
		m_skinModel.Init(m_skinModelData);
		InitAnimation(animationClips, numAnimationClips);
	}
	void CSkinModelRender::InitAnimation(CAnimationClip* animationClips, int numAnimationClips)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init(m_skinModel, m_animationClips, m_numAnimationClips);
		}
	}
	/*!
	 * @brief	�X�V�O�ɌĂ΂��֐��B
	 */
	bool CSkinModelRender::Start() 
	{
		return true;
	}
	/*!
	 * @brief	�X�V�B
	 */
	void CSkinModelRender::Update()
	{
		m_skinModel.Update(m_position, m_rotation, m_scale, m_enFbxUpAxis);
	}
	/*!
	 * @brief	�`��B
	 */
	void CSkinModelRender::Render(CRenderContext& rc)
	{
		//float blendFactor[4] = { 0.0f };

		//������������L���ɂ���B
		//rc.OMSetBlendState(AlphaBlendState::trans, blendFactor, 0xFFFFFFFF);

		//m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
		
		m_skinModel.Draw(rc);

		//�A���t�@�u�����f�B���O���I�t�ɂ���B
		//rc.OMSetBlendState(AlphaBlendState::disable, blendFactor, 0xFFFFFFFF);
	}
}
}