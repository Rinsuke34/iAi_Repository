/* 2024.12.15 ��򕗏�	�t�@�C���쐬 */
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.01.30 �e�r�듹	���[�V���������ǉ� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� */
/* 2025.02.14 �e�r�듹	��]�֘A�̊֐��ǉ� */
/* 2025.02.14 �e�r�듹	�N�i�C�֘A�̏����ǉ� */
/* 2025.02.19 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.02.22 �e�r�듹	�ǃL�b�N�����ǉ� */
/* 2025.02.26 �e�r�듹	�N�[���^�C���̏����ǉ� */
/* 2025.03.02 ��򕗏�	�������A�����쐬 */
/* 2025.03.06 �e�r�듹	�����蔻�菈���C�� */
/* 2025.03.08 ��򕗏�	�V���f���Ή� */
/* 2025.03.11 �e�r�듹	���[�V�����֘A�̏����ǉ� */
/* 2025.03.13 �e�r�듹	�N�i�C�֘A�̏����ǉ� */
/* 2025.03.14 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.03.16 ��򕗏�	�������A�����X�V */
/* 2025.03.17 �e�r�듹	�N�[���^�C���̏����ǉ� */
/* 2025.03.21 �e�r�듹	�������A�����ǉ� */
/* 2025.03.22 ��򕗏�	�������̃J�����v���C���[�Ǐ]�쐬 */
/* 2025.03.25 ��򕗏�	�T�E���h�ǉ� */

#include "CharacterPlayer.h"

/* �v���C���[�N���X�̒�` */
// �R���X�g���N�^
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* ������ */
	{
		/* �I�u�W�F�N�g�̃n���h�� */
		this->pBulletMeleeWeak		=	nullptr;	// �ߐڍU��(��)�̒e
		this->pBulletKunaiWarp		=	nullptr;	// �N�i�C(���[�v)�̒e		/* 2025.03.13 �e�r�듹	�N�i�C�֘A�̏����ǉ� */
		this->pBulletKunaiExplosion	=	nullptr;	// �N�i�C(����)�̒e			/* 2025.03.13 �e�r�듹	�N�i�C�֘A�̏����ǉ� */


		/* �G�t�F�N�g�̃n���h�� */
		this->pChargeEffect			=	nullptr;	//���߃G�t�F�N�g			/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� */
		this->pChargeHoldEffect		=	nullptr;	//���ߊ�����G�t�F�N�g		/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� */
		this->pDodgeEffect			=	nullptr;	//����G�t�F�N�g			/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� */
	

		/* �ϐ� */
		this->vecMove					= VGet(0.f, 0.f, 0.f);	// �ړ���
		this->vecNormalSum				= VGet(0.f, 0.f, 0.f);	// �v���C���[�ɐڐG����I�u�W�F�N�g�̖@���x�N�g���̍��v		/* 2025.02.22 �e�r�듹	�ǃL�b�N�����ǉ� */
		this->iObjectType				= OBJECT_TYPE_PLAYER;	// �I�u�W�F�N�g�̎��
		this->iMeleeWeakNowCoolTime		= 0;					// �ߐڍU��(��)�N�[���^�C��									/* 2025.02.26 �e�r�듹	�N�[���^�C���̏����ǉ� */
		this->iProjectileNowCoolTime	= 0;					// �������U���N�[���^�C��									/* 2025.02.26 �e�r�듹	�N�[���^�C���̏����ǉ� */
		this->iDodgeNowCoolTime			= 0;					// ����N�[���^�C��											/* 2025.02.26 �e�r�듹	�N�[���^�C���̏����ǉ� */
		this->iJumpNowCoolTime			= 0;					// �W�����v�N�[���^�C��										/* 2025.03.17 �e�r�듹	�N�[���^�C���̏����ǉ� */
		this->iFallRecoveryDelayTime	= 0;					// �������̕��A�܂ł̑ҋ@����								/* 2025.03.22 ��򕗏�	�������̃J�����v���C���[�Ǐ]�쐬 */
		this->bPlayRunSound				= false;				// �T�E���h"����"���Đ������̃t���O							/* 2025.03.25 ��򕗏�	�T�E���h�ǉ� */
		this->bPlayChargeSound			= false;				// �T�E���h"���ߋ����`���[�W"���Đ������̃t���O				/* 2025.03.25 ��򕗏�	�T�E���h�ǉ� */

		/* �ϐ�(�f�o�b�O�p) */
		this->stVerticalCollision								= {};				// ���������̃R���W����
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP]	= {};				// ���������R���W����(�㑤)
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN]	= {};				// ���������R���W����(����)
		this->stMeleeStrongMoveCollsion							= {};				// �ߐڍU��(��)�̃R���W����(�ړ���̍��W)
		this->vecMoveSize										= VGet(0, 0, 0);	// �ړ���
		this->iFallingFrame										= 0;				// ������ԂɂȂ��Ă���̃t���[����		/* 2025.03.11 �e�r�듹 ���[�V�����֘A�̏����ǉ� */
	}

	/* �f�[�^���X�g�擾 */
	{
		/* "���͊Ǘ�"���擾 */
		this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));

		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�v���C���[���"���擾 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�G�t�F�N�g���\�[�X�Ǘ�"���擾 */
		this->EffectList		= dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));

		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList	= dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));;
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Player/Player");

		/* �R���W�����t���[���ԍ��擾 */
		/* ���̃t���[�� */
		this->iKatanaFrameNo		= MV1SearchFrame(this->iModelHandle, "Katana_Waist_Hips");		/* 2025.02.19 �e�r�듹	�ǉ� */

		/* 2025.03.13 ��򕗏� �V���f���ǉ� �J�n */
		/* ���̃t���[���ԍ� */
		this->iKatanaFrameNo_Waist		= MV1SearchFrame(this->iModelHandle, "Katana_Waist");		// ���̃t���[���ԍ�(�w��)
		this->iKatanaFrameNo_RightHand	= MV1SearchFrame(this->iModelHandle, "Katana_RightHand");	// ���̃t���[���ԍ�(�E��)
		/* 2025.03.13 ��򕗏� �V���f���ǉ� �I�� */

		/* �㔼�g�̃t���[���ԍ��擾 */
		this->iUpperBodyFrameNo		= MV1SearchFrame(this->iModelHandle, "Character1_Spine");		/* 2025.03.08 ��򕗏� �V���f���Ή� */
		
		/* �N�i�C������̃t���[�� */
		this->iKunaiHandFrameNo		= MV1SearchFrame(this->iModelHandle, "Kunai");					/* 2025.03.10 �e�r�듹	�ǉ� */
	}

	/* ���[�V���������� */
	MotionReset();

	/* �J�n���̃��[�V�����ݒ� */
	StartMotionSet();
}

