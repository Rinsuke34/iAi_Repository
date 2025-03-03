/* 2025.02.02 �t�@�C���쐬 ��򕗏� */
/* 2025.02.23 �e�r�듹	�J�������䏈���C�� */

#include "SceneStage.h"

/* �X�e�[�W�N���X�̒�`(�J�������䕔��) */

// �J�����ݒ�
void SceneStage::SetCamera()
{
	/* �J�������[�h���ύX����Ă��邩�m�F */
	if (this->StageStatusList->iGetCameraMode() != this->StageStatusList->iGetCameraMode_Old())
	{
		// �ύX����Ă���ꍇ
		/* �J�������W�̐��`�ۊǗp�J�E���g������������ */
		this->StageStatusList->SetCameraPositionLeapCount(0);

		/* ���݂̃J�����̍��W���ړ��O���W�Ƃ��Đݒ肷�� */
		this->StageStatusList->SetCameraPosition_Start(this->StageStatusList->vecGetCameraPosition());
	}

	/* �J�����ݒ�Ŏg�p����ϐ��̒�` */
	float fChangeCameraRatio = 1.f;	// ���͂ɂ��J������]�{��(0�Ȃ�v���C���[����ŉ�]�ł��Ȃ��Ȃ�)

	/* �J�������[�h�ɉ����ď�����ύX */
	switch (this->StageStatusList->iGetCameraMode())
	{
		/* �t���[ */
		case CAMERA_MODE_FREE:
			/* �J�����ݒ� */
			SetCamera_Free();
			break;

		/* �Œ� */
		case CAMERA_MODE_LOCK:
			/* �J������]�{����ύX */
			fChangeCameraRatio = 0.f;
			break;

		/* �\��(�Y�[��) */
		case CAMERA_MODE_AIM_MELEE:
			/* �J������]�{����ύX */
			fChangeCameraRatio = 0.5f;

			/* �J�����ݒ� */
			SetCamera_Aim_Melee();
			break;

		/* �\��(�N�i�C�\��) */
		case CAMERA_MODE_AIM_KUNAI:
			/* �J������]�{����ύX */
			fChangeCameraRatio = 0.5f;

			/* �J�����ݒ� */
			SetCamera_Aim_Kunai();
			break;

		/* �^�C�g�� */
		case CAMERA_MODE_TITLE:
			/* �J������]�{����ύX */
			fChangeCameraRatio = 0.f;

			/* �J�����ݒ� */
			SetCamera_Title();
			break;

		/* �X�e�[�W�N���A */
		case CAMERA_MODE_STAGECLEAR:
			/* �J������]�{����ύX */
			fChangeCameraRatio = 0.f;

			/* �J�����ݒ� */
			SetCamera_StageClear();
			break;
	}

	// ���f����ꍇ
	/* ���͂ɂ��J������]�̎擾���������{ */
	CameraRotateUpdata(fChangeCameraRatio);

	/* �J�������W�̕␳ */
	// ����u�Ő؂�ւ��ƈ�a�������邽�߁A�J�������W�ɕ�ԏ������s��
	CameraSmoothing();

	/* �����_�ł̃J�������[�h��ۑ� */
	this->StageStatusList->SetCameraMode_Old(this->StageStatusList->iGetCameraMode());
}

// �J�����ݒ�(�Z�b�g�A�b�v�p)
void SceneStage::SetCmaera_Setup()
{
	/* �O���[�o���A���r�G���g���C�g�J���[��ԐF�ɐݒ� */
	// ���f�t�H���g�̍��F���ƈÂ�����̂ŐԐF�ɕύX
	SetGlobalAmbientLight(GetColorF(1.0f, 0.0f, 0.0f, 0.0f));

	/* �J�����̎�O�Ɖ��̃N���b�v������ݒ� */
	// ���X�J�C�X�t�B�A���a(25000)����]�T���������������l�ɉ��ݒ�
	SetCameraNearFar(100.0f, 30000.f);

	/* �J�����ݒ� */
	SetCameraPositionAndTargetAndUpVec(this->StageStatusList->vecGetCameraPosition(), this->StageStatusList->vecGetCameraTarget(), this->StageStatusList->vecGetCameraUp());
}

