/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <DxLib.h>
#include <cstring>

/* �v���C���[�̓��͂��擾����N���X�̐錾 */

// ���͎擾�N���X
class PlayerInput
{
	public:
		PlayerInput();					// �R���X�g���N�^
		virtual ~PlayerInput() {};		// �f�X�g���N�^

		void	Input();				// �v���C���[�̓��͎擾

	private:
		/* �v���C���[���͎擾�n */
		void	InputJoypad();			// �W���C�p�b�h
		void	InputKeyboard();		// �L�[�{�[�h���}�E�X

	protected:
};
