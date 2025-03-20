/* 2025.02.04 �e�r�듹	�t�@�C���쐬 */
/* 2025.01.09 �e�r�듹	�ړ������ǉ� */
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� */
/* 2025.02.06 �e�r�듹	�G�t�F�N�g�����C�� */
/* 2025.02.07 �e�r�듹	�Փ˔��菈���C�� */
/* 2025.02.10 �e�r�듹	�U����������C�� */
/* 2025.02.10 �e�r�듹	��������C�� */
/* 2025.02.14 �e�r�듹	�U����������C�� */
/* 2025.02.22 �e�r�듹	�ǃL�b�N�����ǉ� */
/* 2025.02.26 �e�r�듹	�N�[���^�C���̏����ǉ� */
/* 2025.02.26 �e�r�듹	�ߋ����U��(��)�֘A�̏����ǉ� */
/* 2025.03.04 �e�r�듹	����̏����C�� */
/* 2025.03.05 �e�r�듹	�Փ˔��菈���C�� */
/* 2025.03.10 ��򕗏�	�ړ������� */
/* 2025.03.08 �e�r�듹	�ړ������C�� */
/* 2025.03.11 �e�r�듹	���[�V�����֘A�̏����ǉ� */
/* 2025.03.11 �e�r�듹	����̏����C�� */
/* 2025.03.12 �e�r�듹	�X���[���[�V���������ǉ� */
/* 2025.03.18 �e�r�듹	�G�f�B�b�g�ɂ�鏈���ǉ� */

#include "CharacterPlayer.h"

