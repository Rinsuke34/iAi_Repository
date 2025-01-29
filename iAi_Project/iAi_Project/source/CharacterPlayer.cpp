/* 2024.12.15 ��򕗏�	�t�@�C���쐬 */
/* 2025.01.09 �e�r�듹	�ړ������ǉ� */
/* 2025.01.22 �e�r�듹	�U�������ǉ� */
/* 2025.01.24 �e�r�듹	�U�������ǉ� */
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� */

#include "CharacterPlayer.h"

// �f�o�b�O�p ��ō폜
/* ���U���ړI�n�_�\���p */
VECTOR vecTest;
/* ��U���U���͈͕\���p */
COLLISION_SQHERE stTestCollision;

/* �v���C���[�N���X�̒�` */
// �R���X�g���N�^
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* ������ */
	{
		/* �I�u�W�F�N�g�̃n���h�� */
		this->pBulletMeleeWeak	=	nullptr;	// �ߐڍU��(��)�̒e

		/* �G�t�F�N�g�̃n���h�� */
		this->pLandEffect = nullptr;				//���n�G�t�F�N�g
		this->pChargeEffect = nullptr;				//���߃G�t�F�N�g
		this->pChargeFinishEffect = nullptr;		//���ߊ����G�t�F�N�g
		this->pChargeHoldEffect = nullptr;			//���ߊ�����G�t�F�N�g
		this->pChargeAttakEffect = nullptr;			//����(����)�U���G�t�F�N�g
		this->pDashEffect = nullptr;				//�_�b�V���G�t�F�N�g


		
		/* �ϐ� */
		this->vecMove		= VGet(0.f, 0.f, 0.f);	// �ړ���
		this->iObjectType	= OBJECT_TYPE_PLAYER;	// �I�u�W�F�N�g�̎��

		/* �ϐ�(�f�o�b�O�p) */
		this->stVerticalCollision								= {};		// ���������̃R���W����
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP]	= {};		// ���������R���W����(�㑤)
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN]	= {};		// ���������R���W����(����)
		this->stMeleeStrongMoveCollsion							= {};		// �ߐڍU��(��)�̃R���W����(�ړ���̍��W)
	}

	/* �f�[�^���X�g�擾 */
	{
		/* "���͊Ǘ�"���擾 */
		this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));

		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�v���C���[���"���擾 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Player/Models/Player");
	}
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
	/*if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_JUMP) == true)
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

	DrawSphere3D(vecTest, 40.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);

	DrawSphere3D(stTestCollision.vecSqhere, stTestCollision.fSqhereRadius, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), false);
	DrawFormatString(500, 16 * 17, GetColor(255, 255, 255), "�v���C���[���W(%f, %f, %f)", this->vecPosition.x, this->vecPosition.y, this->vecPosition.z);
	DrawFormatString(500, 16 * 18, GetColor(255, 255, 255), "�v���C���[�ړ���(%f, %f, %f)", this->vecMove.x, this->vecMove.y, this->vecMove.z);
	DrawFormatString(500, 16 * 19, GetColor(255, 255, 255), "�v���C���[�ړ����x : %f", VSize(this->vecMove));*/

	DrawFormatString(500, 16 * 20, GetColor(255, 255, 255), "%d", this->PlayerStatusList->bGetPlayerLandingFlg());
}

// �����蔻��`��
void CharacterPlayer::CollisionDraw()
{
	//CharacterBase::CollisionDraw();

	/* �v���C���[���W */
	//int iColor = GetColor(255, 0, 0);
	//DrawLine3D(VAdd(this->vecPosition, VGet(+50, 0, 0)), VAdd(this->vecPosition, VGet(-50, 0, 0)), iColor);
	//DrawLine3D(VAdd(this->vecPosition, VGet(0, 0, +50)), VAdd(this->vecPosition, VGet(0, 0, -50)), iColor);

	///* ���������̃R���W���� */
	//iColor	= GetColor(0, 255, 0);
	//DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, iColor);

	///* ���s�����̃R���W���� */
	//iColor	= GetColor(0, 0, 255);
	//DrawCapsule3D(this->stHorizontalCollision[0].vecCapsuleTop, this->stHorizontalCollision[0].vecCapsuleBottom, this->stHorizontalCollision[0].fCapsuleRadius, 16, iColor, iColor, FALSE);
	//DrawCapsule3D(this->stHorizontalCollision[1].vecCapsuleTop, this->stHorizontalCollision[1].vecCapsuleBottom, this->stHorizontalCollision[1].fCapsuleRadius, 16, iColor, iColor, FALSE);

	///* ���U���ړ�����W */
	//iColor = GetColor(255, 0, 255);
	//DrawCapsule3D(this->stMeleeStrongMoveCollsion.vecCapsuleTop, this->stMeleeStrongMoveCollsion.vecCapsuleBottom, this->stMeleeStrongMoveCollsion.fCapsuleRadius, 16, iColor, iColor, FALSE);
}

