/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "CharacterPlayer.h"

/* �v���C���[�N���X�̒�` */
VECTOR vecTest;
// �R���X�g���N�^
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* ������ */
	/* �f�[�^���X�g�擾 */
	this->InputList = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	this->vecMove				= VGet(0.f, 0.f, 0.f);	// �ړ���
	this->vecMove				= {};					// �ړ���
	this->stVerticalCollision	= {};					// ���������̃R���W����
	this->vecLandingPos			= VGet(0.f, 0.f, 0.f);	// ���������̃R���W�������n�ʂɒ��n����ʒu
	this->stHorizontalCollision	= {};					// ���������R���W����
}

// ������
void CharacterPlayer::Initialization()
{
	CharacterBase::Initialization();

	/* �R���W�������X�V */
	CollisionUpdate();
}

// �X�V
void CharacterPlayer::Update()
{
	/* �ڐG�m�F */
	{
		// ���U����I�u�W�F�N�g�ɑ΂��铖���蔻�菈�����s��
	}

	/* �ړ��ʂ����Z�b�g */
	this->vecMove = VGet(0, 0, 0);		// �ړ���

	/* �U���n�A�N�V�������� */
	{
		/* �U����ԑJ�ڊǗ� */
		// ���v���C���[�̓��͂ɉ����čU����Ԃ�J��
		Player_Attack_Transition();
	}

	/* �㉺����(Y��)�ړ����� */
	{
		/* �W�����v���� */
		Player_Jump();

		/* �d�͏��� */
		Player_Gravity();

		/* �ړ�����(��������) */
		Movement_Vertical();
	}

	/* ���s����(X��)�ړ����� */
	{
		/* �ړ����� */
		Player_Move();

		/* ������� */
		Player_Dodg();

		/* �ړ�����(��������) */
		Movement_Horizontal();
	}

	/* �R���W�������X�V */
	CollisionUpdate();
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

	XINPUT_STATE stXInputState;
	GetJoypadXInputState(DX_INPUT_PAD1, &stXInputState);

	DrawFormatString(500, 16 * 10, GetColor(255, 255, 255), "���g���K : %u", stXInputState.LeftTrigger);
	DrawFormatString(500, 16 * 11, GetColor(255, 255, 255), "�E�g���K : %u", stXInputState.RightTrigger);

	float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();
	DrawFormatString(500, 16 * 12, GetColor(255, 255, 255), "�ړ����x : %f", fSpeed);
	
	DrawFormatString(500, 16 * 14, GetColor(255, 255, 255), "�t���[���� : %d", this->PlayerStatusList->iPlayerNowAttakChargeFlame);

	DrawFormatString(500, 16 * 16, GetColor(255, 255, 255), "X : %f Y : %f Z : %f", vecTest.x, vecTest.y, vecTest.z);

	DrawSphere3D(vecTest, 80.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
}

// �����蔻��`��
void CharacterPlayer::CollisionDraw()
{
	CharacterBase::CollisionDraw();

	/* ���������̃R���W���� */
	int iColor	= GetColor(0, 255, 0);
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, iColor);
	DrawSphere3D(this->vecLandingPos, 10.f, 16, iColor, iColor, FALSE);

	/* ���s�����̃R���W���� */
	iColor	= GetColor(0, 0, 255);
	DrawCapsule3D(this->stHorizontalCollision.vecCapsuleTop, this->stHorizontalCollision.vecCapsuleBottom, this->stHorizontalCollision.fCapsuleRadius, 16, iColor, iColor, FALSE);
}

