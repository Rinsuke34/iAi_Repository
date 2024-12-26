/* 2024.12.08 ��򕗏� �t�@�C��"��"�쐬 */

#include "PlayerInput.h"
#include "AppConstantDefine.h"
#include "AppVariableDefine.h"

/* �v���C���[�̓��͎擾�N���X�̒�` */

// �R���X�g���N�^
PlayerInput::PlayerInput()
{
	/* ������ */
	gstJoypadInputData			= {};	// �W���C�p�b�h
	gstKeyboardInputData		= {};	// �L�[�{�[�h���}�E�X
}

// �v���C���[�̓��͎擾
void PlayerInput::Input()
{
	/* �W���C�p�b�h�̓��͎擾 */
	InputJoypad();

	/* �L�[�{�[�h���}�E�X�̓��͎擾 */
	InputKeyboard();
}

// ���͎擾_�W���C�p�b�h
void PlayerInput::InputJoypad()
{
	/* �W���C�p�b�h�p�̓��͎擾 */

	/* �O��̓��͂�ۑ� */
	Struct_Input::PLAYER_INPUT_JOYPAD pOldJoypadInput = gstJoypadInputData;

	/* �W���C�p�b�h(1��)����̃z�[���h���͏��𓾂� */
	gstJoypadInputData.igInput[INPUT_HOLD] = GetJoypadInputState(DX_INPUT_PAD1);

	/* �g���K���͏��̐��� */
	gstJoypadInputData.igInput[INPUT_TRG] = (gstJoypadInputData.igInput[INPUT_HOLD] ^ pOldJoypadInput.igInput[INPUT_HOLD]) & gstJoypadInputData.igInput[INPUT_HOLD];

	/* �����[�X���͏��̐��� */
	gstJoypadInputData.igInput[INPUT_REL] = (gstJoypadInputData.igInput[INPUT_HOLD] ^ pOldJoypadInput.igInput[INPUT_HOLD]) & pOldJoypadInput.igInput[INPUT_HOLD];

	/* ���A�i���O�X�e�B�b�N�̓��͗ʂ��擾 */
	GetJoypadAnalogInput(&gstJoypadInputData.iXAnalog, &gstJoypadInputData.iYAnalog, DX_INPUT_PAD1);
}

// ���͎擾_�L�[�{�[�h���}�E�X
void PlayerInput::InputKeyboard()
{
	/* �L�[�{�[�h���}�E�X�p�̓��͎擾 */

	/* �O��̓��͂�ۑ� */
	Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE pOldKeyboardInput = gstKeyboardInputData;

	/* �L�[�{�[�h����̃z�[���h���͏��𓾂� */
	GetHitKeyStateAll(gstKeyboardInputData.cgInput[INPUT_HOLD]);
	
	for (int i = 0; i < 256; i++)
	{
		/* �g���K���͏��̐��� */
		gstKeyboardInputData.cgInput[INPUT_TRG][i] = (gstKeyboardInputData.cgInput[INPUT_HOLD][i] ^ pOldKeyboardInput.cgInput[INPUT_HOLD][i]) & gstKeyboardInputData.cgInput[INPUT_HOLD][i];

		/* �����[�X���͏��̐��� */
		gstKeyboardInputData.cgInput[INPUT_REL][i] = (gstKeyboardInputData.cgInput[INPUT_HOLD][i] ^ pOldKeyboardInput.cgInput[INPUT_HOLD][i]) & pOldKeyboardInput.cgInput[INPUT_HOLD][i];
	}

	/* �}�E�X�̃z�[���h���͏��𓾂� */
	gstKeyboardInputData.igInput[INPUT_HOLD] = GetMouseInput();

	/* �}�E�X�̃g���K���͏��̐��� */
	gstKeyboardInputData.igInput[INPUT_TRG] = (gstKeyboardInputData.igInput[INPUT_HOLD] ^ pOldKeyboardInput.igInput[INPUT_HOLD]) & gstKeyboardInputData.igInput[INPUT_HOLD];

	/* �}�E�X�̃����[�X���͏��̐��� */
	gstKeyboardInputData.igInput[INPUT_REL] = (gstKeyboardInputData.igInput[INPUT_HOLD] ^ pOldKeyboardInput.igInput[INPUT_HOLD]) & pOldKeyboardInput.igInput[INPUT_HOLD];

	/* �}�E�X���W�擾 */
	int iMouseX, iMouseY;	// �}�E�X���W
	GetMousePoint(&iMouseX, &iMouseY);

	/* �}�E�X���_�ݒ� */
	// ���}�E�X���W�̒��S�����_�Ƃ��Ĉړ��ʂ��擾����
	int iMouseOriginX = SCREEN_SIZE::WIDE	/ 2;
	int iMouseOriginY = SCREEN_SIZE::HEIGHT	/ 2;

	/* �}�E�X�ړ��ʑ��� */
	gstKeyboardInputData.iMouseMoveX = iMouseX - iMouseOriginX;
	gstKeyboardInputData.iMouseMoveY = iMouseY - iMouseOriginY;

	/* �}�E�X���W���Z�b�g */
	SetMousePoint(iMouseOriginX, iMouseOriginY);

	// �}�E�X�J�[�\�����\���ɂ���
	SetMouseDispFlag(FALSE);
}