// �ړ�
void CharacterPlayer::Player_Move()
{
	/* �v���C���[�ړ��ʎ擾 */
	float fStickTiltMagnitude	= this->InputList->fGetGameInputMove();				// �X�e�B�b�N��|��������
	VECTOR vecInput				= this->InputList->vecGetGameInputMoveDirection();	// �ړ�����
	VECTOR vecAddMove			= VGet(0, 0, 0);									// �ړ���(���Z�p)

	/* �v���C���[�̏�Ԃ��擾 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* �v���C���[�̏�Ԃɉ����Ĉړ����x�̔{����ݒ� */
	float fMoveSpeedRatio = 1.f;
	switch (iPlayerState)
	{
		/* �ړ�������ʏ�ʂ�ɍs����� */
		case PLAYER_STATUS_FREE:				// ���R���
			/* �␳�����ɂ��� */
			fMoveSpeedRatio = 1.f;
			break;

		/* �ړ������𑬓x��}���čs����� */
		case PLAYER_STATUS_MELEE_POSTURE:		// �ߐڍU���\����
		case PLAYER_STATUS_PROJECTILE_POSTURE:	// �������U���\����
			/* �ړ����x�␳0.5�{�ɂ��� */
			// �����̒l
			fMoveSpeedRatio = 0.5f;
			break;

		/* �ړ��������s��Ȃ���� */
		case PLAYER_STATUS_DODGING:				// �����Ԓ�
		case PLAYER_STATUS_MELEE_WEEK:			// �ߐڍU����(��)
		case PLAYER_STATUS_MELEE_STRONG:		// �ߐڍU����(��)
		case PLAYER_STATUS_PROJECTILE:			// �������U����
			/* �ړ��������I������ */
			// �������̏�Ԃł͈ړ��������s��Ȃ�
			return;
	}

	/* 2025.01.09 �e�r�듹	�ړ������ǉ�		�J�n	*/
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �J�n	*/

	/* �ړ����͂�����Ă��邩�m�F */
	if (vecInput.x != 0 || vecInput.z != 0)
	{
		// �ړ����͂�����Ă���ꍇ
		/* ���݂̈ړ����x�擾 */
		float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();
		
		// �����t���O��true�Ȃ�ő�_�b�V����ԂɂȂ�
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

			//���t���[���ɒB�������A�_�b�V���G�t�F�N�g���o��������
			if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() == FLAME_COUNT_TO_MAX_SPEED)
			{
				/* �G�t�F�N�g�ǉ� */
				{
					/* �_�b�V���G�t�F�N�g�𐶐� */
					this->pDashEffect = new EffectSelfDelete;

					/* �G�t�F�N�g�̓ǂݍ��� */
					this->pDashEffect->Effect_Load("FX_dash/FX_dash");

					/* ���ǉ� */
					this->pDashEffect->SetDeleteCount(30);

					/* �G�t�F�N�g�̍��W�ݒ� */
					this->pDashEffect->SetPosition(this->vecPosition);

					/* �G�t�F�N�g�̉�]�ʐݒ� */
					this->pDashEffect->SetRotation(this->vecRotation);

					/* �G�t�F�N�g�̏����� */
					this->pDashEffect->Initialization();

					/* �G�t�F�N�g�����X�g�ɓo�^ */
					{
						/* �G�t�F�N�g�����X�g�ɓo�^ */
						this->ObjectList->SetEffect(this->pDashEffect);
					}
				}
			}
			//���t���[���ȏ�ɂȂ����瑖��i�ő�j��
			else if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() >= FLAME_COUNT_TO_MAX_SPEED)
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
		
		// �G�t�F�N�g�����݂��Ă���ꍇ�A�����X�V����
		if (pDashEffect != nullptr)
		{
			/* �G�t�F�N�g�̈ʒu��ݒ� */
			this->pDashEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 80, 0)));
			/* �G�t�F�N�g�̉�]�ʐݒ� */
			this->pDashEffect->SetRotation(this->vecRotation);
		}

		/* 2025.01.09 �e�r�듹	�ړ������ǉ�		�I��	*/
		/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �I��	*/

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
						this->PlayerStatusList->SetPlayerNowFallSpeed(-20.0f);

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
	/* 2025.01.09 �e�r�듹�@�ړ������ǉ�	�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/
	
	/* �v���C���[�̏�Ԃ��擾 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* �v���C���[��O��"�����Ԓ�"�ł��邩�m�F */
	if (iPlayerState == PLAYER_STATUS_DODGING)
	{
		// ��𒆂ł���ꍇ
		/* �����Ԃ��ێ�����鎞�Ԃ𒴂��Ă��Ȃ����m�F */
		if (this->PlayerStatusList->iGetPlayerNowDodgeFlame() <= PLAYER_DODGE_FLAME)
		{
			// �����Ă��Ȃ�(�����Ԃ��p������)�ꍇ
			/* ����ɂ��ړ�������ݒ� */
			this->vecMove = VScale(this->PlayerStatusList->vecGetPlayerDodgeDirection(), PLAYER_DODGE_SPEED);

			/* ����̌o�ߎ��Ԃ�i�߂� */
			this->PlayerStatusList->SetPlayerNowDodgeFlame(this->PlayerStatusList->iGetPlayerNowDodgeFlame() + 1);
		}
		else
		{
			// �����Ă���(�����Ԃ��I������)�ꍇ
			/* �����������t���O��L���ɂ��� */
			this->PlayerStatusList->SetPlayerAfterDodgeFlag(true);

			/* �v���C���[��Ԃ�"���R���"�ɐݒ� */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
		}
	}
	else
	{
		// ��𒆂łȂ��ꍇ
		/* ��������͂���Ă��邩�m�F */
		if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == true)
		{
			// ��������͂���Ă���ꍇ
			/* �󒆂ł̉���񐔐����𒴂��Ă��Ȃ��� */
			if (this->PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() < PLAYER_DODGE_IN_AIR_LIMIT)
			{
				/* ����J�n���̎��Ԃ����Z�b�g */
				this->PlayerStatusList->SetPlayerNowDodgeFlame(0);

				/* �������ݒ� */
				{
					/* ���͂ɂ��ړ��ʂ��擾 */
					VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();

					/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
					float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

					/* �ړ��ʂ��Z�o */
					VECTOR vecMove;
					vecMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
					vecMove.y = 0.0f;
					vecMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);

					/* ����̈ړ����������݂̈ړ��p�̌����ɐݒ� */
					this->PlayerStatusList->SetPlayerDodgeDirection(VNorm(vecMove));
				}

				/* �����Ԃ̐i�s�������Z�b�g */
				this->PlayerStatusList->SetPlayerDodgeProgress(0.0f);

				/* �����̉����x�������� */
				this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

				/* �v���C���[��Ԃ�"�����Ԓ�"�ɐݒ� */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_DODGING);

				/* �v���C���[�����n���Ă��Ȃ������m�F */
				if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
				{
					// ���n���Ă��Ȃ��ꍇ
					/* �󒆂ł̉���񐔂̃J�E���g��i�߂� */
					this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() + 1);
				}

				/* �G�t�F�N�g�ǉ� */
				{
					/* �_�b�V���G�t�F�N�g�𐶐� */
					this->pDashEffect = new EffectSelfDelete;

					/* �G�t�F�N�g�̓ǂݍ��� */
					this->pDashEffect->Effect_Load("FX_dash/FX_dash");

					/* ���ǉ� */
					this->pDashEffect->SetDeleteCount(60);

					/* �G�t�F�N�g�̍��W�ݒ� */
					this->pDashEffect->SetPosition(this->vecPosition);

					/* �G�t�F�N�g�̉�]�ʐݒ� */
					this->pDashEffect->SetRotation(this->vecRotation);

					/* �G�t�F�N�g�̏����� */
					this->pDashEffect->Initialization();

					/* �G�t�F�N�g�����X�g�ɓo�^ */
					{
						/* �G�t�F�N�g�����X�g�ɓo�^ */
						this->ObjectList->SetEffect(this->pDashEffect);
					}
				}
			}
		}
	}

	// �G�t�F�N�g�����݂��Ă���ꍇ�A�����X�V����
	if (pDashEffect != nullptr)
	{
		/* �G�t�F�N�g�̈ʒu��ݒ� */
		this->pDashEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 80, 0)));
		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pDashEffect->SetRotation(this->vecRotation);
	}

	/* 2025.01.09 �e�r�듹�@�ړ������ǉ�	�I�� */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�I��*/
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
	this->stVerticalCollision.vecLineStart.y	+=	PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd		=	stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y		-=	9999;

	/* �ȉ��A������(�߂��I�u�W�F�N�g�̂ݑΏۂɂ���悤�ɂ���) */
	/* ������擾 */
	auto& PlatformList = ObjectList->GetCollisionList();

	/* ���n������W */
	// �������l���ړ���̍��W�ɐݒ�
	float	fStandPosY = vecNextPosition.y;

	/* ���݂̒��n�t���O��ێ� */
	bool bLandingFlg = this->PlayerStatusList->bGetPlayerLandingFlg();

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
			if (stHitPolyDim.HitPosition.y >= fStandPosY)
			{
				// ���݂̒��n���W��荂���ʒu�ł���ꍇ
				/* �����̉����x�������� */
				this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

				
				/* �q�b�g�������W���v���C���[�������ēo���ʒu���Ⴂ�ʒu�ł��邩�m�F */
				if (fStandPosY < this->vecPosition.y + PLAYER_CLIMBED_HEIGHT)
				{
					// ���n���W���v���C���[�̌��݈ʒu���Ⴂ�ꍇ
					// �� �n�ʂɒ��n�����Ɣ��肷��
					/* ���n���W�𒅒n�������W�ɍX�V */
					fStandPosY = stHitPolyDim.HitPosition.y;

					/* �W�����v�񐔂����������� */
					this->PlayerStatusList->SetPlayerNowJumpCount(0);

					/* 2025.01.09 �e�r�듹�@�ړ������ǉ� �ǉ� */

					//�W�����v���̃t���O�����Z�b�g
					this->PlayerStatusList->SetPlayerJumpingFlag(false);

					//�W�����v���̉���񐔂����Z�b�g
					this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(0);

					this->PlayerStatusList->SetPlayerLanding(true);

					/* 2025.01.09 �e�r�듹�@�ړ������ǉ� �I�� */

				}
				else
				{
					// ���n���W���v���C���[�̌��݈ʒu��荂���ꍇ
					/* ���n���W���v���C���[���V��ɂ߂荞�܂Ȃ������ɍX�V */
					fStandPosY = stHitPolyDim.HitPosition.y - PLAYER_HEIGHT - PLAYER_CLIMBED_HEIGHT;

					/* ���[�v�𔲂��� */
					break;
				}
			}
		}
	}
	
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ�	�J�n*/
	/* ���n�t���O���������L���ɂȂ������m�F */
	if (bLandingFlg == false && this->PlayerStatusList->bGetPlayerLandingFlg() == true)
	{
		/* ��𒆂ɃG�t�F�N�g���o�Ȃ��悤�ɂ��� */
		if (this->PlayerStatusList->bGetPlayerAfterDodgeFlag() == false)
		{
			/* �G�t�F�N�g�ǉ� */
			{
				/* ���n�̃G�t�F�N�g�𐶐� */
				this->pLandEffect = new EffectSelfDelete;

				/* �G�t�F�N�g�̓ǂݍ��� */
				this->pLandEffect->Effect_Load("FX_land/FX_land");

				/* ���ǉ� */
				this->pLandEffect->SetDeleteCount(30);

				/* �G�t�F�N�g�̍��W�ݒ� */
				this->pLandEffect->SetPosition(this->vecPosition);

				/* �G�t�F�N�g�̉�]�ʐݒ� */
				this->pLandEffect->SetRotation(this->vecRotation);

				/* �G�t�F�N�g�̏����� */
				this->pLandEffect->Initialization();

				/* �G�t�F�N�g�����X�g�ɓo�^ */
				{
					/* �G�t�F�N�g�����X�g�ɓo�^ */
					this->ObjectList->SetEffect(this->pLandEffect);
				}
			}
		}
	}
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ�	�I��*/

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
		// �� ���̈ʒu����ړ���̈ʒu�֌������J�v�Z���R���W�������쐬
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleBottom	= VAdd(this->vecPosition,	VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleTop		= VAdd(vecNextPosition,		VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].fCapsuleRadius		= PLAYER_WIDE;
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleBottom	= VAdd(this->vecPosition,	VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleTop		= VAdd(vecNextPosition,		VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].fCapsuleRadius	= PLAYER_WIDE;

		/* ������擾 */
		auto& PlatformList = ObjectList->GetCollisionList();

		/* ����ƐڐG���邩�m�F */
		for (auto* platform : PlatformList)
		{
			/* ����Ƃ̐ڐG���� */
			for (int i = 0; i < PLAYER_MOVE_COLLISION_MAX; i++)
			{
				/* �I�u�W�F�N�g�ƐڐG���Ă��邩�m�F */
				MV1_COLL_RESULT_POLY_DIM stHitPolyDim = platform->HitCheck_Capsule(stHorizontalCollision[i]);

				/* �ڐG���Ă��邩�m�F */
				if (stHitPolyDim.HitNum > 0)
				{
					// 1�ȏ�̃|���S�����ڐG���Ă���ꍇ
					/* �@���x�N�g���̍쐬 */
					VECTOR vecNormalSum		= VGet(0.f, 0.f, 0.f);

					/* �|���S���ƐڐG�������W */
					VECTOR vecHitPos		= VGet(0.f, 0.f, 0.f);

					/* �ڐG�����|���S������@���x�N�g�����擾�����Z���� */
					for (int j = 0; j < stHitPolyDim.HitNum; j++)
					{
						/* �@���x�N�g�����擾 */
						// �� �@���x�N�g����0�ł���Ȃ�΁A���Z���Ȃ�
						if (VSize(stHitPolyDim.Dim[j].Normal) > 0.f)
						{
							// �@���x�N�g����0�łȂ��ꍇ
							/* �@���x�N�g����Y���������� */
							stHitPolyDim.Dim[j].Normal.y = 0.f;

							/* �@���x�N�g���𐳋K�� */
							VECTOR vecNormal = VNorm(stHitPolyDim.Dim[j].Normal);

							/* �@���x�N�g�������v�ɉ��Z */
							vecNormalSum = VAdd(vecNormalSum, vecNormal);
						}
					}

					/* �擾�����@���x�N�g���𐳋K�� */
					// �� �擾�����@���x�N�g���̕��ς��擾
					vecNormalSum = VNorm(vecNormalSum);

					/* �ړ�����W�ɋ��̃|���S�����쐬 */
					COLLISION_SQHERE stSphere;
					stSphere.vecSqhere		= vecNextPosition;
					stSphere.fSqhereRadius	= PLAYER_WIDE;

					/* �@���̕����Ƀv���C���[�������o�� */
					// �� �Ώۂ̃R���W�����ƐڐG���Ȃ��Ȃ�܂ŉ����o��
					// �� ���̂����ł́A�����ňړ������ꍇ�ɃR���W�����������o����Ȃ��\��������̂ŏC���\��
					bool bHitFlag = true;
					while (bHitFlag)
					{
						/* ���̃|���S����@���x�N�g���̕����ֈړ� */
						stSphere.vecSqhere = VAdd(stSphere.vecSqhere, VScale(vecNormalSum, 1.f));

						/* ���̂ƃ|���S���̐ڐG���� */
						bHitFlag = platform->HitCheck(stSphere);
					}

					/* ���̃R���W�������ڐG���Ȃ��Ȃ����ʒu���ړ�����W�ɐݒ� */
					vecNextPosition = stSphere.vecSqhere;
				}
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
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT - PLAYER_WIDE, 0));
	this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0, PLAYER_WIDE, 0));
	this->stCollisionCapsule.fCapsuleRadius		= PLAYER_WIDE;
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

	/* 2025.01.24 �e�r�듹�@	�U�������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ�	�J�n*/

	/* �U�����͂�����Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		// �U�����͂�����Ă���ꍇ
		/* �v���C���[���[�V������"����(����)"�ȊO�ł��邩�m�F */
		if (this->PlayerStatusList->iGetPlayerMotion() != PLAYER_MOTION_DRAW_SWORD_CHARGE)
		{
			// ����(����)�ȊO�ł���ꍇ
			/* �v���C���[���[�V������"����(����)"�ɕύX */
			this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_DRAW_SWORD_CHARGE);

			/* ����(����)�̃G�t�F�N�g�𐶐� */
			this->pChargeEffect = new EffectManualDelete;
			/* �G�t�F�N�g�̓ǂݍ��� */
			this->pChargeEffect->Effect_Load("FX_charge/FX_charge");

			/* �G�t�F�N�g�̏����� */
			this->pChargeEffect->Initialization();

			/* �G�t�F�N�g�����X�g�ɓo�^ */
			{
				/* �G�t�F�N�g�����X�g�ɓo�^ */
				this->ObjectList->SetEffect(this->pChargeEffect);
			}
		}

		/* �ߐڍU��(��)�`���[�W���� */
		{
			/* �v���C���[�̌��݂̍U���`���[�W�t���[�������Z */
			PlayerStatusList->SetPlayerNowAttakChargeFlame(iNowAttakChargeFlame + 1);

			/* �v���C���[�̌������J�����̌����ɌŒ� */
			this->PlayerStatusList->SetPlayerAngleX(this->PlayerStatusList->fGetCameraAngleX());

			/* �ړ��ʎZ�o */
			float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 10.f;

			/* �ړ������Z�o */
			VECTOR vecMoveDirection = VNorm(VSub(this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraPosition()));

			/* �f�o�b�O�p�ړ�����W���쐬 */
			this->stMeleeStrongMoveCollsion.vecCapsuleTop = VAdd(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT - PLAYER_WIDE, 0)), VScale(vecMoveDirection, fMove));
			this->stMeleeStrongMoveCollsion.vecCapsuleBottom = VAdd(VAdd(this->vecPosition, VGet(0, PLAYER_WIDE, 0)), VScale(vecMoveDirection, fMove));
			this->stMeleeStrongMoveCollsion.fCapsuleRadius = PLAYER_WIDE;

			/* �ߐڍU��(��)�ɂ��ړ��ʂ�ݒ� */
			this->PlayerStatusList->SetPlayerChargeAttakTargetMove(VScale(vecMoveDirection, fMove));
		}

		//���߂���������t���[�����ɂȂ�����
		if (iNowAttakChargeFlame == PLAYER_CHARGE_FINISH_FLAME)
		{
			/* ���ߊ����G�t�F�N�g�𐶐� */
			this->pChargeFinishEffect = new EffectSelfDelete;

			/* ���ߊ����G�t�F�N�g�̓ǂݍ��� */
			this->pChargeFinishEffect->Effect_Load("FX_charge_finish/FX_charge_finish");

			/* ���ߊ����G�t�F�N�g�̏����� */
			this->pChargeFinishEffect->Initialization();

			/* ���ߊ����G�t�F�N�g�̎��Ԃ�ݒ� */
			this->pChargeFinishEffect->SetDeleteCount(20);

			/* ���ߊ����G�t�F�N�g�����X�g�ɓo�^ */
			{
				/* ���ߊ����G�t�F�N�g�����X�g�ɓo�^ */
				this->ObjectList->SetEffect(this->pChargeFinishEffect);
			}

			/* ���ߊ����G�t�F�N�g�̍��W�ݒ� */
			this->pChargeFinishEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 80, 0)));

			this->pChargeEffect->SetDeleteFlg(true);

			this->pChargeHoldEffect = new EffectManualDelete;

			/* �G�t�F�N�g�̓ǂݍ��� */
			this->pChargeHoldEffect->Effect_Load("FX_charge_hold/FX_charge_hold");

			/* �G�t�F�N�g�̏����� */
			this->pChargeHoldEffect->Initialization();

			/* �G�t�F�N�g�����X�g�ɓo�^ */
			{
				/* �G�t�F�N�g�����X�g�ɓo�^ */
				this->ObjectList->SetEffect(this->pChargeHoldEffect);
			}
		}

		//�G�t�F�N�g�����݂��Ă���ꍇ�A�����X�V����
		if (this->pChargeEffect != nullptr)
		{
			/* ���߃G�t�F�N�g�̍��W�ݒ� */
			this->pChargeEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 80, 0)));
		}
		if (this->pChargeHoldEffect != nullptr)
		{
			/* ���ߊ�����G�t�F�N�g�̍��W�ݒ� */
			this->pChargeHoldEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 80, 0)));
		}
		
	
		/* ����(����)�G�t�F�N�g�̉�]�ʐݒ� */
		this->pChargeEffect->SetRotation(this->vecRotation);
	}
	else
	{
		// �U�����͂�����Ă��Ȃ��ꍇ
		/* �U���`���[�W�t���[���ɉ����ď�����ύX */
		if (iNowAttakChargeFlame < PLAYER_CHARGE_TO_STRONG_TIME)
		{
			// ���U���ɐ؂�ւ��O�̏ꍇ
			/* �v���C���[�̏�Ԃ�"�ߐڍU����(��)"�ɐݒ� */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_MELEE_WEEK);
		}
		else
		{
			// ���U���ɂȂ�Ȃ��ꍇ
			/* �v���C���[�̏�Ԃ�"�ߐڍU����(��)"�ɐݒ� */
			this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_MELEE_STRONG);

			/* �v���C���[�̂��ߍU���p�̃J�E���g�������� */
			this->PlayerStatusList->SetPlayerChargeAttackCount(0);

			/* �����̉����x�������� */
			this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);
		}

		/* �v���C���[�̌��݂̍U���`���[�W�t���[�������Z�b�g */
		this->PlayerStatusList->SetPlayerNowAttakChargeFlame(0);


		if (this->pChargeEffect != nullptr)
		{
			/* ����(����)�G�t�F�N�g���폜 */
			this->pChargeEffect->SetDeleteFlg(true);
		}

		if (this->pChargeHoldEffect != nullptr)
		{
			/* ����(����)�G�t�F�N�g���폜 */
			this->pChargeHoldEffect->SetDeleteFlg(true);
		}
	}
}

