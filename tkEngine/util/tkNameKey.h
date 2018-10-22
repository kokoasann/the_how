#pragma once

#include "tkEngine/Util/tkUtil.h"

namespace tkEngine {
	
	class NameKey {
		std::string m_name;			//!<���O
		unsigned int m_hashCode = 0;	//!<�n�b�V���l�B
	public:
		NameKey(){}
		NameKey( const char* name )
		{
			Init(name);
		}
		//�������B
		void Init(const char* name)
		{
			if (name != nullptr) {
				m_name = name;
				//���O���n�b�V���l�ɕϊ��B
				m_hashCode = CUtil::MakeHash(name);
			}
		}
		//�n�b�V���R�[�h���擾�B
		unsigned int GetHashCode() const
		{
			return m_hashCode;
		}
		//���O���擾�B
		const char* GetName() const
		{
			return m_name.c_str();
		}
	};
}
