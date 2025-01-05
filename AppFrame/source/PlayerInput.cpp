/* 2024.12.08 ��򕗏� �t�@�C��"��"�쐬 */

#include "PlayerInput.h"
#include "AppConstantDefine.h"
#include "AppVariableDefine.h"
#include "AppFunctionDefine.h"

/* �v���C���[�̓��͎擾�N���X�̒�` */

// �R���X�g���N�^
PlayerInput::PlayerInput()
{
	/* ������ */
	gstJoypadInputData		= {};						// �W���C�p�b�h
	gstKeyboardInputData	= {};						// �L�[�{�[�h���}�E�X
	gucTriggerThreshold		= INIT_TRIGGER_THRESHOLD;	// �g���K�[���͂�臒l
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
	// ��XInput��O��Ƃ��Ă��邽�߁ADirectInput�͔�Ή�

	/* �O��̓��͂�ۑ� */
	Struct_Input::PLAYER_INPUT_JOYPAD pOldJoypadInput = gstJoypadInputData;

	/* �W���C�p�b�h(1��)����̓��͓��e���擾(XInput) */
	XINPUT_STATE stXInputState;
	GetJoypadXInputState(DX_INPUT_PAD1, &stXInputState);

	/* �{�^���̓��͏��� */
	{
		/* �z�[���h���͏����擾 */
		for (int i = 0; i < 16; i++)
		{
			gstJoypadInputData.cgInput[INPUT_HOLD][i] = stXInputState.Buttons[i];
		}

		/* �g���K���͏����擾 */
		for (int i = 0; i < 16; i++)
		{
			gstJoypadInputData.cgInput[INPUT_TRG][i] = (gstJoypadInputData.cgInput[INPUT_HOLD][i] ^ pOldJoypadInput.cgInput[INPUT_HOLD][i]) & gstJoypadInputData.cgInput[INPUT_HOLD][i];
		}

		/* �����[�X���͏����擾 */
		for (int i = 0; i < 16; i++)
		{
			gstJoypadInputData.cgInput[INPUT_REL][i] = (gstJoypadInputData.cgInput[INPUT_HOLD][i] ^ pOldJoypadInput.cgInput[INPUT_HOLD][i]) & pOldJoypadInput.cgInput[INPUT_HOLD][i];
		}
	}
	
	/* �g���K�[�̓��͏��� */
	{
		/* �z�[���h���͏����擾 */
		{
			/* ���͒l��臒l�ȏ�ł��邩���� */
			gstJoypadInputData.bgTrigger[INPUT_HOLD][INPUT_LEFT]	= PUBLIC_PROCESS::bCheckAboveThreshold(stXInputState.LeftTrigger, gucTriggerThreshold);
			gstJoypadInputData.bgTrigger[INPUT_HOLD][INPUT_RIGHT]	= PUBLIC_PROCESS::bCheckAboveThreshold(stXInputState.RightTrigger, gucTriggerThreshold);
		}

		/* �g���K���͏����擾 */
		{
			/* �g���K�[�̓��͂��ω����������� */
			gstJoypadInputData.bgTrigger[INPUT_TRG][INPUT_LEFT]		= gstJoypadInputData.bgTrigger[INPUT_TRG][INPUT_LEFT]	^ pOldJoypadInput.bgTrigger[INPUT_HOLD][INPUT_LEFT];
			gstJoypadInputData.bgTrigger[INPUT_TRG][INPUT_RIGHT]	= gstJoypadInputData.bgTrigger[INPUT_TRG][INPUT_RIGHT]	^ pOldJoypadInput.bgTrigger[INPUT_HOLD][INPUT_RIGHT];
		}
		
		/* �����[�X���͏����擾 */
		{
			/* �g���K�[�̓��͂��ω����������� */
			gstJoypadInputData.bgTrigger[INPUT_REL][INPUT_LEFT]		= gstJoypadInputData.bgTrigger[INPUT_TRG][INPUT_LEFT]	^ pOldJoypadInput.bgTrigger[INPUT_HOLD][INPUT_LEFT];
			gstJoypadInputData.bgTrigger[INPUT_REL][INPUT_RIGHT]	= gstJoypadInputData.bgTrigger[INPUT_TRG][INPUT_RIGHT]	^ pOldJoypadInput.bgTrigger[INPUT_HOLD][INPUT_RIGHT];
		}
	}

	/* �A�i���O�X�e�B�b�N�̓��͗ʂ��擾 */
	{
		gstJoypadInputData.sAnalogStickX[INPUT_LEFT]	= stXInputState.ThumbLX;	// ���X�e�B�b�NX��
		gstJoypadInputData.sAnalogStickY[INPUT_LEFT]	= stXInputState.ThumbLY;	// ���X�e�B�b�NY��
		gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]	= stXInputState.ThumbRX;	// �E�X�e�B�b�NX��
		gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]	= stXInputState.ThumbRY;	// �E�X�e�B�b�NY��
	}
}

