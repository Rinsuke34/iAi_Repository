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

		void Effect_Load(std::string effectName);		// �G�t�F�N�g�ǂݍ���
		void Effect_PosUpdate();						// �G�t�F�N�g�ʒu�X�V(���ݍ��W�Ɉړ�)
		void Effect_RotationUpdate();					// �G�t�F�N�g��]�ʍX�V(���݉�]�ɐݒ�)

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		int iEffectHandle_Resource;	// �G�t�F�N�g�n���h��(���\�[�X)
		int iEffectHandle_Play;		// �G�t�F�N�g�n���h��(���s)
};
