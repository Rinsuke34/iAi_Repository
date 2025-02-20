/* 2025.02.04 �e�r�듹	�t�@�C���쐬 */
/* 2025.01.09 �e�r�듹	�ړ������ǉ� */
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� */
/* 2025.02.06 �e�r�듹	�G�t�F�N�g�����C�� */
/* 2025.02.07 �e�r�듹	�Փ˔��菈���C�� */
/* 2025.02.10 �e�r�듹	�U����������C�� */
/* 2025.02.10 �e�r�듹	��������C�� */
/* 2025.02.14 �e�r�듹	�U����������C�� */

#include "CharacterPlayer.h"

// �ړ�
void CharacterPlayer::Player_Move()
{
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */

	/* �v���C���[�ړ��ʎ擾 */
	float fStickTiltMagnitude = this->InputList->fGetGameInputMove();				// �X�e�B�b�N��|��������
	VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();	// �ړ�����
	VECTOR vecAddMove = VGet(0, 0, 0);									// �ړ���(���Z�p)

	/* �v���C���[�̈ړ���Ԃ��擾 */
	int iPlayerMoveState	= this->PlayerStatusList->iGetPlayerMoveState();
	/* �v���C���[�̍U����Ԃ��擾 */
	int iPlayerAttackState	= this->PlayerStatusList->iGetPlayerAttackState();

	/* �v���C���[�̏�Ԃɉ����Ĉړ����x�̔{������ݒ� */
	float	fMoveSpeedRatio = 1.f;		// �ړ����x(�{��)
	bool	bPlayerAngleSetFlg = true;		// �v���C���[�̌������ړ������ɍ��킹�邩�̃t���O
	bool	bPlayerMoveFlg = true;			// �v���C���[�̈ړ����s�����̃t���O	
	
	switch (iPlayerMoveState)
	{
		/* �ړ�������ʏ�ʂ�ɍs����� */
	case PLAYER_MOVESTATUS_FREE:				// ���R���

		/* �ړ��������s�� */
		bPlayerMoveFlg = true;
		
		/* �ړ����x�␳�����ɂ��� */
		fMoveSpeedRatio = 1.f;

		/* �v���C���[�̌������ړ������ɍ��킹�� */
		bPlayerAngleSetFlg = true;
		
		break;

	/* �ړ��������s��Ȃ���� */
	case PLAYER_MOVESTATUS_DODGING:				// �����Ԓ�
	
		// �ړ��������s��Ȃ�
		bPlayerMoveFlg = false;
		
		break;
	}

	switch (iPlayerAttackState)
	{
	
	/* �ړ�������ʏ�ʂ�ɍs����� */
	case PLAYER_ATTACKSTATUS_FREE:	// ���R���
		
		/* �ړ����x�␳�����ɂ��� */
		fMoveSpeedRatio = 1.f;

		/* �v���C���[�̌������ړ������ɍ��킹�� */
		bPlayerAngleSetFlg = true;
		break;

		/* �ړ������𑬓x��}���čs����� */
	case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// �ߐڍU���\����
	case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// �������U���\����
		
		/* �ړ����x�␳0.5�{�ɂ��� */
		// �����̒l
		fMoveSpeedRatio = 0.5f;

		/* �v���C���[�̌������ړ������ɍ��킹�Ȃ� */
		bPlayerAngleSetFlg = false;
		break;

		/* �ړ��������s��Ȃ���� */
	case PLAYER_ATTACKSTATUS_MELEE_WEEK:		// �ߐڍU����(��)
	case PLAYER_ATTACKSTATUS_MELEE_STRONG:		// �ߐڍU����(��)
	case PLAYER_ATTACKSTATUS_PROJECTILE:		// �������U����
		break;	
	}
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */

	/* 2025.01.09 �e�r�듹	�ړ������ǉ�	   �J�n */
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �J�n	*/
	/* 2025.01.30 �e�r�듹	���[�V���������ǉ� �J�n */
	/* 2025.02.06 �e�r�듹	�G�t�F�N�g�����C�� �J�n */

	/* �ړ����͂�����Ă��邩�m�F */
	if ((vecInput.x != 0 || vecInput.z != 0))
	{
		/* �ړ��������s����Ԃ��m�F */
		if (bPlayerMoveFlg = true)
	{
		// �ړ����͂�����Ă���ꍇ
		/* ���݂̈ړ����x�擾 */
		float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();

		// �����t���O��true�Ȃ�ő�_�b�V����ԂɂȂ�
		if (this->PlayerStatusList->bGetPlayerAfterDodgeFlag() == true)
		{
			fSpeed = PLAER_DASH_MAX_SPEED * fMoveSpeedRatio;

			/* ���[�V������"�W�����v(�J�n)"�ȊO�ł��邩�m�F */
			if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
			{
				// �W�����v(�J�n)�ȊO�ł���Ȃ�
				/* ���[�V�����ݒ�(���s) */
				this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WALK);

				/* �v���C���[�̍U�������[�V���������U��(�I��)�ł��邩�m�F */
				if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
				{
					// ���U��(�I��)�ł���Ȃ�
					/* �v���C���[�̍U�������[�V������"����"�ɐݒ� */
					this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
				}
			}
		}

		// �X�e�B�b�N�̓|����ő��x��ω�
		else if (fStickTiltMagnitude > STICK_TILT_PLAER_DASH)
		{
			//����i�ʏ�j
			fSpeed = PLAER_DASH_NOMAL_SPEED * fMoveSpeedRatio;
			//�t���[�������J�E���g
			this->PlayerStatusList->SetPlayerNormalDashFlameCount(PlayerStatusList->iGetPlayerNormalDashFlameCount() + 1);

			//���t���[�����������瑖��i�ő�j��
			/* ���[�V������"�W�����v(�J�n)"�ȊO�ł��邩�m�F */
			if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
			{
				// �W�����v(�J�n)�ȊO�ł���Ȃ�
				/* ���[�V�����ݒ�(���s) */
				this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WALK);

				/* �v���C���[�̍U�������[�V���������U��(�I��)�ł��邩�m�F */
				if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
				{
					// ���U��(�I��)�ł���Ȃ�
					/* �v���C���[�̍U�������[�V������"����"�ɐݒ� */
					this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
				}
			}

			//���t���[���ɒB�������A�_�b�V���G�t�F�N�g���o��������
			if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() == FLAME_COUNT_TO_MAX_SPEED)
			{
				/* �G�t�F�N�g�ǉ� */
				{
					/* �_�b�V���G�t�F�N�g�𐶐� */
					EffectSelfDelete_PlayerFollow* pAddEffect = new EffectSelfDelete_PlayerFollow(true);

					/* �_�b�V���G�t�F�N�g�ǂݍ��� */
					pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_dash/FX_dash")));

					/* �_�b�V���G�t�F�N�g�̎��Ԑݒ� */
					pAddEffect->SetDeleteCount(30);

					///* �_�b�V���G�t�F�N�g�̉�]�ʐݒ� */
					pAddEffect->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

					/* �_�b�V���G�t�F�N�g�̏����� */
					pAddEffect->Initialization();

					/* �_�b�V���G�t�F�N�g�����X�g�ɓo�^ */
					{
						/* �_�b�V���G�t�F�N�g�����X�g�ɓo�^ */
						this->ObjectList->SetEffect(pAddEffect);
					}
				}
			}
			//���t���[���ȏ�ɂȂ����瑖��i�ő�j��
			else if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() >= FLAME_COUNT_TO_MAX_SPEED)
			{
				fSpeed = PLAER_DASH_MAX_SPEED * fMoveSpeedRatio;

				/* ���s(����)���[�V�����ݒ� */
				/* ���[�V������"�W�����v(�J�n)"�ȊO�ł��邩�m�F */
				if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
				{
					// �W�����v(�J�n)�ȊO�ł���Ȃ�
					/* ���[�V�����ݒ�(���s) */
					this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WALK);
				}
			}
		}
		else
		{
			//����
			this->PlayerStatusList->SetPlayerNowMoveSpeed(PLAYER_WALK_MOVE_SPEED);
			this->PlayerStatusList->SetPlayerNormalDashFlameCount(0);
			fSpeed = PLAYER_WALK_MOVE_SPEED * fMoveSpeedRatio;

			/* ���[�V�����ݒ�(���s) */
			/* ���[�V������"�W�����v(�J�n)"�ȊO�ł��邩�m�F */
			if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
			{
				// �W�����v(�J�n)�ȊO�ł���Ȃ�
				/* ���[�V�����ݒ�(���s) */
				this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WALK);
			}
		}

		/* 2025.01.09 �e�r�듹	�ړ������ǉ� �I�� */
		/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �I��	*/
		/* 2025.02.06 �e�r�듹	�G�t�F�N�g�����C�� �I�� */

		/* ���ݑ��x���X�V */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

		/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
		float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

		/* �ړ��ʂ��Z�o */
		vecAddMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecAddMove.y = 0.0f;
		vecAddMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
		vecAddMove = VScale(vecAddMove, fSpeed);

		/* 2025.02.10 �e�r�듹	�U����������C�� �J�n*/
		/* 2025.02.14 �e�r�듹	�U����������C�� �J�n */
		/* �v���C���[�̌������ړ������ɍ��킹�邩�m�F */
		if (bPlayerAngleSetFlg == true)
		{
			// ���킹��ꍇ
			/* �v���C���[�̌������ړ������ɍ��킹�� */
			/* ���͕������擾 */
			float fMoveAngle = atan2f(vecInput.x, vecInput.z);
			
			/* �J�����̐��������̌���������͈̔�(0~2��)�𒴂����ꍇ�A�␳���s�� */
			this->RadianLimitAdjustment(fAngleX);
			
			/* �␳�����J�����p�x��ݒ� */
			this->PlayerStatusList->SetCameraAngleX(fAngleX);

			/* ���͕����ƃJ�����̌������������ړ������Ƃ��� */
			fMoveAngle = fAngleX - fMoveAngle;

			/* �v���C���[�̈ړ�����(���W�A��)������͈̔�(0~2��)�𒴂����ꍇ�A�␳���s�� */
			this->RadianLimitAdjustment(fMoveAngle);

			/* �v���C���[�̌��݂̌���(���W�A��)���擾 */
			float fCurrentAngle = this->PlayerStatusList->fGetPlayerAngleX();

			/* �v���C���[�̌��݂̌���(���W�A��)������͈̔�(0~2��)�𒴂����ꍇ�A�␳���s�� */
			this->RadianLimitAdjustment(fCurrentAngle);

			/* ���݂̃v���C���[�̌����ƈړ������̍������߂� */
			float fDifferrenceAngle = fMoveAngle - fCurrentAngle;

				//�v���C���[�̌����ƈړ������̍�������(��)�𒴂����ꍇ�A��菭�Ȃ��p�x�ŉ�]����悤�ɕ␳���s��
				/* �����Ŕ����𒴂����� */
				if (fDifferrenceAngle > DX_PI_F)
				{
					/* �p�x�����(2��)���␳���� */
				fDifferrenceAngle -= PLAYER_TURN_LIMIT;
				}
				/* �E���Ŕ����𒴂����� */
				else if (fDifferrenceAngle < -DX_PI_F)
				{
					/* �p�x�����(2��)���␳���� */
				fDifferrenceAngle += PLAYER_TURN_LIMIT;
			}

			/* �U��������x�ɉ����Ēi�K�I�Ɉړ����������� */ 
			float fNewAngle = fCurrentAngle + fDifferrenceAngle * this->PlayerStatusList->fGetPlayerTurnSpeed();

			/* �v���C���[�̌������X�V */
			this->PlayerStatusList->SetPlayerAngleX(fNewAngle);

			/* 2025.02.10 �e�r�듹	�U����������C�� �I�� */
			/* 2025.02.14 �e�r�듹	�U����������C�� �I�� */
		}
	}
	}
	else
	{
		// �ړ����͂�����Ă��Ȃ��ꍇ
		/* �ړ����x��0�ɂ��� */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(0);
		//�����t���O�����Z�b�g
		this->PlayerStatusList->SetPlayerAfterDodgeFlag(false);

		// ����(��)(�I��)���[�V�������ȊO�Ȃ�ҋ@���[�V�����ɑJ�� ���o�O�΍�̂��߁A�ȉ��悤�ȏ������ɂȂ��Ă܂�
		if(this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
		{

		}
		else
		{
			// �ҋ@���[�V�����ɑJ��
			/* ���[�V������"�W�����v(�J�n)"�ȊO�ł��邩�m�F */
			if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
			{
				/* ���݂̃��[�V������"���n"�łȂ����m�F */
				if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_LAND)
				{
					/* �ҋ@���[�V�����ݒ� */
					this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WAIT);
				}
			}		
		}
	}

	/* �ړ��ʂ����Z */
	this->vecMove = VAdd(this->vecMove, vecAddMove);
}

