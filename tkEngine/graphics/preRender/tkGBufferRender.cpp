/*!
 * @brief	G-Buffer�̕`��B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkGBufferRender.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"

namespace tkEngine{
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CGBufferRender::CGBufferRender()
	{
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	CGBufferRender::~CGBufferRender()
	{
	}
	/*!
	*@brief	�������B
	*/
	void CGBufferRender::Init(const SGraphicsConfig& config)
	{
		CGraphicsEngine& ge = GraphicsEngine();
		
		//�@���o�b�t�@�̏������B
		m_GBuffer[enGBufferNormal].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_SNORM,
			DXGI_FORMAT_UNKNOWN,
			ge.GetMainRenderTargetMSAADesc()
		);
		

		//�e�}�b�v�̏������B
		m_GBuffer[enGBufferShadow].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			ge.GetMainRenderTargetMSAADesc()
		);

		//Z�o�b�t�@�̓��C�������_�����O�^�[�Q�b�g�̂��̂��g�p����B
		m_GBuffer[0].SetDepthStencilView(
			ge.GetMainRenderTarget().GetDepthStencilView()
		);

		m_shadowBlur.Init(m_GBuffer[enGBufferShadow].GetRenderTargetSRV(), 5.0f, config.shadowRenderConfig);
		
		m_cb.Create(NULL, sizeof(m_cbEntity));
	}
	
	void CGBufferRender::SendGBufferParamToGPU(CRenderContext& rc)
	{
		if (GraphicsEngine().GetShadowMap().GetSoftShadowLevel() == EnSoftShadowQualityLevel::enNone) {
			//�n�[�h�V���h�E�B
			rc.PSSetShaderResource(enSkinModelSRVReg_SoftShadowMap, m_GBuffer[enGBufferShadow].GetRenderTargetSRV());
		}
		else {
			//�\�t�g�V���h�E
			rc.PSSetShaderResource(enSkinModelSRVReg_SoftShadowMap, m_shadowBlur.GetResultSRV());
		}
	}
	
	void CGBufferRender::Render(CRenderContext& rc)
	{
		BeginGPUEvent(L"enRenderStep_RenderGBuffer");
		EnSoftShadowQualityLevel ssLevel = GraphicsEngine().GetShadowMap().GetSoftShadowLevel();

		//�e�𗎂Ƃ����߂̏���]���B
		GraphicsEngine().GetShadowMap().SendShadowReceiveParamToGPU(rc);

		rc.SetRenderStep(enRenderStep_RenderGBuffer);

		m_cbEntity.isPCFShadowMap = ssLevel == EnSoftShadowQualityLevel::eSSSS_PCF;
		rc.UpdateSubresource(m_cb, &m_cbEntity);

		rc.PSSetConstantBuffer(enSkinModelCBReg_GBuffer, m_cb);
		//�����_�����O�^�[�Q�b�g�̃o�b�N�A�b�v���擾����B
		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);

		//�����_�����O�^�[�Q�b�g��ύX����B
		CRenderTarget* renderTargets[] = {
			&m_GBuffer[enGBufferNormal],
			&m_GBuffer[enGBufferShadow],
		};
		rc.OMSetRenderTargets(enGBufferNum, renderTargets);
		//Shadow�o�b�t�@���N���A�B
		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		rc.ClearRenderTargetView(1, clearColor);

		for (auto& skinModel : m_skinModels) {
			skinModel->Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
		}
		//MSAA���]���u�B
		for (auto& rt : renderTargets) {
			rt->ResovleMSAATexture(rc);
		}

		if (ssLevel == EnSoftShadowQualityLevel::eSSSS
			|| ssLevel == EnSoftShadowQualityLevel::eSSSS_PCF
		) {
			//�X�N���[���X�y�[�X�\�t�g�V���h�E�B
			//�e�}�b�v�Ƀu���[��������B
			m_shadowBlur.Execute(rc);
		}

		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
		m_skinModels.clear();

		EndGPUEvent();
	}
}