// �ړ�
void CharacterPlayer::Player_Move()
{
	/* �v���C���[�ړ��ʎ擾 */
	float fStickTiltMagnitude	= this->InputList->fGetGameInputMove();				// �X�e�B�b�N��|��������
	VECTOR vecInput				= this->InputList->vecGetGameInputMoveDirection();	// �ړ�����
	VECTOR vecAddMove			= VGet(0, 0, 0);									// �ړ���(���Z�p)

	/* �ړ����͂�����Ă��邩�m�F */
	if (vecInput.x != 0 || vecInput.z != 0)
	{
		// �ړ����͂�����Ă���ꍇ
		/* ���݂̈ړ����x�擾 */
		float fSpeed	= this->PlayerStatusList->fGetPlayerNowMoveSpeed();

		/* �ő呬�x�𒴂��Ă��Ȃ����m�F */
		if (this->PlayerStatusList->bGetPlayerAfterDodgeFlag() == true)
		{
			fSpeed = PLAER_DASH_MAX_SPEED;
		}

		// �X�e�B�b�N�̓|����ő��x��ω�
		else if (fStickTiltMagnitude > STICK_TILT_PLAER_DASH) 
		{
			//����i�ʏ�j
			fSpeed = PLAER_DASH_NOMAL_SPEED;
			//�t���[�������J�E���g
			this->PlayerStatusList->SetPlayerNormalDashFlameCount(PlayerStatusList->iGetPlayerNormalDashFlameCount() + 1);

			//���t���[�����������瑖��i�ő�j��
			if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() >= FLAME_COUNT_TO_MAX_SPEED)
			{
				fSpeed = PLAER_DASH_MAX_SPEED;
			}
		}
		else
		{
			//����
			this->PlayerStatusList->SetPlayerNowMoveSpeed(PLAYER_WALK_MOVE_SPEED);
			this->PlayerStatusList->SetPlayerNormalDashFlameCount(0);
			fSpeed = PLAYER_WALK_MOVE_SPEED;
		}
		/* 2025.01.09 �e�r�듹�@�ړ������ǉ� �I�� */

		/* ���ݑ��x���X�V */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

		/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
		float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

		/* �ړ��ʂ��Z�o */
		vecAddMove.x	= +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecAddMove.y	= 0.0f;
		vecAddMove.z	= -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
		vecAddMove		= VScale(vecAddMove, fSpeed);

		/* �v���C���[�̌������ړ������ɍ��킹�� */
		float fPlayerAngle	= atan2f(vecInput.x, vecInput.z);	// �ړ������̊p�x(���W�A��)���擾
		fPlayerAngle		= fAngleX - fPlayerAngle;			// �J�����̌����ƍ���
		this->PlayerStatusList->SetPlayerAngleX(fPlayerAngle);	// �v���C���[�̌�����ݒ�
	}
	else
	{
		// �ړ����͂�����Ă��Ȃ��ꍇ
		/* �ړ����x��0�ɂ��� */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(0);
		//�����t���O�����Z�b�g
		this->PlayerStatusList->SetPlayerAfterDodgeFlag(false);
	}

	/* �ړ��ʂ����Z */
	this->vecMove = VAdd(this->vecMove, vecAddMove);
}

// �W�����v
void CharacterPlayer::Player_Jump()
{
	/* �v���C���[�̏�Ԃ��擾 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* �v���C���[�̏�Ԃ��W�����v�\�ł��邩�m�F */
	// ���v���k
	switch (iPlayerState)
	{
		/* �W�����v�\�ȏ�� */
		case PLAYER_STATUS_FREE:				// ���R���
		case PLAYER_STATUS_MELEE_POSTURE:		// �ߐڍU���\����			
		case PLAYER_STATUS_PROJECTILE_POSTURE:	// �������U���\����
		case PLAYER_STATUS_PROJECTILE:			// �������U����
			/* �v���C���[�̃W�����v���� */
			{
				/* �W�����v�񐔂��ő吔�𒴂��Ă��Ȃ����m�F */
				int iNowJumpCount = this->PlayerStatusList->iGetPlayerNowJumpCount();
				int iMaxJumpCount = this->PlayerStatusList->iGetPlayerMaxJumpCount();
				if (iNowJumpCount < iMaxJumpCount)
				{
					/* �W�����v���͂�����Ă��邩�m�F */
					if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
					{
						// �W�����v���͂�����Ă���ꍇ
						/* �W�����v���� */
						// ���ŗ������x��-�ɂ��鏈�����s��
						this->PlayerStatusList->SetPlayerNowFallSpeed(-50.0f);

						/* �W�����v�񐔂��X�V */
						this->PlayerStatusList->SetPlayerNowJumpCount(iNowJumpCount + 1);

						this->PlayerStatusList->SetPlayerJumpingFlag(true);
					}
				}
			}
			break;

		/* �W�����v�s�\�ȏ�� */
		case PLAYER_STATUS_DODGING:			// �����Ԓ�
		case PLAYER_STATUS_MELEE_WEEK:		// �ߐڍU����(��)
		case PLAYER_STATUS_MELEE_STRONG:	// �ߐڍU����(��)
			break;
	}
}

