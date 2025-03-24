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
/* 2025.02.26 �e�r�듹	�N�[���^�C�������ǉ� */
/* 2025.02.26 �e�r�듹	�ߋ����U��(��)�����C�� */
/* 2025.03.03 �e�r�듹	�ߋ����U��(��)�����C�� */
/* 2025.03.04 �e�r�듹	�X���[���[�V���������ǉ� */
/* 2025.03.04 �e�r�듹	�ߋ����U��(��)�����C�� */
/* 2025.03.06 �e�r�듹	�X���[���[�V���������C�� */
/* 2025.03.06 �e�r�듹	�ߋ����U��(��)�����C�� */
/* 2025.03.06 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.03.10 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.03.12 �e�r�듹	�X���[���[�V���������C�� */
/* 2025.03.13 ��򕗏�	�N�i�C�e���ݒ� */
/* 2025.03.13 �e�r�듹	�N�i�C�����ύX */
/* 2025.03.17 ��򕗏�	��ʃG�t�F�N�g�ǉ� */
/* 2025.03.17 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.03.17 �e�r�듹	�ߋ����U��(��)�����C�� */
/* 2025.03.18 �e�r�듹	�G�f�B�b�g�ɂ�鏈���ǉ� */
/* 2025.03.21 �e�r�듹	�X���[���[�V���������ǉ� */

#include "CharacterPlayer.h"

