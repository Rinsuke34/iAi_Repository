/* 2024.12.15 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹�@�ړ������ǉ� */

#include "CharacterPlayer.h"

/* 2025.01.09 �e�r�듹 �g�p�l�[���X�y�[�X�ǉ� �J�n */

using namespace PLAYER_STATUS;
using namespace GAME_SETTING;

/* 2025.01.09 �e�r�듹 �g�p�l�[���X�y�[�X�ǉ� �I�� */

/* �v���C���[�N���X�̒�` */

// �R���X�g���N�^
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* ������ */
	/* �f�[�^���X�g�擾 */
	this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* �������������J�n */
	this->iModelHandle = MV1LoadModel("resource/ModelData/Test/Player/Karisotai_1217.mv1");

	/* 2025.01.09 �e�r�듹 �����������ǉ� �J�n */
	
	this ->fPlayerMoveSpeed = PLAYER_WALK_MOVE_SPEED;
	this ->vecPlayerOldVector = { 0,0,0 };
	this ->fPlayerOldRadian = 0;
	this ->iPlayerNormalDashFlameCount = 0;
	this ->bPlayerJumpingFlag = false;
	this ->iPlayerJumpCount = 0;
	this ->bPlayerDodgingFlag = false;
	this ->fPlayerDodgeProgress = 0.0f;
	this ->vecPlayerDodgeDirection = VGet(0, 0, 0);
	this ->iPlayerDodgeWhileJumpingCount = 0;
	this ->bPlayerAfterDodgeFlag = false;

	/* 2025.01.09 �e�r�듹 �����������ǉ� �I�� */

	/* �R���W�������X�V */
	CollisionUpdate();
}