/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
// �W�����v
void CharacterPlayer::Player_Jump()
{
	/* �v���C���[�̈ړ���Ԃ��擾 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();
	/* �v���C���[�̍U����Ԃ��擾 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();
	/* �W�����v�������s�����̃t���O */
	bool bJumpFlag = true;

	/* �v���C���[�̈ړ���Ԃ��W�����v�\�ł��邩�m�F */
	// ���v���k
	switch (iPlayerMoveState)
	{
		/* �W�����v�\�ȏ�� */
	case PLAYER_MOVESTATUS_FREE:				// ���R���
		
		/* �W�����v�������s�� */
		bJumpFlag = true;
	
		break;

	/* �W�����v�s�\�ȏ�� */
	case PLAYER_MOVESTATUS_DODGING:				// �����Ԓ�
		
		/* �W�����v�������s�� */
		bJumpFlag = false;
		
		break;
	}

	/* �v���C���[�̍U����Ԃ��W�����v�\�ł��邩�m�F */
	// ���v���k
	switch (iPlayerAttackState)
	{
	/* �W�����v�\�ȏ�� */
	case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// �ߐڍU���\����
	case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// �������U���\����
	case PLAYER_ATTACKSTATUS_PROJECTILE:			// �������U����
		
		/* �W�����v�������s�� */
		bJumpFlag = true;
		break;
	
	/* �W�����v�s�\�ȏ�� */
	case PLAYER_ATTACKSTATUS_MELEE_WEEK:		// �ߐڍU����(��)
	case PLAYER_ATTACKSTATUS_MELEE_STRONG:		// �ߐڍU����(��)
		
		/* �W�����v�������s��Ȃ� */
		bJumpFlag = false;
		break;
	}

		/* �v���C���[�̃W�����v���� */
	/* �ړ��������s����Ԃ��m�F */
	if (bJumpFlag == true)
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
				//this->PlayerStatusList->SetPlayerNowFallSpeed(-20.0f);
				this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);

				/* �W�����v�񐔂��X�V */
				this->PlayerStatusList->SetPlayerNowJumpCount(iNowJumpCount + 1);

				this->PlayerStatusList->SetPlayerJumpingFlag(true);

				/* �W�����v��SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_JUMP);

				//�󒆂ŃW�����v�����ꍇ�A�󒆃W�����v�G�t�F�N�g���o��������

				/* �n�ʂɂ��Ȃ������m�F */
				if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
				{
					/*�󒆃W�����v�G�t�F�N�g�ǉ� */
					{
						/* �󒆃W�����v�G�t�F�N�g�𐶐� */
						EffectSelfDelete* pAirJumpEffect = new EffectSelfDelete();

						/* �󒆃W�����v�G�t�F�N�g�̓ǂݍ��� */
						pAirJumpEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_airjump/FX_airjump")));

						/* �󒆃W�����v�G�t�F�N�g�̎��Ԃ�ݒ� */
						pAirJumpEffect->SetDeleteCount(30);

						/* �󒆃W�����v�G�t�F�N�g�̍��W�ݒ� */
						pAirJumpEffect->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y - this->PlayerStatusList->fGetPlayerNowFallSpeed()+PLAYER_HEIGHT , this->vecPosition.z));

						/* �󒆃W�����v�G�t�F�N�g�̉�]�ʐݒ� */
						pAirJumpEffect->SetRotation(this->vecRotation);

						/* �󒆃W�����v�G�t�F�N�g�̏����� */
						pAirJumpEffect->Initialization();

						/* �󒆃W�����v�G�t�F�N�g�����X�g�ɓo�^ */
						{
							/* �󒆃W�����v�G�t�F�N�g�����X�g�ɓo�^ */
							this->ObjectList->SetEffect(pAirJumpEffect);
						}
					}

				}

				/* ���[�V������"�W�����v(�J�n)"�ɐݒ� */
				PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_START);

			}
		}
	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */

