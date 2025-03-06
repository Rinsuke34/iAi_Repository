/* 2024.12.22 ��򕗏� �t�@�C���쐬 */
/* 2025.01.21 �e�r�듹 �萔���ǉ� */

#pragma once
#include <string>

/* ���͊Ǘ��p�̍\���̂�萔�̐錾���s�� */

/* ���͊Ǘ��p�̒萔 */
/* ���͋@�� */
static const int INPUT_EQUIPMENT_JOYPAD			= 0;	// �W���C�p�b�h
static const int INPUT_EQUIPMENT_JOYPAD_TRIGGER	= 1;	// �W���C�p�b�h(�g���K�[)
static const int INPUT_EQUIPMENT_KEYBOARD		= 2;	// �L�[�{�[�h
static const int INPUT_EQUIPMENT_MOUSE			= 3;	// �}�E�X

/* ���͓��e */
// UI����
static const int UI_UP		= 0;	// ��
static const int UI_DOWN	= 1;	// ��
static const int UI_LEFT	= 2;	// ��
static const int UI_RIGHT	= 3;	// �E
static const int UI_DECID	= 4;	// ����
static const int UI_CANCEL	= 5;	// �L�����Z��
static const int UI_PAUSE	= 6;	// �|�[�Y
static const int UI_ANY		= 7;	// �C�ӂ̃{�^��

// �Q�[������
static const int GAME_JUMP		= 0;	// �W�����v
static const int GAME_ATTACK	= 1;	// �U��
static const int GAME_AIM		= 2;	// �G�C��(�\��)
static const int GAME_RESET		= 3;	// �J�������Z�b�g
static const int GAME_DODGE		= 4;	// ���
static const int GAME_FORWARD	= 5;	// �O�i(�L�[�{�[�h���}�E�X��p)
static const int GAME_BACK		= 6;	// ���(�L�[�{�[�h���}�E�X��p)
static const int GAME_LEFT		= 7;	// ���ړ�(�L�[�{�[�h���}�E�X��p)
static const int GAME_RIGHT		= 8;	// �E�ړ�(�L�[�{�[�h���}�E�X��p)

/* ���̓R�[�h(�I���W�i�������p) */
// �W���C�p�b�h(XInput�p)
static const int XINPUT_TRIGGER_LEFT	= 0;	// ���g���K�[
static const int XINPUT_TRIGGER_RIGHT	= 1;	// �E�g���K�[

/* ���ǉ� */
const float STICK_DEAD_ZONE = 0.01f; //�X�e�B�b�N���͂̃f�b�h�]�[���i�͈́F�͈́F0 �` 32767�j/*2025.01.09 �e�r�듹 ���ǉ� */

/* ���͊Ǘ��p�̍\���� */

namespace Struct_Json_Input
{
	/* ���͏�� */
	struct INPUT_INFO
	{
		int			iInput;			// ���̓R�[�h
		int			iEquipmentType;	// ���͋@��̎��		
		std::string pcName;			// ���̖͂���
	};

	/* �L�[�R���t�B�O��� */
	struct CONFIG_INFO
	{
		int			iGameControl;	// �Q�[������̎��
		int			iInput;			// ���̓R�[�h
		int			iEquipmentType;	// ���͋@��̎��
	};

	/* Json�t�@�C���ǂݍ��ݗp��� */
	struct CONFIG_JSON
	{
		int			iGameControl;		// �Q�[������̎��
		std::string	pcControlName;		// ���̖͂���
		bool		bKeyboardMouseOnly;	// �L�[�{�[�h���}�E�X��p
	};
}