// �X�V
void CharacterPlayer::Update()
{
	/* �g�p�� */
	// InputList�ɓ����Ă���֐����g�p����΂���Ȋ����œ��͂��擾�ł��܂��B
	// �����Ɋւ��ẮAInputList.h���Q�Ƃ��Ă��������B
	/* �ړ� */
	float fSpeed = 2.0f;
	VECTOR vecMove = VScale(this->InputList->vecGetGameInputMove(), fSpeed);
	this->vecPosition = VAdd(this->vecPosition, vecMove);

	/* 2025.01.09 �e�r�듹�@�ړ������ǉ� �J�n */
	// �L�����ړ�(�J�����ݒ�ɍ��킹��)

		// �J�����̌����Ă���p�x���擾(��)
	VECTOR stVecCameraPosition = VGet(0, 100, -300);
	VECTOR stVecCameraTarget = VGet(0, 100, 0);
	VECTOR stVecCameraUp = VGet(0, 1, 0);

	float sx = stVecCameraPosition.x - stVecCameraTarget.x;
	float sz = stVecCameraPosition.z - stVecCameraTarget.z;
	float camrad = atan2(sz, -sx);


	VECTOR vecPlayerMove = { 0,0,0 }; //�v���C���[�̈ړ��x�N�g��

	//�n��ɂ���ꍇ�̏���
	//if (this ->bPlayerJumpingFlag == false) {

	//	// �A�i���O�X�e�B�b�N�̓��͂𐳋K�����Ĉړ��������v�Z
	//	//float fStickTiltMagnitude = sqrt(InputX * InputX + InputY * InputY);
	//	// �f�b�h�]�[����ݒ�
	//	if (fStickTiltMagnitude > STICK_DEAD_ZONE)
	//	{
	//		//���K���������͕������擾
	//		float fNormalizedInputX = InputX / fStickTiltMagnitude;
	//		float fNormalizedInputY = InputY / fStickTiltMagnitude;

	//		// �J�����������l�����Ĉړ��x�N�g������]
	//		float fInputAngle = atan2(fNormalizedInputY, fNormalizedInputX);
	//		float fPlayerMoveAngle = fInputAngle + camrad;

	//		// �����t���O��true�Ȃ�ő�_�b�V����ԂɂȂ�
	//		if (this ->bPlayerAfterDodgeFlag == true)
	//		{
	//			this ->fPlayerMoveSpeed = PLAER_DASH_MAX_SPEED;

	//		}
	//		// �X�e�B�b�N�̓|����ő��x��ω�
	//		else if (fStickTiltMagnitude > STICK_TILT_PLAER_DASH) {
	//			//����i�ʏ�j
	//			this ->fPlayerMoveSpeed = PLAER_DASH_NOMAL_SPEED;
	//			this ->iPlayerNormalDashFlameCount += 1;

	//			//���t���[�����������瑖��i�ő�j��
	//			if (this ->iPlayerNormalDashFlameCount >= FLAME_COUNT_TO_MAX_SPEED)
	//			{
	//				this ->fPlayerMoveSpeed = PLAER_DASH_MAX_SPEED;
	//			}
	//		}
	//		else
	//		{
	//			//����
	//			this ->fPlayerMoveSpeed = PLAYER_WALK_MOVE_SPEED;
	//			this ->iPlayerNormalDashFlameCount = 0;
	//		}

	//		//�ړ��̕����Ƒ��x���x�N�g���ɐݒ�
	//		vecPlayerMove = VScale(this->InputList->vecGetGameInputMove() , this->fPlayerMoveSpeed);
	//		//�ړ��̊p�x��ۑ�����i��̏����Ɏg�p�j
	//		this ->fPlayerOldRadian = fPlayerMoveAngle;
	//	}
	//	//�X�e�B�b�N�̌X�����f�b�h�]�[���ȉ�
	//	else
	//	{
	//		//�����t���O�����Z�b�g
	//		this ->bPlayerAfterDodgeFlag = false;

	//	}

	//	//�ړ��̃x�N�g����ۑ�����i��̏����Ɏg�p�j
	//	this ->vecPlayerOldVector = VScale(vecPlayerMove, 1 / this ->fPlayerMoveSpeed);
	//}
	////�󒆂ɂ���ꍇ�̏���
	//else
	//{
	//	// �A�i���O�X�e�B�b�N�̓��͂𐳋K�����Ĉړ��������v�Z
	//	float fStickTiltMagnitude = sqrt(InputX * InputX + InputY * InputY);
	//	// �f�b�h�]�[����ݒ�
	//	if (fStickTiltMagnitude > STICK_DEAD_ZONE)
	//	{
	//		//���K���������͕������擾
	//		float fNormalizedX = InputX / fStickTiltMagnitude;
	//		float fNormalizedY = InputY / fStickTiltMagnitude;

	//		// �J�����������l�����Ĉړ��x�N�g������]
	//		float fInputAngle = atan2(fNormalizedY, fNormalizedX);
	//		float fPlayerMoveAngle = fInputAngle + camrad;

	//		//�󒆂ł̈ړ����x��ݒ�
	//		this ->fPlayerMoveSpeed = PLAER_DASH_MAX_SPEED;

	//		//�ړ��̕����Ƒ��x���x�N�g���ɐݒ�
	//		vecPlayerMove.z = -cos(fPlayerMoveAngle) * this ->fPlayerMoveSpeed;
	//		vecPlayerMove.x = -sin(fPlayerMoveAngle) * this ->fPlayerMoveSpeed;

	//		//�ړ��̊p�x��ۑ�����i��̏����Ɏg�p�j
	//		this ->fPlayerOldRadian = fPlayerMoveAngle;
	//	}
	//}

	///* �W�����v */
	//if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
	//{
	//	//�W�����v
	//	//�A���W�����v�񐔂̐����ȓ�
	//	if (this->iPlayerJumpCount <= PLAYER_JUMPING_IN_AIR_LIMIT)
	//	{
	//		//�W�����v���x���Z�b�g
	//		this->fPlayerJumpSpeed = 0;
	//		//�W�����v�̉����x��^����
	//		this->fPlayerJumpSpeed += ACCELERATION(PLAYER_JUMP_SPEED);
	//		//�W�����v���̃t���Otrue
	//		this->bPlayerJumpingFlag = true;
	//		//�A���W�����v�񐔂����Z
	//		this->iPlayerJumpCount += 1;
	//	}

	//	//�W�����v������𒆂ł͂Ȃ�
	//	if (this->bPlayerJumpingFlag == true && this->bPlayerDodgingFlag == false)
	//	{
	//		//�W�����v���x�ɒn��̉e����^����
	//		this->fPlayerJumpSpeed += ACCELERATION(GRAVITY_SREED * GRAVITY_BUFFER);
	//		//�ړ����Ă��������֌���
	//		vecMove = VAdd(vecMove, this->vecPlayerOldVector);
	//	}

	//	//�W�����v���x���v���C���[�ړ��x�N�g���ɃZ�b�g
	//	vecMove.y = this->fPlayerJumpSpeed;

	//	//�W�����v�̈ړ��x�N�g�����ʒu�x�N�g���ɔ��f
	//	this->vecPosition = VAdd(this->vecPosition, vecMove);

	//}
	//else
	//{
	//	this->vecPosition.y = 0.f;
	//}


	//if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == true)
	//{
	//	//���
	//	
	//		// ����t���O���Z�b�g
	//		this->bPlayerDodgingFlag = true;
	//		// ����J�n���̎��Ԃ����Z�b�g
	//		this->fPlayerDodgeTime = 0.0f;
	//		//���݂̈ړ������։��
	//		this->vecPlayerDodgeDirection = VNorm(vecPlayerMove);
	//		//��𑬓x�ݒ�
	//		this->fPlayerDodgeSpeed = PLAYER_DODGE_SPEED;
	//		//�����Ԃ̐i�s�������Z�b�g
	//		this->fPlayerDodgeProgress = 0.0f;

	//		//�W�����v���ł���Ή���񐔂��J�E���g
	//		if (this->bPlayerJumpingFlag == true)
	//		{
	//			this->iPlayerDodgeWhileJumpingCount += 1;
	//		}
	//	
	//	//����t���O���L���ł���Ή���������s��
	//	if (this->bPlayerDodgingFlag == true) {

	//		// ���Ԍo�߂����Z
	//		this->fPlayerDodgeTime += deltaTime;

	//		// ��𒆁i�ݒ莞�Ԃ̊ԁj
	//		if (this->fPlayerDodgeTime < 0.3)
	//		{
	//			//�ݒ莞�Ԃ����ĉ���ړ����s��
	//			VECTOR vecPlayerDodgeMove = VScale(this->vecPlayerDodgeDirection, PLAYER_DODGE_SPEED * deltaTime);
	//			vecPlayerMove = vecPlayerDodgeMove;
	//		}
	//		// ����I��
	//		else
	//		{
	//			this->bPlayerDodgingFlag = false;
	//			this->bPlayerAfterDodgeFlag = true;
	//		}
	//	}
	//}

	//
	////�n��ɍ~�肽�Ƃ��̏���
	//if (this ->vecPosition.y <= 0)
	//{
	//	//�v���C���[Y���W�Œ�
	//	this ->vecPosition.y = 0;
	//	//�v���C���[��Y�����̓��������Z�b�g
	//	vecPlayerMove.y = 0;
	//	//�W�����v���̃t���O�����Z�b�g
	//	this ->bPlayerJumpingFlag = false;
	//	//�A���W�����v�񐔂����Z�b�g
	//	this ->iPlayerJumpCount = 0;
	//	//�W�����v���̉���񐔂����Z�b�g
	//	this ->iPlayerDodgeWhileJumpingCount = 0;
	//}

	//vecPlayerMove = VScale(this->InputList->vecGetGameInputMove(), fSpeed);
	//this->vecPosition = VAdd(this->vecPosition, vecMove);

	//// �ړ��ʂ����̂܂܃L�����̌����ɂ���
	//if (VSize(VGet(vecPlayerMove.x, 0, vecPlayerMove.z)) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
	//	this ->vecPlayerDirection = vecPlayerMove;
	//}

	/* 2025.01.09 �e�r�듹�@�ړ������ǉ� �I�� */

	/* �d�͏��� */
	Player_Gravity();

	/* �W�����v���� */
	Player_Jump();

	/* �ړ����� */
	Player_Move();
}

