/* 2025.02.24 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"

/* ���ׂẲ�ʃG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̐錾 */

// ��ʃG�t�F�N�g�x�[�X�N���X
class ScreenEffect_Base
{
	public:
		ScreenEffect_Base();				// �R���X�g���N�^
		virtual ~ScreenEffect_Base()	{};	// �f�X�g���N�^

		void	Update(int iGrHandle_Screen);	// �X�V

		bool	bGetDeleteFlg() { return this->bDeleteFlg; };	// �폜�t���O���擾

	protected:
		/* �֐� */
		virtual void	ScreenEffectDraw(int iGrHandle_Screen) {};	// ��ʃG�t�F�N�g�`��(�����͑Ώۂ̉摜�̃n���h��)

		/* �ϐ� */
		bool bDeleteFlg;	// �폜�t���O(�L���Ȃ��ʃG�t�F�N�g�N���X���폜)
		int iDeleteTime;	// �폜����(�t���[����)
};