// �f�X�g���N�^
CharacterPlayer::~CharacterPlayer()
{
	/* ���[�v���鋰��̂���SE���~���� */
	gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_RUN);
	gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE_HOLD);
	gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE);
}

// ������
void CharacterPlayer::Initialization()
{
	CharacterBase::Initialization();

	/* �R���W�������X�V */
	CollisionUpdate();
}

// ���Z�b�g����
void CharacterPlayer::Reset()
{
	/* ���W�A��]�ʁA�g�嗦�������l�ɐݒ� */
	this->vecPosition	= this->vecPosition_Initial;
	this->vecScale		= this->vecScale_Initial;
	this->vecRotation	= this->vecRotation_Initial;

	/* ���[�V�����������ݒ� */
	this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WAIT);
	this->PlayerStatusList->SetPlayerMotion_Move_Old(MOTION_ID_MOVE_WALK);
	this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
	this->PlayerStatusList->SetPlayerMotion_Attack_Old(MOTION_ID_ATTACK_NONE);


	/* �v���C���[��ԏ����� */
	this->PlayerStatusList->SetPlayerMoveState(PLAYER_MOVESTATUS_FREE);
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

	/* ���S�t���O�𖳌��ɂ��� */
	this->PlayerStatusList->SetPlayerDeadFlg(false);
}