// �`��
void CharacterPlayer::Draw()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);



	/* �e�X�g�p�`�� */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_JUMP) == true)
	{
		DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "JUMP");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "ATTACK");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
	{
		DrawFormatString(500, 16 * 2, GetColor(255, 255, 255), "AIM");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_RESET) == true)
	{
		DrawFormatString(500, 16 * 3, GetColor(255, 255, 255), "RESET");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_DODGE) == true)
	{
		DrawFormatString(500, 16 * 4, GetColor(255, 255, 255), "DODGE");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_FORWARD) == true)
	{
		DrawFormatString(500, 16 * 5, GetColor(255, 255, 255), "FORWARD");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_BACK) == true)
	{
		DrawFormatString(500, 16 * 6, GetColor(255, 255, 255), "BACK");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_LEFT) == true)
	{
		DrawFormatString(500, 16 * 7, GetColor(255, 255, 255), "LEFT");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_RIGHT) == true)
	{
		DrawFormatString(500, 16 * 8, GetColor(255, 255, 255), "RIGHT");
	}

	VECTOR vecMove = this->InputList->vecGetGameInputMove();
	DrawFormatString(500, 16 * 9, GetColor(255, 255, 255), "X:%f, Z:%f", vecMove.x, vecMove.z);

	XINPUT_STATE stXInputState;
	GetJoypadXInputState(DX_INPUT_PAD1, &stXInputState);

	DrawFormatString(500, 16 * 10, GetColor(255, 255, 255), "���g���K : %u", stXInputState.LeftTrigger);
	DrawFormatString(500, 16 * 11, GetColor(255, 255, 255), "�E�g���K : %u", stXInputState.RightTrigger);

	float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();
	DrawFormatString(500, 16 * 12, GetColor(255, 255, 255), "�ړ����x : %f", fSpeed);
}