// �d�͏���
void CharacterPlayer::Player_Gravity()
{
	/* �v���C���[�̏�Ԃ��擾 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* �v���C���[���d�͏������s����Ԃł��邩�m�F */
	// ���v���k
	switch (iPlayerState)
	{
		/* �d�͏������s����� */
		case PLAYER_STATUS_FREE:				// ���R���		
		case PLAYER_STATUS_MELEE_POSTURE:		// �ߐڍU���\����		
		case PLAYER_STATUS_PROJECTILE_POSTURE:	// �������U���\����
			/* �d�͏��������s */
			break;

		/* �d�͏������s��Ȃ���� */
		case PLAYER_STATUS_DODGING:			// �����Ԓ�
		case PLAYER_STATUS_MELEE_WEEK:		// �ߐڍU����(��)
		case PLAYER_STATUS_MELEE_STRONG:	// �ߐڍU����(��)
		case PLAYER_STATUS_PROJECTILE:		// �������U����
			/* �d�͏������s��Ȃ�(�d�͏������I��) */
			return;
	}

	/* �����ʎ擾 */
	float fFallSpeed	=	this->PlayerStatusList->fGetPlayerNowFallSpeed();		// �����_�ł̉����ʎ擾
	fFallSpeed			+=	this->PlayerStatusList->fGetPlayerFallAcceleration();	// �����x�����Z

	/* �����̉����x���X�V */
	this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

	/* �d�͂ɂ��ړ���̍��W���擾 */
	this->vecMove.y		-= this->PlayerStatusList->fGetPlayerNowFallSpeed();
}

// ���
void CharacterPlayer::Player_Dodg()
{
	/* 2025.01.09 �e�r�듹�@�ړ������ǉ� �J�n */
	/* ���͂ɂ��ړ��ʂ��擾 */
	VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();

	/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
	float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

	/* �ړ��ʂ��Z�o */
	VECTOR vecMove;
	vecMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
	vecMove.y = 0.0f;
	vecMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
	
	//����t���O�������Ă��炸�A�i�W�����v���ł���΁j����񐔐����ȓ��̏�ԂŁA����{�^���������ꂽ
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == true && this->PlayerStatusList->bGetPlayerDodgingFlag() == false && this->PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() < PLAYER_DODGE_IN_AIR_LIMIT)
	{	
		// ����t���O���Z�b�g
		this->PlayerStatusList->SetPlayerDodgingFlag(true);
		// ����J�n���̎��Ԃ����Z�b�g
		this->PlayerStatusList->SetPlayerNowDodgeFlame(0.0f);
		//���݂̈ړ������։��
		this->PlayerStatusList->SetPlayerDodgeDirection(VNorm(vecMove));
	
		//�����Ԃ̐i�s�������Z�b�g
		this->PlayerStatusList->SetPlayerDodgeProgress(0.0f);
	}

	//����t���O���L���ł���Ή���������s��
	if (this->PlayerStatusList->bGetPlayerDodgingFlag() == true)
	{
		//�W�����v���ł���Ή���񐔂��J�E���g
		if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true)
		{
			this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() + 1);
		}

		// ���Ԍo�߂����Z
		this->PlayerStatusList->SetPlayerNowDodgeFlame(this->PlayerStatusList->iGetPlayerNowDodgeFlame() + 1);

		// ��𒆁i�ݒ莞�Ԃ̊ԁj
		if (this->PlayerStatusList->iGetPlayerNowDodgeFlame() <= PLAYER_DODGE_FLAME)
		{
			//�ݒ莞�Ԃ����ĉ���ړ����s��
			// ��𒆁i�ݒ莞�Ԃ̊ԁj
			vecMove = VScale(vecMove, PLAYER_DODGE_SPEED);

			/* �ړ���̍��W���Z�o */
			VECTOR vecNextPosition = VAdd(this->vecPosition, vecMove);

			/* �����ŃI�u�W�F�N�g�ɐڐG���Ă��邩���� */
			// ����\��

			/* �v���C���[�̍��W���ړ������� */
			this->vecPosition = vecNextPosition;
		}
		// ����I��
		else
		{
			this->PlayerStatusList->SetPlayerDodgingFlag(false);
			this->PlayerStatusList->SetPlayerAfterDodgeFlag(true);
		}
	}

	/* �v���C���[�̌������ړ������ɍ��킹�� */
	float fPlayerAngle = atan2f(vecInput.x, vecInput.z);	// �ړ������̊p�x(���W�A��)���擾
	fPlayerAngle = fAngleX - fPlayerAngle;					// �J�����̌����ƍ���
	this->PlayerStatusList->SetPlayerAngleX(fPlayerAngle);	// �v���C���[�̌�����ݒ�
	/* 2025.01.09 �e�r�듹�@�ړ������ǉ� �I�� */
}