// �ړ�
void CharacterPlayer::Player_Move()
{
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
	/* 2025.03.12 �e�r�듹	�X���[���[�V���������ǉ� �J�n */
	/* 2025.03.18 �e�r�듹	�G�f�B�b�g�ɂ�鏈���ǉ� �J�n */

	/* �v���C���[�ړ��ʎ擾 */
	float fStickTiltMagnitude	= this->InputList->fGetGameInputMove();				// �X�e�B�b�N��|��������
	VECTOR vecInput				= this->InputList->vecGetGameInputMoveDirection();	// �ړ�����
	VECTOR vecAddMove			= VGet(0, 0, 0);									// �ړ���(���Z�p)

	/* �v���C���[�̏�Ԃ��擾 */
	int iPlayerMoveState	= this->PlayerStatusList->iGetPlayerMoveState();
	int iPlayerAttackState	= this->PlayerStatusList->iGetPlayerAttackState();

	/* �v���C���[�̏�Ԃɉ����Ĉړ����x�̔{������ݒ� */
	float	fMoveSpeedRatio		= 1.f;		// �ړ����x(�{��)
	float	fEditAddSpeed		= this->PlayerStatusList->fGetAddMoveSpeedUp();		// �G�f�B�b�g�ɂ��ړ����x���Z�l
	bool	bPlayerAngleSetFlg	= true;		// �v���C���[�̌������ړ������ɍ��킹�邩�̃t���O
	bool	bPlayerMoveFlg		= true;		// �v���C���[�̈ړ����s�����̃t���O	
	
	/* �v���C���[�̈ړ���Ԃ��ړ��������s����Ԃł��邩�m�F */
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
		case PLAYER_MOVESTATUS_EVENT:				// �C�x���g���(����s��)
		case PLAYER_MOVESTATUS_DODGING:				// �����Ԓ�
		case PLYAER_MOVESTATUS_DEAD:				// ���S���(����s��)
	
			// �ړ��������s��Ȃ�
			bPlayerMoveFlg = false;
		
			break;
	}

	/* �v���C���[�̈ړ���Ԃ��ړ��������s���ꍇ�ł��邩�m�F */
	if (bPlayerMoveFlg == true)
	{
		// �ړ��������s���ꍇ
		/* �v���C���[�̍U����Ԃ��ړ��������s����Ԃł��邩�m�F */
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

				/* �ړ����x�␳0.5�{�ɂ��� */
				// �����̒l
				fMoveSpeedRatio = 0.5f;

				/* �v���C���[�̌������ړ������ɍ��킹�Ȃ� */
				bPlayerAngleSetFlg = false;
				break;

		case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// �������U���\����
			
			/* �X���[���[�V�������ł��邩�m�F */
			if (this->StageStatusList->bGetGameSlowFlg() == true)
			{
				// �X���[���[�V�������ł���ꍇ
				/* �ړ����x�␳0.1�{�ɂ��� */
				fMoveSpeedRatio = 0.1f;
			}
			else
			{
				// �X���[���[�V�������łȂ��ꍇ
				/* �ړ����x�␳0.5�{�ɂ��� */
				fMoveSpeedRatio = 0.5f;
			}
				

			/* �v���C���[�̌������ړ������ɍ��킹�Ȃ� */
			bPlayerAngleSetFlg = false;
			break;

			/* �ړ��������s��Ȃ���� */
			case PLAYER_ATTACKSTATUS_MELEE_WEEK:		// �ߐڍU����(��)
			case PLAYER_ATTACKSTATUS_MELEE_STRONG:		// �ߐڍU����(��)
			case PLAYER_ATTACKSTATUS_PROJECTILE:		// �������U����
				break;
		}
	}
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */
	/* 2025.03.12 �e�r�듹	�X���[���[�V���������ǉ� �I�� */

	/* 2025.01.09 �e�r�듹	�ړ������ǉ�		�J�n */
	/* 2025.01.30 �e�r�듹	���[�V���������ǉ�	�J�n */
	/* 2025.03.08 �e�r�듹	�ړ������C��		�J�n */

	/* �ړ��������s�����Ԃ��A���͂�����Ă��邩�m�F */
	if ((vecInput.x != 0 || vecInput.z != 0) && (bPlayerMoveFlg == true))
	{
		// �ړ����͂�����Ă���ꍇ
		/* ���݂̈ړ����x�擾 */
		float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();

		/* �ړ����x�̐ݒ�l���擾 */
		float fBaseSpeed = this->PlayerStatusList->fGetPlayerMoveAcceleration();

		/* �ŏI�I�Ȉړ����x���v�Z */
		fSpeed = (fBaseSpeed + fEditAddSpeed) * fMoveSpeedRatio;

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

		/* 2025.01.09 �e�r�듹	�ړ������ǉ� �I�� */
		/* 2025.03.08 �e�r�듹	�ړ������C�� �I�� */
	/* 2025.03.18 �e�r�듹	�G�f�B�b�g�ɂ�鏈���ǉ� �I�� */

		/* ���ݑ��x���X�V */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

		/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
		float fAngleX = this->StageStatusList->fGetCameraAngleX();

		/* �ړ��ʂ��Z�o */
		vecAddMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecAddMove.y = 0.0f;
		vecAddMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
		vecAddMove = VScale(vecAddMove, fSpeed);

		/* 2025.02.10 �e�r�듹	�U����������C�� �J�n*/
		/* 2025.03.14 �e�r�듹	�U����������C�� �J�n */
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
			this->StageStatusList->SetCameraAngleX(fAngleX);

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
			/* 2025.03.14 �e�r�듹	�U����������C�� �I�� */
		}
	}
	else
	{
		// �ړ����͂�����Ă��Ȃ��ꍇ
		/* �ړ����x��0�ɂ��� */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(0);

		// �ߋ����U��(��)(�I��)���[�V�������ȊO�Ȃ�ҋ@���[�V�����ɑJ�� ���o�O�΍�̂��߁A�ȉ��悤�ȏ������ɂȂ��Ă܂�
		if(this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
		{

		}
		else
		{
			/* ���݂̃��[�V������"���n"�A���邢��"���S"�łȂ����m�F */
			int iMotionMove = this->PlayerStatusList->iGetPlayerMotion_Move();
			if ((iMotionMove != MOTION_ID_MOVE_LAND) && (iMotionMove != MOTION_ID_MOVE_DIE))
			{
				// "���n","���S"�ȊO�ł���ꍇ
				/* ���[�V������"�W�����v(�J�n)"�łȂ����m�F */
				if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
				{
					// �W�����v(�J�n)�ȊO�ł���ꍇ
					/* ���݂̃��[�V������"���n"�łȂ����m�F */
					if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_LAND)
					{
						// "���n"�łȂ��ꍇ		
						/* ���݂̃��[�V������"���"�łȂ����m�F */
						if (this->PlayerStatusList->iGetPlayerMoveState() != PLAYER_MOVESTATUS_DODGING)
						{
							/* �ҋ@���[�V�����ݒ� */
							this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_WAIT);
						
						}		
					}
				}
			}
		}
	}
	/* 2025.02.22 �e�r�듹	�ǃL�b�N�����ǉ� �J�n*/
	// �ǃL�b�N�̉��ړ�����
	/* �ǃL�b�N�t���O���L�����m�F */
	if (this->PlayerStatusList->bGetPlayerKickWallFlg() == true)
	{
		// �ǃL�b�N�t���O���L���ȏꍇ
		/* �ǃL�b�N���Ă���̌o�߃t���[�������擾 */
		int iNowAfterKickWallFlame = this->PlayerStatusList->iGetPlayerAfterKickWallCount();

		/* �ǃL�b�N�̉��ړ����x���擾 */
		float fKickWallHorizontalSpeed = this->PlayerStatusList->fGetPlayerKickWallHorizontalSpeed();	

		/* �ǃL�b�N�p���t���[�������擾 */
		int iKickWallFlame = this->PlayerStatusList->iGetPlayerKickWallFlame();
		
		/* �o�߃t���[�������m�F */
		if (iNowAfterKickWallFlame <= iKickWallFlame)
		{
			// �o�߃t���[�������ݒ�t���[�����𒴂��Ă��Ȃ��ꍇ
			/* �ǃL�b�N�̉��ړ����x��ݒ� */
			/* �o�߃t���[�����ɉ����āA���x����������(1.0f���ő�Ƃ��Č������Ă���) */
			float fKickWallSpeed = fKickWallHorizontalSpeed * (1.0f - (float)(iNowAfterKickWallFlame / iKickWallFlame));
			
			/* �ǂ̖@������(���������̂�)�ֈړ����� */
			this->vecMove.x += vecNormalSum.x * fKickWallSpeed;
			this->vecMove.z += vecNormalSum.z * fKickWallSpeed;

		}
		else
		{
			// �o�߃t���[�������ݒ�t���[�����𒴂����ꍇ

			/* �o�߃t���[���������Z�b�g */
			this->PlayerStatusList->SetPlayerAfterKickWallCount(0);

			/* �ǃL�b�N�t���O�𖳌��ɂ��� */
			this->PlayerStatusList->SetPlayerKickWallFlg(false);
		}
	}
	/* 2025.02.22 �e�r�듹	�ǃL�b�N�����ǉ� �I�� */

	/* �ړ��ʂ����Z */
	this->vecMove = VAdd(this->vecMove, vecAddMove);

	/* �f�o�b�O�`�ʗp�̈ړ��ʂ�ݒ� */
	this->vecMoveSize = vecAddMove;
}

