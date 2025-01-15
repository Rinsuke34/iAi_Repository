/* 2025.01.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ObjectBase.h"
#include <EffekseerForDXLib.h>

/* ���ׂẴG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̐錾 */

// �G�t�F�N�g�x�[�X�N���X
class EffectBase : public ObjectBase
{
	public:
		EffectBase();			// �R���X�g���N�^
		virtual ~EffectBase();	// �f�X�g���N�^

		virtual void	Initialization()	override {};	// ������
		virtual void	Update()			override {};	// �X�V

		virtual void Effect_Load(std::string effectName);		// �G�t�F�N�g�ǂݍ���
		virtual void Effect_PosUpdate();						// �G�t�F�N�g�ʒu�X�V(vecPos��)

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		int iEffectHandle_Resource;	// �G�t�F�N�g�n���h��(���\�[�X)
		int iEffectHandle_Play;		// �G�t�F�N�g�n���h��(���s)
};