/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
// �d�͏���
void CharacterPlayer::Player_Gravity()
{
	/* �v���C���[�̈ړ���Ԃ��擾 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();
	/* �v���C���[�̈ړ���Ԃ��擾 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();
	/* �v���C���[�̏d�͏������s�����̃t���O */
	bool bGravityFlag = true;

	/* �v���C���[���d�͏������s���ړ���Ԃł��邩�m�F */
	// ���v���k
	switch (iPlayerMoveState)
	{
		/* �d�͏������s����� */
	case PLAYER_MOVESTATUS_FREE:				// ���R���

		/* �d�͏������s�� */
		bGravityFlag = true;
		break;

		/* �d�͏������s��Ȃ���� */
	case PLAYER_MOVESTATUS_DODGING:			// �����Ԓ�

		/* �d�͏������s��Ȃ�(�d�͏������I��) */
		bGravityFlag = false;
		break;
	}

	/* �v���C���[���d�͏������s���U����Ԃł��邩�m�F */
	// ���v���k
	switch (iPlayerAttackState)
	{
		/* �d�͏������s����� */
	case PLAYER_ATTACKSTATUS_FREE:					// ���R���		
	case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// �ߐڍU���\����		
	case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// �������U���\����
		/* �d�͏������s�� */
		bGravityFlag = true;
		break;

		/* �d�͏������s��Ȃ���� */
	case PLAYER_ATTACKSTATUS_MELEE_WEEK:			// �ߐڍU����(��)
	case PLAYER_ATTACKSTATUS_MELEE_STRONG:			// �ߐڍU����(��)
	case PLAYER_ATTACKSTATUS_PROJECTILE:			// �������U����
		/* �d�͏������s��Ȃ�(�d�͏������I��) */
		bGravityFlag = false;
		break;
	}

	/* �d�͏������s�t���O�̊m�F */
	if(bGravityFlag == true)
	{
		// �d�͏������s���ꍇ
		/* �����ʎ擾 */
		float fFallSpeed = this->PlayerStatusList->fGetPlayerNowFallSpeed();		// �����_�ł̉����ʎ擾
		fFallSpeed += this->PlayerStatusList->fGetPlayerFallAcceleration();	// �����x�����Z

		/* �����̉����x���X�V */
		this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

		/* �d�͂ɂ��ړ���̍��W���擾 */
		this->vecMove.y -= this->PlayerStatusList->fGetPlayerNowFallSpeed();	
	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */


// ���
void CharacterPlayer::Player_Dodg()
{
	/* 2025.01.09 �e�r�듹	�ړ������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �J�n */
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
	/* 2025.02.06 �e�r�듹	�G�t�F�N�g�����C�� �J�n */
	/* 2025.02.10 �e�r�듹	��������C�� �J�n */

	/* �v���C���[�̈ړ���Ԃ��擾 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();

	/* �v���C���[��O��"�����Ԓ�"�ł��邩�m�F */
	if (iPlayerMoveState == PLAYER_MOVESTATUS_DODGING)
	{
		// ��𒆂ł���ꍇ
		/* �����Ԃ��ێ�����鎞�Ԃ𒴂��Ă��Ȃ����m�F */
		if (this->PlayerStatusList->iGetPlayerNowDodgeFlame() <= PLAYER_DODGE_FLAME)
		{
			// �����Ă��Ȃ�(�����Ԃ��p������)�ꍇ
			
			/* ����ɂ��ړ�������ݒ肵�A�ړ����� */
			/* �o�߃t���[�����ɉ����āA��𑬓x����������(1.0f���ő�Ƃ��Č������Ă���) */
			this->vecMove = VScale(this->PlayerStatusList->vecGetPlayerDodgeDirection(), PLAYER_DODGE_SPEED * (1.0f - (float)this->PlayerStatusList->iGetPlayerNowDodgeFlame() / (float)PLAYER_DODGE_FLAME));

			/* ����̌o�ߎ��Ԃ�i�߂� */
			this->PlayerStatusList->SetPlayerNowDodgeFlame(this->PlayerStatusList->iGetPlayerNowDodgeFlame() + 1);

		}
		else
		{
			// �����Ă���(�����Ԃ��I������)�ꍇ
			/* �����������t���O��L���ɂ��� */
			this->PlayerStatusList->SetPlayerAfterDodgeFlag(true);

			/* �v���C���[��Ԃ�"���R���"�ɐݒ� */
			this->PlayerStatusList->SetPlayerMoveState(PLAYER_MOVESTATUS_FREE);

			/* ����G�t�F�N�g���폜 */
			this->pDodgeEffect->SetDeleteFlg(true);
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
				this->PlayerStatusList->SetPlayerMoveState(PLAYER_MOVESTATUS_DODGING);

				/* �v���C���[�����n���Ă��Ȃ������m�F */
				if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
				{
					// ���n���Ă��Ȃ��ꍇ
					/* �󒆂ł̉���񐔂̃J�E���g��i�߂� */
					this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() + 1);
				}

				/* �����SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_DODGE);

				/* ����G�t�F�N�g�ǉ� */
				{
					/* ����G�t�F�N�g�𐶐� */
					this->pDodgeEffect = new EffectManualDelete_PlayerFollow(true);

					/* ����G�t�F�N�g�̓ǂݍ��� */
					this->pDodgeEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_dash/FX_dash")));

					/* �G�t�F�N�g�̉�]�ʐݒ� */
					this->pDodgeEffect->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

					/* ����G�t�F�N�g�̏����� */
					this->pDodgeEffect->Initialization();

					/* ����G�t�F�N�g�����X�g�ɓo�^ */
					{
						/* ����G�t�F�N�g�����X�g�ɓo�^ */
						this->ObjectList->SetEffect(this->pDodgeEffect);
					}
				}
			}
		}
	}

	/* 2025.01.09 �e�r�듹	�ړ������ǉ� �I�� */
	/* 2025.01.26 ��򕗏�	�R�[�h�C�� �I�� */
	/* 2025.01.27 �e�r�듹�@�G�t�F�N�g�����ǉ� �I�� */
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */
	/* 2025.02.06 �e�r�듹	�G�t�F�N�g�����C�� �I�� */
	/* 2025.02.10 �e�r�듹	��������C�� �I�� */
}