/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
/* 2025.02.22 �e�r�듹	�ǃL�b�N�����ǉ�	�J�n*/
/* 2025.03.18 �e�r�듹	�G�f�B�b�g�ɂ�鏈���ǉ�	�J�n */
// �W�����v
void CharacterPlayer::Player_Jump()
{
	/* �v���C���[�̏�Ԃ��擾 */
	int iPlayerMoveState	= this->PlayerStatusList->iGetPlayerMoveState();
	int iPlayerAttackState	= this->PlayerStatusList->iGetPlayerAttackState();

	/* �G�f�B�b�g�ɂ��W�����v�񐔉��Z�����擾 */
	int iEditAddJumpCount	= this->PlayerStatusList->iGetAddJumpCount();
	
	/* �W�����v�������s�����̃t���O */
	bool bJumpFlag = true;

	/* �v���C���[�̈ړ���Ԃ��W�����v�\�ł��邩�m�F */
	switch (iPlayerMoveState)
	{
		/* �W�����v�\�ȏ�� */
		case PLAYER_MOVESTATUS_FREE:				// ���R���
		
			/* �W�����v�������s�� */
			bJumpFlag = true;
	
			break;

		/* �W�����v�s�\�ȏ�� */
		case PLAYER_MOVESTATUS_EVENT:				// �C�x���g���(����s��)
		case PLAYER_MOVESTATUS_DODGING:				// �����Ԓ�
		case PLYAER_MOVESTATUS_DEAD:				// ���S���(����s��)
		
			/* �W�����v�������s�� */
			bJumpFlag = false;
		
			break;
	}

	/* �v���C���[�̈ړ���Ԃ��W�����v�\�ł��������m�F */	
	if (bJumpFlag == true)
	{
		// �W�����v�\�ł���ꍇ
		/* �v���C���[�̍U����Ԃ��W�����v�\�ł��邩�m�F */
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
			case PLAYER_ATTACKSTATUS_DEAD:				// ���S���(����s��)
				/* �W�����v�������s��Ȃ� */
				bJumpFlag = false;
				break;
		}
	}
	// �ǃL�b�N�̏��������(�ǃL�b�N�\���̓W�����v���ǃL�b�N��D�悷�邽�߁A�W�����v������ɏ�������)
	/* �ǃL�b�N�t���O���L�����m�F */
	if (this->PlayerStatusList->bGetPlayerKickWallFlg() == true)
	{
		/* �ǃL�b�N��̌o�߃t���[������0�̏ꍇ */
		if (this->PlayerStatusList->iGetPlayerAfterKickWallCount() == 0)
		{
			/* �ǃL�b�N�̈ړ����x(��������)���擾 */
			float fKickWallVerticalSpeed = this->PlayerStatusList->fGetPlayerKickWallVerticalSpeed();

			/*������Ɉړ� */
			this->PlayerStatusList->SetPlayerNowFallSpeed(-fKickWallVerticalSpeed);
			
			/* SE���Đ� */
			gpDataList_Sound->SE_PlaySound(SE_PLAYER_JUMP);
			
			/* ���[�V������"�W�����v(�J�n)"�ɐݒ� */
			PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_START);

			/* �ǃL�b�N��̃t���O��L���ɂ��� */
			this->PlayerStatusList->SetPlayerAfterKickWallFlg(true);
		}

		/* �ǃL�b�N��̌o�߃t���[������i�߂� */
		this->PlayerStatusList->SetPlayerAfterKickWallCount(this->PlayerStatusList->iGetPlayerAfterKickWallCount() + 1);

	}
	// �W�����v����
	/* �W�����v�������s����Ԃ��m�F */
	if (bJumpFlag == true)
	{
		// �W�����v�������s���ꍇ
		/* �W�����v�̃N�[���^�C�����c���Ă��邩�m�F */
		if (this->iJumpCoolTime > 0)
		{
			// �N�[���^�C�����c���Ă���ꍇ
			/* �W�����v���s��Ȃ� */
			return;
		}
		/* ���݂̃W�����v�񐔂��擾 */
		int iNowJumpCount = this->PlayerStatusList->iGetPlayerNowJumpCount();
		
		/* �ő�W�����v�񐔂��擾 */
		int iMaxJumpCount = this->PlayerStatusList->iGetPlayerMaxJumpCount() + iEditAddJumpCount;

		/* �W�����v�񐔂��ő吔�𒴂��Ă��Ȃ����m�F */
		if (iNowJumpCount < iMaxJumpCount)
		{
			// �W�����v�񐔂��ő吔�𒴂��Ă��Ȃ��ꍇ
			/* �W�����v���͂�����Ă��邩�m�F */
			if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
			{
				// �W�����v���͂�����Ă���ꍇ
				// �ǃL�b�N���s�����ォ���m�F(�ǃL�b�N�ƃW�����v�̏d���h�~�̂���)
				if (this->PlayerStatusList->bGetPlayerAfterKickWallFlg() == false)
				{ 
					// �ǃL�b�N��̃t���O���L���ł͂Ȃ��ꍇ
					/* �W�����v���� */
					/* �W�����v���x���擾 */
					float fJumpSpeed = this->PlayerStatusList->fGetPlayerJumpSpeed();
					
					/* �W�����v���x��ݒ�(�}�C�i�X�̒l��ݒ肷��) */
					this->PlayerStatusList->SetPlayerNowFallSpeed(-fJumpSpeed);

					/* �W�����v�񐔂��X�V */
					this->PlayerStatusList->SetPlayerNowJumpCount(iNowJumpCount + 1);

					/* �W�����v�t���O��L���ɂ��� */
					this->PlayerStatusList->SetPlayerJumpingFlag(true);

					/* �W�����v��SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_JUMP);

					/* �W�����v�̃{�C�X���Đ� */
					gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_ACTION);
					
					//�󒆂ŃW�����v�����ꍇ�A�󒆃W�����v�G�t�F�N�g���o��������

					/* �n�ʂɂ��Ȃ������m�F */
					if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
					{
						/*�󒆃W�����v�G�t�F�N�g�ǉ� */
						{
							/* �󒆃W�����v�G�t�F�N�g�𐶐� */
							EffectSelfDelete* pAirJumpEffect = new EffectSelfDelete();

							/* �󒆃W�����v�G�t�F�N�g�̓ǂݍ��� */
							pAirJumpEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_airjump/FX_airjump"));

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

					/* �v���C���[�̃��[�V������"�ߋ����U��(��)(�I��)"�ł��邩�m�F */
					if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
					{
						// �ߋ����U��(��)(�I��)���[�V�������̏ꍇ
						/* �v���C���[�̃��[�V������"����"�ɕύX */
						this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
					}

					/* ���[�V������"�W�����v(�J�n)"�ɐݒ� */
					PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_START);

					/* �W�����v�̃N�[���^�C����ݒ� */
					this->iJumpCoolTime = PLAYER_JUMP_COOLTIME;
				}
				else
				{ 
					// �ǃL�b�N��̃t���O���L���ȏꍇ
					// �W�����v���͂�����Ă���ꍇ
					if (this->InputList->bGetGameInputAction(INPUT_REL, GAME_JUMP) == false)
					{
						/* �ǃL�b�N��̃t���O������ */
						this->PlayerStatusList->SetPlayerAfterKickWallFlg(false);
					}
				}		
			}
		}
	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */
/* 2025.02.22 �e�r�듹	�ǃL�b�N�����ǉ�	�I��*/
/* 2025.03.18 �e�r�듹	�G�f�B�b�g�ɂ�鏈���ǉ�	�I�� */

/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
/* 2025.03.12 �e�r�듹	�X���[���[�V���������ǉ� �J�n */
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
	switch (iPlayerMoveState)
	{
		/* �d�͏������s����� */
		case PLAYER_MOVESTATUS_FREE:			// ���R���
		case PLYAER_MOVESTATUS_DEAD:			// ���S���(����s��)

			/* �d�͏������s�� */
			bGravityFlag = true;
			break;

		/* �d�͏������s��Ȃ���� */
		case PLAYER_MOVESTATUS_EVENT:			// �C�x���g���(����s��)
		case PLAYER_MOVESTATUS_DODGING:			// �����Ԓ�

			/* �d�͏������s��Ȃ�(�d�͏������I��) */
			bGravityFlag = false;
			break;
	}

	/* �v���C���[�̈ړ���Ԃ��d�͏������s����Ԃł��������m�F */
	if (bGravityFlag == true)
	{
		// �d�͏������s���ꍇ
		/* �v���C���[���d�͏������s���U����Ԃł��邩�m�F */
		switch (iPlayerAttackState)
		{
			/* �d�͏������s����� */
			case PLAYER_ATTACKSTATUS_FREE:					// ���R���
			case PLAYER_ATTACKSTATUS_MELEE_WEEK:			// �ߐڍU����(��)
			case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// �ߐڍU���\����
			case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// �������U���\����
			case PLAYER_ATTACKSTATUS_DEAD:					// ���S���(����s��)
				/* �d�͏������s�� */
				bGravityFlag = true;
				break;

			/* �d�͏������s��Ȃ���� */
			case PLAYER_ATTACKSTATUS_MELEE_STRONG:			// �ߐڍU����(��)
			case PLAYER_ATTACKSTATUS_PROJECTILE:			// �������U����
				/* �d�͏������s��Ȃ�(�d�͏������I��) */
				bGravityFlag = false;
				break;
		}
	}

	/* �d�͏������s�t���O�̊m�F */
	if(bGravityFlag == true)
	{
		// �d�͏������s���ꍇ
		/* �����ʎ擾 */
		float fFallSpeed = this->PlayerStatusList->fGetPlayerNowFallSpeed();		// �����_�ł̉����ʎ擾
		fFallSpeed += this->PlayerStatusList->fGetPlayerFallAcceleration();			// �����x�����Z

		/* �ő嗎�����x���擾 */
		float fFallSpeedMax = this->PlayerStatusList->fGetPlayerMaxFallSpeed();		// �ő嗎�����x�擾

		/* ���݂̗������x���ő嗎�����x�𒴂��Ă��邩(������Ă��邩)�m�F */
		if (fFallSpeedMax < fFallSpeed)
		{
			// �����Ă���ꍇ
			/* �ő嗎�����x�ɐݒ� */
			fFallSpeed = fFallSpeedMax;	
		}

		/* �X���[���[�V���������m�F */
		if (this->StageStatusList->bGetGameSlowFlg() == true)
		{
			// �X���[���[�V�������̏ꍇ
			/* �����x�����Ȃ����� */
			fFallSpeed = fFallSpeed * 0.5f;
		}

		/* �����̉����x���X�V */
		this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

		/* �d�͂ɂ��ړ���̍��W���擾 */
		this->vecMove.y -= this->PlayerStatusList->fGetPlayerNowFallSpeed();	
	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */
/* 2025.03.12 �e�r�듹	�X���[���[�V���������ǉ� �J�n */


// ���
void CharacterPlayer::Player_Dodg()
{
	/* 2025.01.09 �e�r�듹	�ړ������ǉ�		�J�n */
	/* 2025.01.26 ��򕗏�	�R�[�h�C��		�J�n*/
	/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �J�n */
	/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �J�n */
	/* 2025.02.06 �e�r�듹	�G�t�F�N�g�����C�� �J�n */
	/* 2025.02.10 �e�r�듹	��������C�� �J�n */
	/* 2025.02.26 �e�r�듹	�N�[���^�C�������ǉ� �J�n */
	/* 2025.03.04 �e�r�듹	����̏����C�� �J�n */
	/* 2025.03.11 �e�r�듹	����̏����C�� �J�n */
	/* 2025.03.17 ��򕗏�	��ʃG�t�F�N�g�ǉ� �J�n */

	/* �v���C���[�̈ړ���Ԃ��擾 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();
	/* �v���C���[�̍U����Ԃ��擾 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* �v���C���[�̉���������s�����̃t���O */
	bool bDodgeFlag = true;

	/* �v���C���[������������s���ړ���Ԃł��邩�m�F */
	// ���U����Ԃ͍l�����Ȃ�
	switch (iPlayerMoveState)
	{
		/* ����������s����� */
		case PLAYER_MOVESTATUS_DODGING:			// �����Ԓ�
		case PLAYER_MOVESTATUS_FREE:			// ���R���
			/* ����������s�� */
			bDodgeFlag = true;
			break;

		/* ����������s��Ȃ���� */
		case PLAYER_MOVESTATUS_EVENT:			// �C�x���g���(����s��)
		case PLYAER_MOVESTATUS_DEAD:			// ���S���(����s��)

			/* ����������s��Ȃ�(����������I��) */
			bDodgeFlag = false;
			break;
	}

	/* ����������s�����m�F */
	if (bDodgeFlag == true)
	{
		// ����������s���ꍇ
		/* �v���C���[��O��"�����Ԓ�"�ł��邩�m�F */
		if (iPlayerMoveState == PLAYER_MOVESTATUS_DODGING)
		{
			// ��𒆂ł���ꍇ
			/* �����Ԃ̍ő�t���[�������擾 */
			int iDodgeMaxFrame = this->PlayerStatusList->iGetPlayerMaxDodgeFlame();

			/* ���݂̉����ԃt���[�������擾 */
			int NowDodgeFrame = this->PlayerStatusList->iGetPlayerNowDodgeFlame();

			/* �����Ԃ��ێ�����鎞�Ԃ𒴂��Ă��Ȃ����m�F */
			if (NowDodgeFrame <= iDodgeMaxFrame)
			{
				// �����Ă��Ȃ�(�����Ԃ��p������)�ꍇ
				/* �v���C���[�̍U����Ԃ��ߋ����U��(��)�����m�F */
				if (iPlayerAttackState == PLAYER_ATTACKSTATUS_MELEE_STRONG)
				{
					// �ߋ����U��(��)���ł���ꍇ
					/* ����������s��Ȃ� */
					return;
				}

				/* ��𑬓x���擾 */
				float fPlayerDodgeSpeed = this->PlayerStatusList->fGetPlayerDodgeSpeed();

				/* ����ɂ��ړ�������ݒ肵�A�ړ����� */
				/* �o�߃t���[�����ɉ����āA��𑬓x����������(1.0f���ő�Ƃ��Č������Ă���) */
				this->vecMove = VScale(this->PlayerStatusList->vecGetPlayerDodgeDirection(), fPlayerDodgeSpeed * (1.0f - (float)NowDodgeFrame / (float)iDodgeMaxFrame));

				/* ����̌o�ߎ��Ԃ�i�߂� */
				this->PlayerStatusList->SetPlayerNowDodgeFlame(NowDodgeFrame + 1);

			}
			else
			{
				// �����Ă���(�����Ԃ��I������)�ꍇ

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
				/* �v���C���[�̍U����Ԃ��ߋ����U��(��)���łȂ����Ƃ��m�F */
				if (iPlayerAttackState != PLAYER_ATTACKSTATUS_MELEE_STRONG)
				{
					// �ߋ����U��(��)���łȂ��ꍇ
					/* �󒆂ł̉���񐔐����𒴂��Ă��Ȃ��� */
					if (this->PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() < PLAYER_DODGE_IN_AIR_LIMIT)
					{
						/* ����̃N�[���^�C�����c���Ă��邩�m�F */
						if (this->iDodgeCoolTime > 0)
						{
							// �N�[���^�C�����c���Ă���ꍇ
							/* ������s��Ȃ� */
							return;
						}

						/* ����J�n���̎��Ԃ����Z�b�g */
						this->PlayerStatusList->SetPlayerNowDodgeFlame(0);

						/* ��ʃG�t�F�N�g(�W����)�쐬 */
						ScreenEffect_Base* pScreenEffect = new ScreenEffect_ConcentrationLine();
						this->StageStatusList->SetScreenEffect(pScreenEffect);
						pScreenEffect->SetDeleteTime(this->PlayerStatusList->iGetPlayerMaxDodgeFlame());

						/* �������ݒ� */
						{
							/* ���͂ɂ��ړ��ʂ��擾 */
							VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();

							/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
							float fAngleX = this->StageStatusList->fGetCameraAngleX();

							/* �������x�N�g�� */
							VECTOR vecDodgMove;

							/* �X�e�B�b�N���͂�����Ă��邩�m�F */
							if (vecInput.x != 0 || vecInput.z != 0)
							{
								// �X�e�B�b�N���͂�����Ă���ꍇ
								/* �X�e�B�b�N���͂ɂ���������ݒ� */
								vecDodgMove.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
								vecDodgMove.y = 0.0f;
								vecDodgMove.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
							}
							else
							{
								// �X�e�B�b�N���͂�����Ă��Ȃ��ꍇ
								//�v���C���[�������Ă�������ɉ������
								/* �v���C���[���f���̏����̌�����Z���ɑ΂��ă}�C�i�X�����������Ă���Ƃ��� */
								vecDodgMove = { 0,0,-1 };

								/* �v���C���[�̊p�x����Y���̉�]�s������߂� */
								MATRIX matPlayerRotation = MGetRotY(-(this->PlayerStatusList->fGetPlayerAngleX()));

								/* �v���C���[�̌����ɂ���������ݒ� */
								vecDodgMove = VTransform(vecDodgMove, matPlayerRotation);
							}

							/* �������𐳋K�� */
							vecDodgMove = VNorm(vecDodgMove);

							/* ���݂̉��������Z�b�g���� */
							this->PlayerStatusList->SetPlayerDodgeDirection(vecDodgMove);
						}

						/* �����̉����x�������� */
						this->PlayerStatusList->SetPlayerNowFallSpeed(0.f);

						/* �v���C���[��Ԃ�"�����Ԓ�"�ɐݒ� */
						this->PlayerStatusList->SetPlayerMoveState(PLAYER_MOVESTATUS_DODGING);

						/* �v���C���[�̃��[�V����������ɐݒ� */
						this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_DODGE);

						/* �v���C���[�����n���Ă��Ȃ������m�F */
						if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
						{
							// ���n���Ă��Ȃ��ꍇ
							/* �󒆂ł̉���񐔂̃J�E���g��i�߂� */
							this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(PlayerStatusList->iGetPlayerDodgeWhileJumpingCount() + 1);
						}

						/* �����SE���Đ� */
						gpDataList_Sound->SE_PlaySound(SE_PLAYER_DODGE);

						/* ����̃{�C�X���Đ� */
						gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_ACTION);

						/* ����G�t�F�N�g�ǉ� */
						{
							/* ����G�t�F�N�g�𐶐� */
							this->pDodgeEffect = new EffectManualDelete_PlayerFollow(true);

							/* ����G�t�F�N�g�̓ǂݍ��� */
							this->pDodgeEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_dash/FX_dash"));

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
						/* ����N�[���^�C����ݒ� */
						this->iDodgeCoolTime = PLAYER_DODGE_COOLTIME;
					}
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
/* 2025.02.26 �e�r�듹	�N�[���^�C�������ǉ�	�I�� */
/* 2025.03.04 �e�r�듹	����̏����C�� �I�� */
/* 2025.03.11 �e�r�듹	����̏����C�� �I�� */
/* 2025.03.17 ��򕗏�	��ʃG�t�F�N�g�ǉ� �I�� */

/* 2025.01.09 �e�r�듹�@�ړ������ǉ�					�ǉ� */
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ�				�J�n */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C��				�J�n */
/* 2025.02.26 �e�r�듹	�ߋ����U��(��)�֘A�̏����ǉ�	�J�n */
/* 2025.03.10 ��򕗏�	�ړ�������						�J�n */
/* 2025.03.11 �e�r�듹	���[�V�����֘A�̏����ǉ�		�J�n */
/* 2025.03.18 ��򕗏�	�ړ����K�^�K�^�΍�				�J�n */

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
	auto& PlatformList = ObjectList->GetPlatformList();

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
			// ������l�͏����]�T����������(�ړ����ɓ��撆�ɏ����痣��Ȃ��悤�ɂ��邽��)
			if (stHitPolyDim.HitPosition.y >= fStandPosY + PLAYER_PLATFORM_RAND_CORRECTION)
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

					/* �W�����v���̃t���O�����Z�b�g */
					this->PlayerStatusList->SetPlayerJumpingFlag(false);

					/* �W�����v���̉���񐔂����Z�b�g */
					this->PlayerStatusList->SetPlayerDodgeWhileJumpingCount(0);

					/* �󒆂ł̋ߋ����U��(��)�񐔂����Z�b�g */
					this->PlayerStatusList->SetPlayerMeleeStrongAirCount(0);

					/* ������ԂɂȂ��Ă���̃t���[���������Z�b�g */
					this->iFallingFrame = 0;

					/* ���n�����v���b�g�t�H�[���̈ړ��ʂ��v���C���[�ړ��ʂɉ��Z */
					vecNextPosition = VAdd(this->vecPosition, platform->vecGetPlatformMove());

					/* �v���C���[�̃X���[���[�V�����J�E���g�����Z�b�g */
					this->PlayerStatusList->SetPlayerSlowMotionCount(0);

					/* �Ώۂ̃v���b�g�t�H�[�����v���C���[������Ă����Ԃɂ��� */
					platform->SetRidePlayerFlg(true);
				}
				else
				{
					// ���n���W���v���C���[�̌��݈ʒu��荂���ꍇ
					/* ���n���W���v���C���[���V��ɂ߂荞�܂Ȃ������ɍX�V */
					fStandPosY = stHitPolyDim.HitPosition.y - PLAYER_HEIGHT - PLAYER_CLIMBED_HEIGHT;

					/* �Ώۂ̃v���b�g�t�H�[�����v���C���[������Ă��Ȃ���Ԃɂ��� */
					platform->SetRidePlayerFlg(false);

					/* ���[�v�𔲂��� */
					break;
				}
			}
		}
	}

	/* ���n�t���O���������L���ɂȂ������m�F */
	if (bjumppingFlg == true && this->PlayerStatusList->bGetPlayerJumpingFlag() == false)
	{
		/* �v���C���[�̏�Ԃ��擾 */
		int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();

		/* ��𒆂�SE�ƃG�t�F�N�g���o�Ȃ��悤�ɂ��� */
		if (iPlayerMoveState != PLAYER_MOVESTATUS_DODGING)
		{
			/* ���n��SE���Đ� */
			gpDataList_Sound->SE_PlaySound(SE_PLAYER_LANDING);

			/* �G�t�F�N�g�ǉ� */
			{
				/* ���n�̃G�t�F�N�g�𐶐� */
				EffectSelfDelete* pAddEffect = new EffectSelfDelete;

				/* ���n�G�t�F�N�g�̓ǂݍ��� */
				pAddEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_land/FX_land"));

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

	/* ���n���W���X�V */
	vecNextPosition.y = fStandPosY;

	/* �v���C���[���W���X�V */
	this->vecPosition = vecNextPosition;

	/* ���݂̃v���C���[��Ԃ��擾 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* ���[�V�������X�V */
	{
		/* ���n�t���O�������ł���(�󒆂ɂ���)���m�F */
		if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
		{
			// �����ł���(�󒆂ɂ���)�ꍇ
			/* �v���C���[�̈ړ����[�V������"���"�łȂ����m�F */
			if (this->PlayerStatusList->iGetPlayerMoveState() != PLAYER_MOVESTATUS_DODGING)
			{
				// ������[�V�����łȂ��ꍇ
				/* �㏸���Ă��邩�m�F */
				if (this->PlayerStatusList->fGetPlayerNowFallSpeed() < 0)
				{
					// �㏸���Ă���ꍇ
					/* �v���C���[�̍U�����[�V������"����(����)"�łȂ����m�F */
					if(this->PlayerStatusList->iGetPlayerMotion_Attack() != MOTION_ID_ATTACK_THROW_READY)
					{
						// �U�����[�V����������(����)�łȂ��ꍇ
					/* ���[�V������"�W�����v(�J�n)"�łȂ����Ƃ��m�F */
					if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_JUMP_START)
					{
						/* ���[�V������"�W�����v(�㏸)"�ɐݒ� */
							this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_UP);
						}
					}
				}
				else
				{
					// ���~���Ă���ꍇ
					/* �v���C���[���W�����v���ł��邩�m�F */
					if (this->PlayerStatusList->bGetPlayerJumpingFlag() == true)
					{
						/* ���[�V������"�W�����v(���~)"�ɐݒ� */
						this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_DOWN);
					}
					else
					{
						// �W�����v���łȂ��ꍇ
						/* ������ԂɂȂ��Ă���̃t���[��������萔�𒴂��Ă��邩�m�F */
						if (this->iFallingFrame > PLAYER_JUNP_DOWN_MOTION_SWITCH_FRAME)
						{
							// ��萔�𒴂��Ă���ꍇ
							/* ���[�V������"�W�����v(���~)"�ɐݒ� */
							this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_JUMP_DOWN);
						}					
					}

					/* ������ԂɂȂ��Ă���̃t���[���������Z */
					this->iFallingFrame++;
				}
					
			}
		}
	}
}
/* 2025.01.09 �e�r�듹�@�ړ������ǉ�					�I�� */
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ�				�I�� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C��				�I�� */
/* 2025.02.26 �e�r�듹	�ߋ����U��(��)�֘A�̏����ǉ�	�I�� */
/* 2025.03.10 ��򕗏�	�ړ�������						�I�� */
/* 2025.03.11 �e�r�듹	���[�V�����֘A�̏����ǉ�		�I�� */
/* 2025.03.18 ��򕗏�	�ړ����K�^�K�^�΍�				�I�� */