// �X�V
void CharacterPlayer::Update()
{
	/* �Q�[����Ԃ�"�Q�[�����s��"�ȊO�ł��邩�m�F */
	if (StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		// �Q�[�����s���łȂ��ꍇ
		/* ���[�v���鋰��̂���SE���~���� */
		gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_RUN);
		gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE_HOLD);
		gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_RUN);
	}

	/* �J�n�����[�V�����J�E���g���L��(1�ȏ�)�ł��邩�m�F */
	if (this->PlayerStatusList->iGetFastMotionCount() > 0)
	{
		// �L���ł���ꍇ
		/* �J�n�����[�V�����̏������s�� */
		FastMotion();

		/* ���W�ݒ� */
		MV1SetPosition(this->iModelHandle, this->vecPosition);

		return;
	}

	/* ���t���[�����{���鏉�������� */
	{
		/* �ړ��ʂ����Z�b�g */
		this->vecMove = VGet(0, 0, 0);

		/* �J�������[�h��"�t���[���[�h"�ɕύX */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_NORMAL);
	}

	/* �����蔻�菈�� */
	PlayerHitCheck();

	/* �v���C���[�̌���HP��0�ȉ�(���S���)�ł��邩�m�F */
	if (this->PlayerStatusList->iGetPlayerNowHp() <= 0)
	{
		// HP��0�ȉ�(���S���)�ł���ꍇ
		/* �v���C���[�̏�Ԃ�"���S"�ɂ��� */
		this->PlayerStatusList->SetPlayerMoveState(PLYAER_MOVESTATUS_DEAD);
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_DEAD);

		/* �v���C���[�̃��[�V������"���S"�ɐݒ� */
		this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_DIE);
		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
	}

	/* �U���n�A�N�V�������� */
	{
		/* �U����ԑJ�ڊǗ� */
		// ���v���C���[�̓��͂ɉ����čU����Ԃ�J��
		Player_Attack_Transition();
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

	/* �㉺����(Y��)�ړ����� */
	{
		/* �W�����v���� */
		Player_Jump();

		/* �d�͏��� */
		Player_Gravity();

		/* �ړ�����(��������) */
		Movement_Vertical();
	}

	/* �R���W�������X�V */
	CollisionUpdate();

	/* ���[�V�����J�ڊǗ� */
	Player_Motion_Transition();

	/* �V�F�C�v���� */
	Player_Shape();

	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* �N�[���^�C���̍X�V */
	UpdateCooldownTime();

	/* 2025.03.02 ��򕗏� �������A�����쐬 �J�n */
	/* �v���C���[�������������m�F */
	if (PlayerStatusList->bGetFallFlg() == true)
	{
		// �������Ă���ꍇ
		/* 2025.03.22 ��򕗏� �������̃J�����v���C���[�Ǐ]�쐬 �J�n */
		/* �������̕��A�܂ł̑ҋ@���Ԃ�i�߂� */
		this->iFallRecoveryDelayTime++;

		/* �J�������[�h��"����"�ɐݒ肷�� */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_FALL);

		/* ���A���Ԃ��w��̎��Ԃ𒴂��Ă��邩�m�F */
		if (this->iFallRecoveryDelayTime >= PLAYER_FALL_DELAY)
		{
			// �����Ă���ꍇ
			/* �������A���� */
			PlayerFallRecovery();

			/* ���A���Ԃ������� */
			this->iFallRecoveryDelayTime = 0;
		}
		/* 2025.03.22 ��򕗏� �������̃J�����v���C���[�Ǐ]�쐬 �I�� */
	}
	/* 2025.03.02 ��򕗏� �������A�����쐬 �I�� */
}

// �R���W�����X�V
void CharacterPlayer::CollisionUpdate()
{
	/* �v���C���[�̃R���W�������X�V */
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT - PLAYER_WIDE, 0));
	this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0, PLAYER_WIDE, 0));
	this->stCollisionCapsule.fCapsuleRadius		= PLAYER_WIDE;
}

