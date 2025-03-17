/* 2025.02.02 �t�@�C���쐬 ��򕗏� */
/* 2025.02.23 �e�r�듹	�J�������䏈���C�� */
/* 2025.03.06 �e�r�듹	�J�������䏈���C�� */
/* 2025.03.16 ��򕗏�	�J�������䏈���C�� */

#include "SceneStage.h"

/* �X�e�[�W�N���X�̒�`(�J�������䕔��) */

/* 2025.03.06 �e�r�듹	�J�������䏈���C�� �J�n */
// �J�����ݒ菀��
void SceneStage::SetCamera_Setup()
{
	/* �J�������[�h���ύX�A���邢�̓J�����Œ���W���ύX����Ă��邩�m�F */
	if ((this->StageStatusList->iGetCameraMode() != this->StageStatusList->iGetCameraMode_Old()) ||
		(this->iNowCameraFixedPositionNo != this->iOldCameraFixedPositionNo))
	{
		// �ύX����Ă���ꍇ
		/* �J�����̐��`�ۊǗp�J�E���g������������ */
		this->StageStatusList->SetCameraPositionLeapCount(0);
		this->StageStatusList->SetCameraTargetLeapCount(0);

		/* ���݂̃J�����̍��W���ړ��O���W�Ƃ��Đݒ肷�� */
		this->StageStatusList->SetCameraPosition_Start(this->StageStatusList->vecGetCameraPosition());
		this->StageStatusList->SetCameraTarget_Start(this->StageStatusList->vecGetCameraTarget());
	}

	/* �J�����ݒ�Ŏg�p����ϐ��̒�` */
	int iCameraType			= INPUT_CAMERA_NORMAL;						// �J�����ړ��^�C�v
	int iCameraLeapCountMax	= CAMERA_POSITION_LEAP_COUNT_MAX_NORMAL;	// �J�������W�̕�ԃJ�E���g�ő�l

	/* �J�������[�h�ɉ����ď�����ύX */
	switch (this->StageStatusList->iGetCameraMode())
	{
		/* �t���[ */
		case CAMERA_MODE_NORMAL:
			/* �J�����ݒ� */
			SetCamera_Free();
			
			/* �J�������W�̕�ԃJ�E���g�ő�l���t���[�̒l�ɐݒ� */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_COUNT_MAX_NORMAL;
			break;

		/* �Œ� */
		case CAMERA_MODE_LOCK:
			/* �J�����ړ��^�C�v��"����"�ɐݒ� */
			iCameraType = INPUT_CAMERA_NONE;
			break;

		/* �\��(�Y�[��) */
		case CAMERA_MODE_AIM_MELEE:
			/* �J�����ړ��^�C�v��"�G�C��"�ɐݒ� */
			iCameraType = INPUT_CAMERA_AIM;

			/* �J�������W�̕�ԃJ�E���g�ő�l���ߋ����U��(��)�̒l�ɐݒ� */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_COUNT_MAX_MELEE;
			
			/* �J�����ݒ� */
			SetCamera_Aim_Melee();
			break;

		/* �\��(�N�i�C�\��) */
		case CAMERA_MODE_AIM_KUNAI:
			/* �J�����ړ��^�C�v��"�G�C��"�ɐݒ� */
			iCameraType = INPUT_CAMERA_AIM;

			/* �J�������W�̕�ԃJ�E���g�ő�l���������U���̒l�ɐݒ� */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_COUNT_MAX_PROJECTILE;

			/* �J�����ݒ� */
			SetCamera_Aim_Kunai();
			break;

		/* �^�C�g�� */
		case CAMERA_MODE_TITLE:
			/* �J�����ړ��^�C�v��"����"�ɐݒ� */
			iCameraType = INPUT_CAMERA_NONE;

			/* �J�������W�̕�ԃJ�E���g�ő�l���^�C�g���̒l�ɐݒ� */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_CONT_MAX_TITLE;
			/* �J�����ݒ� */
			SetCamera_Title();
			break;

		/* �X�e�[�W�N���A */
		case CAMERA_MODE_STAGECLEAR:
			/* �J�����ړ��^�C�v��"����"�ɐݒ� */
			iCameraType = INPUT_CAMERA_NONE;

			/* �J�������W�̕�ԃJ�E���g�ő�l���X�e�[�W�N���A�̒l�ɐݒ� */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_COUNT_MAX_STAGECLEAR;

			/* �J�����ݒ� */
			SetCamera_StageClear();
			break;

		/* �X�e�[�W�J�n */
		case CAMERA_MODE_STAGESTART:
			/* �J�����ړ��^�C�v��"����"�ɐݒ� */
			iCameraType = INPUT_CAMERA_NONE;

			/* �J�������W�̕�ԃJ�E���g�ő�l���X�e�[�W�N���A�̒l�ɐݒ� */
			iCameraLeapCountMax = CAMERA_POSITION_LEAP_COUNT_MAX_STAGESTART;

			/* �J�����ݒ� */
			SetCamera_StageStart();
			break;
	}

	// ���f����ꍇ
	/* ���͂ɂ��J������]�̎擾���������{ */
	CameraRotateUpdata(iCameraType);

	/* �J�������W�̕␳ */
	// ����u�Ő؂�ւ��ƈ�a�������邽�߁A�J�������W�ɕ�ԏ������s��
	CameraSmoothing(iCameraLeapCountMax);

	/* �����_�ł̃J�������[�h��ۑ� */
	this->StageStatusList->SetCameraMode_Old(this->StageStatusList->iGetCameraMode());

	/* �����_�ł̃J�����Œ���W�ԍ���ۑ� */
	this->iOldCameraFixedPositionNo = this->iNowCameraFixedPositionNo;
}
/* 2025.03.06 �e�r�듹	�J�������䏈���C�� �I�� */