/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
/* 2025.03.03 �e�r�듹	�ߋ����U��(��)�����C�� �J�n */
/* 2025.03.04 �e�r�듹	�X���[���[�V���������ǉ�	�J�n */
/* 2025.03.17 �e�r�듹	�G�t�F�N�g�����ǉ�	�J�n */
/* 2025.03.21 �e�r�듹	�X���[���[�V���������ǉ� �J�n */
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


			//�ߐڍU��(��)�̏���
			/* �U�����͂�����Ă��邩�m�F */
			if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
			{
				// �U�����͂�����Ă���ꍇ
				/* �v���C���[��Ԃ�"�ߐڍU���\����"�ɐݒ� */
				this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_POSTURE);
			}
			
			// �ߋ����U��(��)�œG��|������̏���
			/* �v���C���[���ߐڍU��(��)�œG��|�����ォ�̃t���O���m�F */
			if (this->PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg() == true)
			{
				// �ߐڍU��(��)�œG��|������A���̓G���U���ł���ꍇ�G�t�F�N�g��SE���o�� 
				/* �v���C���[���ߋ����U��(��)��A���ōs���邩�̃t���O���m�F */
				if (this->PlayerStatusList->bGetPlayerMeleeStrongContinuousFlg() == true)
				{
					//�ߋ����U��(��)��A���ōs����ꍇ
					/* �v���C���[���ߐڍU��(��)�œG��|������̃J�E���g���擾 */
					int iPlayerMeleeStrongAfterCount = this->PlayerStatusList->iGetPlayerMeleeStrongAfterCount();

					/* �ߐڍU��(��)�œG��|������̃J�E���g��0���m�F */
					if (iPlayerMeleeStrongAfterCount == 0)
					{
						// �J�E���g��0�̏ꍇ
						/* ���ߋ����`���[�W������SE���Đ� */
						gpDataList_Sound->SE_PlaySound(SE_PLAYER_CHARGE_COMPLETE);

						/* ���ߊ����G�t�F�N�g�𐶐� */
						EffectSelfDelete_PlayerFollow_Frame* pAddEffect = new EffectSelfDelete_PlayerFollow_Frame(iKatanaFrameNo);

						/* ���ߊ����G�t�F�N�g�̓ǂݍ��� */
						pAddEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge_finish/FX_charge_finish")));

						/* ���ߊ����G�t�F�N�g�̏����� */
						pAddEffect->Initialization();

						/* ���ߊ����G�t�F�N�g�̎��Ԃ�ݒ� */
						pAddEffect->SetDeleteCount(20);

						/* ���ߊ����G�t�F�N�g�����X�g�ɓo�^ */
						{
							/* ���ߊ����G�t�F�N�g�����X�g�ɓo�^ */
							this->ObjectList->SetEffect(pAddEffect);
						}

						/* ���ߊ�����G�t�F�N�g�𐶐� */
						this->pChargeHoldEffect = new EffectManualDelete_PlayerFollow_Frame(iKatanaFrameNo);

						/* ���ߊ�����G�t�F�N�g�̓ǂݍ��� */
						this->pChargeHoldEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge_hold/FX_charge_hold")));

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
					/* �ߋ����U��(��)��̃J�E���g����萔�𒴂��Ă��Ȃ����m�F */
					else if (iPlayerMeleeStrongAfterCount < PLAYER_STRONG_MELEE_AFTER_COUNT_MAX)
					{
						// �ߋ����U��(��)��̃J�E���g����萔�𒴂��Ă��Ȃ��ꍇ
						/* �󒆂ɂ��邩�m�F���� */
						if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
						{
							// �󒆂ɂ���ꍇ
							/* �X���[���[�V�����t���O�������ł��邩�m�F */
							if (this->StageStatusList->bGetGameSlowFlg() == false)
							{
								// �����ł���ꍇ								
								/* ��ʃG�t�F�N�g(��_���[�W)�쐬 */
								this->StageStatusList->SetScreenEffect(new ScreenEffect_Damage());
								
								/* �X���[���[�V�����t���O��L���� */
								this->StageStatusList->SetGameSlowFlg(true);

								/* �X���[���[�V�����J�E���g�����Z�b�g���� */
								this->PlayerStatusList->SetPlayerSlowMotionCount(0);
							}
						}
						else
						{
							// �󒆂ɂ��Ȃ��ꍇ
							/* �X���[���[�V�����t���O���L���ł��邩�m�F */
							if (this->StageStatusList->bGetGameSlowFlg() == true)
							{
								// �L���ł���ꍇ
								/* �X���[���[�V�����t���O�𖳌��� */
								this->StageStatusList->SetGameSlowFlg(false);

								/* �X���[���[�V�����J�E���g�����Z�b�g���� */
								this->PlayerStatusList->SetPlayerSlowMotionCount(0);
							}
						}
					}
					/* �ߋ����U��(��)��̃J�E���g����萔�𒴂��Ă��邩�m�F */
					else if (iPlayerMeleeStrongAfterCount >= PLAYER_STRONG_MELEE_AFTER_COUNT_MAX)
					{
						// �ߋ����U��(��)��̃J�E���g����萔�𒴂����ꍇ
						/* �ߋ����U��(��)��̃J�E���g�����Z�b�g */
						this->PlayerStatusList->SetPlayerMeleeStrongAfterCount(0);

						/* �ߋ����U��(��)�œG��|������̃t���O������ */
						this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(false);

						/* �ߋ����U��(��)�ł̌��j�������Z�b�g���� */
						this->PlayerStatusList->SetMeleeStrongDestroyCount(0);

						/* ���ߊ����G�t�F�N�g�����݂��Ă��邩�m�F */
						if (this->pChargeHoldEffect != nullptr)
						{
							// ���ߊ����G�t�F�N�g�����݂��Ă���ꍇ
							/* ���ߊ�����G�t�F�N�g���폜 */
							this->pChargeHoldEffect->SetDeleteFlg(true);
							this->pChargeHoldEffect = nullptr;
						}

						/* �X���[���[�V�����t���O���L���ł��邩�m�F */
						if (this->StageStatusList->bGetGameSlowFlg() == true)
						{
							// �L���ł���ꍇ
							/* �X���[���[�V�����t���O�𖳌��� */
							this->StageStatusList->SetGameSlowFlg(false);

							/* �X���[���[�V�����J�E���g�����Z�b�g���� */
							this->PlayerStatusList->SetPlayerSlowMotionCount(0);
						}
					}
					/* �ߋ����U��(��)��̃J�E���g�����Z */
					this->PlayerStatusList->SetPlayerMeleeStrongAfterCount(iPlayerMeleeStrongAfterCount + 1);
				}
				else
				{
					//�ߋ����U��(��)��A���ōs���Ȃ��ꍇ
					/* �X���[���[�V�����t���O���L���ł��邩�m�F */
					if (this->StageStatusList->bGetGameSlowFlg() == true)
					{
						// �L���ł���ꍇ
						/* �X���[���[�V�����t���O�𖳌��� */
						this->StageStatusList->SetGameSlowFlg(false);
					}
				}
			}
			else
			{
				// �ߋ����U��(��)�œG��|������łȂ��ꍇ
				/* �X���[���[�V�����t���O���L���ł��邩�m�F */
				if (this->StageStatusList->bGetGameSlowFlg() == true)
				{
					// �L���ł���ꍇ
					/* �X���[���[�V�����t���O�𖳌��� */
					this->StageStatusList->SetGameSlowFlg(false);

					/* �X���[���[�V�����J�E���g�����Z�b�g���� */
					this->PlayerStatusList->SetPlayerSlowMotionCount(0);
				}
			}
			
			/* �X���[���[�V�������L���ł��邩�m�F */
			if (this->StageStatusList->bGetGameSlowFlg() == true)
			{
				// �L���ł���ꍇ
				/* �X���[���[�V�����J�E���g���擾 */
				int iNowSlowMotionCount = this->PlayerStatusList->iGetPlayerSlowMotionCount();

				/* �X���[���[�V�����J�E���g�����l�𒴂��Ă��邩�m�F */
				if (iNowSlowMotionCount > PLAYER_STRONG_MELEE_AFTER_COUNT_MAX)
				{
					// �X���[���[�V�����J�E���g�����l�𒴂��Ă���ꍇ
					/* �X���[���[�V�����t���O���L���ł��邩�m�F */
					if (this->StageStatusList->bGetGameSlowFlg() == true)
					{
						// �L���ł���ꍇ
						/* �X���[���[�V�����t���O�𖳌��� */
						this->StageStatusList->SetGameSlowFlg(false);

						/* �X���[���[�V�����J�E���g�����Z�b�g���� */
						this->PlayerStatusList->SetPlayerSlowMotionCount(0);
					}
				}

				/* �X���[���[�V�����J�E���g�����Z���� */
				this->PlayerStatusList->SetPlayerSlowMotionCount(iNowSlowMotionCount + 1);
		
			}
			
			// �������U���̏���
			/* �G�C��(�\��)���͂�����Ă��邩�m�F */
			if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
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
/* 2025.03.03 �e�r�듹	�ߋ����U��(��)�����C�� �I�� */
/* 2025.03.04 �e�r�듹	�X���[���[�V���������ǉ�	�I�� */
/* 2025.03.17 �e�r�듹	�G�t�F�N�g�����ǉ�	�I�� */
/* 2025.03.21 �e�r�듹	�X���[���[�V���������ǉ� �I�� */

	/* 2025.01.24 �e�r�듹	�U�������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �J�n */
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
	/* 2025.02.07 �e�r�듹	�G�t�F�N�g�����C�� �J�n */
	/* 2025.02.19 �e�r�듹	�G�t�F�N�g�����C�� �J�n */
/* 2025.02.26 �e�r�듹	�ߋ����U��(��)�����C��	�J�n */
/* 2025.03.03 �e�r�듹	�ߋ����U��(��)�����C�� �J�n */
/* 2025.03.18 �e�r�듹	�G�f�B�b�g�ɂ�鏈���ǉ� �J�n */
/* 2025.03.21 �e�r�듹	�X���[���[�V���������ǉ� �J�n */
// �ߐڍU��(�\��)
void CharacterPlayer::Player_Melee_Posture()
{
	/* �G�f�B�b�g�ɂ��U���`���[�W�t���[���̒Z�k�l���擾 */
	int iEditChargeFlameShortening = this->PlayerStatusList->iGetAddAttackChargeFrameShortening();

	/* �ߐڍU��(��)�̐؂�ւ��t���[�������擾 */
	int iMeleeStrongChangeFrame = this->PlayerStatusList->iGetPlayerMelleStrongChangeChargeFrame();

	/* �v���C���[�̌��݂̍U���`���[�W�t���[�����擾 */
	int iNowAttakChargeFlame = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() + iEditChargeFlameShortening;

	/* �ߐڍU��(��)�`���[�W�ő�t���[�������擾 */
	int iMeleeChargeMaxFlame = this->PlayerStatusList->iGetPlayerMelleStrongMaxChargeFrame();

	/* �v���C���[�̋󒆂ł̋ߐڍU��(��)�̉񐔂��擾 */
	int iNowMeleeStrongAirCount = this->PlayerStatusList->iGetPlayerMeleeStrongAirCount();

	/* �v���C���[���ߐڍU��(��)�œG��|������̃J�E���g���擾 */
	int iPlayerMeleeStrongAfterCount = this->PlayerStatusList->iGetPlayerMeleeStrongAfterCount();

	/* �U�����͂�����Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		/* �X���[���[�V�������L�����m�F���� */
		if (this->StageStatusList->bGetGameSlowFlg() == true)
		{
			/* �X���[���[�V�����J�E���g���擾 */
			int iNowSlowMotionCount = this->PlayerStatusList->iGetPlayerSlowMotionCount();

			/* �X���[���[�V�����J�E���g�����l�𒴂��Ă��邩�m�F */
			if (iNowSlowMotionCount > PLAYER_SLOWMOTION_COUNT_MAX)
			{
				// �X���[���[�V�����J�E���g�����l�𒴂��Ă���ꍇ
				/* �X���[���[�V�����t���O���L���ł��邩�m�F */
				if (this->StageStatusList->bGetGameSlowFlg() == true)
				{
					// �L���ł���ꍇ
					/* �X���[���[�V�����t���O�𖳌��� */
					this->StageStatusList->SetGameSlowFlg(false);

					/* �X���[���[�V�����J�E���g�����Z�b�g���� */
					this->PlayerStatusList->SetPlayerSlowMotionCount(0);
				}
			}

			/* �X���[���[�V�����J�E���g�����Z���� */
			this->PlayerStatusList->SetPlayerSlowMotionCount(iNowSlowMotionCount + 1);
		
		}
		
		// �ߐڍU��(��)�œG��|������A��莞�ԓ��ł���΍U���`���[�W�t���[�������ő�ɂ��� 
		/* �v���C���[���ߐڍU��(��)�œG��|�����ォ�̃t���O���m�F */
		if (this->PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg() == true)
		{
			// �ߐڍU��(��)�œG��|������̏ꍇ
			// �ߐڍU��(��)�ŘA���ł���ő�t���[�������擾
			int iMeleeStrongContinuosMaxFrame = this->PlayerStatusList->iGetPlayerMeleeStrongContinusMaxFrame();
			
			/* �ߐڍU��(��)�œG��|������̃J�E���g�����l�ȉ����m�F */
			if (iPlayerMeleeStrongAfterCount <= iMeleeStrongContinuosMaxFrame)
			{
					/* �ߐڍU��(��)�̍U���`���[�W�t���[�������ő�ɐݒ� */
					this->PlayerStatusList->SetPlayerNowAttakChargeFlame(iMeleeChargeMaxFlame);

					/* ���݂̍U���`���[�W�t���[�����擾 */
					iNowAttakChargeFlame = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame();

					/* �ߐڍU��(��)�œG��|������̃J�E���g�����Z�b�g */
					this->PlayerStatusList->SetPlayerMeleeStrongAfterCount(0);

					/* �ߐڍU��(��)�œG��|������̃t���O������ */
					this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(false);
							
			}
			else
			{
				// �ߐڍU��(��)�œG��|������̃J�E���g�����l�ȏ�̏ꍇ
				/* �X���[���[�V�����t���O���L���ł��邩�m�F */
				if (this->StageStatusList->bGetGameSlowFlg() == true)
				{
					// �L���ł���ꍇ
					/* �X���[���[�V�����t���O�𖳌��� */
					this->StageStatusList->SetGameSlowFlg(false);

					/* �X���[���[�V�����J�E���g�����Z�b�g���� */
					this->PlayerStatusList->SetPlayerSlowMotionCount(0);
				}
			}


		}

		// �U���`���[�W�t���[�������U���̐؂�ւ��ɒB������
		if (iNowAttakChargeFlame == iMeleeStrongChangeFrame)
		{
			/* �󒆂ł̋ߐڍU��(��)�̉񐔂��ő吔�������Ă��Ȃ����m�F */
			if (iNowMeleeStrongAirCount >= this->PlayerStatusList->iGetPlayerMeleeStrongAirMaxCount())
			{
				// �����Ă���ꍇ
				/* �ߐڍU��(��)�̏������s��Ȃ� */
				return;
			}

			/* �v���C���[���[�V������"����(����)"�ɕύX */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_CHARGE);

			/* ���߂�SE���Đ� */
			gpDataList_Sound->SE_PlaySound(SE_PLAYER_CHARGE);

			/* ���߂̃G�t�F�N�g�𓁂̈ʒu�ɐ��� */
			this->pChargeEffect = new EffectManualDelete_PlayerFollow_Frame(this->iKatanaFrameNo);

			/* ���߃G�t�F�N�g�̓ǂݍ��� */
			this->pChargeEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge/FX_charge")));

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
			if (iNowAttakChargeFlame <= iMeleeChargeMaxFlame)
			{
				// �����Ă��Ȃ��ꍇ
				/* �v���C���[�̌��݂̍U���`���[�W�t���[�������Z */
				PlayerStatusList->SetPlayerNowAttakChargeFlame(iNowAttakChargeFlame + 1);

				/* ���Z�ɂ��`���[�W�t���[�����ő�l�ɒB�������m�F */
				if ((iNowAttakChargeFlame + 1) == iMeleeChargeMaxFlame)
				{
					// �ő�l�ɒB�����ꍇ
					/* ���ߋ����`���[�W������SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_CHARGE_COMPLETE);

					/* ���߃G�t�F�N�g�����݂��邩�m�F */
					if (this->pChargeEffect != nullptr)
					{
						// ���߃G�t�F�N�g�����݂���ꍇ
					/* ���߃G�t�F�N�g�͍폜 */
					this->pChargeEffect->SetDeleteFlg(true);
					this->pChargeEffect = nullptr;
					}

					/* ���ߊ����G�t�F�N�g�𐶐� */
					EffectSelfDelete_PlayerFollow_Frame* pAddEffect = new EffectSelfDelete_PlayerFollow_Frame(iKatanaFrameNo);

					/* ���ߊ����G�t�F�N�g�̓ǂݍ��� */
					pAddEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge_finish/FX_charge_finish")));

					/* ���ߊ����G�t�F�N�g�̏����� */
					pAddEffect->Initialization();

					/* ���ߊ����G�t�F�N�g�̎��Ԃ�ݒ� */
					pAddEffect->SetDeleteCount(20);

					/* ���ߊ����G�t�F�N�g�����X�g�ɓo�^ */
					{
						/* ���ߊ����G�t�F�N�g�����X�g�ɓo�^ */
						this->ObjectList->SetEffect(pAddEffect);
					}

					/* ���ߊ�����G�t�F�N�g�𐶐� */
					this->pChargeHoldEffect = new EffectManualDelete_PlayerFollow_Frame(iKatanaFrameNo);
					
					/* ���ߊ�����G�t�F�N�g�̓ǂݍ��� */
					this->pChargeHoldEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge_hold/FX_charge_hold")));
					
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

			/* �ߋ����U��(��)�ɂ��ړ������̃X�P�[�������߂� */
			float fMoveScale = this->PlayerStatusList->fGetPlayerMelleStrongMoveScale();
		
			/* �`���[�W�t���[�����Ɉړ������̃X�P�[������Z���ړ��ʂ��Z�o���� */
			float fMoveDistance = this->PlayerStatusList->iGetPlayerNowAttakChargeFlame() * fMoveScale;

			/* �ړ������Z�o */
			VECTOR vecMoveDirection = VNorm(VSub(this->StageStatusList->vecGetCameraTarget(), this->StageStatusList->vecGetCameraPosition()));

			/* �ߐڍU��(��)�ɂ��ړ��ʂ�ݒ� */
			this->PlayerStatusList->SetPlayerChargeAttakTargetMove(VScale(vecMoveDirection, fMoveDistance));

			/* �ߐڍU��(��)�ւ̐؂�ւ��t���[�������擾 */
			int MelleStrongChangeFrame = this->PlayerStatusList->iGetPlayerMelleStrongChangeChargeFrame();

			/* �U���`���[�W�t���[�������U���ɔh�����Ă��邩�m�F */
			if (iNowAttakChargeFlame >= MelleStrongChangeFrame)
			{
				/* �J�������[�h��"�\��(�ߐڍU���\��)"�ɕύX */
				this->StageStatusList->SetCameraMode(CAMERA_MODE_AIM_MELEE);

				/* �v���C���[�̌������J�����̌����ɌŒ� */
				this->PlayerStatusList->SetPlayerAngleX(this->StageStatusList->fGetCameraAngleX());
				

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
				this->stMeleeStrongMoveCollsion.vecCapsuleTop = VAdd(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT - PLAYER_WIDE, 0)), VScale(vecMoveDirection, fMoveDistance));
				this->stMeleeStrongMoveCollsion.vecCapsuleBottom = VAdd(VAdd(this->vecPosition, VGet(0, PLAYER_WIDE, 0)), VScale(vecMoveDirection, fMoveDistance));
				this->stMeleeStrongMoveCollsion.fCapsuleRadius = PLAYER_WIDE;
			}
		}
	}
	else
	{
		// �U�����͂�����Ă��Ȃ��ꍇ
		/* �U���`���[�W�t���[���ɉ����ď�����ύX */
		if (iNowAttakChargeFlame < iMeleeStrongChangeFrame)
		{
			// ���U���ɐ؂�ւ��O�̏ꍇ
			/* �v���C���[�̏�Ԃ�"�ߐڍU����(��)"�ɐݒ� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_WEEK);
		}
		else
		{
			// ���U���ɂȂ�ꍇ
			/* �v���C���[�̋󒆂ł̋ߐڍU��(��)�ő吔���擾 */
			int iMeleeStrongAirMaxCount = this->PlayerStatusList->iGetPlayerMeleeStrongAirMaxCount();

			/* �G�f�B�b�g�ɂ��󒆂ł̋ߐڍU��(��)�ő吔�̉��Z�����擾 */
			int iEditAddMeleeStrongAirMaxCount = this->PlayerStatusList->iGetAddMeleeStrongAirMaxCount();

			/* �󒆂ł̋ߐڍU��(��)�̉񐔂��ő吔�������Ă��Ȃ����m�F */
			if (iNowMeleeStrongAirCount >= iMeleeStrongAirMaxCount + iEditAddMeleeStrongAirMaxCount)
			{
				// �����Ă���ꍇ
				/*�ߐڍU��(��)�̏������s��Ȃ� */
				return;
			}

			/* �v���C���[�̏�Ԃ�"�ߐڍU����(��)"�ɐݒ� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_MELEE_STRONG);

			/* �v���C���[�̂��ߍU���p�̃J�E���g�������� */
			this->PlayerStatusList->SetPlayerMeleeStrongChargeCount(0);

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
/* 2025.01.24 �e�r�듹	�U�������ǉ�			�I��*/
/* 2025.01.26 ��򕗏�	�R�[�h�C��				�I��*/
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �I�� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */
/* 2025.02.07 �e�r�듹	�G�t�F�N�g�����C�� �I�� */
/* 2025.02.19 �e�r�듹	�G�t�F�N�g�����C�� �I�� */
/* 2025.02.26 �e�r�듹	�ߋ����U��(��)�����C��	�I�� */
/* 2025.03.18 �e�r�듹	�G�f�B�b�g�ɂ�鏈���ǉ� �I�� */
/* 2025.03.21 �e�r�듹	�X���[���[�V���������ǉ� �I�� */

// �ߐڍU��(��)
void CharacterPlayer::Player_Melee_Weak()
{
	/* 2025.01.22 �e�r�듹	�U�������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
	/* 2025.02.26 �e�r�듹	�N�[���^�C�������ǉ� �J�n */
	/* 2025.03.06 �e�r�듹	�G�t�F�N�g�����ǉ�		�J�n */

	// �N�[���^�C�����c���Ă���ꍇ�U�����Ȃ�
	/* �ߐڍU��(��)�̃N�[���^�C�����m�F */
	if (this->iMeleeWeakNowCoolTime > 0)
	{
		// �N�[���^�C�����c���Ă���ꍇ
		/* �ߋ����U��(��)�������s��Ȃ� */
		return;
	}

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

	/* �ߐڍU��(��)��SE���Đ� */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

	/* �U���{�C�X���Đ� */
	gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_ACTION);

	/* �����G�t�F�N�g�𐶐� */
	EffectSelfDelete_PlayerFollow_Frame* pSeathEffect = new EffectSelfDelete_PlayerFollow_Frame(iKatanaFrameNo);

	/* �����G�t�F�N�g�̓ǂݍ��� */
	pSeathEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_seath_unseath/FX_seath_unseath")));

	/* �����G�t�F�N�g�̏����� */
	pSeathEffect->Initialization();

	/* �����G�t�F�N�g�̎��Ԃ�ݒ� */
	pSeathEffect->SetDeleteCount(20);

	/* �����G�t�F�N�g�����X�g�ɓo�^ */
	{
		/* �����G�t�F�N�g�����X�g�ɓo�^ */
		this->ObjectList->SetEffect(pSeathEffect);
	}

	/* �ߐڍU��(��)�̃N�[���^�C���ݒ�l���擾 */
	int iMeleeWeakCoolTime = this->PlayerStatusList->iGetPlayerMeleeWeakCoolTime();

	/* �ߐڍU��(��)�̃N�[���^�C���ݒ� */
	this->iMeleeWeakNowCoolTime = iMeleeWeakCoolTime;

	/* ���R��Ԃɖ߂� */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
}
/* 2025.01.22 �e�r�듹�@�U�������ǉ�	�I�� */
/* 2025.01.26 ��򕗏�	�R�[�h�C��		�I�� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */
/* 2025.02.26 �e�r�듹	�N�[���^�C�������ǉ� �I�� */
/* 2025.03.06 �e�r�듹	�G�t�F�N�g�����ǉ�		�I�� */

/* 2025.01.22 �e�r�듹	�U�������ǉ�		�J�n */
/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n */
/* 2025.02.03 �e�r�듹	�ߋ����U��(��)��̏����ǉ�	�J�n */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
/* 2025.02.26 �e�r�듹	�ߋ����U��(��)�����C��		�J�n */
/* 2025.03.03 �e�r�듹	�ߋ����U��(��)�����C��		�J�n */
/* 2025.03.04 �e�r�듹	�ߋ����U��(��)�����C��		�J�n */
/* 2025.03.06 �e�r�듹	�ߋ����U��(��)�����C��		�J�n */
/* 2025.03.17 ��򕗏�	��ʃG�t�F�N�g�ǉ�			�J�n */
/* 2025.03.17 �e�r�듹	�ߋ����U��(��)�����C��		�J�n */

// �ߋ����U��(��)
void CharacterPlayer::Player_Charge_Attack()
{

	/* �ߋ����U��(��)��Ԃł̃`���[�W�t���[�������擾 */
	int iMeleeStrongChargeCount = this->PlayerStatusList->iGetPlayerMeleeStrongChargeCount();

	/* �ߋ����U��(��)��ɐڒn���Ă邩�̃t���O */
	bool bLandingAfterMeleeStrongFlg = false;

	/* �J�E���g���m�F */
	if (iMeleeStrongChargeCount == 0)
	{
		// 0�ł���ꍇ
		// �����[�V�����J�ڒ���ł���ꍇ
		/* �v���C���[�̃��[�V�������ߐڍU��(��)�ɕύX���� */
		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG);

		/* ���ߋ����U����SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_SPIAI);

		/* �ߋ����U��(��)�{�C�X���Đ� */
		gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_STRONG_MELEE);

		// �󒆂ōU�������ꍇ�̏���
		/* �v���C���[�̒��n�t���O���m�F */
		if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
		{
			// ���n���Ă��Ȃ��ꍇ
			/* ���݂̋󒆂ł̋ߋ����U��(��)�񐔂��擾 */
			int iNowMelleeStrongAirCount = this->PlayerStatusList->iGetPlayerMeleeStrongAirCount();

			/* �󒆂ł̋ߋ����U��(��)�񐔂����Z */
			this->PlayerStatusList->SetPlayerMeleeStrongAirCount(iNowMelleeStrongAirCount + 1);
		}

		/* ���b�N�I�����̃G�l�~�[���擾 */
		Enemy_Basic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

		/* �ߐڍU��(��)�ɂ��ړ��ʂ��擾 */
		VECTOR vecMoveDirection = this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove();

		// �����b�N�I�����̃G�l�~�[�����݂��邩�ŏ����𕪊򂳂���
		/* ���b�N�I�����̃G�l�~�[�����݂��邩 */
		if (pLockOnEnemy != nullptr)
		{
			// ���݂���ꍇ(�G�ɍU������ꍇ)
			/* �󒆂ł̋ߐڍU��(��)�̉񐔂����Z�b�g */
			this->PlayerStatusList->SetPlayerMeleeStrongAirCount(0);

			/* �ړ��ʂ��v���C���[�̌��݈ʒu���烍�b�N�I�����̃G�l�~�[�̈ʒu�ɏC�� */
			vecMoveDirection = VSub(pLockOnEnemy->vecGetPosition(), this->vecPosition);

			/* �G�l�~�[�̈ʒu����ǉ��ňړ�(�˂������銴�����o������) */
			vecMoveDirection = VAdd(vecMoveDirection, VScale(VNorm(vecMoveDirection), 500.f));

			/* �G���U�������t���O��ݒ� */
			this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(true);

			/* ���݂̋ߐڍU��(��)�ł̌��j�����擾 */
			int iNowMeleeStrongDestroyCount = this->PlayerStatusList->iGetiMeleeStrongDestroyCount();

			/* �ߐڍU��(��)�ł̌��j�������Z */
			this->PlayerStatusList->SetMeleeStrongDestroyCount(iNowMeleeStrongDestroyCount + 1);

			//�ړ���̍��W�ɑ��ꂪ���邩�m�F���A�v���C���[�������Ȃ��悤�ɂ��鏈��
			{
				/* �v���C���[�̑���𔻒肷����� */
				COLLISION_LINE stCollisionLine;

				/* �ړ���̃v���C���[�̒��_���牺�����֌������������쐬 */
				stCollisionLine.vecLineStart = VAdd(this->vecGetPosition(), vecMoveDirection);
				stCollisionLine.vecLineStart.y += PLAYER_HEIGHT;
				stCollisionLine.vecLineEnd = stCollisionLine.vecLineStart;
				stCollisionLine.vecLineEnd.y -= PLAYER_HEIGHT + PLAYER_CLIMBED_HEIGHT;

				/* ������擾 */
				auto& PlatformList = ObjectList->GetPlatformList();

				/* ����ƃv���C���[���ڐG���邩�m�F���鏈�� */
				for (auto* platform : PlatformList)
				{
					/* ����Ɛ����̐ڐG������s�� */
					MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stCollisionLine);

					/* ����Ɛ������ڐG���Ă��邩�m�F */
					if (stHitPolyDim.HitFlag == 1)
					{
						// �ڐG���Ă���ꍇ
						/* �ړ��ʂ��v���C���[�̌��݈ʒu���烍�b�N�I�����̃G�l�~�[�̈ʒu�ɏC�� */
						vecMoveDirection = VSub(pLockOnEnemy->vecGetPosition(), this->vecPosition);

						/* �G�l�~�[�̈ʒu����ǉ��ňړ�(�˂������銴�����o������) */
						vecMoveDirection = VAdd(vecMoveDirection, VScale(VNorm(vecMoveDirection), 500.f));

						/* �U����̐ڒn�t���O��ݒ肷�� */
						bLandingAfterMeleeStrongFlg = true;
						
						/* �������I������ */
						break;
					}
					else
					{
						// �ڐG���Ă��Ȃ��ꍇ
						/* �G�l�~�[�̈ʒu�Ɉړ����� */
						vecMoveDirection = VSub(pLockOnEnemy->vecGetPosition(), this->vecPosition);
					}
				}

			}

			/* �ߐڍU��(��)�ɂ��ړ��ʂ�ݒ� */
			this->PlayerStatusList->SetPlayerChargeAttakTargetMove(vecMoveDirection);
		}
		else
		{
			// ���݂��Ȃ��ꍇ(�G�ɍU�����Ȃ��ꍇ)
			/* �ߐڍU��(��)�ł̌��j�������Z�b�g */
			this->PlayerStatusList->SetMeleeStrongDestroyCount(0);
		}
			/* ��ʃG�t�F�N�g(�W����)�쐬 */
			// ���������Ԃ͉���Ɠ����Ƃ���
			ScreenEffect_Base* pScreenEffect = new ScreenEffect_ConcentrationLine();
			this->StageStatusList->SetScreenEffect(pScreenEffect);
			pScreenEffect->SetDeleteTime(this->PlayerStatusList->iGetPlayerMaxDodgeFlame());
		
		}
		else
		{
			// 1�ȏ�ł���ꍇ
			/* �U�����ړ����� */
			
			/* �ߐڍU��(��)�ɂ��ړ��ʂ��擾 */
			VECTOR vecMoveDirection = this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove();
			
				/* �ߐڍU��(��)�̈ړ����x���擾 */
			float fMoveSpeed = this->PlayerStatusList->fGetPlayerMeleeStrongMoveSpeed();

			//�ߐڍU��(��)���ɕǂɓ��������ꍇ�A���Ɉړ����Ȃ��悤�ɂ���
			/* �ǂƂ̐ڐG�t���O���m�F */
			if (this->PlayerStatusList->bGetPlayerWallTouchFlg()==true)
			{
				// �ǂɐڐG���Ă���ꍇ
				/* �������Ɉړ����Ă��邩�m�F */
				if (vecMoveDirection.y <=0)
				{
					// �������Ɉړ����Ă���ꍇ
					/* �ړ��ʂ�Y������0�ɐݒ� */
					vecMoveDirection.y = 0;
				}
			}

			/* �ړ��ʂ�float�^�Ŏ擾 */
			float fMove = VSize(vecMoveDirection);
			
			/* �U�����ړ������ɓ����Ă���̃J�E���g���擾 */
			int iCount = iMeleeStrongChargeCount;

			/* �ړ��ʂ��ړ����x�Ŋ����Ă��̏������s���񐔂��Z�o���� */
			int	iMoveCount = (int)(fMove / fMoveSpeed);

			/* �v���C���[�ړ� */
			if (iCount <= iMoveCount)
			{
				// ���݂̃J�E���g���ړ��񐔈ȉ��ł���ꍇ
				/* �ړ��ʕ��v���C���[���ړ������� */
				this->vecMove = VAdd(this->vecMove, VScale(VNorm(vecMoveDirection), fMoveSpeed));
			}
			else
			{
				// �Ō�̈ړ��̏ꍇ
				/* �Ō�̈ړ��ʂ��擾 */
				float	iLastMove = fMove - (iMoveCount * fMoveSpeed);

				/* �Ō�̈ړ��ʕ��v���C���[���ړ������� */
				this->vecMove = VAdd(this->vecMove, VScale(VNorm(vecMoveDirection), iLastMove));

				// �����ȊO�ł���ꍇ(��A�̍s�����I�������ꍇ)
				/* �v���C���[�̏�Ԃ�"���R���"�ɑJ�� */
				this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

				/* �v���C���[�̃��[�V������"�ߋ����U��(��)(�I��)"�ɕύX */
				this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG_END);

				/* ���b�N�I���͈̓R���W�����g�p�t���O�𖳌��� */
				this->PlayerStatusList->SetMeleeSearchCollisionUseFlg(false);
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
				/* �ߋ����U��(��)�̃G�t�F�N�g�𐶐� */
				EffectSelfDelete* pAddEffect = new EffectSelfDelete();

				/* �ߋ����U��(��)�G�t�F�N�g�̓ǂݍ��� */
				pAddEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_iai_dash/FX_iai_dash")));

				/* �ߋ����U��(��)�G�t�F�N�g�̍Đ����Ԃ�ݒ� */
				pAddEffect->SetDeleteCount(30);

				/* �ߋ����U��(��)�G�t�F�N�g�̍��W�ݒ� */
				pAddEffect->SetPosition(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2.f, 0)));

				/* �ߋ����U��(��)�G�t�F�N�g�̉�]�ʐݒ� */
				pAddEffect->SetRotation(VGet(this->vecRotation.x, this->vecRotation.y, this->vecRotation.z * -1));

				/*�ߋ����U��(��) �G�t�F�N�g�̏����� */
				pAddEffect->Initialization();

				/* �ߋ����U��(��)�G�t�F�N�g�����X�g�ɓo�^ */
				this->ObjectList->SetEffect(pAddEffect);
			}
		}

		// �ߐڍU��(��)�œG��|������A���̓G��T��
		/* �v���C���[���ߐڍU��(��)�œG��|�����ォ�̃t���O���m�F */
		if (this->PlayerStatusList->bGetPlayerMeleeStrongEnemyAttackFlg() == true)
		{
			// �ߐڍU��(��)�œG��|������̏ꍇ
			// ���̓G��T������
			/* �v���C���[�̃��[�V������"�ߋ����U��(��)(�I��)"�ɂȂ����^�C�~���O�Ƃ��� */
			if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
			{
				// ���[�V������"�ߋ����U��(��)(�I��)"�ɂȂ����ꍇ

				/* ���G�͈͂̐ݒ�l���擾 */
				float fSearchRange = this->PlayerStatusList->fGetPlayerMeleeStrongNextSearchRange();

				/* ���G�͈͂�ݒ� */
				COLLISION_SQHERE stSearchSqere{ this->vecPosition, fSearchRange };

				/* �v���C���[�ɋ߂��G�l�~�[���擾���� */
				NearEnemy stNearEnemy = { nullptr, 0.f };

				/* �G�l�~�[���X�g���擾 */
				auto& EnemyList = ObjectList->GetEnemyList();

				/* �v���C���[����G�l�~�[�̍ŏ��x�N�g����ێ�����ϐ� */
				VECTOR vecMinDirection = VGet(fSearchRange, fSearchRange, fSearchRange);

				/* �v���C���[����G�l�~�[�̍ŏ�������ێ�����ϐ� */
				float fMinDistance = VSize(vecMinDirection);

				/* ���G�͈͓��̃G�l�~�[�̂����ł��v���C���[�ɋ߂��G�l�~�[��Ώۂɐݒ� */
				for (auto* enemy : EnemyList)
				{
					/* �Ώۂ̃G�l�~�[�̎��S�t���O���L���ł��邩�m�F */
					if (enemy->bGetDeadFlg() == true)
					{
						// �L���ł���ꍇ
						/* ����̑ΏۊO�Ƃ��� */
						continue;
					}

					/* ���G�͈͂ɐڐG���Ă��邩�m�F */
					if (enemy->HitCheck(stSearchSqere) == true)
					{
						// ���G�͈͓��ł���ꍇ
						/* �R�A�̃��[���h���W���擾 */
						VECTOR vecCoreWorld = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

						/* �v���C���[�ƃG�l�~�[�̊Ԃ��m�F��������R���W������ݒ� */
						COLLISION_LINE stCollisionLine;

						/* �����R���W�����̊J�n�_��ݒ�(�v���C���[) */
						stCollisionLine.vecLineStart = this->vecPosition;

						/* �J�n�_�̍������v���C���[�̍����Ƃ��� */
						stCollisionLine.vecLineStart.y = this->vecPosition.y + PLAYER_HEIGHT;

						/* �����R���W�����I���_��ݒ�(�G�l�~�[) */
						stCollisionLine.vecLineEnd = vecCoreWorld;

						/* �v���b�g�t�H�[�����擾 */
						auto& PlatformList = ObjectList->GetPlatformList();

						/* �v���b�g�t�H�[���Ƃ̐ڐG�t���O */
						bool bPlatformHitFlag = false;

						// �ː���Ƀv���b�g�t�H�[�������݂��邩�m�F����
						for (auto* platform : PlatformList)
						{
							/* �v���b�g�t�H�[���ƐڐG���Ă��邩�m�F */
							MV1_COLL_RESULT_POLY stHitPoly = platform->HitCheck_Line(stCollisionLine);

							/* �ڐG���Ă���ꍇ */
							if (stHitPoly.HitFlag == true)
							{
								/* �v���b�g�t�H�[���Ƃ̐ڐG�t���O��ݒ� */
								bPlatformHitFlag = true;

								/* ���[�v�𔲂���(���̓G�Ɉڂ�) */
								break;
							}
						}

						// �v���C���[�ƃG�l�~�[�̊ԂɃv���b�g�t�H�[�������݂��Ȃ��ꍇ�A�������m�F����
						/* �v���b�g�t�H�[���Ƃ̐ڐG�t���O�������Ă��Ȃ����m�F */
						if (bPlatformHitFlag == false)
						{
							// �ڐG�t���O�������Ă��Ȃ��ꍇ
							/* �v���C���[����G�l�~�[�̃x�N�g����ݒ� */
							VECTOR vecDirection = VSub(vecCoreWorld, this->vecPosition);

							/* �v���C���[����G�l�~�[�̋�����ݒ� */
							float fDistance = VSize(vecDirection);

							/* ���݂̍ł��v���C���[����߂��G�l�~�[�����v���C���[�ɋ߂����m�F */
							if (fMinDistance >= fDistance)
							{
								// �߂��ꍇ
								/* �v���C���[����߂��G�l�~�[���X�V */
								stNearEnemy.pEnemy = enemy;
								stNearEnemy.fDistance = fDistance;

								/* �v���C���[����G�l�~�[�̍ŏ��������X�V */
								fMinDistance = fDistance;
							}
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

					/* �v���C���[���猩���G�̊p�x(XZ)���擾 */
					float fNearEnemyRotate_xz = -atan2f(vecNearEnemy.x, vecNearEnemy.z);
					
					/* �v���C���[���猩���G�̊p�x(Y)���擾 */
					float fNearEnemyRotate_y = -atan2f(vecNearEnemy.y, sqrtf(vecNearEnemy.x * vecNearEnemy.x + vecNearEnemy.z * vecNearEnemy.z));

					/* �v���C���[�̌�����ݒ� */
					this->PlayerStatusList->SetPlayerAngleX(fNearEnemyRotate_xz);

					/* �G�̌����ɃJ�����̌������Œ� */
					this->StageStatusList->SetCameraAngleX(fNearEnemyRotate_xz);
					this->StageStatusList->SetCameraAngleY(fNearEnemyRotate_y);

					/* �v���C���[���ߋ����U��(��)��A���ōs����t���O��ݒ� */
					this->PlayerStatusList->SetPlayerMeleeStrongContinuousFlg(true);
				}
				else
				{
					// �Ώۂ����݂��Ȃ��ꍇ
					/* �G���U�������t���O������ */
					this->PlayerStatusList->SetPlayerMeleeStrongEnemyAttackFlg(false);

					/* �v���C���[���ߋ����U��(��)��A���ōs����t���O������ */
					this->PlayerStatusList->SetPlayerMeleeStrongContinuousFlg(false);

					/* �U����{�C�X���Đ� */
					//gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_KILL_ENEMY);	

					/* ���݂̋ߐڍU��(��)�ł̌��j�����擾 */
					int iNowMeleeStrongDestroyCount = this->PlayerStatusList->iGetiMeleeStrongDestroyCount();

					/* ���݂̋ߐڍU��(��)�ł̌��j������萔�ȏォ�m�F���� */
					if (iNowMeleeStrongDestroyCount >= MELEE_STRONG_PERFORMANCE_DESTROY_NUM)
					{
						// ��萔�ȏ�̏ꍇ
						/* �U����̐ڒn�t���O���m�F */
						if (bLandingAfterMeleeStrongFlg == true)
						{
							//�U����ɐݒu���Ă���ꍇ
							/* �X�e�B�b�N�̓��͂��擾 */
							VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();

							/* �X�e�B�b�N�̓��͂��Ȃ����m�F */
							if (vecInput.x == 0 && vecInput.z == 0)
							{
								// ���͂��Ȃ��ꍇ
								/* �v���C���[�̏�Ԃ�"���R���"�ɑJ�� */
								/* ���ʂȃJ�������[�N���s��(��) */
							
							}	
						}
					}

					/* �ߐڍU��(��)�ł̌��j�������Z�b�g���� */
					this->PlayerStatusList->SetMeleeStrongDestroyCount(0);
				}
			}
		}
	/* ���ߍU���̃`���[�W�t���[������+1���� */
	this->PlayerStatusList->SetPlayerMeleeStrongChargeCount(iMeleeStrongChargeCount + 1);
}
/* 2025.01.22 �e�r�듹	�U�������ǉ�				�I�� */
/* 2025.01.26 ��򕗏�	�R�[�h�C��		�I�� */
/* 2025.02.03 �e�r�듹	�ߋ����U��(��)��̏����ǉ�	�I�� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C��			�I�� */
/* 2025.02.26 �e�r�듹	�ߋ����U��(��)�����C��		�I�� */
/* 2025.03.03 �e�r�듹	�ߋ����U��(��)�����C��		�I�� */
/* 2025.03.04 �e�r�듹	�ߋ����U��(��)�����C��		�I�� */
/* 2025.03.06 �e�r�듹	�ߋ����U��(��)�����C��		�I�� */
/* 2025.03.17 ��򕗏�	��ʃG�t�F�N�g�ǉ�			�I�� */
/* 2025.03.17 �e�r�듹	�ߋ����U��(��)�����C��		�I�� */

/* 2025.02.12 �e�r�듹	�������U�������ǉ� �J�n */
/* 2025.02.26 �e�r�듹	�N�[���^�C�������ǉ�	�J�n */
/* 2025.03.04 �e�r�듹	�X���[���[�V���������ǉ�	�J�n */
/* 2025.03.06 �e�r�듹	�X���[���[�V���������C��	�J�n */
/* 2025.03.12 �e�r�듹	�X���[���[�V���������C��	�J�n */
/* 2025.03.13 ��򕗏�	�N�i�C�e���ݒ�				�J�n */
// �������U��(�\��)
void CharacterPlayer::Player_Projectile_Posture()
{
	/* �G�C��(�\��)���͂�����Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
	{
		/* �v���C���[�̌������J�����̌����ɌŒ� */
		this->PlayerStatusList->SetPlayerAngleX(this->StageStatusList->fGetCameraAngleX());
		
		/* �J�������[�h��"�\��(�N�i�C�U��)"�ɕύX */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_AIM_KUNAI);

		// �W�����v���ł���΃X���[���[�V�������s��
		/* �W�����v���̃t���O���m�F */
		if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true)
		{
			/* �X���[���[�V�����J�E���g���擾 */
			int iNowSlowMotionCount = this->PlayerStatusList->iGetPlayerSlowMotionCount();
			// �W�����v���̏ꍇ
			/* �X���[���[�V�����t���O�������ł��邩�m�F */
			if (this->StageStatusList->bGetGameSlowFlg() == false)
			{
				// �����ł���ꍇ
				/* �X���[���[�V�����J�E���g�����l�𒴂��Ă��Ȃ����m�F */
				if (iNowSlowMotionCount <= PLAYER_SLOWMOTION_COUNT_MAX)
				{
					//�X���[���[�V�����J�E���g�����l�ȉ��̏ꍇ
				/* ��ʃG�t�F�N�g(��_���[�W)�쐬 */
				this->StageStatusList->SetScreenEffect(new ScreenEffect_Damage());

				/* �X���[���[�V�����t���O��L���� */
				this->StageStatusList->SetGameSlowFlg(true);
			}
			}

			/* �X���[���[�V�����J�E���g�����l�𒴂��Ă��邩�m�F */
			if (iNowSlowMotionCount > PLAYER_SLOWMOTION_COUNT_MAX)
			{
				// �X���[���[�V�����J�E���g�����l�𒴂��Ă���ꍇ
				/* �X���[���[�V�����t���O���L���ł��邩�m�F */
				if (this->StageStatusList->bGetGameSlowFlg() == true)
				{
					// �L���ł���ꍇ
				/* �X���[���[�V�����t���O�𖳌��� */
				this->StageStatusList->SetGameSlowFlg(false);	
			}
			}

			/* �X���[���[�V�����J�E���g�����Z���� */
			this->PlayerStatusList->SetPlayerSlowMotionCount(iNowSlowMotionCount + 1);
		}
		else
		{
			// �W�����v���łȂ��ꍇ
			/* �X���[���[�V�����t���O���L���ł��邩�m�F */
			if (this->StageStatusList->bGetGameSlowFlg() == true)
			{
				// �L���ł���ꍇ
				/* �X���[���[�V�����t���O�𖳌��� */
			this->StageStatusList->SetGameSlowFlg(false);
		}
		}

		/* �v���C���[�̃��[�V�����������łȂ����m�F */
		if (this->PlayerStatusList->iGetPlayerMotion_Attack() != MOTION_ID_ATTACK_THROW)
		{
			// �v���C���[�̃��[�V�����������łȂ��ꍇ
			/* �v���C���[�̃��[�V�����𓊝�(����)�ɐݒ� */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_THROW_READY);
		}

		//���͂��ꂽ�{�^���ɉ����ď�����ς���
		/* �U�����͂����ꂽ�ꍇ */
		if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
		{
			/* �������U���̃N�[���^�C�����m�F */
			if (this->iProjectileNowCoolTime == 0)
			{
				// �N�[���^�C����0�̏ꍇ
				/* ���݂̃N�i�C�̏��������擾 */
				int iNowKunaiCount = this->PlayerStatusList->iGetNowHaveKunai();

				/* �N�i�C���������Ă��邩���m�F */
				if (iNowKunaiCount > 0)
				{
					// �������Ă���ꍇ
					/* �N�i�C�������(%)���擾 */
					int iKeepProbability = this->PlayerStatusList->iGetAddKunaiKeepProbability();

					/* �����_��(0�`100)�Ȓl���擾���A�N�i�C������������������l�ł��邩�m�F */
					if (GetRand(100) <= iKeepProbability)
					{
						// �������ꍇ
						/* �N�i�C������Ȃ� */
						iNowKunaiCount = 0;
					}
					else
					{
						// �傫���ꍇ
						/* �N�i�C������� */
						iNowKunaiCount--;
					}

					/* �N�i�C�̏�������ݒ� */
					this->PlayerStatusList->SetNowHaveKunai(iNowKunaiCount);

					/* �v���C���[�̃��[�V�����𓊝��ɐݒ� */
					this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_THROW);

					/* �v���C���[�̍U����Ԃ�"�������U����"�ɑJ�� */
					this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE);
				}
			}
		}
		/* �W�����v���͂����ꂽ�ꍇ */
		else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
		{
			// �������U���\����Ԃ��L�����Z������
			/* �������U���\����ԃL�����Z���t���O�����Ă� */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			
			/* �v���C���[�̃��[�V�����𖳂��ɐݒ� */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);

			/* �v���C���[�U����Ԃ�"���R���"�ɐݒ� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

			/* �X���[���[�V�����t���O���L���ł��邩�m�F */
			if (this->StageStatusList->bGetGameSlowFlg() == true)
			{
				// �L���ł���ꍇ
				/* �X���[���[�V�����t���O�𖳌��� */
			this->StageStatusList->SetGameSlowFlg(false);
			}
		}
		/* �����͂����ꂽ�ꍇ */
		else if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_DODGE) == true)
		{
			// �������U���\����Ԃ��L�����Z������
			/* �������U���\����ԃL�����Z���t���O�����Ă� */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			
			/* �v���C���[�̃��[�V�����𖳂��ɐݒ� */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);

			/* �v���C���[�U����Ԃ�"���R���"�ɐݒ� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

			/* �X���[���[�V�����t���O���L���ł��邩�m�F */
			if (this->StageStatusList->bGetGameSlowFlg() == true)
			{
				// �L���ł���ꍇ
				/* �X���[���[�V�����t���O�𖳌��� */
			this->StageStatusList->SetGameSlowFlg(false);
		}
		}
		
	}
	/* �G�C��(�\��)���͂�����Ă��Ȃ��ꍇ */
	else 
	{
		/* �v���C���[�U����Ԃ�"���R���"�ɐݒ� */
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

		/* �v���C���[�̃��[�V�����𖳂��ɐݒ� */
		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);

		/* �X���[���[�V�����t���O�𖳌��� */
		this->StageStatusList->SetGameSlowFlg(false);
	}
}
/* 2025.02.12 �e�r�듹	�������U�������ǉ� �I�� */
/* 2025.02.26 �e�r�듹	�N�[���^�C�������ǉ� �I�� */
/* 2025.03.04 �e�r�듹	�X���[���[�V���������ǉ�	�I�� */
/* 2025.03.06 �e�r�듹	�X���[���[�V���������C��	�I�� */
/* 2025.03.12 �e�r�듹	�X���[���[�V���������C��	�I�� */
/* 2025.03.13 ��򕗏�	�N�i�C�e���ݒ�				�I�� */