/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
/* 2025.02.19 �e�r�듹	�G�t�F�N�g�����ǉ� �J�n */
/* 2025.03.06 �e�r�듹	�����蔻�菈���C�� �J�n */
/* �����蔻�菈�� */
void CharacterPlayer::PlayerHitCheck()
{
	/* �v���C���[�̏�Ԃ��擾 */
	/* �ړ���� */
	int iPlayerMoveState	= this->PlayerStatusList->iGetPlayerMoveState();
	/* �U����� */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* �v���C���[����e�������s����(���G��)���肷��t���O */
	bool bHiteFlag = true;

	/* ���G���Ԓ��ł��邩�m�F */
	if (this->PlayerStatusList->iGetPlayerNowInvincibleTime() > 0)
	{
		// ���G���Ԓ��ł���ꍇ
		/* ���G���Ԃ����� */
		this->PlayerStatusList->SetPlayerNowInvincibleTime(this->PlayerStatusList->iGetPlayerNowInvincibleTime() - 1);
	}
	else
	{
		// ���G���Ԓ��łȂ��ꍇ
		/* �v���C���[�̈ړ���Ԃ���e�������󂯂��Ԃ��m�F */
		switch (iPlayerMoveState)
		{
			/* ��e�������s����� */
			case PLAYER_MOVESTATUS_FREE:			// ���R���	
				/* ��e�������s����� */
				bHiteFlag = true;	
				break;

			/* ��e�������s��Ȃ����(���G���) */
			case PLAYER_MOVESTATUS_EVENT:				// �C�x���g���(����s��)
			case PLAYER_MOVESTATUS_DODGING:				// �����Ԓ�
			case PLYAER_MOVESTATUS_DEAD:				// ���S���(����s��)

				/* ��e�������s��Ȃ�(���G���) */
				bHiteFlag = false;
					
				break;
		}
		/* �v���C���[�̍U����Ԃ���e�������󂯂��Ԃ��m�F */
		switch (iPlayerAttackState)
		{
			/* ��e�������s����� */			
			case PLAYER_ATTACKSTATUS_FREE:					// ���R���	
			case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// �ߐڍU���\����
			case PLAYER_ATTACKSTATUS_MELEE_WEEK:			// �ߐڍU����(��)	
			case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// �������U���\����
			case PLAYER_ATTACKSTATUS_PROJECTILE:			// �������U����

				/* ��e�������s�� */
				bHiteFlag = true;
				
				break;
	
			/* ��e�������s��Ȃ����(���G���) */
			case PLAYER_ATTACKSTATUS_EVENT:					// �C�x���g���(����s��)
			case PLAYER_ATTACKSTATUS_MELEE_STRONG:			// �ߐڍU����(��)
			case PLAYER_ATTACKSTATUS_DEAD:					// ���S���(����s��)

				/* ��e�������s��Ȃ�(���G���) */
				bHiteFlag = false;

				break;
			
		}
	
		/* ��e���� */
		/* ��e�������s����Ԃ��m�F���� */
		if(bHiteFlag == true)
		{
			/* �o���b�g���X�g���擾 */
			auto& BulletList = ObjectList->GetBulletList();

			/* �e�Ƃ̓����蔻�� */
			for (auto* bullet : BulletList)
			{
				/* �I�u�W�F�N�g�^�C�v���e��(�G)�ł���Ȃ画����s�� */
				if (bullet->iGetObjectType() == OBJECT_TYPE_BULLET_ENEMY)
				{
					// �e��(�G)�ł���ꍇ
					/* �e�ۂƂ̓����蔻�� */
					if (bullet->HitCheck(this->stCollisionCapsule))
					{
						// �������Ă���ꍇ
						/* �v���C���[��HP������ */
						this->PlayerStatusList->SetPlayerNowHp(this->PlayerStatusList->iGetPlayerNowHp() - 1);

						/* ��_���[�W�J�E���g�����Z���� */
						this->PlayerStatusList->SetPlayerDamageCount(this->PlayerStatusList->iGetPlayerDamageCount() + 1);

						/* �v���C���[�̖��G���Ԃ�ݒ� */
						this->PlayerStatusList->SetPlayerNowInvincibleTime(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());

						/* �e�̍폜�t���O��L���ɂ��� */
						bullet->SetDeleteFlg(true);

						/* "��_���[�W"��SE���Đ� */
						gpDataList_Sound->SE_PlaySound(SE_PLAYER_DAMAGE);

						/* "��_���[�W�r���r��"��SE���Đ� */
						gpDataList_Sound->SE_PlaySound(SE_PLAYER_DAMAGE_ELEC);

						/* ��_���[�W�{�C�X���Đ� */
						gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_DAMAGE);

						/* ��_���[�W�̃G�t�F�N�g�𐶐� */
						{
							/* �_���[�W�������G�t�F�N�g */
							{
								/* ��_���[�W�̏u�Ԃɔ�������G�t�F�N�g��ǉ� */
								EffectSelfDelete* pDamageEffect = new EffectSelfDelete();

								/* ���W��ݒ� */
								pDamageEffect->SetPosition(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2, 0)));

								/* �G�t�F�N�g���擾 */
								pDamageEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_damaged/FX_damaged"));

								/* �g�嗦��ݒ� */
								pDamageEffect->SetScale(VGet(1.f, 1.f, 1.f));

								/* �폜�J�E���g��ݒ� */
								// ������1�b��
								pDamageEffect->SetDeleteCount(60);

								/* �G�t�F�N�g���������� */
								pDamageEffect->Initialization();

								/* �I�u�W�F�N�g���X�g�ɓo�^ */
								this->ObjectList->SetEffect(pDamageEffect);
							}
							
							/* ���d�G�t�F�N�g */
							{
								/* ���d�G�t�F�N�g�𐶐� */
								EffectSelfDelete_PlayerFollow* pShockEffect = new EffectSelfDelete_PlayerFollow(false);

								/* ���d�G�t�F�N�g�̓ǂݍ��� */
								pShockEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_eshock/FX_eshock")));

								/* ���d�G�t�F�N�g�̏����� */
								pShockEffect->Initialization();

								/* ���d�G�t�F�N�g�̎��Ԃ�ݒ� */
								pShockEffect->SetDeleteCount(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());

								/* ���d�G�t�F�N�g�����X�g�ɓo�^ */
								this->ObjectList->SetEffect(pShockEffect);
							}
							
							/* ��ʃG�t�F�N�g(��_���[�W)�쐬 */
							this->StageStatusList->SetScreenEffect(new ScreenEffect_Damage());

							/* �V�F�C�v(�u��)��K�p��Ԃɂ��� */
							this->fShapeRate = 1.f;
						}
					}
				}
			}
		}
	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */
