/* 2024.12.15 ��򕗏�	�t�@�C���쐬 */
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.01.30 �e�r�듹	���[�V���������ǉ� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� */
/* 2025.02.14 �e�r�듹	��]�֘A�̊֐��ǉ� */
/* 2025.02.14 �e�r�듹	�N�i�C�֘A�̏����ǉ� */

#include "CharacterPlayer.h"

/* �v���C���[�N���X�̒�` */
// �R���X�g���N�^
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* ������ */
	{
		/* �I�u�W�F�N�g�̃n���h�� */
		this->pBulletMeleeWeak	=	nullptr;	// �ߐڍU��(��)�̒e
		this->pBulletKunaiEffect =	nullptr;	// �N�i�C(�G�t�F�N�g)�̒e	/* 2025.02.14 �e�r�듹	�N�i�C�֘A�̏����ǉ� */

		/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �J�n */
		/* �G�t�F�N�g�̃n���h�� */
		this->pChargeEffect			=	nullptr;		//���߃G�t�F�N�g
		this->pChargeHoldEffect		=	nullptr;		//���ߊ�����G�t�F�N�g
		this->pDodgeEffect			=	nullptr;		//����G�t�F�N�g
		/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �I�� */

		/* 2025.01.30 �e�r�듹	���[�V���������ǉ� �J�n */
		this->iMotionAttachIndex	=	-1;		// �A�^�b�`���郂�[�V�����̃C���f�b�N�X(�����A�^�b�`���Ȃ�)
		this->iOldMotion			=	-1;		// �ȑO�ɃA�^�b�`���ꂽ���[�V����(�����A�^�b�`���Ȃ�)
		this->fMotionTotalTime		=	0;		// ���[�V�����̑�����
		this->fMoionPlayTime		=	0;		// ���[�V�����̍Đ�����
		/* 2025.01.30 �e�r�듹	���[�V���������ǉ� �I�� */

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

		/* "�G�t�F�N�g���\�[�X�Ǘ�"���擾 */
		this->EffectList		= dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Player/Player");
	}
}

// ������
void CharacterPlayer::Initialization()
{
	CharacterBase::Initialization();

	/* �R���W�������X�V */
	CollisionUpdate();

	/* �J�������[�h��"�t���[���[�h"�ɕύX */
	this->PlayerStatusList->SetCameraMode(CAMERA_MODE_FREE);
}

// �X�V
void CharacterPlayer::Update()
{
	/* �J�������[�h��"�t���[���[�h"�ɕύX */
	this->PlayerStatusList->SetCameraMode(CAMERA_MODE_FREE);

	/* �ڐG�m�F */
	{
		// ���U����I�u�W�F�N�g�ɑ΂��铖���蔻�菈�����s��
		/* �����蔻�菈�� */
		PlayerHitCheck();
	}

	/* ���t���[���̏��������� */
	{
	/* �ړ��ʂ����Z�b�g */
	this->vecMove = VGet(0, 0, 0);

		/* ���b�N�I���͈̓R���W�����g�p�t���O�𖳌��� */
		this->PlayerStatusList->SetMeleeSearchCollisionUseFlg(false);
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
/* �����蔻�菈�� */
void CharacterPlayer::PlayerHitCheck()
{
	/* �v���C���[�̈ړ���Ԃ��擾 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();
	/* �v���C���[�̍U����Ԃ��擾 */
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
		case PLAYER_MOVESTATUS_DODGING:				// �����Ԓ�
				
			/* ��e�������s��Ȃ�(���G���) */
			bHiteFlag = true;
					
			break;
		}
		
		/* ��e�������󂯂�v���C���[�̍U����Ԃ��m�F */
		switch (iPlayerAttackState)
		{
			/* ��e�������s����� */
		case PLAYER_ATTACKSTATUS_FREE:				// ���R���
		case PLAYER_ATTACKSTATUS_MELEE_POSTURE:		// �ߐڍU���\����
		case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// �������U���\����
		case PLAYER_ATTACKSTATUS_MELEE_STRONG:		// �ߐڍU����(��)
		case PLAYER_ATTACKSTATUS_PROJECTILE:			// �������U����
				
			/* ��e�������s�� */
			bHiteFlag = true;

			break;

			/* ��e�������s��Ȃ����(���G���) */
		case PLAYER_ATTACKSTATUS_MELEE_WEEK:			// �ߐڍU����(��)
				
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

								/* �v���C���[�̖��G���Ԃ�ݒ� */
								this->PlayerStatusList->SetPlayerNowInvincibleTime(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());

								/* �e�̍폜�t���O��L���ɂ��� */
								bullet->SetDeleteFlg(true);

								/* ��_���[�W��SE���Đ� */
								gpDataList_Sound->SE_PlaySound(SE_PLAYER_DAMAGE);
							}
						}
					}
				}
	}
}
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� �I�� */

/* 2025.02.14 �e�r�듹	��]�֘A�̊֐��ǉ� �J�n */
// �p�x(���W�A��)�̐����ƕ␳
void CharacterPlayer::RadianLimitAdjustment(float& fRadian)
{
	// �p�x(���W�A��)������͈̔�(0~2��)�𒴂����ꍇ�A�␳���s��
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
/* 2025.02.14 �e�r�듹	��]�֘A�̊֐��ǉ� �I�� */