// �ړ�
void CharacterPlayer::Player_Move()
{
	/* �v���C���[�̈ړ����� */

	/* ���͂ɂ��ړ��ʂ��擾 */
	VECTOR vecInput = this->InputList->vecGetGameInputMove();

	/* �ړ����͂�����Ă��邩�m�F */
	if (vecInput.x != 0 || vecInput.z != 0)
	{
		// �ړ����͂�����Ă���ꍇ
		/* ���݂̈ړ����x�擾 */
		float fSpeed	= this->PlayerStatusList->fGetPlayerNowMoveSpeed();

		/* �����x��K�p */
		fSpeed += this->PlayerStatusList->fGetPlayerMoveAcceleration();

		/* �ő呬�x�𒴂��Ă��Ȃ����m�F */
		float fMaxSpeed = this->PlayerStatusList->fGetPlayerMaxMoveSpeed();
		if (fSpeed > fMaxSpeed)
		{
			// �ő呬�x�𒴂��Ă���ꍇ
			/* �ő呬�x�ɐݒ� */
			fSpeed = fMaxSpeed;
		}

		/* ���ݑ��x���X�V */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

		/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
		float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

		/* �ړ��ʂ��Z�o */
		VECTOR vecMove;
		vecMove.x	= +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecMove.y	= 0.0f;
		vecMove.z	= -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
		vecMove		= VScale(vecMove, fSpeed);

		/* �ړ���̍��W���Z�o */
		VECTOR vecNextPosition = VAdd(this->vecPosition, vecMove);

		/* �����ŃI�u�W�F�N�g�ɐڐG���Ă��邩���� */
		// ����\��

		/* �v���C���[�̍��W���ړ������� */
		this->vecPosition = vecNextPosition;

		/* �v���C���[�̌������ړ������ɍ��킹�� */
		float fPlayerAngle = atan2f(vecInput.x, vecInput.z);	// �ړ������̊p�x(���W�A��)���擾
		fPlayerAngle = fAngleX - fPlayerAngle;					// �J�����̌����ƍ���
		this->PlayerStatusList->SetPlayerAngleX(fPlayerAngle);	// �v���C���[�̌�����ݒ�
	}
	else
	{
		// �ړ����͂�����Ă��Ȃ��ꍇ
		/* �ړ����x��0�ɂ��� */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(0);
	}

	/* �R���W�������X�V */
	CollisionUpdate();
}