/* 2025.02.14 �e�r�듹	�������U�������ǉ� �J�n */
/* 2025.02.21 �e�r�듹	�������U���C�� �J�n */
/* 2025.02.26 �e�r�듹	�N�[���^�C�������ǉ�	�J�n */
/* 2025.03.10 �e�r�듹	�G�t�F�N�g�����ǉ�		�J�n */
/* 2025.03.13 �e�r�듹	�N�i�C�����ύX �J�n */
/* 2025.03.18 �e�r�듹	�G�f�B�b�g�ɂ�鏈���ǉ�	�J�n */
// �������U��
void CharacterPlayer::Player_Projectile()
{
	/* �v���C���[�̌������J�����̌����ɌŒ� */
	this->PlayerStatusList->SetPlayerAngleX(this->StageStatusList->fGetCameraAngleX());

	/* �J�������[�h��"�\��(�N�i�C�U��)"�ɕύX */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_AIM_KUNAI);
	
	/* �J�������W����J�����̒����_�Ɍ������x�N�g�����擾 */
	VECTOR vecKunaiTarget = VSub(this->StageStatusList->vecGetCameraTarget(), this->StageStatusList->vecGetCameraPosition());

	/* �x�N�g���𐳋K�� */
	vecKunaiTarget = VNorm(vecKunaiTarget);

	/* �x�N�g�����˒������܂ŃX�P�[�����O */
	vecKunaiTarget = VScale(vecKunaiTarget, KUNAI_RANGE);

	/* �^�[�Q�b�g���W�̍��W�x�N�g�����擾 */
	vecKunaiTarget = VAdd(this->StageStatusList->vecGetCameraPosition(), vecKunaiTarget);

	/* ���b�N�I�����̃G�l�~�[���擾 */
	Enemy_Basic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

	// �G�f�B�b�g�̓��e����ď�����ς���
	/* �N�i�C�������t���O���L�����m�F���� */
	if (this->PlayerStatusList->bGetKunaiExplosion() == true)
	{
		// �N�i�C�������t���O���L���ł���ꍇ
		/* �N�i�C(����)���쐬 */
		this->pBulletKunaiExplosion = new BulletPlayerKunaiExplosion;

		/* ���b�N�I�����̃G�l�~�[�����݂��邩 */
		if (pLockOnEnemy != nullptr)
		{
			// ���݂���ꍇ
			/* �N�i�C(����)�̃^�[�Q�b�g���W�����b�N�I�����̃G�l�~�[�ɐݒ� */
			this->pBulletKunaiExplosion->SetKunaiTargetPosition(pLockOnEnemy->vecGetPosition());
		}
		else
		{
			// ���݂��Ȃ��ꍇ
			// �N�i�C(����)�̃^�[�Q�b�g���W���J�����̒����_�̐�ɐݒ�
			/* �N�i�C(����)�Ƀ^�[�Q�b�g���W��ݒ� */
			this->pBulletKunaiExplosion->SetKunaiTargetPosition(vecKunaiTarget);
		}

		/* ���������s�� */
		this->pBulletKunaiExplosion->Initialization();

		/* �o���b�g���X�g�ɒǉ� */
		ObjectList->SetBullet(this->pBulletKunaiExplosion);
	}
	else
	{
		// �N�i�C�������t���O���L���łȂ��ꍇ
	/* �N�i�C(���[�v)���쐬 */
	this->pBulletKunaiWarp = new BulletPlayerKunaiWarp;

	/* �N�i�C(���[�v)�������W��ݒ� */
	this->pBulletKunaiWarp->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y + PLAYER_HEIGHT / 2, this->vecPosition.z));
	
	/* ���b�N�I�����̃G�l�~�[�����݂��邩 */
	if (pLockOnEnemy != nullptr)
	{
		// ���݂���ꍇ
		/* �N�i�C(���[�v)�̃^�[�Q�b�g���W�����b�N�I�����̃G�l�~�[�ɐݒ� */
		this->pBulletKunaiWarp->SetKunaiTargetPosition(pLockOnEnemy->vecGetPosition());

		/* ���b�N�I�����̃G�l�~�[�̃|�C���^���N�i�C(���[�v)�ɓn�� */
		this->pBulletKunaiWarp->SetKunaiTargetEnemy(pLockOnEnemy);
}
	else
	{
		// ���݂��Ȃ��ꍇ
		// �N�i�C(���[�v)�̃^�[�Q�b�g���W���J�����̒����_�̐�ɐݒ�
		// �N�i�C(���[�v)�Ƀ^�[�Q�b�g���W��ݒ�
		this->pBulletKunaiWarp->SetKunaiTargetPosition(vecKunaiTarget);

	}

	/* ���������s�� */
	this->pBulletKunaiWarp->Initialization();
	
	/* �o���b�g���X�g�ɒǉ� */
	ObjectList->SetBullet(this->pBulletKunaiWarp);
	}

	/* �������U����SE���Đ� */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_KUNAI);

	/* �������U���{�C�X���Đ� */
	gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_PROJECTILE);

	/* �������U���G�t�F�N�g�𐶐� */
	EffectSelfDelete* pProjectileEffect = new EffectSelfDelete();

	/* �������U���G�t�F�N�g�̓ǂݍ��� */
	pProjectileEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_seath_unseath/FX_seath_unseath")));

	/* �������U���G�t�F�N�g�̏����� */
	pProjectileEffect->Initialization();

	/* �������U���G�t�F�N�g�̎��Ԃ�ݒ� */
	pProjectileEffect->SetDeleteCount(20);

	/* �N�i�C�̎�̍��W���擾 */
	VECTOR vecKunaiHand = MV1GetFramePosition(this->iModelHandle, iKunaiHandFrameNo);

	/* �������U���G�t�F�N�g�̍��W��ݒ� */
	pProjectileEffect->SetPosition(vecKunaiHand);

	/* �������U���G�t�F�N�g�����X�g�ɓo�^ */
	{
		/* �������U���G�t�F�N�g�����X�g�ɓo�^ */
		this->ObjectList->SetEffect(pProjectileEffect);
	}

	/* �������U���̃N�[���^�C���ݒ�l���擾 */
	int iProjectileCoolTime = this->PlayerStatusList->iGetPlayerKunaiCoolTime();

	/* �������U���̃N�[���^�C����ݒ� */
	this->iProjectileNowCoolTime = iProjectileCoolTime;

	/* �������U���\����Ԃɖ߂� */
	this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE);
}
/* 2025.02.14 �e�r�듹	�������U�������ǉ� �I�� */
/* 2025.02.21 �e�r�듹	�������U���C��			�I�� */
/* 2025.02.26 �e�r�듹	�N�[���^�C�������ǉ�	�I�� */
/* 2025.03.10 �e�r�듹	�G�t�F�N�g�����ǉ�		�I�� */
/* 2025.03.13 �e�r�듹	�N�i�C�����ύX				�I�� */
/* 2025.03.18 �e�r�듹	�G�f�B�b�g�ɂ�鏈���ǉ�	�I�� */