// �ߐڍU��(��)
void CharacterPlayer::Player_Melee_Weak()
{
	/* 2025.01.22 �e�r�듹�@�U�������ǉ�	�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/

	/* �U�����[�V�������m�F */
	// �����݂̃��[�V�������ߐڍU��(��)�ł��邩�m�F
	// if
	{
		// �ߐڍU��(��)�ł���ꍇ
		/* �v���C���[���[�V�����̌��݂̃J�E���g��i�߂� */

		/* ���݂̃��[�V�����̑����Ԃ��擾 */

		/* ���݂̃��[�V�����̑����Ԃ𒴂��Ă��邩 */
		// if
		{
			// �����Ă���ꍇ
			/* �v���C���[��Ԃ�"���R���"�ɕύX */
			//this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);

			/* �v���C���[�̃��[�V������"�ҋ@"�ɐݒ� */
			//this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_WAIT);

			/* �v���C���[�̃��[�V�����̌��݂̃J�E���g�������� */

			/* �o���b�g�N���X"�ߐڍU��(��)"�̍폜�t���O��L�� */
			//this->pAddBullet->SetDeleteFlag(true);

			/* ���̃N���X�ŏ�������o���b�g�N���X"�ߐڍU��(��)"�̃n���h���������� */
			//this->pBulletMeleeWeak = nullptr;
		}
	}
	// else
	{
		// �ߐڍU��(��)�łȂ��ꍇ
		/* �v���C���[�̃��[�V�������ߐڍU��(��)�ɐݒ� */
		
		/* �v���C���[�̃��[�V�����̌��݂̃J�E���g�������� */

		/* �ߐڍU���Ƃ��Ĉ����e���쐬 */
		// �����݂̃v���C���[�̌����ɒe���쐬
		this->pBulletMeleeWeak = new BulletPlayerMeleeWeak;

		/* �������W���擾 */
		{
			/* �U���̐��������̐ݒ� */
			// ���v���C���[�̌����ł͂Ȃ��J�����̌����Ƃ���
			VECTOR vecInput = VGet(0.f, 0.f, 1.f);

			/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
			float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

			/* �U�����W���Z�o */
			VECTOR vecAdd;
			// ����
			vecAdd.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
			vecAdd.y = 0.f;
			vecAdd.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
			vecAdd = VNorm(vecAdd);
			vecAdd = VScale(vecAdd, PLAYER_WIDE);
			// ����
			vecAdd.y = PLAYER_HEIGHT / 2.f;

			/* �U���������W��ݒ� */
			this->pBulletMeleeWeak->SetPosition(VAdd(this->vecPosition, vecAdd));
		}

		/* �U���̌�����ݒ� */
		this->pBulletMeleeWeak->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetCameraAngleX()), 0.0f));

		/* ���������s�� */
		this->pBulletMeleeWeak->Initialization();

		/* �o���b�g���X�g�ɒǉ� */
		ObjectList->SetBullet(this->pBulletMeleeWeak);
	}

	/* 2025.01.22 �e�r�듹	�U�������ǉ�		�I�� */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�I�� */
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ�	�I��*/

	/* �������Ȃ̂łƂ肠�������R��Ԃɖ߂� */
	this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);
}