// �ړ�����(��������)
void CharacterPlayer::Movement_Vertical()
{
	/* �ړ���̍��W���擾(��������) */
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z = this->vecPosition.z;

	/* ��l���̏㕔���̓����蔻�肩�牺�����֌������������쐬 */
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 9999;

	/* �ȉ��A������(�߂��I�u�W�F�N�g�̂ݑΏۂɂ���悤�ɂ���) */
	/* ������擾 */
	auto& PlatformList = ObjectList->GetCollisionList();

	/* ���n������W */
	// �������l���ړ���̍��W�ɐݒ�
	float	fStandPosY = vecNextPosition.y;

	/* ���݂̃W�����v�t���O��ێ� */
	bool bjumppingFlg = this->PlayerStatusList->bGetPlayerJumpingFlag();

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

					/* �v���C���[�̒��n�t���O��L���ɂ��� */
					this->PlayerStatusList->SetPlayerLanding(true);

					/* 2025.01.09 �e�r�듹�@�ړ������ǉ� �ǉ� */

					//�W�����v���̃t���O�����Z�b�g
					this->PlayerStatusList->SetPlayerJumpingFlag(false);

					//�W�����v���̉���񐔂����Z�b�g
					this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(0);
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
	if (bjumppingFlg == true && this->PlayerStatusList->bGetPlayerJumpingFlag() == false)
	{
		/* �v���C���[�̏�Ԃ��擾 */
		int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();

		/* ��𒆂ɃG�t�F�N�g���o�Ȃ��悤�ɂ��� */
		if (iPlayerMoveState != PLAYER_MOVESTATUS_DODGING)
		{
			/* �G�t�F�N�g�ǉ� */
			{
				/* ���n�̃G�t�F�N�g�𐶐� */
				EffectSelfDelete* pAddEffect = new EffectSelfDelete;

				/* ���n�G�t�F�N�g�̓ǂݍ��� */
				pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_land/FX_land")));

				/* ���n�G�t�F�N�g�̎��Ԃ�ݒ� */
				pAddEffect->SetDeleteCount(30);

				/* ���n�G�t�F�N�g�̍��W�ݒ� */
				pAddEffect->SetPosition(this->vecPosition);

				/* ���n�G�t�F�N�g�̉�]�ʐݒ� */
				pAddEffect->SetRotation(this->vecRotation);

				/* ���n�G�t�F�N�g�̏����� */
				pAddEffect->Initialization();

				/* ���n�G�t�F�N�g�����X�g�ɓo�^ */
				{
					/* ���n�G�t�F�N�g�����X�g�ɓo�^ */
					this->ObjectList->SetEffect(pAddEffect);
				}
			}

			/* ���n���[�V�����ݒ� */
			this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_LAND);
		}
	}
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ�	�I��*/

	/* ���n���W���X�V */
	vecNextPosition.y = fStandPosY;

	/* �v���C���[���W���X�V */
	this->vecPosition = vecNextPosition;

	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
	/* ���݂̃v���C���[��Ԃ��擾 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* ���[�V�������X�V */
	{
		/* ���n�t���O�������ł���(�󒆂ɂ���)���m�F */
		if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
		{
			// �����ł���(�󒆂ɂ���)�ꍇ
			/* �㏸���Ă��邩�m�F */
			if (this->PlayerStatusList->fGetPlayerNowFallSpeed() < 0)
			{
				// �㏸���Ă���ꍇ
				/* ���[�V������"�W�����v(�J�n)"�łȂ����Ƃ��m�F */
				if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
				{
					/* ���[�V������"�W�����v(�㏸)"�ɐݒ� */
					PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_UP);
				}
			}
			else
			{
				// ���~���Ă���ꍇ
				/* ���[�V������"�W�����v(���~)"�ɐݒ� */
				PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_DOWN);
			}
		}
	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */

/* 2025.02.07 �e�r�듹	�Փ˔��菈���C���@�J�n */
// �ړ�����(��������)
void CharacterPlayer::Movement_Horizontal()
{
	/* �ړ���̍��W���擾(��������) */
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x + this->vecMove.x;
	vecNextPosition.y = this->vecPosition.y;
	vecNextPosition.z = this->vecPosition.z + this->vecMove.z;

	/* 1�t���[���ł̈ړ��ʂ𕪊����Ĕ��肷��� */
	/* ���ړ��ʂɉ����ĕ�����ݒ肷�� */
	int iMoveHitCheckCount = (int)VSize(VGet(this->vecMove.x,0,this->vecMove.z));
	
	/* ���������ړ��� */
	VECTOR vecDevisionMove = VScale(this->vecMove, 1.0f / iMoveHitCheckCount);

	/* �������Ĉړ�������̍��W */
	VECTOR vecDevisionMovePosition = this->vecPosition;

	/* �����ŃI�u�W�F�N�g�ɐڐG���Ă��邩���� */
	{
		/* ���݈ʒu����ړ�����W�֌������J�v�Z���R���W�������쐬 */
		// �� ���̈ʒu����ړ���̈ʒu�֌������J�v�Z���R���W�������쐬
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleTop = VAdd(vecNextPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].fCapsuleRadius = PLAYER_WIDE;
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleTop = VAdd(vecNextPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].fCapsuleRadius = PLAYER_WIDE;

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

					/* �ړ��ʂ𕪊����ďՓ˔��肷�� */
					for (int i = 0; i < iMoveHitCheckCount; i++)
					{
						/* �ړ�����W�ɋ��̃|���S�����쐬 */
						vecDevisionMovePosition = VAdd(vecDevisionMovePosition, vecDevisionMove);

						/* �@���x�N�g���̍쐬 */
						VECTOR vecNormalSum = VGet(0.f, 0.f, 0.f);

						/* �|���S���ƐڐG�������W */
						VECTOR vecHitPos = VGet(0.f, 0.f, 0.f);

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
						stSphere.vecSqhere = vecDevisionMovePosition;
						stSphere.fSqhereRadius = PLAYER_WIDE;

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

						// ���̃R���W�����ƏՓ˂��������ꍇ�A�����ړ��������I������
						if (stHitPolyDim.HitNum > 0)
						{
							break;
						}
					}
				}
			}
		}
	}

	/* �v���C���[�̍��W���ړ������� */
	this->vecPosition = vecNextPosition;
}
/* 2025.02.07 �e�r�듹	�Փ˔��菈���C���@�I�� */