/*!
 * @brief	G-Buffer��`��B
 */

#pragma once

#include "tkEngine/graphics/tkShadowBlur.h"

namespace tkEngine{
	/*!
	 * @brief	G-Buffer�B
	 */
	class CGBufferRender : Noncopyable{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CGBufferRender();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CGBufferRender();
		/*!
		 *@brief	�������B
		 */
		void Init(const SGraphicsConfig& config);
		/*!
		*@brief	�X�L�����f����ǉ��B
		*/
		void AddSkinModel(CSkinModel* skinModel)
		{
			m_skinModels.push_back(skinModel);
		}
		/*!
		 * @brief	�`��B
		 */
		void Render(CRenderContext& rc);
		/*!
		*@brief	GBuffer�̃p�����[�^��GPU�ɓ]���B
		*/
		void SendGBufferParamToGPU(CRenderContext& rc);
	private:
		enum EnGBuffer{
			enGBufferNormal,	//!<�@���B
			enGBufferShadow,	//!<�e�}�b�v�B
			enGBufferNum,		//!<G-Buffer�̐��B
		};
		//�萔�p�����[�^�B
		struct SCBParam {
			bool isPCFShadowMap;		//�e�}�b�v�����Ƃ���PCF���s���B
		};
		std::vector<CSkinModel*>	m_skinModels;	//!<�X�L�����f���̃��X�g�B
		CRenderTarget m_GBuffer[enGBufferNum];		//!<G-Buffer
		CShadowBlur m_shadowBlur;					//!<�e�}�b�v�ւ̃u���[�����B
		SCBParam m_cbEntity;
		CConstantBuffer m_cb;
	};
}
