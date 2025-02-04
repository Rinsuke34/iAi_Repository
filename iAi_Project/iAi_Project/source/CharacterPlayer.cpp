/* 2024.12.15 ��򕗏�	�t�@�C���쐬 */
/* 2025.01.30 �e�r�듹	���[�V���������ǉ� */

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
		this->iModelHandle = ModelListHandle->iGetModel("Player/Models/Player");
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

	/* �v���C���[�̃��[�V������Ԃ�ۑ����� */
	iOldMotion = this->PlayerStatusList->iGetPlayerMotion();

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

/* �����蔻�菈�� */
void CharacterPlayer::HitCheck()
{
	/* �v���C���[�̏�Ԃ��擾 */
	int iPlayerState = this->PlayerStatusList->iGetPlayerState();

	/* ��e���� */
	{
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
			/* ��e�������󂯂邩�ǂ������� */
			switch (iPlayerState)
			{
				/* ��e�������s����� */
				case PLAYER_STATUS_FREE:				// ���R���
				case PLAYER_STATUS_MELEE_POSTURE:		// �ߐڍU���\����
				case PLAYER_STATUS_PROJECTILE_POSTURE:	// �������U���\����
				case PLAYER_STATUS_MELEE_STRONG:		// �ߐڍU����(��)
				case PLAYER_STATUS_PROJECTILE:			// �������U����
				/* ��e���� */
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
				break;

				/* ��e�������s��Ȃ����(���G���) */
				case PLAYER_STATUS_DODGING:				// �����Ԓ�
				case PLAYER_STATUS_MELEE_WEEK:			// �ߐڍU����(��)
					/* ��e�������s��Ȃ� */
					break;
			}
		}
	}
}

/* 2025.01.30 �e�r�듹	���[�V���������ǉ� �J�n */
// �v���C���[�̃��[�V�����J�ڊǗ�
void CharacterPlayer::Player_Motion_Transition()
{
	/* �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����*/
	this->fMotionTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMotionAttachIndex);

	// ����(��)(�I��)���[�V�����͂P���[�v�Đ�����
	if (iOldMotion == PLAYER_MOTION_DRAW_SWORD_END)
	{	
		// ���[�V�����̍Đ����Ԃ����Đ����Ԃ𒴂��Ă��Ȃ���� �����Đ����Ԃ��̂܂܂��ƃX���[�����̂�-2���Ă��܂�
		if (fMoionPlayTime <= this->fMotionTotalTime -2)
		{
			/* ���[�V�����̍Đ����Ԃ�i�߂� */
			this->fMoionPlayTime += 1.0f;
		}
		else
		{
			/* ����(��)(�I��)���[�V�������f�^�b�` */
			MV1DetachAnim(this->iModelHandle, this->iMotionAttachIndex);
			
			/* ����(��)(�I��)���[�V�������I�������A�ҋ@���[�V�������A�^�b�` */
			this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_loop"), -1, FALSE);
		}
	}
	// ����ȊO�́A���[�V�������ς���Ă��Ȃ���΍Đ����Ԃ�i�߂�
	else  if (iOldMotion == this->PlayerStatusList->iGetPlayerMotion())
	{
		/* ���[�V�����̍Đ����Ԃ�i�߂� */
		this->fMoionPlayTime += 1.0f;
	}
	// ���[�V�������ς�����ꍇ�̏���
	else
	{
		// ���[�V�������A�^�b�`����Ă����� 
		if (this->iMotionAttachIndex != -1)
		{
			/* ���[�V�������f�^�b�` */
			MV1DetachAnim(this->iModelHandle, this->iMotionAttachIndex);
		}

		/* �v���C���[�̃��[�V������Ԃ��擾 */
		int iPlayerMotion = this->PlayerStatusList->iGetPlayerMotion();

		// �v���C���[�̃��[�V������Ԃɉ����āA���[�V�������A�^�b�`����
		switch (iPlayerMotion)
		{
			/* �ҋ@ */
			case PLAYER_MOTION_IDLE:
				/* �ҋ@���[�V�������A�^�b�` */
				this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_loop"), -1, FALSE);
				break;

			/* ���s */
			case PLAYER_MOTION_WALK:
			/* ���s(�ᑬ) */
			case PLAYER_MOTION_RUN_LOW:
			/* ���s(����) */
			case PLAYER_MOTION_RUN_HIGH:
			/* ���胂�[�V�������A�^�b�` */
				this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_move_run"), -1, FALSE);
				break;

			/* ����(����) */
			case PLAYER_MOTION_DRAW_SWORD_CHARGE:
				/* �����i���߁j���[�V�������A�^�b�` */
				this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_loop"), -1, FALSE);
				break;

			/* ����(��) */
			case PLAYER_MOTION_DRAW_SWORD_WEAK:
				break;
				/* ����(��) */
			case PLAYER_MOTION_DRAW_SWORD_STRONG:
				/* �����i���߁j���[�V�������A�^�b�` */
				this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_step"), -1, FALSE);
				break;

			/* ����(��)(�I��) */
			case PLAYER_MOTION_DRAW_SWORD_END:
				/* ����(��)(�I��)���[�V�������A�^�b�` */
				this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_finish"), -1, FALSE);
				break;

			/* �N�i�C(�\��) */
			case PLAYER_MOTION_THROW_KUNAI_AIM:
				break;

			/* �N�i�C(����) */
			case PLAYER_MOTION_THROW_KUNAI_THROW:
				break;

			/* ��� */
			case PLAYER_MOTION_DODGE:
				break;

			/* �W�����v(�㏸) */
			case PLAYER_MOTION_JUMP_UP:
				break;

			/* �W�����v(���~) */
			case PLAYER_MOTION_JUMP_DOWN:
				break;

			return;
		}

		/* ���[�V�����̍Đ����Ԃ����Z�b�g���� */
		this->fMoionPlayTime = 0.0f;
	}

	// ���[�V�����̍Đ����Ԃ����Đ����Ԃ𒴂����ꍇ
	if (this->fMoionPlayTime > this->fMotionTotalTime)
	{
		/* ���[�V�����̍Đ����Ԃ����Z�b�g���� */
		this->fMoionPlayTime = 0.0f;
	}
}