/* 2025.02.19 �e�r�듹	�G�t�F�N�g�����ǉ� �I�� */
/* 2025.03.06 �e�r�듹	�����蔻�菈���C�� �I�� */

/* 2025.02.14 �e�r�듹	��]�֘A�̊֐��ǉ� �J�n */
// �p�x(���W�A��)�̐����ƕ␳
void CharacterPlayer::RadianLimitAdjustment(float& fRadian)
{
	// �p�x(���W�A��)������͈̔�(0~2��)�𒴂����ꍇ�A�␳���s��
	while (fRadian > PLAYER_TURN_LIMIT || fRadian < 0)
	{
	/* 2�΂𒴂����ꍇ */
	if (fRadian > PLAYER_TURN_LIMIT)
	{
		/* �p�x�����(2��)���␳���� */
		fRadian -= PLAYER_TURN_LIMIT;
	}
	/* 0����������ꍇ */
	else if (fRadian < 0)
	{
		/* �p�x�����(2��)���␳���� */
		fRadian += PLAYER_TURN_LIMIT;
	}
}
}
/* 2025.02.14 �e�r�듹	��]�֘A�̊֐��ǉ� �I�� */

/* 2025.02.26 �e�r�듹	�N�[���^�C���̏����ǉ� */
//�N�[���^�C���̍X�V
void CharacterPlayer::UpdateCooldownTime()
{
	/* �N�[���^�C�����X�V���鋤�ʊ֐� */ 
	auto UpdateCooldownTime = [](int& iCooldownTime) 
	{
		/* �N�[���^�C�����c���Ă��邩�m�F */ 
		if (iCooldownTime > 0)
		{
			// �N�[���^�C�����c���Ă���ꍇ
			/* �N�[���^�C�������� */
			iCooldownTime--;
		}
	};

	/* �ߐڍU��(��)�̃N�[���^�C���X�V */
	UpdateCooldownTime(this->iMeleeWeakNowCoolTime);
	/* �������U���̃N�[���^�C���X�V */
	UpdateCooldownTime(this->iProjectileNowCoolTime);
	/* ����̃N�[���^�C���X�V */
	UpdateCooldownTime(this->iDodgeNowCoolTime);
	/* �W�����v�̃N�[���^�C�����X�V */
	UpdateCooldownTime(this->iJumpNowCoolTime);
}
/* 2025.02.26 �e�r�듹	�N�[���^�C���̏����ǉ� */