// �W�����v
void CharacterPlayer::Player_Jump()
{
	/* �v���C���[�̃W�����v���� */

	/* �W�����v���͂�����Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
	{
		// �W�����v���͂�����Ă���ꍇ
		/* �W�����v���� */
		// ���ŗ������x��-�ɂ��鏈�����s��
		this->PlayerStatusList->SetPlayerNowFallSpeed(-10.0f);
	}

	/* �R���W�������X�V */
	CollisionUpdate();
}

// �d��
void CharacterPlayer::Player_Gravity()
{
	/* �v���C���[�̏d�͏��� */

	/* �����ʎ擾 */
	float fFallSpeed	=	this->PlayerStatusList->fGetPlayerNowFallSpeed();		// �����_�ł̉����ʎ擾
	fFallSpeed			+=	this->PlayerStatusList->fGetPlayerFallAcceleration();	// �����x�����Z

	/* �d�͂ɂ��ړ���̍��W���擾 */
	VECTOR vecNextPosition	=	this->vecPosition;
	vecNextPosition.y		-=	this->PlayerStatusList->fGetPlayerNowFallSpeed();

	/* ��l���̏㕔���̓����蔻�肩�牺�����֌������������쐬 */
	COLLISION_LINE stCollision;
	stCollision.vecLineStart	=	this->vecPosition;
	stCollision.vecLineStart.y	+=	100;		// �����œo��鍂���̏��

	stCollision.vecLineEnd		=	stCollision.vecLineStart;
	stCollision.vecLineEnd.y	-=	9999;

	/* �ȉ��A������(�߂��I�u�W�F�N�g�̂ݑΏۂɂ���悤�ɂ���) */
	/* ������擾 */
	auto& PlatformList = ObjectList->GetPlatformList();

	/* ���n������W */
	float	fStandPosY		= vecNextPosition.y;	// �����l���ړ���̍��W�ɐݒ�

	/* ����ƐڐG���邩�m�F */
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stCollision);

		/* �ڐG���Ă��邩�m�F */
		if (stHitPolyDim.HitFlag == 1)
		{
			// �ڐG���Ă���ꍇ
			/* �q�b�g�������W�����݂̒��n���W��荂���ʒu�ł��邩�m�F */
			if (stHitPolyDim.HitPosition.y > fStandPosY)
			{
				// ���݂̒��n���W��荂���ʒu�ł���ꍇ
				/* ���n���W���X�V */
				fStandPosY = stHitPolyDim.HitPosition.y;

				/* �����̉����x������������ */
				fFallSpeed = 0.f;
			}
		}
	}

	/* ���n���W���X�V */
	vecNextPosition.y = fStandPosY;

	/* �v���C���[���W���X�V */
	this->vecPosition = vecNextPosition;

	/* �������x���X�V */
	this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

	/* �R���W�������X�V */
	CollisionUpdate();
}

// �R���W�����X�V
void CharacterPlayer::CollisionUpdate()
{
	/* �v���C���[�̃R���W�����X�V���� */

	/* �v���C���[�̃R���W�������X�V */
	COLLISION_CAPSULE stCapsule;
	stCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0, 100, 0));
	stCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0, 0, 0));
	stCapsule.fCapsuleRadius	= 50.0f;

	/* �R���W������ݒ� */
	this->SetCollision_Capsule(stCapsule);
}