// �ړ�����(��������)
void CharacterPlayer::Movement_Vertical()
{
	/* �ړ���̍��W���擾(��������) */
	VECTOR vecNextPosition;
	vecNextPosition.x		= this->vecPosition.x;
	vecNextPosition.y		= this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z		= this->vecPosition.z;

	/* ��l���̏㕔���̓����蔻�肩�牺�����֌������������쐬 */
	this->stVerticalCollision.vecLineStart		=	this->vecPosition;
	this->stVerticalCollision.vecLineStart.y	+=	160;		// �����������鍂��

	this->stVerticalCollision.vecLineEnd		=	stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y		-=	9999;

	/* �ȉ��A������(�߂��I�u�W�F�N�g�̂ݑΏۂɂ���悤�ɂ���) */
	/* ������擾 */
	auto& PlatformList = ObjectList->GetCollisionList();

	/* ���n������W */
	// �������l���ړ���̍��W�ɐݒ�
	float	fStandPosY = vecNextPosition.y;

	/* �v���C���[�̒��n�t���O�𖳌��ɂ��� */
	this->PlayerStatusList->SetPlayerLanding(false);

	/* ����ƐڐG���邩�m�F */
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

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

				/* �����̉����x���X�V */
				this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

				/* �W�����v�񐔂����������� */
				this->PlayerStatusList->SetPlayerNowJumpCount(0);

				/* �v���C���[�̒��n�t���O��L���ɂ��� */
				this->PlayerStatusList->SetPlayerLanding(true);

				/* 2025.01.09 �e�r�듹�@�ړ������ǉ� �ǉ� */

				//�W�����v���̃t���O�����Z�b�g
				this->PlayerStatusList->SetPlayerJumpingFlag(false);

				//�W�����v���̉���񐔂����Z�b�g
				this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(0);
				/* 2025.01.09 �e�r�듹�@�ړ������ǉ� �I�� */
			}

			/* �q�b�g�������W��ۑ� */
			this->vecLandingPos = stHitPolyDim.HitPosition;
		}
	}

	/* ���n���W���X�V */
	vecNextPosition.y = fStandPosY;

	/* �v���C���[���W���X�V */
	this->vecPosition = vecNextPosition;

	/* ���݂̃v���C���[��Ԃ��擾 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* ���[�V�������X�V */
	{
		/* �󒆂ɂ���(���n���Ă��Ȃ�)���m�F */
		if (this->PlayerStatusList->bGetPlayerJumpingFlag() == false)
		{
			// �󒆂ɂ���(���n���Ă��Ȃ�)�ꍇ
			/* �U�����\���Ă��Ȃ���Ԃł��邩�m�F */
			// ���\���Ă���Œ��͗������[�V�����ɑJ�ڂ����Ȃ�
			if ((iPlayerState != PLAYER_STATUS_MELEE_POSTURE) && (iPlayerState != PLAYER_STATUS_PROJECTILE_POSTURE))
			{
				/* �㏸���Ă��邩�m�F */
				if (this->PlayerStatusList->fGetPlayerFallAcceleration() < 0)
				{
					// �㏸���Ă���ꍇ
					/* ���[�V������"�W�����v(�㏸)"�ɐݒ� */
					PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_JUMP_UP);
				}
				else
				{
					// ���~���Ă���ꍇ
					/* ���[�V������"�W�����v(���~)"�ɐݒ� */
					PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_JUMP_DOWN);
				}
			}
		}
	}
}