// ���͎擾_�L�[�{�[�h���}�E�X
void PlayerInput::InputKeyboard()
{
	/* �L�[�{�[�h���}�E�X�p�̓��͎擾 */

	/* �O��̓��͂�ۑ� */
	Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE pOldKeyboardInput = gstKeyboardInputData;

	/* �L�[�{�[�h�̓��͏��� */
	{
		/* �L�[�{�[�h����̃z�[���h���͏��𓾂� */
		GetHitKeyStateAll(gstKeyboardInputData.cgInput[INPUT_HOLD]);

		for (int i = 0; i < 256; i++)
		{
			/* �g���K���͏��̐��� */
			gstKeyboardInputData.cgInput[INPUT_TRG][i] = (gstKeyboardInputData.cgInput[INPUT_HOLD][i] ^ pOldKeyboardInput.cgInput[INPUT_HOLD][i]) & gstKeyboardInputData.cgInput[INPUT_HOLD][i];

			/* �����[�X���͏��̐��� */
			gstKeyboardInputData.cgInput[INPUT_REL][i] = (gstKeyboardInputData.cgInput[INPUT_HOLD][i] ^ pOldKeyboardInput.cgInput[INPUT_HOLD][i]) & pOldKeyboardInput.cgInput[INPUT_HOLD][i];
		}
	}

	/* �}�E�X�̓��͏��� */
	{
		/* �}�E�X�̃z�[���h���͏��𓾂� */
		gstKeyboardInputData.igInput[INPUT_HOLD] = GetMouseInput();

		/* �}�E�X�̃g���K���͏��̐��� */
		gstKeyboardInputData.igInput[INPUT_TRG] = (gstKeyboardInputData.igInput[INPUT_HOLD] ^ pOldKeyboardInput.igInput[INPUT_HOLD]) & gstKeyboardInputData.igInput[INPUT_HOLD];

		/* �}�E�X�̃����[�X���͏��̐��� */
		gstKeyboardInputData.igInput[INPUT_REL] = (gstKeyboardInputData.igInput[INPUT_HOLD] ^ pOldKeyboardInput.igInput[INPUT_HOLD]) & pOldKeyboardInput.igInput[INPUT_HOLD];

		/* �}�E�X���W�擾 */
		int iMouseX, iMouseY;	// �}�E�X���W
		GetMousePoint(&iMouseX, &iMouseY);

		/* �}�E�X���W�ݒ� */
		gstKeyboardInputData.iMouseX = iMouseX;
		gstKeyboardInputData.iMouseY = iMouseY;

		/* �}�E�X��Ԏ擾 */
		if (gbUseMouseFlg == false)
		{
			// �}�E�X�g�p�t���O�������ł���Ȃ��
			/* �}�E�X���_�ݒ� */
			// ���}�E�X���W�̒��S�����_�Ƃ��Ĉړ��ʂ��擾����
			int iMouseOriginX =	SCREEN_SIZE_WIDE	/ 2;
			int iMouseOriginY =	SCREEN_SIZE_HEIGHT	/ 2;

			/* �}�E�X�ړ��ʑ��� */
			gstKeyboardInputData.iMouseMoveX = iMouseX - iMouseOriginX;
			gstKeyboardInputData.iMouseMoveY = iMouseY - iMouseOriginY;

			/* �}�E�X���W���Z�b�g */
			SetMousePoint(iMouseOriginX, iMouseOriginY);

			/* �}�E�X�J�[�\���\���𖳌��� */
			SetMouseDispFlag(FALSE);
		}
		else
		{
			// �}�E�X�g�p�t���O���L���ł���Ȃ��
			/* �}�E�X�ړ��ʑ��� */
			gstKeyboardInputData.iMouseMoveX = iMouseX - pOldKeyboardInput.iMouseX;
			gstKeyboardInputData.iMouseMoveY = iMouseY - pOldKeyboardInput.iMouseY;

			/* �}�E�X�J�[�\���\����L���� */
			SetMouseDispFlag(TRUE);
		}
	}
}
