/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "CharacterBase.h"

/* �f�[�^���X�g */
#include "DataList_Input.h"

/* �v���C���[�N���X�̐錾 */

// �v���C���[�N���X
class CharacterPlayer : public CharacterBase
{
	public:
		CharacterPlayer();				// �R���X�g���N�^
		virtual ~CharacterPlayer() {};	// �f�X�g���N�^

		virtual void	Update();	// �X�V
		virtual void	Draw();		// �`��

	private:
	protected:
		/* �g�p����f�[�^���X�g */
		// ����f�[�^���X�g�T�[�o�[����擾����͔̂�����Ȃ��߁A�����ŕۑ����Ă���
		DataList_Input*	InputList;	// ���͊Ǘ�
};
