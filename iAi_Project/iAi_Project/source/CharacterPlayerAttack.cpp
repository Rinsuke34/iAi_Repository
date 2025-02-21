/* 2025.02.04 �e�r�듹	�t�@�C���쐬 */
/* 2025.01.22 �e�r�듹	�U�������ǉ� */
/* 2025.01.24 �e�r�듹	�U�������ǉ� */
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.02.03 �e�r�듹	�ߋ����U��(��)��̏����ǉ� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� */
/* 2025.02.07 �e�r�듹	�G�t�F�N�g�����C�� */
/* 2025.02.12 �e�r�듹	�������U�������ǉ� */
/* 2025.02.14 �e�r�듹	�������U�������ǉ� */
/* 2025.02.19 �e�r�듹	�G�t�F�N�g�����C�� */
/* 2025.02.21 �e�r�듹	�������U���C�� */

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

	/* �v���C���[�̍U����Ԃ��擾 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* �v���C���[�̍U����Ԃɉ����ď�����ύX */
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
			else if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
			{
				/* �G�C��(�\��)�L�����Z���t���O����������Ă���ꍇ */
				if (this->PlayerStatusList->bGetPlayerAimCancelledFlg() == false)
				{
					// �G�C��(�\��)���͂�����Ă���ꍇ
					/* �v���C���[��Ԃ�"�������U���\����"�ɐݒ� */
					this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE);
				}
			}
			// �G�C��(�\��)���L�����Z�����ꂽ��A�{�^���������ςȂ��ōĔ��������Ȃ����߂̏���
			/* �G�C��(�\��)�L�����Z���t���O���ݒ肳��Ă���ꍇ */
			else if (this->PlayerStatusList->bGetPlayerAimCancelledFlg() == true)
			{
				/* �G�C��(�\��)�{�^���𗣂����� */
				if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_AIM) == false)
				{
					/* �G�C��(�\��)�L�����Z���t���O������ */
					this->PlayerStatusList->SetPlayerAimCancelledFlg(false);
				}
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

		/* ���S���(����s��) */
		case PLAYER_ATTACKSTATUS_DEAD:
			/* �������s��Ȃ� */
			break;

	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */

// �ߐڍU��(�\��)
void CharacterPlayer::Player_Melee_Posture()
{
	/* �v���C���[�̌��݂̍U���`���[�W�t���[���̎擾 */
	int iNowAttakChargeFlame = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame();

	/* 2025.01.24 �e�r�듹	�U�������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �J�n */
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
	/* 2025.02.07 �e�r�듹	�G�t�F�N�g�����C�� �J�n */
	/* 2025.02.19 �e�r�듹	�G�t�F�N�g�����C�� �J�n */

	/* �U�����͂�����Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		// �U���`���[�W�t���[�������U���̐؂�ւ��ɒB������
		if (iNowAttakChargeFlame == PLAYER_CHARGE_TO_STRONG_TIME)
		{
			/* �v���C���[���[�V������"����(����)"�ɕύX */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_CHARGE);

			/* ���߂̃G�t�F�N�g�𓁂̈ʒu�ɐ��� */
			this->pChargeEffect = new EffectManualDelete_PlayerFollow_Frame(this->iKatanaFrameNo);

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
					this->pChargeEffect = nullptr;

					/* ���ߊ����G�t�F�N�g�𐶐� */
					EffectSelfDelete_PlayerFollow_Frame* pAddEffect = new EffectSelfDelete_PlayerFollow_Frame(iKatanaFrameNo);

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
					this->pChargeHoldEffect = new EffectManualDelete_PlayerFollow_Frame(iKatanaFrameNo);
					
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
		
			/* �ړ��ʎZ�o */
			//float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 2.7f;
			// �Վ��ł�����ƒ��߂ɂ���
			//float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 5.f;
			float fMove = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * 5.f * 3.f;

			/* �ړ������Z�o */
			VECTOR vecMoveDirection = VNorm(VSub(this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraPosition()));

			/* �c�����ɂ͈ړ����Ȃ��悤�ɐݒ� */
			vecMoveDirection.y = 0;

			/* �ߐڍU��(��)�ɂ��ړ��ʂ�ݒ� */
			this->PlayerStatusList->SetPlayerChargeAttakTargetMove(VScale(vecMoveDirection, fMove));

			/* �U���`���[�W�t���[�������U���ɔh�����Ă��邩�m�F */
			if (iNowAttakChargeFlame >= PLAYER_CHARGE_TO_STRONG_TIME)
			{
				/* �J�������[�h��"�\��(�ߐڍU���\��)"�ɕύX */
				this->PlayerStatusList->SetCameraMode(CAMERA_MODE_AIM_MELEE);

				/* �v���C���[�̌������J�����̌����ɌŒ� */
				this->PlayerStatusList->SetPlayerAngleX(this->PlayerStatusList->fGetCameraAngleX());
				
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

					/* ���b�N�I���͈͂̃R���W������ݒ� */
					this->PlayerStatusList->SetMeleeSearchCollision(stMeleeSearchCollision);

					/* ���b�N�I���͈̓R���W�����g�p�t���O��L���� */
					this->PlayerStatusList->SetMeleeSearchCollisionUseFlg(true);
				}
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
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �I�� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */
/* 2025.02.07 �e�r�듹	�G�t�F�N�g�����C�� �I�� */
/* 2025.02.19 �e�r�듹	�G�t�F�N�g�����C�� �I�� */