// ���͂ɂ��J������]�ʎ擾
void SceneStage::CameraRotateUpdata(float fRate)
{
	// ����
	// fRate	:	��]�ʔ{��(�I�v�V�����ݒ�ɂ��{���Ƃ͕ʕ�)

	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX						= this->StageStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY						= this->StageStatusList->fGetCameraAngleY();						// Y����]��
	float fCameraRotationalSpeed_Controller	= this->StageStatusList->fGetCameraRotationalSpeed_Controller();	// ��]���x(�R���g���[���[)
	float fCameraRotationalSpeed_Mouse		= this->StageStatusList->fGetCameraRotationalSpeed_Mouse();			// ��]���x(�}�E�X)

	/* ���͂���J������]�ʂ��擾 */
	/* �}�E�X */
	fCameraAngleX -= gstKeyboardInputData.iMouseMoveX * fCameraRotationalSpeed_Mouse * fRate;
	fCameraAngleY -= gstKeyboardInputData.iMouseMoveY * fCameraRotationalSpeed_Mouse * fRate;

	/* �R���g���[���[ */
	fCameraAngleX += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]) * fRate;
	fCameraAngleY += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]) * fRate;

	/* Y���̉�]�p�x���� */
	float fAngleLimitUp		= this->StageStatusList->fGetCameraAngleLimitUp();		// ������̐����p�x
	float fAngleLimitDown	= this->StageStatusList->fGetCameraAngleLimitDown();	// �������̐����p�x

	if (fCameraAngleY > fAngleLimitUp)		{ fCameraAngleY = fAngleLimitUp; }		// ������̐����p�x�𒴂����琧���p�x�ɐݒ�
	if (fCameraAngleY < fAngleLimitDown)	{ fCameraAngleY = fAngleLimitDown; }	// �������̐����p�x�𒴂����琧���p�x�ɐݒ�

	/* ��]�ʂ��X�V */
	this->StageStatusList->SetCameraAngleX(fCameraAngleX);
	this->StageStatusList->SetCameraAngleY(fCameraAngleY);
}

// �J�����ݒ�(�t���[���[�h)
void SceneStage::SetCamera_Free()
{
	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX = this->StageStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY = this->StageStatusList->fGetCameraAngleY();						// Y����]��

	/* �v���C���[���W�擾 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* �J���������_�ݒ� */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT, 0));
	this->StageStatusList->SetCameraTarget(vecCameraTarget);

	vecCameraTarget.y += 20.f;

	/* �J�������W�ݒ� */
	float fRadius	= this->StageStatusList->fGetCameraRadius();			// �����_����̋���
	float fCameraX	= fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X���W
	float fCameraY	= fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y���W
	float fCameraZ	= fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z���W

	this->StageStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));
}

// �J�����ݒ�(�\��(�ߐڍU���\��))
void SceneStage::SetCamera_Aim_Melee()
{
	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX = this->StageStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY = this->StageStatusList->fGetCameraAngleY();						// Y����]��

	/* �v���C���[���W�擾 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* �J���������_�ݒ� */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT, 0));
	this->StageStatusList->SetCameraTarget(vecCameraTarget);

	vecCameraTarget.y += 20.f;

	/* �J�������W�ݒ� */
	//float fRadius = this->StageStatusList->fGetCameraRadius();			// �����_����̋���
	float fRadius = 200.f;			// �����_����̋���
	float fCameraX = fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X���W
	float fCameraY = fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y���W
	float fCameraZ = fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z���W

	this->StageStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));
}

/* 2025.02.23 �e�r�듹	�J�������䏈���C�� �J�n */
// �J�����ݒ�(�\��(�N�i�C�\��))
void SceneStage::SetCamera_Aim_Kunai()
{
	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX = this->StageStatusList->fGetCameraAngleX();		// X����]��
	float fCameraAngleY = this->StageStatusList->fGetCameraAngleY();		// Y����]��

	/* �v���C���[���W�擾 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* �J���������_�ݒ� */
	float fRadius	= 1000;				// �����_����̋���
	float fCameraX	= fRadius * +sinf(fCameraAngleX) + vecPlayerPos.x;	// X���W
	float fCameraY	= fRadius * +sinf(fCameraAngleY) + vecPlayerPos.y;	// Y���W
	float fCameraZ	= fRadius * -cosf(fCameraAngleX) + vecPlayerPos.z;	// Z���W

	this->StageStatusList->SetCameraTarget(VGet(fCameraX, fCameraY, fCameraZ));

	
	// �v���C���[�̉E�΂ߌ��ɃJ������z�u����

	/* �J�����̊�{�̍��� */ 
	float fHeightOffset = PLAYER_HEIGHT; 
	
	// �v���C���[�����؂�Ȃ��悤�Ɋp�x�ɉ����č�����ω�������
	/* �㉺�p�x�ɉ������␳ */ 
	float fHeightCorrection = fHeightOffset + 100.0f * -sinf(fCameraAngleY);

	// �v���C���[�̌����ɉ����ăJ�����̈ʒu��ݒ肷��
	/* �v���C���[���f���̏����̌�����Z���ɑ΂��ă}�C�i�X�����������Ă���Ƃ��� */
	/* �J�����̈ʒu�x�N�g�� */
	VECTOR vecCameraPos = { 0,0,-1 };
	
	/* �v���C���[�̊p�x����Y���̉�]�s������߂� */
	MATRIX matPlayerRotation = MGetRotY(-(this->PlayerStatusList->fGetPlayerAngleX()));

	/* �J�����ʒu�̐��������̕��s�ړ��s�� */
	MATRIX matHorizontalOffset = MGetTranslate(VGet(-100.0f, 0, 150.0f));

	/* �s�����Z���J�����ʒu�̍s������߂� */
	MATRIX matCameraPos = MMult(matHorizontalOffset, matPlayerRotation);

	/* �s����x�N�g���ɕϊ� */
	vecCameraPos = VTransform(vecCameraPos, matCameraPos);

	/* �J�����̍�����ݒ� */
	vecCameraPos.y = fHeightCorrection;

	/* �J�������W�ݒ� */
	this->StageStatusList->SetCameraPosition_Target(VAdd(vecPlayerPos, vecCameraPos));
}
/* 2025.02.23 �e�r�듹	�J�������䏈���C�� �I�� */

