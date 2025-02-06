/* 2025.02.02 �t�@�C���쐬 ��򕗏� */

#include "SceneStage.h"

/* �X�e�[�W�N���X�̒�`(�J�������䕔��) */

// �J�����ݒ�
void SceneStage::SetCamera()
{
	/* �O���[�o���A���r�G���g���C�g�J���[��ԐF�ɐݒ� */
	// ���f�t�H���g�̍��F���ƈÂ�����̂ŐԐF�ɕύX
	SetGlobalAmbientLight(GetColorF(1.0f, 0.0f, 0.0f, 0.0f));

	/* �J�������[�h���ύX����Ă��邩�m�F */
	if (this->PlayerStatusList->iGetCameraMode() != this->PlayerStatusList->iGetCameraMode_Old())
	{
		// �ύX����Ă���ꍇ
		/* �J�������W�̐��`�ۊǗp�J�E���g������������ */
		this->PlayerStatusList->SetCameraPositionLeapCount(0);

		/* ���݂̃J�����̍��W���ړ��O���W�Ƃ��Đݒ肷�� */
		this->PlayerStatusList->SetCameraPosition_Start(this->PlayerStatusList->vecGetCameraPosition());
	}

	/* �J�����ݒ�Ŏg�p����ϐ��̒�` */
	float fChangeCameraRatio = 1.f;	// ���͂ɂ��J������]�{��

	/* �J�������[�h�ɉ����ď�����ύX */
	switch (this->PlayerStatusList->iGetCameraMode())
	{
		/* �t���[ */
		case CAMERA_MODE_FREE:
			/* �J�����ݒ� */
			SetCamera_Free();
			break;

		/* �Œ� */
		case CAMERA_MODE_LOCK:
			/* �J�����ݒ� */
			SetCamera_Lock();
			break;

		/* �\��(�Y�[��) */
		case CAMERA_MODE_AIM:
			/* �J������]�{����ύX */
			fChangeCameraRatio = 0.5f;

			/* �J�����ݒ� */
			SetCamera_Aim();
			break;
	}

	/* ���͂ɂ��J������]�̎擾���������{ */
	CameraRotateUpdata(fChangeCameraRatio);

	/* �J�������W�̕␳ */
	// ����u�Ő؂�ւ��ƈ�a�������邽�߁A�J�������W�ɕ�ԏ������s��
	CameraSmoothing();

	/* �J�����ݒ� */
	SetCameraPositionAndTargetAndUpVec(this->PlayerStatusList->vecGetCameraPosition(), this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraUp());

	/* �����_�ł̃J�������[�h��ۑ� */
	this->PlayerStatusList->SetCameraMode_Old(this->PlayerStatusList->iGetCameraMode());
}

// ���͂ɂ��J������]�ʎ擾
void SceneStage::CameraRotateUpdata(float fRate)
{
	// ����
	// fRate	:	��]�ʔ{��(�I�v�V�����ݒ�ɂ��{���Ƃ͕ʕ�)

	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX						= this->PlayerStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY						= this->PlayerStatusList->fGetCameraAngleY();						// Y����]��
	float fCameraRotationalSpeed_Controller	= this->PlayerStatusList->fGetCameraRotationalSpeed_Controller();	// ��]���x(�R���g���[���[)
	float fCameraRotationalSpeed_Mouse		= this->PlayerStatusList->fGetCameraRotationalSpeed_Mouse();		// ��]���x(�}�E�X)

	/* ���͂���J������]�ʂ��擾 */
	/* �}�E�X */
	fCameraAngleX -= gstKeyboardInputData.iMouseMoveX * fCameraRotationalSpeed_Mouse * fRate;
	fCameraAngleY -= gstKeyboardInputData.iMouseMoveY * fCameraRotationalSpeed_Mouse * fRate;

	/* �R���g���[���[ */
	fCameraAngleX += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]) * fRate;
	fCameraAngleY += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]) * fRate;

	/* Y���̉�]�p�x���� */
	float fAngleLimitUp		= this->PlayerStatusList->fGetCameraAngleLimitUp();		// ������̐����p�x
	float fAngleLimitDown	= this->PlayerStatusList->fGetCameraAngleLimitDown();	// �������̐����p�x

	if (fCameraAngleY > fAngleLimitUp)		{ fCameraAngleY = fAngleLimitUp; }		// ������̐����p�x�𒴂����琧���p�x�ɐݒ�
	if (fCameraAngleY < fAngleLimitDown)	{ fCameraAngleY = fAngleLimitDown; }	// �������̐����p�x�𒴂����琧���p�x�ɐݒ�

	/* ��]�ʂ��X�V */
	this->PlayerStatusList->SetCameraAngleX(fCameraAngleX);
	this->PlayerStatusList->SetCameraAngleY(fCameraAngleY);
}

