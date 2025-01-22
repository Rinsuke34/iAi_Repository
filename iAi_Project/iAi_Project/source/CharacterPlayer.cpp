/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "CharacterPlayer.h"

/* �I�u�W�F�N�g */
#include "EffectTest.h"

/* �v���C���[�N���X�̒�` */
VECTOR vecTest;
// �R���X�g���N�^
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* ������ */
	/* �f�[�^���X�g�擾 */
	this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* �R���W�������X�V */
	CollisionUpdate();
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
	/* �v���C���[�̍X�V���� */

	/* �v���C���[�̏�Ԃɉ����ď�����ύX */
	int iInput = this->PlayerStatusList->iGetPlayerState();
	switch (iInput)
	{
		/* ��{���(�s���ɐ���̂Ȃ���Ԃ̑���) */
		case PLAYER_STATE_IDLE:			// �ҋ@
		case PLAYER_STATE_WALK:			// ���s
		case PLAYER_STATE_RUN_LOW:		// ���s(�ᑬ)
		case PLAYER_STATE_RUN_HIGH:		// ���s(����)
		case PLAYER_STATE_JUMP_UP:		// ��(�㏸)
		case PLAYER_STATE_JUMP_DOWN:	// ��(���~)
			/* �d�͏��� */
			Player_Gravity();

			/* �W�����v���� */
			Player_Jump();

			/* �ړ����� */
			Player_Move();

			/* ������� */
			Player_Dodg();

			Player_Charge_Attack();

			/* ���͎擾 */
			if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK))
			{
				/* ����(�\��)��Ԃ֑J�� */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATE_DRAW_SWORD_CHARGE);
			}
			else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_AIM))
			{
				/* �N�i�C(�\��)��Ԃ֑J�� */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATE_THROW_KUNAI_AIM);
			}
			else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE))
			{
				/* �����ԂɑJ�� */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATE_DODGE);
			}
			break;

		/* �s���������(�ꕔ�s���ɐ��񂠂�) */
		case PLAYER_STATE_DRAW_SWORD_CHARGE:	// ����(����)
		case PLAYER_STATE_THROW_KUNAI_AIM:		// �N�i�C(�\��)
			/* �d�͏��� */
			Player_Gravity();

			/* �ړ����� */
			Player_Move();

			/* ���͎擾 */
			switch (iInput)
			{
				case PLAYER_STATE_DRAW_SWORD_CHARGE:	// ����(����)
					/* �U���{�^���𗣂����� */
					if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_ATTACK))
					{
						/* ����(��)��ԂɑJ�� */
						this->PlayerStatusList->SetPlayerState(PLAYER_STATE_DRAW_SWORD_WEAK);
					}
					/* �������͂����� */
					else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE))
					{
						/* �����ԂɑJ�� */
						this->PlayerStatusList->SetPlayerState(PLAYER_STATE_DODGE);
					}
					break;

				case PLAYER_STATE_THROW_KUNAI_AIM:		// �N�i�C(�\��)
					/* �U���{�^������������ */
					if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK))
					{
						/* �N�i�C(����)��ԂɑJ�� */
						this->PlayerStatusList->SetPlayerState(PLAYER_STATE_THROW_KUNAI_THROW);
					}
					/* �\�������������� */
					else if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_AIM))
					{
						/* �ҋ@��ԂɑJ�� */
						this->PlayerStatusList->SetPlayerState(PLAYER_STATE_IDLE);
					}
					/* �������͂����� */
					else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE))
					{
						/* �����ԂɑJ�� */
						this->PlayerStatusList->SetPlayerState(PLAYER_STATE_DODGE);
					}
					break;
			}
			break;

		/* �U����� */
		// �����n
		case PLAYER_STATE_DRAW_SWORD_WEAK:		// ����(��)
		case PLAYER_STATE_DRAW_SWORD_STRONG:	// ����(��)
			/* �U������(�e�X�g) */
			Player_Attack();

			/* �ҋ@��Ԃɖ߂�(��) */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATE_IDLE);
			break;

		// �N�i�C�n
		case PLAYER_STATE_THROW_KUNAI_THROW:	// �N�i�C(����)
			/* �U������(�e�X�g) */
			Player_Attack();

			/* �ҋ@��Ԃɖ߂�(��) */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATE_IDLE);
			break;

		/* ������ */
		case PLAYER_STATE_DODGE:				// ���
			/* �ړ����� */
			Player_Move();

			/* �ҋ@��Ԃɖ߂�(��) */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATE_IDLE);
			break;
	}
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

// �ړ�
void CharacterPlayer::Player_Move()
{
	/* �v���C���[�̈ړ����� */

	float fStickTiltMagnitude	= this->InputList->fGetGameInputMove();
	VECTOR vecInput				= this->InputList->vecGetGameInputMoveDirection();

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
		//�����t���O�����Z�b�g
		this->PlayerStatusList->SetPlayerAfterDodgeFlag(false);

	}
	/* �R���W�������X�V */
	CollisionUpdate();
}

// �W�����v
void CharacterPlayer::Player_Jump()
{
	/* �v���C���[�̃W�����v���� */

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
			/* ��(�㏸)�֑J�� */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATE_JUMP_UP);
		}
	}

	/* �R���W�������X�V */
	CollisionUpdate();
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

// �d��
void CharacterPlayer::Player_Gravity()
{
	/* �v���C���[�̏d�͏��� */
	// ���v���C���[��Y�����ւ̈ړ��������܂Ƃ߂čs��

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

	/* �v���C���[�̒��n�t���O�𖳌��ɂ��� */
	this->PlayerStatusList->SetPlayerLanding(false);

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
		}
	}

	/* ���n���W���X�V */
	vecNextPosition.y = fStandPosY;

	/* �v���C���[���W���X�V */
	this->vecPosition = vecNextPosition;

	/* �������x���X�V */
	this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

	/* �������x��+�ł���Ȃ��(���~)�ɑJ�� */
	if (fFallSpeed < 0)
	{
		// �������x��+�ł���ꍇ
		/* ��(���~)�ɑJ�� */
		this->PlayerStatusList->SetPlayerState(PLAYER_STATE_JUMP_DOWN);
	}

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

// �v���C���[�U��(��)
void CharacterPlayer::Player_Attack()
{
	/* �e�X�g�p�U������ */

	/* �U�������͂���Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
	{
		EffectBase* Effect_Test = new TestEffect();
		Effect_Test->Effect_Load("FX_e_bullet");
		Effect_Test->SetPosition(VAdd(this->vecPosition, VGet(0.f, 10.f, 0.f)));

		dynamic_cast<TestEffect*>(Effect_Test)->Initialization();

		
		ObjectList->SetEffect(Effect_Test);
	}
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
	if (this->PlayerStatusList->iGetPlayerState() == PLAYER_STATE_DRAW_SWORD_CHARGE)
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
