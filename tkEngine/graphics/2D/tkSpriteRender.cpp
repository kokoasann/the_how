/*!
* @brief	�X�v���C�g�����_���[
*/

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/2D/tkSpriteRender.h"
#include "tkEngine/graphics/tkPresetRenderState.h"

namespace tkEngine {
	namespace prefab {
		
		void CSpriteRender::Init(const wchar_t* texFilePath, float w, float h, bool isDraw3D)
		{
			m_isDraw3D = isDraw3D;
			m_texture.CreateFromDDSTextureFromFile(texFilePath);
			m_sprite.Init(m_texture, w, h);
		}
		
		void CSpriteRender::Update()
		{
			m_sprite.SetTexture(m_texture);
			m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
		}
		void CSpriteRender::Render(CRenderContext& rc)
		{
			if (m_isDraw3D == true) {
				float blendFactor[4] = { 0.0f };
				//������������L���ɂ���B
				rc.OMSetBlendState(AlphaBlendState::trans, blendFactor, 0xFFFFFFFF);
				m_sprite.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
				//�A���t�@�u�����f�B���O���I�t�ɂ���B
				rc.OMSetBlendState(AlphaBlendState::disable, blendFactor, 0xFFFFFFFF);
			}
		}
		void CSpriteRender::PostRender(CRenderContext& rc)
		{
			if (m_isDraw3D == false) {
				m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
			}
		}
	}
}