// �ߐڍU��(��)
void CharacterPlayer::Player_Melee_Weak()
{
	/* 2025.01.22 �e�r�듹	�U�������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */

	// �ߐڍU��(��)�łȂ��ꍇ
	/* �v���C���[�̃��[�V�������ߐڍU��(��)�ɐݒ� */
	this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_WEAK);

	/* �ߐڍU���Ƃ��Ĉ����e���쐬 */
	// �����݂̃v���C���[�̌����ɒe���쐬
	this->pBulletMeleeWeak = new BulletPlayerMeleeWeak;

	/* �U���̌�����ݒ� */
	this->pBulletMeleeWeak->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* ���������s�� */
	this->pBulletMeleeWeak->Initialization();

	/* �o���b�g���X�g�ɒǉ� */
	ObjectList->SetBullet(this->pBulletMeleeWeak);

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
		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG);

		/* ���ߋ����U����SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_SPIAI);
	}
	else
	{
		// 1�ȏ�ł���ꍇ
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
				vecMoveDirection = VAdd(vecMoveDirection, VScale(VNorm(vecMoveDirection), 1000.f));
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
				this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG_END);
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
				pAddEffect->SetPosition(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2.f, 0)));

				/* ����(��)�G�t�F�N�g�̉�]�ʐݒ� */
				pAddEffect->SetRotation(VGet(this->vecRotation.x, this->vecRotation.y, this->vecRotation.z * -1));

				/*����(��) �G�t�F�N�g�̏����� */
				pAddEffect->Initialization();

				/* ����(��)�G�t�F�N�g�����X�g�ɓo�^ */
				this->ObjectList->SetEffect(pAddEffect);
			}
		}
	}

	// ���ߍU����A���̓G��T������
	// ���Ńv���C���[�̃��[�V������"����(��)(�I��)"�ɂȂ����^�C�~���O�Ƃ���
	if(this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
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

/* 2025.02.12 �e�r�듹	�������U�������ǉ� �J�n */
// �������U��(�\��)
void CharacterPlayer::Player_Projectile_Posture()
{
	/* �G�C��(�\��)���͂�����Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
	{
		/* �v���C���[�̌������J�����̌����ɌŒ� */
		this->PlayerStatusList->SetPlayerAngleX(this->PlayerStatusList->fGetCameraAngleX());
		
		/* �J�������[�h��"�\��(�N�i�C�U��)"�ɕύX */
		this->PlayerStatusList->SetCameraMode(CAMERA_MODE_AIM_KUNAI);

		/* �U�����͂����ꂽ�ꍇ */
		if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
		{
			/* �v���C���[�̍U����Ԃ�"�������U����"�ɑJ�� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE);
		}
		/* �W�����v���͂����ꂽ�ꍇ */
		else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
		{
			// �������U���\����Ԃ��L�����Z������
			/* �������U���\����ԃL�����Z���t���O�����Ă� */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			
			/* �v���C���[�U����Ԃ�"���R���"�ɐݒ� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

		}
		/* �W�����v���̏ꍇ */
		else if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true)
		{
			/* �X���[���[�V�����������s��(��) */ 
		}
		/* �����͂����ꂽ�ꍇ */
		else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == true)
		{
			// �������U���\����Ԃ��L�����Z������
			/* �������U���\����ԃL�����Z���t���O�����Ă� */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			
			/* �v���C���[�U����Ԃ�"���R���"�ɐݒ� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
		}
	}
	/* �G�C��(�\��)���͂�����Ă��Ȃ��ꍇ */
	else 
	{
		/* �v���C���[�U����Ԃ�"���R���"�ɐݒ� */
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
	}
}
/* 2025.02.12 �e�r�듹	�������U�������ǉ� �I�� */

/* 2025.02.14 �e�r�듹	�������U�������ǉ� �J�n */
/* 2025.02.21 �e�r�듹	�������U���C�� �J�n */
// �������U��
void CharacterPlayer::Player_Projectile()
{
	/* �v���C���[�̌������J�����̌����ɌŒ� */
	this->PlayerStatusList->SetPlayerAngleX(this->PlayerStatusList->fGetCameraAngleX());

	/* �J�������[�h��"�\��(�N�i�C�U��)"�ɕύX */
	this->PlayerStatusList->SetCameraMode(CAMERA_MODE_AIM_KUNAI);
	
	/* �N�i�C(�G�t�F�N�g)���쐬 */
	this->pBulletKunaiEffect = new BulletPlayerKunaiEffect;

	/* �N�i�C(�G�t�F�N�g)�������W��ݒ� */
	this->pBulletKunaiEffect->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y + PLAYER_HEIGHT / 2, this->vecPosition.z));
	
	/* ���b�N�I�����̃G�l�~�[���擾 */
	EnemyBasic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

	/* ���b�N�I�����̃G�l�~�[�����݂��邩 */
	if (pLockOnEnemy != nullptr)
	{
		// ���݂���ꍇ
		/* �N�i�C(�G�t�F�N�g)�̃^�[�Q�b�g���W�����b�N�I�����̃G�l�~�[�ɐݒ� */
		this->pBulletKunaiEffect->SetKunaiTargetPosition(pLockOnEnemy->vecGetPosition());
}
	else
	{
		// ���݂��Ȃ��ꍇ
		// �N�i�C(�G�t�F�N�g)�̃^�[�Q�b�g���W���J�����̒����_�̐�ɐݒ�

		/* �J�������W����J�����̒����_�Ɍ������x�N�g�����擾 */
		VECTOR vecKunaiTarget = VSub(this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraPosition());
		
		/* �x�N�g���𐳋K�� */
		vecKunaiTarget = VNorm(vecKunaiTarget);

		/* �x�N�g�����˒������܂ŃX�P�[�����O */
		vecKunaiTarget = VScale(vecKunaiTarget, KUNAI_RANGE);

		/* �^�[�Q�b�g���W�̍��W�x�N�g�����擾 */
		vecKunaiTarget = VAdd(this->PlayerStatusList->vecGetCameraPosition(), vecKunaiTarget);

		// �N�i�C(�G�t�F�N�g)�Ƀ^�[�Q�b�g���W��ݒ�
		this->pBulletKunaiEffect->SetKunaiTargetPosition(vecKunaiTarget);
	}

	/* ���������s�� */
	this->pBulletKunaiEffect->Initialization();
	
	/* �o���b�g���X�g�ɒǉ� */
	ObjectList->SetBullet(this->pBulletKunaiEffect);

	/* �������U���\����Ԃɖ߂� */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE);
}
/* 2025.02.14 �e�r�듹	�������U�������ǉ� �I�� */
/* 2025.02.21 �e�r�듹	�������U���C�� �I�� */