// �J�����ݒ�(�^�C�g��)
void SceneStage::SetCamera_Title()
{
	/* �J�����̒����_�ݒ� */
	this->StageStatusList->SetCameraTarget(this->vecCameraPositionInfo[iNowCameraFixedPositionNo].vecTarget);

	/* �J�����̍��W�ݒ� */
	this->StageStatusList->SetCameraPosition_Target(this->vecCameraPositionInfo[iNowCameraFixedPositionNo].vecPosition);
}

// �J�����ݒ�(�X�e�[�W�N���A)
void SceneStage::SetCamera_StageClear()
{
	/* �N���A���J�E���g��"�J������]"�ɐݒ肳�ꂽ�J�E���g�ł��邩�m�F */
	if ((this->iStageClear_Count == STAGECLEAR_COUNT_CAMERA_TRUN_FAST) || (this->iStageClear_Count == STAGECLEAR_COUNT_CAMERA_TRUN_LAST))
	{
		/* ���݂̃J�������W���擾 */
		VECTOR vecCameraPosition = this->StageStatusList->vecGetCameraPosition();
		VECTOR vecCameraTarget = this->StageStatusList->vecGetCameraTarget();

		/* ���݂̉�]�ʓ����擾 */
		float fCameraAngleX = this->StageStatusList->fGetCameraAngleX();						// X����]��
		float fCameraAngleY = this->StageStatusList->fGetCameraAngleY();						// Y����]��

		fCameraAngleX += 120.f;

		/* �X�V�����J�����A���O����ݒ� */
		this->StageStatusList->SetCameraAngleX(fCameraAngleX);

		/* �J�������W�ݒ� */
		float fRadius = this->StageStatusList->fGetCameraRadius();			// �����_����̋���
		float fCameraX = fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X���W
		float fCameraY = fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y���W
		float fCameraZ = fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z���W

		this->StageStatusList->SetCameraPosition_Target(VGet(fCameraX, fCameraY, fCameraZ));

	}
}

// �J�����␳
void SceneStage::CameraSmoothing()
{
	/* �J�������`��ԗp�J�E���g���擾 */
	int iCameraPositionLeapCount = this->StageStatusList->iGetCameraPositionLeapCount();

	/* �J�������`�⊮�p�J�E���g���ő�l�ɒB���Ă��邩 */
	if (iCameraPositionLeapCount < CAMERA_POSITION_LEAP_COUNT_MAX)
	{
		// �ő�l�ɒB���Ă��Ȃ��ꍇ
		/* �J�������`��Ԃ̊������擾 */
		float fLeapRatio = ((float)iCameraPositionLeapCount / (float)CAMERA_POSITION_LEAP_COUNT_MAX);

		/* �J�����̍��W(���`��Ԍ�)���Z�o */
		VECTOR vecStart		= this->StageStatusList->vecGetCameraPosition_Start();		// ���`�⊮�̈ړ��O���W
		VECTOR vecTarget	= this->StageStatusList->vecGetCameraPosition_Target();	// ���`�⊮�̈ړ�����W
		VECTOR vecCameraPosition;
		vecCameraPosition.x = vecStart.x + (vecTarget.x - vecStart.x) * fLeapRatio;
		vecCameraPosition.y = vecStart.y + (vecTarget.y - vecStart.y) * fLeapRatio;
		vecCameraPosition.z = vecStart.z + (vecTarget.z - vecStart.z) * fLeapRatio;

		/* �J�����̍��W(���`��Ԍ�)�����݂̃J�������W�ɐݒ� */
		this->StageStatusList->SetCameraPosition(vecCameraPosition);

		/* �J�E���g�����Z���Đݒ肷�� */
		this->StageStatusList->SetCameraPositionLeapCount(iCameraPositionLeapCount + 1);
	}
	else
	{
		// �ő�l�ɒB���Ă���ꍇ
		/* �J�����̍��W(�ړ���)�����݂̃J�������W�ɐݒ� */
		this->StageStatusList->SetCameraPosition(this->StageStatusList->vecGetCameraPosition_Target());

		this->StageStatusList->SetCameraPosition_Start(this->StageStatusList->vecGetCameraPosition_Target());
	}
}