/* 2025.03.02 ��򕗏�	�������A�����쐬 �J�n */
/* 2025.03.14 �e�r�듹	�G�t�F�N�g�����ǉ� �ǉ� */
/* 2025.03.16 ��򕗏�	�������A�����X�V �J�n */
/* 2025.03.21 �e�r�듹	�������A�����ǉ� �J�n */
// ��������̕��A
void CharacterPlayer::PlayerFallRecovery()
{
	/* �ł��߂����A�n�_�̍��W */
	VECTOR	vecCloseRecoveryPoint	= VGet(0.f, 0.f, 0.f);	// ���W
	float	fCloseDistance			= 0.f;					// ����
	bool	bFastFlg				= true;					// �ŏ��̊m�F�t���O

	/* �v���C���[�̍��W���ł��߂����A�n�_�ɐݒ� */
	for (auto& platform : this->ObjectList->GetPlatformList())
	{
		/* "�`�F�b�N�|�C���g"�Ƃ��ăL���X�g */
		Gimmick_CheckPoint* pCheckPoint = dynamic_cast<Gimmick_CheckPoint*>(platform);

		/* �L���X�g����������(�`�F�b�N�|�C���g�ł��邩)�m�F */
		if (pCheckPoint != nullptr)
		{
			// �`�F�b�N�|�C���g�ł���ꍇ
			/* �A�N�e�B�u��Ԃł��邩�m�F */
			if (pCheckPoint->bGetActiveFlg() == true)
			{
				// �A�N�e�B�u��Ԃł���ꍇ
				// /* ���A�n�_�ƌ��݂̍��W�̋������擾 */
				// ��������2����擾
				float fDistance = VSize(VSub(pCheckPoint->vecGetPosition(), this->vecPosition));

				/* ���ݐݒ肳��Ă��镜�A�n�_�����������Z�����A���邢�͍ŏ��̊m�F�ł��邩�m�F */
				if ((fDistance < fCloseDistance) || (bFastFlg == true))
				{
					// �������Z���A���邢�͍ŏ��̊m�F�ł���ꍇ
					/* �ł��߂����A�n�_���X�V */
					vecCloseRecoveryPoint = pCheckPoint->vecGetPosition();

					/* �ł��߂����A�n�_�̋������X�V */
					fCloseDistance = fDistance;
				}
			}
		}
	}

	/* �v���C���[�̍��W���ł��߂����A�n�_�ɐݒ� */
	this->vecPosition = vecCloseRecoveryPoint;

	/* �v���C���[��HP��-1���� */
	this->PlayerStatusList->SetPlayerNowHp(this->PlayerStatusList->iGetPlayerNowHp() - 1);

	/* �����t���O�𖳌��ɂ��� */
	this->PlayerStatusList->SetFallFlg(false);

	/* �ߋ����U��(��)�̃`���[�W�t���[���������Z�b�g */ 
	this->PlayerStatusList->SetPlayerNowAttakChargeFlame(0);

	/* �v���C���[�̏�Ԃ�"���R"�ɐݒ� */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

	/* ���߃G�t�F�N�g�����݂��邩�m�F */
	if (this->pChargeEffect != nullptr)
	{
		// ���߃G�t�F�N�g�����݂���ꍇ
		/* ���߃G�t�F�N�g�͍폜 */
		this->pChargeEffect->SetDeleteFlg(true);
		this->pChargeEffect = nullptr;
	}

	/* ���ߊ�����G�t�F�N�g�����݂��邩�m�F */
	if (this->pChargeHoldEffect != nullptr)
	{ 
		// ���ߊ�����G�t�F�N�g�����݂���ꍇ
		/* ���ߊ�����G�t�F�N�g���폜 */
		this->pChargeHoldEffect->SetDeleteFlg(true);
		this->pChargeHoldEffect = nullptr;
	}

	/* ���A�G�t�F�N�g�𐶐� */
	EffectSelfDelete_PlayerFollow* pRecoveryEffect = new EffectSelfDelete_PlayerFollow(true);

	/* ���A�G�t�F�N�g�̓ǂݍ��� */
	pRecoveryEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_appearance/FX_appearance")));

	/* ���A�G�t�F�N�g�̏����� */
	pRecoveryEffect->Initialization();

	/* ���A�G�t�F�N�g�̎��Ԃ�ݒ� */
	pRecoveryEffect->SetDeleteCount(90);

	/* ���A�G�t�F�N�g�����X�g�ɓo�^ */
	{
		/* ���A�G�t�F�N�g�����X�g�ɓo�^ */
		this->ObjectList->SetEffect(pRecoveryEffect);
}
}
/* 2025.03.02 ��򕗏� �������A�����쐬 �I�� */
/* 2025.03.14 �e�r�듹	�G�t�F�N�g�����ǉ� �I�� */
/* 2025.03.16 ��򕗏�	�������A�����X�V �I�� */
/* 2025.03.21 �e�r�듹	�������A�����ǉ� �I�� */