// �ړ�����(��������)
void CharacterPlayer::Movement_Horizontal()
{
	/* �ړ���̍��W���擾(��������) */
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x + this->vecMove.x;
	vecNextPosition.y = this->vecPosition.y;
	vecNextPosition.z = this->vecPosition.z + this->vecMove.z;

	/* �����ŃI�u�W�F�N�g�ɐڐG���Ă��邩���� */
	{
		/* ���݈ʒu����ړ�����W�֌������J�v�Z���R���W�������쐬 */
		// �J�v�Z���R���W����
		stHorizontalCollision.vecCapsuleBottom	= VAdd(this->vecPosition,	VGet(0.f, 45.f, 0.f));	// ���݂̍��W
		stHorizontalCollision.vecCapsuleTop		= VAdd(vecNextPosition,		VGet(0.f, 45.f, 0.f));	// �ړ���̍��W
		stHorizontalCollision.fCapsuleRadius	= 15.f;

		/* ������擾 */
		auto& PlatformList = ObjectList->GetCollisionList();

		/* ����ƐڐG���邩�m�F */
		for (auto* platform : PlatformList)
		{
			/* ����Ƃ̐ڐG���� */
			bool bHitFlg = platform->HitCheck(stHorizontalCollision);

			/* �ڐG���Ă��邩�m�F */
			if (bHitFlg == true)
			{
				/* �ڐG���Ă���ꍇ */
				vecNextPosition = this->vecPosition;
			}
		}
	}

	/* �v���C���[�̍��W���ړ������� */
	this->vecPosition = vecNextPosition;

	/* ���[�V�������X�V */
	{
		// ���ړ��ʂƂ��Ń��[�V������ύX���鏈����ǉ�
	}
}

// �R���W�����X�V
void CharacterPlayer::CollisionUpdate()
{
	/* �v���C���[�̃R���W�������X�V */
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0, 135, 0));
	this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0, 15, 0));
	this->stCollisionCapsule.fCapsuleRadius		= 15.f;
}

// �U����ԑJ�ڊǗ�
void CharacterPlayer::Player_Attack_Transition()
{
	/* �U����Ԃ̑J�ڂ͉��L�Ƃ��� */
	//           --> �\��(�ߐ�)   ---> ��U��(�ߐ�) --
	//           |                 |                 |
	// ���R��� -|                 --> ���U��(�ߐ�) ---> ���R���
	//           |                                   |
	//           --> �\��(������) ---> �U��(������) --

	/* �v���C���[�̏�Ԃ��擾 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* �v���C���[��Ԃɉ����ď�����ύX */
	switch (iPlayerState)
	{
		/* ���R��� */
		case PLAYER_STATUS_FREE:
			/* �U�����͂�����Ă��邩�m�F */
			if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
			{
				// �U�����͂�����Ă���ꍇ
				/* �v���C���[��Ԃ�"�ߐڍU���\����"�ɐݒ� */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_MELEE_POSTURE);
			}
			/* �G�C��(�\��)���͂�����Ă��邩�m�F */
			else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_AIM) == true)
			{
				// �G�C��(�\��)���͂�����Ă���ꍇ
				/* �v���C���[��Ԃ�"�������U���\����"�ɐݒ� */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_PROJECTILE_POSTURE);
			}
			break;

		/* �ߐڍU���\���� */
		case PLAYER_STATUS_MELEE_POSTURE:
			/* �ߐڍU��(�\��) */
			Player_Melee_Posture();
			break;

		/* �ߐڍU����(��) */
		case PLAYER_STATUS_MELEE_WEEK:
			/* �ߐڍU��(��) */
			Player_Melee_Weak();
			break;

		/* �ߐڍU����(��) */
		case PLAYER_STATUS_MELEE_STRONG:
			/* �ߋ����U��(��) */
			Player_Charge_Attack();
			break;

		/* �������U���\���� */
		case PLAYER_STATUS_PROJECTILE_POSTURE:
			/* �������U��(�\��) */
			Player_Projectile_Posture();
			break;

		/* �������U���� */
		case PLAYER_STATUS_PROJECTILE:
			/* �������U�� */
			Player_Projectile();
			break;
	}
}