/* 2025.02.07 �e�r�듹	�Փ˔��菈���C��	�J�n */
/* 2025.02.22 �e�r�듹	�ǃL�b�N�����ǉ�	�J�n */
/* 2025.03.05 �e�r�듹	�Փ˔��菈���C��	�J�n */

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
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].vecCapsuleTop = VAdd(vecNextPosition, VGet(0.f, PLAYER_HEIGHT - PLAYER_WIDE, 0.f));
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP].fCapsuleRadius = PLAYER_WIDE;
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].vecCapsuleTop = VAdd(vecNextPosition, VGet(0.f, PLAYER_WIDE + PLAYER_CLIMBED_HEIGHT, 0.f));
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN].fCapsuleRadius = PLAYER_WIDE;
		

		/* ������擾 */
		auto& PlatformList = ObjectList->GetPlatformList();

		/* ����ƐڐG���邩�m�F */
		for (auto* platform : PlatformList)
		{
			/* ����Ƃ̐ڐG���� */
			for (int i = 0; i < PLAYER_MOVE_COLLISION_MAX; i++)
			{
				/* �I�u�W�F�N�g�ƐڐG���Ă��邩�m�F */
				MV1_COLL_RESULT_POLY_DIM stHitPolyDim = platform->HitCheck_Capsule(this->stHorizontalCollision[i]);

				/* �ڐG���Ă��邩�m�F */
				if (stHitPolyDim.HitNum > 0)
				{
					// 1�ȏ�̃|���S�����ڐG���Ă���ꍇ
					if (this->PlayerStatusList->bGetPlayerKickWallFlg() == true)
					{
						/* �ǃL�b�N�t���O������ */
						this->PlayerStatusList->SetPlayerKickWallFlg(false);
						
						/* �o�߃t���[���������Z�b�g */
						this->PlayerStatusList->SetPlayerAfterKickWallCount(0);
					}

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

					/* �ǂ̐ڐG�t���O��ݒ� */
					this->PlayerStatusList->SetPlayerWallTouchFlg(true);

					/* �ǂɐڐG���Ă���̌o�߃t���[���������Z�b�g */
					this->PlayerStatusList->SetPlayerAfterWallTouchCount(0);

					// �v���C���[���ړ����Ă��邩�ɂ���ď����𕪊�
					/* �v���C���[�̈ړ��ʂ𕪊����Ĕ��肷��񐔂��m�F */
					if (iMoveHitCheckCount > 0)
					{
						// �ړ��ʂ𕪊����Ĕ��肷��񐔂�1�ȏ�̏ꍇ(�ړ����Ă���ꍇ)
						/* �ړ��ʂ𕪊����ďՓ˔��肷�� */
						for (int i = 0; i < iMoveHitCheckCount; i++)
						{
							/* �ړ�����W�ɋ��̃|���S�����쐬 */
							vecDevisionMovePosition = VAdd(vecDevisionMovePosition, vecDevisionMove);

						/* �ړ�����W�ɋ��̃|���S�����쐬 */
						COLLISION_SQHERE stSphere;
						stSphere.vecSqhere = vecDevisionMovePosition;
						stSphere.fSqhereRadius = PLAYER_WIDE;

						/* �@���̕����Ƀv���C���[�������o�� */
						// �� �Ώۂ̃R���W�����ƐڐG���Ȃ��Ȃ�܂ŉ����o��
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
					else
					{
						// �ړ��ʂ𕪊����Ĕ��肷��񐔂�0�̏ꍇ(�ړ����Ă��Ȃ��ꍇ)
						/* �@���x�N�g���̕����։����o���������s�� */
						vecNextPosition = VAdd(this->vecPosition, VScale(vecNormalSum, 1.f));
				}
			}
				
			}	
		}
	}

	/* �ǂƂ̐ڐG�t���O���擾 */
	bool bWallTouch = this->PlayerStatusList->bGetPlayerWallTouchFlg();	

	// �ǂƐڐG���Ă����ꍇ�A�����𖞂�������ǃL�b�N���s��
	/* �ǂƂ̐ڐG�t���O���m�F */
	if (bWallTouch == true)
	{	
		// �ǂƂ̐ڐG�t���O���L���̏ꍇ
		/* �ǂɐڐG���Ă���̌o�߃t���[�������擾 */
		int iNowAfterWallTouchCount = this->PlayerStatusList->iGetPlayerAfterWallTouchCount();

		/* �ǂɐڐG���Ă���̌o�߃t���[���������Z */
		this->PlayerStatusList->SetPlayerAfterWallTouchCount(iNowAfterWallTouchCount + 1);

		/* �ǃL�b�N�̓��͗P�\�t���[�������擾 */
		int iWallKickInputMaxFlame = this->PlayerStatusList->iGetPlayerKickWallInputMaxFlame();

		/* �ǂɐڐG���Ă���̌o�߃t���[���������l�ȉ����m�F���� */
		if (iNowAfterWallTouchCount <= iWallKickInputMaxFlame)
		{
			//�ǂɐڐG���Ă���̌o�߃t���[���������l�ȉ��̏ꍇ

			/* �X�e�B�b�N�̓��͂��擾 */
			VECTOR vecInput = this->InputList->vecGetGameInputMoveDirection();

			/* �X�e�B�b�N���͕��������߂� */
			float fMoveAngle = atan2f(vecInput.x, vecInput.z);

			/* �J�����̐��������̌������擾 */
			float fAngleX = this->StageStatusList->fGetCameraAngleX();

			/* �J�����̐��������̌���������͈̔�(0~2��)�𒴂����ꍇ�A�␳���s�� */
			this->RadianLimitAdjustment(fAngleX);

			/* �␳�����J�����p�x��ݒ� */
			this->StageStatusList->SetCameraAngleX(fAngleX);

			/* ���͕����ƃJ�����̌������������ړ������Ƃ��� */
			fMoveAngle = fAngleX - fMoveAngle;

			/* �X�e�B�b�N���͕��� */
			VECTOR vecInputDerection = VGet(0.0f, 0.0f, 0.0f);

			/* �X�e�B�b�N���͂ɕ�����ݒ� */
			vecInputDerection.x = +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
			vecInputDerection.y = 0.0f;
			vecInputDerection.z = -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);

			/* �ǂ̖@���x�N�g���ƃX�e�B�b�N���͕����̓��ς����߂� */
			float fWallInputDot = VDot(vecNormalSum, vecInputDerection);

			/* �ǂ̖@���x�N�g���ƃX�e�B�b�N���͕����̓��ς���(��������)���m�F���� */
			if (fWallInputDot > 0)
			{
				// �ǂ̖@���x�N�g���ƃX�e�B�b�N���͕����̓��ς���(��������)�̏ꍇ
				/* �W�����v�{�^�������������m�F���� */
				if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
				{
					// �W�����v�{�^�����������ꍇ
					/* �ǃL�b�N�t���O��L���ɂ��� */
					this->PlayerStatusList->SetPlayerKickWallFlg(true);
					
					/* �ǂƂ̐ڐG�t���O���������� */
					this->PlayerStatusList->SetPlayerWallTouchFlg(false);

					/* �ǂɐڐG���Ă���̌o�߃t���[���������Z�b�g */
					this->PlayerStatusList->SetPlayerAfterWallTouchCount(0);
				}
			}
		}
		else
		{
			//�ǂɐڐG���Ă���̌o�߃t���[���������l�ȏ�̏ꍇ
			/* �ǂƂ̐ڐG�t���O���������� */
			this->PlayerStatusList->SetPlayerWallTouchFlg(false);

			/* �ǂɐڐG���Ă���̌o�߃t���[���������Z�b�g */
			this->PlayerStatusList->SetPlayerAfterWallTouchCount(0);
		}
		
	}

	/* �v���C���[�̍��W���ړ������� */
	this->vecPosition = vecNextPosition;
}
/* 2025.02.07 �e�r�듹	�Փ˔��菈���C��	�I�� */
/* 2025.02.22 �e�r�듹	�ǃL�b�N�����ǉ�	�I�� */
/* 2025.03.05 �e�r�듹	�Փ˔��菈���C��	�I�� */