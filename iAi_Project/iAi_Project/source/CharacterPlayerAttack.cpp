/* 2025.02.04 �e�r�듹	�t�@�C���쐬 */
/* 2025.01.22 �e�r�듹	�U�������ǉ� */
/* 2025.01.24 �e�r�듹	�U�������ǉ� */
/* 2025.02.03 �e�r�듹	�ߋ����U��(��)��̏����ǉ� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� */

#include "CharacterPlayer.h"

/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
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
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* �v���C���[��Ԃɉ����ď�����ύX */
	switch (iPlayerAttackState)
	{
		/* ���R��� */
	case PLAYER_ATTACKSTATUS_FREE:
		/* �U�����͂�����Ă��邩�m�F */
		if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
		{
			// �U�����͂�����Ă���ꍇ
			/* �v���C���[��Ԃ�"�ߐڍU���\����"�ɐݒ� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_POSTURE);
		}
		/* �G�C��(�\��)���͂�����Ă��邩�m�F */
		else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_AIM) == true)
		{
			// �G�C��(�\��)���͂�����Ă���ꍇ
			/* �v���C���[��Ԃ�"�������U���\����"�ɐݒ� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE);
		}
		break;

		/* �ߐڍU���\���� */
	case PLAYER_ATTACKSTATUS_MELEE_POSTURE:
		/* �ߐڍU��(�\��) */
		Player_Melee_Posture();
		break;

		/* �ߐڍU����(��) */
	case PLAYER_ATTACKSTATUS_MELEE_WEEK:
		/* �ߐڍU��(��) */
		Player_Melee_Weak();
		break;

		/* �ߐڍU����(��) */
	case PLAYER_ATTACKSTATUS_MELEE_STRONG:
		/* �ߋ����U��(��) */
		Player_Charge_Attack();
		break;

		/* �������U���\���� */
	case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:
		/* �������U��(�\��) */
		Player_Projectile_Posture();
		break;

		/* �������U���� */
	case PLAYER_ATTACKSTATUS_PROJECTILE:
		/* �������U�� */
		Player_Projectile();
		break;
	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */

/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �ǉ� */
/* 2025.01.30 �e�r�듹	���[�V���������ǉ� �J�n */
// �ߐڍU��(�\��)
void CharacterPlayer::Player_Melee_Posture()
{
	/* �v���C���[�̌��݂̍U���`���[�W�t���[���̎擾 */
	int iNowAttakChargeFlame = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame();

	/* 2025.01.24 �e�r�듹	�U�������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ�	�J�n*/
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */

	/* �U�����͂�����Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		// �U���`���[�W�t���[�������U���̐؂�ւ��ɒB������
		if (iNowAttakChargeFlame == PLAYER_CHARGE_TO_STRONG_TIME)
		{
			/* �v���C���[���[�V������"����(����)"�ɕύX */
			this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_DRAW_SWORD_CHARGE);

			/* ���߂̃G�t�F�N�g�𐶐� */
			this->pChargeEffect = new EffectManualDelete;

			/* ���߃G�t�F�N�g�̓ǂݍ��� */
			this->pChargeEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_charge/FX_charge")));

			/* ���߃G�t�F�N�g�̍��W�ݒ�(�����W) */
			this->pChargeEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 100, 0)));

			/* ���߃G�t�F�N�g�̉�]�ʐݒ� */
			this->pChargeEffect->SetRotation(this->vecRotation);

			/* ���߃G�t�F�N�g�̏����� */
			this->pChargeEffect->Initialization();

			/* ���߃G�t�F�N�g�����X�g�ɓo�^ */
			{
				/* ���߃G�t�F�N�g�����X�g�ɓo�^ */
				this->ObjectList->SetEffect(this->pChargeEffect);
			}
		}

		/* �ߐڍU��(��)�`���[�W���� */
		{
			/* �`���[�W�t���[�����ő�l�𒴂��Ă��Ȃ����m�F */
			if (iNowAttakChargeFlame < PLAYER_MELEE_CHARGE_MAX)
			{
				// �����Ă��Ȃ��ꍇ
				/* �v���C���[�̌��݂̍U���`���[�W�t���[�������Z */
				PlayerStatusList->SetPlayerNowAttakChargeFlame(iNowAttakChargeFlame + 1);

				/* ���Z�ɂ��`���[�W�t���[�����ő�l�ɒB�������m�F */
				if ((iNowAttakChargeFlame + 1) == PLAYER_MELEE_CHARGE_MAX)
				{
					// �ő�l�ɒB�����ꍇ
					/* ���ߋ����`���[�W������SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_CHARGE_COMPLETE);

					/* ���߃G�t�F�N�g�͍폜 */
					this->pChargeEffect->SetDeleteFlg(true);

					/* ���ߊ����G�t�F�N�g�𐶐� */
					EffectSelfDelete_PlayerFollow* pAddEffect = new EffectSelfDelete_PlayerFollow(true);

					/* ���ߊ����G�t�F�N�g�̓ǂݍ��� */
					pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_charge_finish/FX_charge_finish")));

					/* ���ߊ����G�t�F�N�g�̏����� */
					pAddEffect->Initialization();

					/* ���ߊ����G�t�F�N�g�̎��Ԃ�ݒ� */
					pAddEffect->SetDeleteCount(20);

					/* ���ߊ����G�t�F�N�g�����X�g�ɓo�^ */
					{
						/* ���ߊ����G�t�F�N�g�����X�g�ɓo�^ */
						this->ObjectList->SetEffect(pAddEffect);
					}

					/* ���ߊ����G�t�F�N�g�̍��W�ݒ�(��) */
					pAddEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 100, 0)));

					/* ���ߊ�����G�t�F�N�g�𐶐� */
					this->pChargeHoldEffect = new EffectManualDelete;
					
					/* ���ߊ�����G�t�F�N�g�̓ǂݍ��� */
					this->pChargeHoldEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_charge_hold/FX_charge_hold")));
					
					/* ���ߊ�����G�t�F�N�g�̍��W�ݒ�(�����W) */
					this->pChargeHoldEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 100, 0)));
					
					/* ���ߊ�����G�t�F�N�g�̉�]�ʐݒ� */
					this->pChargeHoldEffect->SetRotation(this->vecRotation);

					/* ���ߊ�����G�t�F�N�g�̏����� */
					this->pChargeHoldEffect->Initialization();

					/* ���ߊ�����G�t�F�N�g�����X�g�ɓo�^ */
					{
						/* ���ߊ�����G�t�F�N�g�����X�g�ɓo�^ */
						this->ObjectList->SetEffect(this->pChargeHoldEffect);
					}
				}
			}
		
			/* �v���C���[�̌������J�����̌����ɌŒ� */
			this->PlayerStatusList->SetPlayerAngleX(this->PlayerStatusList->fGetCameraAngleX());

			/* �ړ��ʎZ�o */
			//float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 2.7f;
			// �Վ��ł�����ƒ��߂ɂ���
			float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 5.f;

			/* �ړ������Z�o */
			VECTOR vecMoveDirection = VNorm(VSub(this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraPosition()));

			/* �c�����ɂ͈ړ����Ȃ��悤�ɐݒ� */
			vecMoveDirection.y = 0;

			/* �ߐڍU��(��)�ɂ��ړ��ʂ�ݒ� */
			this->PlayerStatusList->SetPlayerChargeAttakTargetMove(VScale(vecMoveDirection, fMove));

			/* �U���`���[�W�t���[�������U���ɔh�����Ă��邩�m�F */
			if (iNowAttakChargeFlame >= PLAYER_CHARGE_TO_STRONG_TIME)
			{
				/* �J�������[�h��"�\��(�Y�[��)"�ɕύX */
				this->PlayerStatusList->SetCameraMode(CAMERA_MODE_AIM);

				
				/* ���b�N�I���͈͂̃R���W�����쐬 */
				{
					/* ���b�N�I���͈̓R���W���� */
					COLLISION_CAPSULE stMeleeSearchCollision;

					/* ���b�N�I���͈͂̔��a���擾 */
					stMeleeSearchCollision.fCapsuleRadius = this->PlayerStatusList->fGetPlayerRockOnRadius();

					/* �Е��͌��݂̃v���C���[�̒��S�ɐݒ� */
					stMeleeSearchCollision.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2.f, 0));

					/* �����Е��͈ړ���(����)�̃v���C���[�̒��S�ɐݒ� */
					stMeleeSearchCollision.vecCapsuleBottom = VAdd(stMeleeSearchCollision.vecCapsuleTop, this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove());
					//// �Վ��Ńv���C���[�̒����_�ɐݒ�
					//stMeleeSearchCollision.vecCapsuleBottom = this->PlayerStatusList->vecGetCameraTarget();
					//stMeleeSearchCollision.vecCapsuleBottom.y = stMeleeSearchCollision.vecCapsuleTop.y;

					/* ���b�N�I���͈͂̃R���W������ݒ� */
					this->PlayerStatusList->SetMeleeSearchCollision(stMeleeSearchCollision);

					/* ���b�N�I���͈̓R���W�����g�p�t���O��L���� */
					this->PlayerStatusList->SetMeleeSearchCollisionUseFlg(true);
				}
			}

			//�G�t�F�N�g�����݂��Ă���ꍇ�A�����X�V����
			if (this->pChargeEffect != nullptr)
			{
				/* ���߃G�t�F�N�g�̍��W�ݒ�(�����W) */
				this->pChargeEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 100, 0)));
				/* ���߃G�t�F�N�g�̉�]�ʐݒ� */
				this->pChargeEffect->SetRotation(this->vecRotation);
			}
			if (this->pChargeHoldEffect != nullptr)
			{
				/* ���ߊ����G�t�F�N�g�̍��W�ݒ�(�����W) */
				this->pChargeHoldEffect->SetPosition(VAdd(this->vecPosition, VGet(0, 100, 0)));
				/* ���ߊ����G�t�F�N�g�̉�]�ʐݒ� */
				this->pChargeEffect->SetRotation(this->vecRotation);
			}

			/* �f�o�b�O�p���� */
			{
				/* �f�o�b�O�p�ړ�����W��ݒ� */
				this->stMeleeStrongMoveCollsion.vecCapsuleTop = VAdd(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT - PLAYER_WIDE, 0)), VScale(vecMoveDirection, fMove));
				this->stMeleeStrongMoveCollsion.vecCapsuleBottom = VAdd(VAdd(this->vecPosition, VGet(0, PLAYER_WIDE, 0)), VScale(vecMoveDirection, fMove));
				this->stMeleeStrongMoveCollsion.fCapsuleRadius = PLAYER_WIDE;
			}
		}

		/* 2025.01.24 �e�r�듹	�U�������ǉ�		�I��*/
		/* 2025.01.26 ��򕗏�	�R�[�h�C��		�I��*/
		/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ�	�I��*/
	}
	else
	{
		// �U�����͂�����Ă��Ȃ��ꍇ
		/* �U���`���[�W�t���[���ɉ����ď�����ύX */
		if (iNowAttakChargeFlame < PLAYER_CHARGE_TO_STRONG_TIME)
		{
			// ���U���ɐ؂�ւ��O�̏ꍇ
			/* �v���C���[�̏�Ԃ�"�ߐڍU����(��)"�ɐݒ� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_WEEK);
		}
		else
		{
			// ���U���ɂȂ�ꍇ
			/* �v���C���[�̏�Ԃ�"�ߐڍU����(��)"�ɐݒ� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_STRONG);

			/* �v���C���[�̂��ߍU���p�̃J�E���g�������� */
			this->PlayerStatusList->SetPlayerChargeAttackCount(0);

			/* �����̉����x�������� */
			this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

		}

		/* �v���C���[�̌��݂̍U���`���[�W�t���[�������Z�b�g */
		this->PlayerStatusList->SetPlayerNowAttakChargeFlame(0);
	}

	//�G�t�F�N�g�̍폜
	//�ߐڍU���\����Ԃ��������ꂽ�ꍇ
	if (this->PlayerStatusList->iGetPlayerAttackState() != PLAYER_ATTACKSTATUS_MELEE_POSTURE)
	{
		this->PlayerStatusList->SetPlayerNowAttakChargeFlame(0);

		//�G�t�F�N�g�����݂��Ă���ꍇ�A�폜����
		if (this->pChargeEffect != nullptr)
		{
			/* ���߃G�t�F�N�g���폜 */
			this->pChargeEffect->SetDeleteFlg(true);
			this->pChargeEffect = nullptr;
		}
		if (this->pChargeHoldEffect != nullptr)
		{
			/* ���ߊ�����G�t�F�N�g���폜 */
			this->pChargeHoldEffect->SetDeleteFlg(true);
			this->pChargeHoldEffect = nullptr;
		}
	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */

// �ߐڍU��(��)
void CharacterPlayer::Player_Melee_Weak()
{
	/* 2025.01.22 �e�r�듹	�U�������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */

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

	/* 2025.01.22 �e�r�듹�@�U�������ǉ�	�I�� */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�I�� */

	/* �ߐڍU��(��)��SE���Đ� */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

	/* �������Ȃ̂łƂ肠�������R��Ԃɖ߂� */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */


// �ߋ����U��(��)
void CharacterPlayer::Player_Charge_Attack()
{
	/* 2025.01.22 �e�r�듹	�U�������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n */
	/* 2025.02.03 �e�r�듹	�ߋ����U��(��)��̏����ǉ�	�J�n */
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */

	/* ���ߍU���p�̃J�E���g���擾 */
	int iChargeAttackCount = this->PlayerStatusList->iGetPlayerChargeAttackCount();

	/* �J�E���g���m�F */
	if (iChargeAttackCount == 0)
	{
		// 0�ł���ꍇ
		// �����[�V�����J�ڒ���ł���ꍇ
		/* �v���C���[�̃��[�V�������ߐڍU��(��)�ɕύX���� */
		this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_DRAW_SWORD_STRONG);

		/* ���ߋ����U����SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_SPIAI);
	}
	//else if(iChargeAttackCount <= 20)
	//{
	//	// 20�ȉ��ł���ꍇ
	//	/* ���[�V�����̏������쒆?�Ȃ̂ł��̏�Ԃł͍U�����Ȃ� */
	//}
	else
	{
		// 21�ȏ�ł���ꍇ
		/* �U�����ړ����� */
		// �����b�N�I�����̃G�l�~�[�����݂��邩�ŏ����𕪊򂳂���
		{
			/* ���b�N�I�����̃G�l�~�[���擾 */
			EnemyBasic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

			/* �ߐڍU��(��)�ɂ��ړ��ʂ��擾 */
			VECTOR vecMoveDirection = this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove();

			/* �ړ��ʂ�float�^�Ŏ擾 */
			float fMove = VSize(vecMoveDirection);

			/* ���b�N�I�����̃G�l�~�[�����݂��邩 */
			if (pLockOnEnemy != nullptr)
			{
				// ���݂���ꍇ
				/* �ړ��ʂ��v���C���[�̌��݈ʒu���烍�b�N�I�����̃G�l�~�[�̈ʒu�ɏC�� */
				vecMoveDirection = VSub(pLockOnEnemy->vecGetPosition(), this->vecPosition);

				/* �G�l�~�[�̈ʒu����ǉ��ňړ�(�˂������銴�����o������) */
				fMove += 500.f;
				vecMoveDirection = VAdd(vecMoveDirection, VScale(VNorm(vecMoveDirection), 500.f));
			}

			/* �U�����ړ������ɓ����Ă���̃J�E���g���擾 */
			//int iCount	= iChargeAttackCount - 20;
			int iCount = iChargeAttackCount;

			/* �ړ��ʂ��ړ����x�Ŋ����Ă��̏������s���񐔂��Z�o���� */
			int	iMoveCount = (int)(fMove / PLAYER_MELEE_STRONG_MOVESPEED);

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
				this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

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
				EffectSelfDelete* pAddEffect = new EffectSelfDelete();

				/* ����(��)�G�t�F�N�g�̓ǂݍ��� */
				pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_iai_dash/FX_iai_dash")));

				/* ����(��)�G�t�F�N�g�̍Đ����Ԃ�ݒ� */
				pAddEffect->SetDeleteCount(30);

				/* ����(��)�G�t�F�N�g�̍��W�ݒ� */
				pAddEffect->SetPosition(this->vecPosition);

				/* ����(��)�G�t�F�N�g�̉�]�ʐݒ� */
				pAddEffect->SetRotation(this->vecRotation);

				/*����(��) �G�t�F�N�g�̏����� */
				pAddEffect->Initialization();

				/* ����(��)�G�t�F�N�g�����X�g�ɓo�^ */
				{
					/* ����(��)�G�t�F�N�g�����X�g�ɓo�^ */
					this->ObjectList->SetEffect(pAddEffect);
				}
			}
		}
	}

	// ���ߍU����A���̓G��T������
	// ���Ńv���C���[�̃��[�V������"����(��)(�I��)"�ɂȂ����^�C�~���O�Ƃ���
	if (this->PlayerStatusList->iGetPlayerMotion() == PLAYER_MOTION_DRAW_SWORD_END)
	{
		/* ���G�͈͂�ݒ聦�l�͉� */
		COLLISION_SQHERE stSearchSqere{ this->vecPosition, PLAYER_SEARCH_RANGE_AFTER_MELEE };

		/* �v���C���[�ɋ߂��G�l�~�[���擾���� */
		NearEnemy stNearEnemy = { nullptr, 0.f };

		/* �G�l�~�[���X�g���擾 */
		auto& EnemyList = ObjectList->GetEnemyList();

		/* ���G�͈͓��̃G�l�~�[�̂����ł��v���C���[�ɋ߂��G�l�~�[��Ώۂɐݒ� */
		for (auto* enemy : EnemyList)
		{
			/* ���G�͈͂ɐڐG���Ă��邩�m�F */
			if (enemy->HitCheck(stSearchSqere) == true)
			{
				// ���G�͈͓��ł���ꍇ
				/* �R�A�̃��[���h���W���擾 */
				VECTOR vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

				/* �v���C���[�Ƃ̍������߂� */
				float fx = vecCoreWord.x - this->vecPosition.x;
				float fy = vecCoreWord.y - this->vecPosition.y;
				float fDistance = (fx * fx) + (fy * fy);

				/* ���݂̍ł��v���C���[����߂��G�l�~�[�����v���C���[�ɋ߂����m�F */
				if (fDistance < stNearEnemy.fDistance || stNearEnemy.pEnemy == nullptr)
				{
					// �߂��ꍇ
					/* �v���C���[����߂��G�l�~�[���X�V */
					stNearEnemy.pEnemy = enemy;
					stNearEnemy.fDistance = fDistance;
				}
			}
		}

		/* �ł��v���C���[�߂��G�l�~�[��ΏۂɎw�� */
		if (stNearEnemy.pEnemy != nullptr)
		{
			//�Ώۂ����݂���ꍇ
			/* �v���C���[���猩���G�̌������擾 */
			VECTOR vecNearEnemy = VSub(this->vecPosition, stNearEnemy.pEnemy->vecGetPosition());

			/* �v���C���[���猩���G�̌����𐳋K�� */
			vecNearEnemy = VNorm(vecNearEnemy);

			/* �v���C���[���猩���G�̊p�x���擾 */
			float fNearEnemyRotate = -atan2f(vecNearEnemy.x, vecNearEnemy.z);

			/* �v���C���[�̌�����ݒ� */
			this->PlayerStatusList->SetPlayerAngleX(fNearEnemyRotate);

			/* �v���C���[�̌����ɃJ�����̌������Œ� */
			this->PlayerStatusList->SetCameraAngleX(this->PlayerStatusList->fGetPlayerAngleX());
		}

	}
	/* ���ߍU���p�̃J�E���g��+1���� */
	this->PlayerStatusList->SetPlayerChargeAttackCount(iChargeAttackCount + 1);

	/* 2025.01.22 �e�r�듹	�U�������ǉ�				�I�� */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�I�� */
	/* 2025.02.03 �e�r�듹	�ߋ����U��(��)��̏����ǉ�	�I�� */
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C��			�I�� */
}

// �������U��(�\��)
void CharacterPlayer::Player_Projectile_Posture()
{
	/* �������Ȃ̂łƂ肠�������R��Ԃɖ߂� */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
}

// �������U��
void CharacterPlayer::Player_Projectile()
{
	/* �������Ȃ̂łƂ肠�������R��Ԃɖ߂� */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
}
