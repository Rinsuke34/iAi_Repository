/* 2025.02.04 �e�r�듹	�t�@�C���쐬 */
/* 2025.01.09 �e�r�듹	�ړ������ǉ� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� */

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
	float	fMoveSpeedRatio = 1.f;			// �ړ����x(�{��)
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

	/* 2025.01.09 �e�r�듹	�ړ������ǉ�		�J�n	*/
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �J�n	*/
	/* 2025.01.30 �e�r�듹	���[�V���������ǉ� �J�n */
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

				/* ���[�V�����ݒ� */
				this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_RUN_HIGH);
			}

			// �X�e�B�b�N�̓|����ő��x��ω�
			else if (fStickTiltMagnitude > STICK_TILT_PLAER_DASH)
			{
				//����i�ʏ�j
				fSpeed = PLAER_DASH_NOMAL_SPEED * fMoveSpeedRatio;
				//�t���[�������J�E���g
				this->PlayerStatusList->SetPlayerNormalDashFlameCount(PlayerStatusList->iGetPlayerNormalDashFlameCount() + 1);

				//���t���[�����������瑖��i�ő�j��
				this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_RUN_LOW);

				//���t���[���ɒB�������A�_�b�V���G�t�F�N�g���o��������
				if (this->PlayerStatusList->iGetPlayerNormalDashFlameCount() == FLAME_COUNT_TO_MAX_SPEED)
				{
					/* �G�t�F�N�g�ǉ� */
					{
						/* �_�b�V���G�t�F�N�g�𐶐� */
						EffectSelfDelete* pAddEffect = new EffectSelfDelete;

						/* �_�b�V���G�t�F�N�g�ǂݍ��� */
						pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_dash/FX_dash")));

						/* �_�b�V���G�t�F�N�g�̎��Ԑݒ� */
						pAddEffect->SetDeleteCount(30);

						/* �G�t�F�N�g�̐��������̐ݒ� */
						// ���v���C���[�̑O�ɏo��
						VECTOR vecInput = VGet(0.f, 0.f, 1.f);

						/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
						float fAngleX = this->PlayerStatusList->fGetPlayerAngleX();

						/* �G�t�F�N�g�̍��W���Z�o */
						VECTOR vecAdd;

						// ����
						vecAdd.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
						vecAdd.y = 0.f;
						vecAdd.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
						vecAdd = VNorm(vecAdd);

						// ������̑��x������
						vecAdd = VScale(vecAdd, PLAYER_DODGE_SPEED);

						// ����
						vecAdd.y = PLAYER_HEIGHT / 2.f;

						/* �_�b�V���G�t�F�N�g�̍��W�ݒ� */
						pAddEffect->SetPosition(VAdd(this->vecPosition, vecAdd));

						/* �_�b�V���G�t�F�N�g�̉�]�ʐݒ� */
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
					this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_RUN_HIGH);
				}
			}
			else
			{
				//����
				this->PlayerStatusList->SetPlayerNowMoveSpeed(PLAYER_WALK_MOVE_SPEED);
				this->PlayerStatusList->SetPlayerNormalDashFlameCount(0);
				fSpeed = PLAYER_WALK_MOVE_SPEED * fMoveSpeedRatio;

				/* ���s���[�V�����ݒ� */
				this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_WALK);
			}

			/* 2025.01.09 �e�r�듹	�ړ������ǉ�		�I��	*/
			/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �I��	*/

			/* ���ݑ��x���X�V */
			this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

			/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
			float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

			/* �ړ��ʂ��Z�o */
			vecAddMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
			vecAddMove.y = 0.0f;
			vecAddMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
			vecAddMove = VScale(vecAddMove, fSpeed);

			/* �v���C���[�̌������ړ������ɍ��킹�邩�m�F */
			if (bPlayerAngleSetFlg == true)
			{
				// ���킹��ꍇ
				/* �v���C���[�̌������ړ������ɍ��킹�� */
				float fPlayerAngle = atan2f(vecInput.x, vecInput.z);	// �ړ������̊p�x(���W�A��)���擾
				fPlayerAngle = fAngleX - fPlayerAngle;			// �J�����̌����ƍ���
				this->PlayerStatusList->SetPlayerAngleX(fPlayerAngle);	// �v���C���[�̌�����ݒ�
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
		if (this->PlayerStatusList->iGetPlayerMotion() == PLAYER_MOTION_DRAW_SWORD_END)
		{
		}
		else
		{
			/* �ҋ@���[�V�����ݒ� */
			this->PlayerStatusList->SetPlayerMotion(PLAYER_MOTION_IDLE);
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
		bGravityFlag = true;
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

	// ������bGravityFlag�ŏd�͏����͕����Ă��Ȃ��i�v���k�j

	/* �����ʎ擾 */
	float fFallSpeed = this->PlayerStatusList->fGetPlayerNowFallSpeed();		// �����_�ł̉����ʎ擾
	fFallSpeed += this->PlayerStatusList->fGetPlayerFallAcceleration();	// �����x�����Z

	/* �����̉����x���X�V */
	this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

	/* �d�͂ɂ��ړ���̍��W���擾 */
	this->vecMove.y -= this->PlayerStatusList->fGetPlayerNowFallSpeed();
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */


// ���
void CharacterPlayer::Player_Dodg()
{
	/* 2025.01.09 �e�r�듹�@	�ړ������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n */
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */

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
			this->PlayerStatusList->SetPlayerMoveState(PLAYER_MOVESTATUS_FREE);

			/* ����G�t�F�N�g���폜 */
			this->pDodgeEffect->SetDeleteFlg(true);
			/* ����G�t�F�N�g�̃|�C���^���폜 */
			this->pDodgeEffect = nullptr;
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
					this->pDodgeEffect = new EffectManualDelete;

					/* ����G�t�F�N�g�̓ǂݍ��� */
					this->pDodgeEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_dash/FX_dash")));

					/* �G�t�F�N�g�̍��W�ݒ� */
					this->pDodgeEffect->SetPosition(this->vecPosition);

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

	/* 2025.01.09 �e�r�듹	�ړ������ǉ�		�I�� */
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */

	/* ����G�t�F�N�g�����݂��Ă���ꍇ */
	if (pDodgeEffect != nullptr)
	{
		/* �G�t�F�N�g�̐��������̐ݒ� */
		// ���v���C���[�̑O�ɏo��
		VECTOR vecInput = VGet(0.f, 0.f, 1.f);

		/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
		float fAngleX = this->PlayerStatusList->fGetPlayerAngleX();

		/* �G�t�F�N�g�̍��W���Z�o */
		VECTOR vecAdd;
		
		// ����
		vecAdd.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecAdd.y = 0.f;
		vecAdd.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
		vecAdd = VNorm(vecAdd);
		
		// ������̑��x������
		vecAdd = VScale(vecAdd, PLAYER_DODGE_SPEED);
		
		// ����
		vecAdd.y = PLAYER_HEIGHT / 2.f;

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->pDodgeEffect->SetPosition(VAdd(this->vecPosition, vecAdd));

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pDodgeEffect->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));
	}

	/* 2025.01.09 �e�r�듹	�ړ������ǉ�		�I�� */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�I��*/
	/* 2025.01.29 �e�r�듹�@	�G�t�F�N�g�����ǉ�	�J�n */
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
		/* �󒆂ɂ���(���n���Ă��Ȃ�)���m�F */
		if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true)
		{	
			/* �U�����\���Ă��Ȃ���Ԃł��邩�m�F */
			// ���\���Ă���Œ��͗������[�V�����ɑJ�ڂ����Ȃ�
			/* �ߐڍU���\�����łȂ����m�F */
			if (iPlayerAttackState != PLAYER_ATTACKSTATUS_MELEE_POSTURE)
			{
				/* �������U���\�����łȂ����m�F */
				if (iPlayerAttackState != PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
				{
					/* ���U��(�ߐ�)���łȂ����m�F */
					if (iPlayerAttackState != PLAYER_ATTACKSTATUS_MELEE_STRONG)
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
	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */

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
					stSphere.vecSqhere = vecNextPosition;
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