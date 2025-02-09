/* 2024.12.15 ��򕗏�	�t�@�C���쐬 */
/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� */
/* 2025.01.30 �e�r�듹	���[�V���������ǉ� */
/* 2025.02.05 �e�r�듹	�X�e�[�^�X�֘A�C�� */

#include "CharacterPlayer.h"

/* �v���C���[�N���X�̒�` */
// �R���X�g���N�^
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* ������ */
	{
		/* �I�u�W�F�N�g�̃n���h�� */
		this->pBulletMeleeWeak	=	nullptr;	// �ߐڍU��(��)�̒e

		/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �J�n */
		/* �G�t�F�N�g�̃n���h�� */
		this->pChargeEffect			=	nullptr;		//���߃G�t�F�N�g
		this->pChargeHoldEffect		=	nullptr;		//���ߊ�����G�t�F�N�g
		this->pDodgeEffect			=	nullptr;		//����G�t�F�N�g
		/* 2025.01.27 �e�r�듹	�G�t�F�N�g�����ǉ� �I�� */

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

	/* ���[�V�������X�g�̐ݒ� */
	{
		for (int i = 0; i < MOTION_ID_MAX; i++)
		{
			/* ���[�V����ID��ݒ� */
			this->PlayerMotionList[i].iMotionID			= MOTION_LIST[i].iMotionID;

			/* ���[�V��������ݒ� */
			this->PlayerMotionList[i].strMotionName		= MOTION_LIST[i].strMotionName;

			/* ���[�V�����̑��Đ����Ԃ��擾���ݒ� */
			this->PlayerMotionList[i].fMotion_MaxTime	= MV1GetAnimTotalTime(this->iModelHandle, this->PlayerMotionList[i].iMotionID);

			/* ���̃��[�V����ID��ݒ� */
			this->PlayerMotionList[i].iNextMotionID		= MOTION_LIST[i].iNextMotionID;
		}
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
		HitCheck();
	}

	/* ���t���[���̏��������� */
	{
		/* �ړ��ʂ����Z�b�g */
		this->vecMove = VGet(0, 0, 0);

		/* ���b�N�I���͈̓R���W�����g�p�t���O�𖳌��� */
		this->PlayerStatusList->SetMeleeSearchCollisionUseFlg(false);
	}

	///* �v���C���[�̃��[�V������Ԃ�ۑ����� */
	//this->PlayerStatusList->SetPlayerMotion_Move_Old(this->PlayerStatusList->iGetPlayerMotion_Move());
	//this->PlayerStatusList->SetPlayerMotion_Attack_Old(this->PlayerStatusList->iGetPlayerMotion_Attack());

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
void CharacterPlayer::HitCheck()
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