// �ߋ����U��(��)
void CharacterPlayer::Player_Charge_Attack()
{
	/* 2025.01.22 �e�r�듹�@�U�������ǉ�	�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n */

	/* ���ߍU���p�̃J�E���g���擾 */
	int iChargeAttackCount = this->PlayerStatusList->iGetPlayerChargeAttackCount();

	/* �J�E���g���m�F */
	if (iChargeAttackCount == 0)
	{
		// 0�ł���ꍇ
		// �����[�V�����J�ڒ���ł���ꍇ
		/* �v���C���[�̃��[�V�������ߐڍU��(��)�ɕύX���� */
	}
	else if(iChargeAttackCount <= 20)
	{
		// 20�ȉ��ł���ꍇ
		/* ���[�V�����̏������쒆?�Ȃ̂ł��̏�Ԃł͍U�����Ȃ� */

	}
	else
	{
		// 21�ȏ�ł���ꍇ
		/* �U�����ړ����� */
		{
			/* �ߐڍU��(��)�ɂ��ړ��ʂ��擾 */
			VECTOR vecMoveDirection = this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove();

			/* �ړ��ʂ�float�^�Ŏ擾 */
			float fMove	= VSize(vecMoveDirection);

			/* �U�����ړ������ɓ����Ă���̃J�E���g���擾 */
			int iCount	= iChargeAttackCount - 20;

			/* �ړ��ʂ��ړ����x�Ŋ����Ă��̏������s���񐔂��Z�o���� */
			int	iMoveCount = fMove / PLAYER_MELEE_STRONG_MOVESPEED;

			/* �v���C���[�ړ� */
			if (iCount <= iMoveCount)
			{
				// ���݂̃J�E���g���ړ��񐔈ȉ��ł���ꍇ
				/* �ړ��ʕ��v���C���[���ړ������� */
				this->vecMove = VAdd(this->vecMove, VScale(VNorm(vecMoveDirection), PLAYER_MELEE_STRONG_MOVESPEED));
			}
			else
			{
				// �Ō�̈ړ��̏ꍇ
				/* �Ō�̈ړ��ʂ��擾 */
				float	iLastMove = fMove - (iMoveCount * PLAYER_MELEE_STRONG_MOVESPEED);

				/* �Ō�̈ړ��ʕ��v���C���[���ړ������� */
				this->vecMove = VAdd(this->vecMove, VScale(VNorm(vecMoveDirection), iLastMove));

				// �����ȊO�ł���ꍇ(��A�̍s�����I�������ꍇ)
				/* �v���C���[�̏�Ԃ�"���R���"�ɑJ�� */
				this->PlayerStatusList->SetPlayerState(PLAYER_STATUS_FREE);

				/* �v���C���[�̃��[�V������"����(��)(�I��)"�ɕύX */
				this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_DRAW_SWORD_END);
			}

			/* �ߐڍU���Ƃ��Ĉ����e���쐬 */
			// ���ʏ�̒e�Ƃ͈Ⴂ�J�v�Z���^�ō쐬����
			{
				BulletPlayerMeleeStrong* pBulletMeleeStrong = new BulletPlayerMeleeStrong;

				/* �e�Ɏg�p����J�v�Z�����쐬 */
				COLLISION_CAPSULE stBulletCollision;

				/* �R���W�����̎Z�o */
				{
					/* �����蔻��͑傫�߂Ɏ��(���Ŕ��a���v���C���[�̑S���ɐݒ�) */
					stBulletCollision.fCapsuleRadius = PLAYER_HEIGHT;

					/* �Е��͌��݂̃v���C���[�̒��S�ɐݒ� */
					stBulletCollision.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2.f, 0));

					/* �����Е��͈ړ���(����)�̃v���C���[�̒��S�ɐݒ� */
					stBulletCollision.vecCapsuleBottom = VAdd(stBulletCollision.vecCapsuleTop, this->vecMove);
				}

				/* �쐬�����e�ɃR���W������ݒ� */
				pBulletMeleeStrong->SetCollision_Capsule(stBulletCollision);

				/* �o���b�g���X�g�ɒǉ� */
				ObjectList->SetBullet(pBulletMeleeStrong);
			}

			/* �G�t�F�N�g�ǉ� */
			{
				/* ����(��)�̃G�t�F�N�g�𐶐� */
				this->pChargeAttakEffect = new EffectSelfDelete;

				/* �G�t�F�N�g�̓ǂݍ��� */
				this->pChargeAttakEffect->Effect_Load("FX_iai_dash/FX_iai_dash");

				/* ���ǉ� */
				this->pChargeAttakEffect->SetDeleteCount(30);

				/* �G�t�F�N�g�̍��W�ݒ� */
				this->pChargeAttakEffect->SetPosition(this->vecPosition);

				/* �G�t�F�N�g�̉�]�ʐݒ� */
				this->pChargeAttakEffect->SetRotation(this->vecRotation);

				/* �G�t�F�N�g�̏����� */
				this->pChargeAttakEffect->Initialization();

				/* �G�t�F�N�g�����X�g�ɓo�^ */
				{
					/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
					DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
					/* �G�t�F�N�g�����X�g�ɓo�^ */
					ObjectListHandle->SetEffect(this->pChargeAttakEffect);
				}
			}
		}
	}

	/* ���ߍU���p�̃J�E���g��+1���� */
	this->PlayerStatusList->SetPlayerChargeAttackCount(iChargeAttackCount + 1);

	/* 2025.01.22 �e�r�듹�@�U�������ǉ�	�I�� */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�I�� */	
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