// �J�����ݒ�(�t���[���[�h)
void SceneStage::SetCamera_Free()
{
	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX = this->PlayerStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY = this->PlayerStatusList->fGetCameraAngleY();						// Y����]��

	/* �v���C���[���W�擾 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* �J���������_�ݒ� */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT, 0));
	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	vecCameraTarget.y += 20.f;

	/* �J�������W�ݒ� */
	float fRadius	= this->PlayerStatusList->fGetCameraRadius();			// �����_����̋���
	float fCameraX	= fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X���W
	float fCameraY	= fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y���W
	float fCameraZ	= fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z���W

	this->PlayerStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));
	//this->PlayerStatusList->SetCameraPosition(VGet(fCameraX, fCameraY, fCameraZ));
}

// �J�����ݒ�(�Œ胂�[�h)
void SceneStage::SetCamera_Lock()
{
	/* �ύX�͍s��Ȃ� */
}

// �J�����ݒ�(�\��(�Y�[��))
void SceneStage::SetCamera_Aim()
{
	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX = this->PlayerStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY = this->PlayerStatusList->fGetCameraAngleY();						// Y����]��

	/* �v���C���[���W�擾 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* �J���������_�ݒ� */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT, 0));
	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	vecCameraTarget.y += 20.f;

	/* �J�������W�ݒ� */
	//float fRadius = this->PlayerStatusList->fGetCameraRadius();			// �����_����̋���
	float fRadius = 200.f;			// �����_����̋���
	float fCameraX = fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X���W
	float fCameraY = fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y���W
	float fCameraZ = fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z���W

	this->PlayerStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));
}

// �J�����␳
void SceneStage::CameraSmoothing()
{
	/* �J�������`��ԗp�J�E���g���擾 */
	int iCameraPositionLeapCount = this->PlayerStatusList->iGetCameraPositionLeapCount();

	/* �J�������`�⊮�p�J�E���g���ő�l�ɒB���Ă��邩 */
	if (iCameraPositionLeapCount < CAMERA_POSITION_LEAP_COUNT_MAX)
	{
		// �ő�l�ɒB���Ă��Ȃ��ꍇ
		/* �J�������`��Ԃ̊������擾 */
		float fLeapRatio = ((float)iCameraPositionLeapCount / (float)CAMERA_POSITION_LEAP_COUNT_MAX);

		/* �J�����̍��W(���`��Ԍ�)���Z�o */
		VECTOR vecStart		= this->PlayerStatusList->vecGetCameraPosition_Start();		// ���`�⊮�̈ړ��O���W
		VECTOR vecTarget	= this->PlayerStatusList->vecGetCameraPosition_Target();	// ���`�⊮�̈ړ�����W
		VECTOR vecCameraPosition;
		vecCameraPosition.x = vecStart.x + (vecTarget.x - vecStart.x) * fLeapRatio;
		vecCameraPosition.y = vecStart.y + (vecTarget.y - vecStart.y) * fLeapRatio;
		vecCameraPosition.z = vecStart.z + (vecTarget.z - vecStart.z) * fLeapRatio;

		/* �J�����̍��W(���`��Ԍ�)�����݂̃J�������W�ɐݒ� */
		this->PlayerStatusList->SetCameraPosition(vecCameraPosition);

		/* �J�E���g�����Z���Đݒ肷�� */
		this->PlayerStatusList->SetCameraPositionLeapCount(iCameraPositionLeapCount + 1);
	}
	else
	{
		// �ő�l�ɒB���Ă���ꍇ
		/* �J�����̍��W(�ړ���)�����݂̃J�������W�ɐݒ� */
		this->PlayerStatusList->SetCameraPosition(this->PlayerStatusList->vecGetCameraPosition_Target());

		this->PlayerStatusList->SetCameraPosition_Start(this->PlayerStatusList->vecGetCameraPosition_Target());
	}
}