// �ߐڍU��(�\��)
void CharacterPlayer::Player_Melee_Posture()
{
	/* �v���C���[�̌��݂̍U���`���[�W�t���[���̎擾 */
	int iNowAttakChargeFlame = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame();

	/* �U�����͂�����Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		// �U�����͂�����Ă���ꍇ
		/* �v���C���[�̌��݂̍U���`���[�W�t���[�������Z */
		PlayerStatusList->SetPlayerNowAttakChargeFlame(iNowAttakChargeFlame + 1);
	}
	else
	{
		// �U�����͂�����Ă��Ȃ��ꍇ
		/* �U���`���[�W�t���[���ɉ����ď�����ύX */
		if (iNowAttakChargeFlame < 5)
		{
			// 5�t���[�������̏ꍇ
			/* �v���C���[�̏�Ԃ�"�ߐڍU����(��)"�ɐݒ� */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_MELEE_WEEK);
		}
		else
		{
			// 5�t���[���ȏ�̏ꍇ
			/* �v���C���[�̏�Ԃ�"�ߐڍU����(��)"�ɐݒ� */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_MELEE_STRONG);

			/* �������Ȃ̂łƂ肠�������R��Ԃɖ߂� */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
		}

		/* �v���C���[�̌��݂̍U���`���[�W�t���[�������Z�b�g */
		PlayerStatusList->SetPlayerNowAttakChargeFlame(0);
	}
}

// �ߐڍU��(��)
void CharacterPlayer::Player_Melee_Weak()
{
	/* �U�����[�V�������m�F */
	// ���U�����[�V�������I��������A���R��ԂɑJ�ڂ���悤�ɂ���

	/* �v���C���[�̌����̕����ɃG�t�F�N�g���o�� */
	EffectPlayerMeleeWeak* pAddEffect = new EffectPlayerMeleeWeak();
	ObjectList->SetEffect(pAddEffect);
	pAddEffect->Effect_Load("FX_slash/FX_slash");
	pAddEffect->SetPosition(this->vecPosition);
	pAddEffect->Initialization();

	/* �������Ȃ̂łƂ肠�������R��Ԃɖ߂� */
	this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
}

/* 2025.01.22 �e�r�듹�@�U�������ǉ� �J�n */
// �v���C���[���ߍU��
void CharacterPlayer::Player_Charge_Attack()
{
	/* ���^�[�Q�b�g��ݒ� */
	VECTOR vecTarget = VSub(this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraPosition());
	vecTarget = VNorm(vecTarget);
	vecTarget = VScale(vecTarget, 2000);
	vecTarget = VAdd(this->vecPosition, vecTarget);
	vecTest = vecTarget;
	int iFlamecount = 0;
	if (this->PlayerStatusList->iGetPlayerState() == PLAYER_STATUS_MELEE_POSTURE)
	{		
		this->PlayerStatusList->iPlayerNowAttakChargeFlame += 1;	
	}
	else if(this->InputList->bGetGameInputAction(INPUT_REL, GAME_ATTACK) == true)
	{
		/* ���݂̈ړ����x�擾 */
		VECTOR vecMove;
		vecMove = VSub(vecTarget, this->vecPosition);
		vecMove = VNorm(vecMove);
		vecMove = VScale(vecMove, this->PlayerStatusList->iPlayerNowAttakChargeFlame);
		/* �ړ���̍��W���Z�o */
		VECTOR vecNextPosition = VAdd(this->vecPosition, vecMove);
		/* �v���C���[�̍��W���ړ������� */
		this->vecPosition = vecNextPosition;

		this->PlayerStatusList->iPlayerNowAttakChargeFlame = 0;
	}
}

// �������U��(�\��)
void CharacterPlayer::Player_Projectile_Posture()
{
	/* �������Ȃ̂łƂ肠�������R��Ԃɖ߂� */
	this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
}

// �������U��
void CharacterPlayer::Player_Projectile()
{
	/* �������Ȃ̂łƂ肠�������R��Ԃɖ߂� */
	this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
}