// �J�����ݒ�
void SceneStage::SetCmaera()
{
	/* �O���[�o���A���r�G���g���C�g�J���[��ԐF�ɐݒ� */
	// ���f�t�H���g�̍��F���ƈÂ�����̂ŐԐF�ɕύX
	SetGlobalAmbientLight(GetColorF(0.5f, 0.5f, 0.5f, 0.0f));

	/* �J�����̎�O�Ɖ��̃N���b�v������ݒ� */
	// ���X�J�C�X�t�B�A���a(25000)����]�T���������������l�ɉ��ݒ�
	SetCameraNearFar(INIT_CAMERA_NEAR, INIT_CAMERA_FAR);

	/* �t�H�O�͈̔͂�ݒ� */
	SetFogEnable(TRUE);
	SetFogColor(256, 44, 42);
	SetFogStartEnd(INIT_CAMERA_FOG_START, INIT_CAMERA_FOG_END);

	/* �J�����ݒ� */
	SetCameraPositionAndTargetAndUpVec(this->StageStatusList->vecGetCameraPosition(), this->StageStatusList->vecGetCameraTarget(), this->StageStatusList->vecGetCameraUp());
}

// ���͂ɂ��J������]�ʎ擾
void SceneStage::CameraRotateUpdata(int iCameraType)
{
	// ����
	// iCameraType	:	�J�����ړ��^�C�v

	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX						= this->StageStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY						= this->StageStatusList->fGetCameraAngleY();						// Y����]��
	float fCameraRotationalSpeed_Controller	= this->StageStatusList->fGetCameraRotationalSpeed_Controller();	// ��]���x(�R���g���[���[)
	float fCameraRotationalSpeed_Mouse		= this->StageStatusList->fGetCameraRotationalSpeed_Mouse();			// ��]���x(�}�E�X)

	/* �I�v�V���������]�{�����擾 */
	float	fCameraSensitive[INPUT_TYPE_MAX];	// ��]�ʔ{��
	switch (iCameraType)
	{
		// �m�[�}�����
		case INPUT_CAMERA_NORMAL:
			/* ���͊��x���I�v�V��������擾 */
			fCameraSensitive[INPUT_TYPE_CONTROLLER]	= OptionList->fGetCameraSensitivity(INPUT_TYPE_CONTROLLER,	INPUT_CAMERA_MODE_NORMAL);
			fCameraSensitive[INPUT_TYPE_MOUSE]		= OptionList->fGetCameraSensitivity(INPUT_TYPE_MOUSE,		INPUT_CAMERA_MODE_NORMAL);
			break;

		// �G�C�����
		case INPUT_CAMERA_AIM:
			/* ���͊��x���I�v�V��������擾 */
			fCameraSensitive[INPUT_TYPE_CONTROLLER]	= OptionList->fGetCameraSensitivity(INPUT_TYPE_CONTROLLER,	INPUT_CAMERA_MODE_AIM);
			fCameraSensitive[INPUT_TYPE_MOUSE]		= OptionList->fGetCameraSensitivity(INPUT_TYPE_MOUSE,		INPUT_CAMERA_MODE_AIM);
			break;

		// ����(���͎�t����)���
		case INPUT_CAMERA_NONE:
			/* ���͊��x��0�ɐݒ� */
			fCameraSensitive[INPUT_TYPE_CONTROLLER]	= 0.f;
			fCameraSensitive[INPUT_TYPE_MOUSE]		= 0.f;
			break;
	}

	/* �I�v�V�������甽�]�ݒ���擾 */
	int		iCameraReverse[INPUT_TYPE_MAX][AXIS_MAX];	// ���]�ݒ�(1�Ȃ�ʏ�A-1�Ȃ甽�])
	for (int i = 0; i < INPUT_TYPE_MAX; ++i)
	{
		for (int j = 0; j < AXIS_MAX; ++j)
		{
			/* ���]�ݒ�ł��邩�m�F */
			// ��i�͓��̓^�C�v,j�͎�
			if (OptionList->bGetCameraInversion(i, j) == true)
			{
				// ���]�ݒ�ł���ꍇ
				iCameraReverse[i][j] = -1;
			}
			else
			{
				// �ʏ�ݒ�ł���ꍇ
				iCameraReverse[i][j] = 1;
			}
		}
	}

	/* ���͂���J������]�ʂ��擾 */
	/* �}�E�X */
	fCameraAngleX -= gstKeyboardInputData.iMouseMoveX * fCameraRotationalSpeed_Mouse * fCameraSensitive[INPUT_TYPE_MOUSE] * iCameraReverse[INPUT_TYPE_MOUSE][AXIS_X];
	fCameraAngleY -= gstKeyboardInputData.iMouseMoveY * fCameraRotationalSpeed_Mouse * fCameraSensitive[INPUT_TYPE_MOUSE] * iCameraReverse[INPUT_TYPE_MOUSE][AXIS_Y];

	/* �R���g���[���[ */
	fCameraAngleX -= fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]) * fCameraSensitive[INPUT_TYPE_CONTROLLER] * iCameraReverse[INPUT_TYPE_CONTROLLER][AXIS_X];
	fCameraAngleY += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]) * fCameraSensitive[INPUT_TYPE_CONTROLLER] * iCameraReverse[INPUT_TYPE_CONTROLLER][AXIS_Y];

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
	this->StageStatusList->SetCameraTarget_Target(vecCameraTarget);

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
	this->StageStatusList->SetCameraTarget_Target(vecCameraTarget);

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

	this->StageStatusList->SetCameraTarget_Target(VGet(fCameraX, fCameraY, fCameraZ));

	
	// �v���C���[�̉E�΂ߌ��ɃJ������z�u����

	/* �J�����̊�{�̍��� */ 
	float fHeightOffset = 120.0f; 
	
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
	this->StageStatusList->SetCameraTarget_Target(this->vecCameraPositionInfo[iNowCameraFixedPositionNo].vecTarget);

	/* �J�����̍��W�ݒ� */
	this->StageStatusList->SetCameraPosition_Target(this->vecCameraPositionInfo[iNowCameraFixedPositionNo].vecPosition);
}

// �J�����ݒ�(�X�e�[�W�N���A)
void SceneStage::SetCamera_StageClear()
{
	/* �N���A���J�E���g��"�J������]"�ɐݒ肳�ꂽ�J�E���g�ł��邩�m�F */
	if ((this->iStageClear_Count == STAGECLEAR_COUNT_CAMERA_TRUN_FAST))
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

/* �J�����ݒ�(�X�e�[�W�J�n) */
void SceneStage::SetCamera_StageStart()
{
	/* ���݂̃J�����Œ���W�ԍ��ɑ΂��Ă̕�Ԃ��������Ă��邩�m�F */
	if (this->StageStatusList->iGetCameraPositionLeapCount() >= CAMERA_POSITION_LEAP_COUNT_MAX_STAGESTART)
	{
		// �������Ă���ꍇ
		/* �^�[�Q�b�g�Ƃ���J�����Œ���W�ԍ����X�V */
		/* �^�[�Q�b�g�Ƃ��Ă���J�����Œ���W�ԍ���ۑ� */
		this->iNowCameraFixedPositionNo += 1;

		/* ���݂̍��W���Ԃ̈ړ��O�n�_�ɐݒ肷�� */
		this->StageStatusList->SetCameraPosition_Start(this->StageStatusList->vecGetCameraPosition());
		this->StageStatusList->SetCameraTarget_Start(this->StageStatusList->vecGetCameraTarget());

		/* �J�����̐��`�ۊǗp�J�E���g������������ */
		this->StageStatusList->SetCameraPositionLeapCount(0);
		this->StageStatusList->SetCameraTargetLeapCount(0);
	}

	/* �J�����Œ���W�̒l���ő�l�𒴂��Ă��Ȃ����m�F */
	if (this->iNowCameraFixedPositionNo <= this->iMaxCameraFixedPositionNo )
	{
		// �����Ă���ꍇ
		/* �J�����̒����_�ݒ� */
		this->StageStatusList->SetCameraTarget_Target(this->vecCameraPositionInfo[iNowCameraFixedPositionNo + 1].vecTarget);

		/* �J�����̍��W�ݒ� */
		this->StageStatusList->SetCameraPosition_Target(this->vecCameraPositionInfo[iNowCameraFixedPositionNo + 1].vecPosition);
	}


	///* ���ݔԖڂ̃J�����Œ���W�ł��邩���擾 */
	//int iCameraPointMax = (this->StageStatusList->iGetCameraPositionLeapCount() / CAMERA_POSITION_LEAP_COUNT_MAX_STAGESTART);

	///* �J�����̒����_�ݒ� */
	//this->StageStatusList->SetCameraTarget_Target(this->vecCameraPositionInfo[iCameraPointMax + 1].vecTarget);

	///* �J�����̍��W�ݒ� */
	//this->StageStatusList->SetCameraPosition_Target(this->vecCameraPositionInfo[iCameraPointMax + 1].vecPosition);

	///* �^�[�Q�b�g�Ƃ��Ă���J�����Œ���W�ԍ���ۑ� */
	//this->iNowCameraFixedPositionNo = iCameraPointMax + 1;

	///* �^�[�Q�b�g�Ƃ��Ă���J�����Œ���W�ԍ����ύX����Ă��邩�m�F */
	//if (this->iOldCameraFixedPositionNo != this->iNowCameraFixedPositionNo)
	//{
	//	// �ύX����Ă���ꍇ
	//	/* �J�����̐��`�ۊǗp�J�E���g������������ */
	//	this->StageStatusList->SetCameraPositionLeapCount(0);
	//}
}

/* 2025.03.06 �e�r�듹	�J�������䏈���C�� �J�n */
/* 2025.03.16 ��򕗏�	�J�������䏈���C�� �J�n */
// �J�����␳
void SceneStage::CameraSmoothing(int iCameraLeapCountMax)
{
	/* �J�����ʒu */
	{
		/* �J�������`��ԗp�J�E���g���擾 */
		int iCameraPositionLeapCount = this->StageStatusList->iGetCameraPositionLeapCount();

		/* �J�������`�⊮�p�J�E���g���ő�l�ɒB���Ă��邩 */
		if (iCameraPositionLeapCount < iCameraLeapCountMax)
		{
			// �ő�l�ɒB���Ă��Ȃ��ꍇ
			/* �J�������`��Ԃ̊������擾 */
			float fLeapRatio = ((float)iCameraPositionLeapCount / (float)iCameraLeapCountMax);

			/* �J�����̍��W(���`��Ԍ�)���Z�o */
			VECTOR vecStart		= this->StageStatusList->vecGetCameraPosition_Start();		// ���`�⊮�̈ړ��O���W
			VECTOR vecTarget	= this->StageStatusList->vecGetCameraPosition_Target();		// ���`�⊮�̈ړ�����W
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

	/* �J���������_ */
	{
		/* �J�������`��ԗp�J�E���g���擾 */
		int iCameraTargetLeapCount = this->StageStatusList->iGetCameraTargetLeapCount();

		/* �J�������`�⊮�p�J�E���g���ő�l�ɒB���Ă��邩 */
		if (iCameraTargetLeapCount < iCameraLeapCountMax)
		{
			// �ő�l�ɒB���Ă��Ȃ��ꍇ
			/* �J�������`��Ԃ̊������擾 */
			float fLeapRatio = ((float)iCameraTargetLeapCount / (float)iCameraLeapCountMax);

			/* �J�����̍��W(���`��Ԍ�)���Z�o */
			VECTOR vecStart = this->StageStatusList->vecGetCameraTarget_Start();		// ���`�⊮�̈ړ��O���W
			VECTOR vecTarget = this->StageStatusList->vecGetCameraTarget_Target();		// ���`�⊮�̈ړ�����W
			VECTOR vecCameraTarget;
			vecCameraTarget.x = vecStart.x + (vecTarget.x - vecStart.x) * fLeapRatio;
			vecCameraTarget.y = vecStart.y + (vecTarget.y - vecStart.y) * fLeapRatio;
			vecCameraTarget.z = vecStart.z + (vecTarget.z - vecStart.z) * fLeapRatio;

			/* �J�����̒����_(���`��Ԍ�)�����݂̃J���������_�ɐݒ� */
			this->StageStatusList->SetCameraTarget(vecCameraTarget);

			/* �J�E���g�����Z���Đݒ肷�� */
			this->StageStatusList->SetCameraTargetLeapCount(iCameraTargetLeapCount + 1);
		}
		else
		{
			// �ő�l�ɒB���Ă���ꍇ
			/* �J�����̒����_(�ړ���)�����݂̃J���������_�ɐݒ� */
			this->StageStatusList->SetCameraTarget(this->StageStatusList->vecGetCameraTarget_Target());

			this->StageStatusList->SetCameraTarget_Start(this->StageStatusList->vecGetCameraTarget_Target());
		}
	}
}
/* 2025.03.06 �e�r�듹	�J�������䏈���C��  */
/* 2025.03.16 ��򕗏�	�J�������䏈���C�� �I�� */
