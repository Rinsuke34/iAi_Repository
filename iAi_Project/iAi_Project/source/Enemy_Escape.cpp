/* 2025.01.2�W �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Escape.h"

// �R���X�g���N�^
Enemy_Escape::Enemy_Escape() : Enemy_Basic()
{
	//������
	//X���̋���
	this->iXescapedistance = ENEMY_X_ESCAPE_DISTANCE;

	//Z���̋���
	this->iZescapedistance = ENEMY_Z_ESCAPE_DISTANCE;

	// �ړ����x
	this->iEscapespeed = ENEMY_ESCAPE_SPEED;

	//�d��
	this->fGravity = ENEMY_GRAVITY_SREED;

	//SE���Đ��J�n�������̃t���O
	this->bPlayeSeFlg	= false;		// SE���Đ��J�n�������̃t���O(�Q�[���J�n��Ɏ��s���Ȃ��Ƒ��̃V�[�����ɍĐ�����邽��)

	//�G�t�F�N�g��nullptr�ɐݒ�
	this->pEffect = nullptr;

	// HP��ݒ�
	this->iMaxHp = 1;
	this->iNowHp = 1;

	// �I�u�W�F�N�g�̎�ނ�TypeEnemy�ɐݒ�
	this->iObjectType = OBJECT_TYPE_ENEMY;

	// �o������u���b�h�ʂ�ݒ�
	this->iBloodAmount = 20;

	//�q�b�g�G�t�F�N�g�����t���O
	this->bHitEffectGenerated = false;

	//�����G�t�F�N�g�����t���O
	this->bEscapeEffectGenerated = true;

	//�����Œ�t���O
	this->bDirectionFlg = true;

	//�ҋ@�J�E���g
	this->iWaitCount = 5;

	//�ǂɓ����������̃t���O
	this->bWallHitFlg = false;

	//�ҋ@�J�E���g
	this->iReturnCount = 1;

	//�ăX�^�[�g�J�E���g
	this->iRestartCount = 10;

	//�ǂ̖@���x�N�g��
	this->wallNormal = VGet(0, 0, 0);

	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Escape/Enemy_Escape");


	}

}

// �f�X�g���N�^
Enemy_Escape::~Enemy_Escape()
{

}

// ������
void Enemy_Escape::Initialization()
{
	/* �R���W�����Z�b�g */
	//�G�l�~�[�̃J�v�Z�����a
	this->stCollisionCapsule.fCapsuleRadius = 100;

	//�J�v�Z���R���W�����̏�̍��W
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));

	//�J�v�Z���R���W�����̉��̍��W
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	//�������W��ۑ�
	this->vecInitialPosition = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();

	//��������t���[���̏���
	UpdataLightFrame();
}

// �G�l�~�[�̈ړ�����
void Enemy_Escape::MoveEnemy()
{
	//�G�l�~�[�̐��������p�̃J�v�Z���R���W�����̐ݒ�
	//�J�v�Z���̔��a��ݒ�
	this->stHorizontalCollision.fCapsuleRadius = 50;

	//�J�v�Z���̏�̍��W��ݒ�
	this->stHorizontalCollision.vecCapsuleTop = VAdd(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z), VGet(0, 50, 0));

	//�J�v�Z���̉��̍��W��ݒ�
	this->stHorizontalCollision.vecCapsuleBottom = VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z);

	// �v���C���[�̍��W���擾
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	// �d�͏���
	this->vecMove.y -= ENEMY_GRAVITY_SREED;

	// �G�l�~�[�̍��W���X�V
	this->vecPosition.y += this->vecMove.y;

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//�G�l�~�[�����j����Ă��Ȃ����m�F
	if (this->iNowHp > 0)
	{
		//�G�l�~�[�����j����Ă��Ȃ��ꍇ
		// �v���C���[�ƃG�l�~�[�̋����̕������v�Z
		float distanceToPlayerSquared = (this->vecPosition.x - playerPos.x) * (this->vecPosition.x - playerPos.x) +
			(this->vecPosition.y - playerPos.y) * (this->vecPosition.y - playerPos.y) + (this->vecPosition.z - playerPos.z) * (this->vecPosition.z - playerPos.z);

		// ���G�͈͂̔��a�̕���
		float detectionRadiusSquared = ENEMY_X_ESCAPE_DISTANCE * ENEMY_X_ESCAPE_DISTANCE;

		// �v���C���[�����G�͈͓��ɂ��邩�m�F
		if (distanceToPlayerSquared < detectionRadiusSquared)
		{
			//�v���C���[�����G�͈͓��ɂ���ꍇ
			//�ҋ@�J�E���g�����Z
			this->iWaitCount--;

			//�ҋ@�J�E���g��0�ȉ����m�F
			if (this->iWaitCount <= 0)
			{
				//�ҋ@�J�E���g��0�ȉ��̏ꍇ
				//�ҋ@���[�V�������f�^�b�`����
				MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);

				//���胂�[�V�������A�^�b�`����
				this->iRunAttachIndex = MV1AttachAnim(this->iModelHandle, 7, -1, FALSE);

				//���胂�[�V�����̑��Đ����Ԃ��擾����
				this->fRunTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iRunAttachIndex);

				//�Đ����x�����Z
				this->fRunPlayTime += 1.0f;

				//�Đ����Ԃ��Z�b�g����
				MV1SetAttachAnimTime(this->iModelHandle, this->iRunAttachIndex, this->fRunPlayTime);

				//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
				if (this->fRunPlayTime >= this->fRunTotalTime)
				{
					//�A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
					//�Đ����Ԃ�����������
					this->fRunPlayTime = 0.0f;
				}
				if (this->bEscapeEffectGenerated == true)
				{
					// �G�t�F�N�g�𐶐�
					this->pEffect = new EffectSelfDelete();

					// �G�t�F�N�g�̓ǂݍ���
					this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_glitter/FX_e_glitter")));

					// �G�t�F�N�g�̍��W�ݒ�
					this->pEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

					// �G�t�F�N�g�̉�]�ʐݒ�
					this->pEffect->SetRotation(this->vecRotation);

					//�G�t�F�N�g�̍폜����
					this->pEffect->SetDeleteCount(60);

					// �G�t�F�N�g�̏�����
					this->pEffect->Initialization();

					// �G�t�F�N�g�����X�g�ɓo�^
					{
						// "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾
						DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

						// �G�t�F�N�g�����X�g�ɓo�^
						ObjectListHandle->SetEffect(pEffect);
					}

					// �v���C���[���T�m�͈͓��ɂ���ꍇ
					// �v���C���[���瓦����
					VECTOR directionAwayFromPlayer = VNorm(VSub(VGet(this->vecPosition.x, 0, this->vecPosition.z), VGet(playerPos.x, 0, playerPos.z)));

					// �v���C���[���瓦��������Ƒ��x��ݒ�
					this->vecPosition = VAdd(this->vecPosition, VScale(directionAwayFromPlayer, this->iEscapespeed));

					// �G�l�~�[�̌���������������
					VRot = VGet(0, 0, 0);

					// �v���C���[�̕����������悤�ɃG�l�~�[�̌������`
					VRot.y = atan2f(playerPos.x - this->vecPosition.x, playerPos.z - this->vecPosition.z);

					//�G�l�~�[�̌����Œ�t���O���L�����m�F
					if (this->bDirectionFlg == true)
					{
						//�G�l�~�[�̌����Œ�t���O���L���̏ꍇ
						// �G�l�~�[�̌�����ݒ�
						this->vecRotation = VRot;

						//�G�l�~�[�̌������擾
						MV1SetRotationXYZ(iModelHandle, VRot);
					}
				}
			}
		}
		else
		{
			// �T�m�͈͊O�ɂ���ꍇ

			//�ҋ@�J�E���g��������
			this->iWaitCount = 5;

			// ���郂�[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);

			// �ҋ@���[�V�������A�^�b�`����
			this->iWaitAttachIndex = MV1AttachAnim(this->iModelHandle, 3, -1, FALSE);

			// �ҋ@���[�V�����̑��Đ����Ԃ��擾����	
			this->fWaitTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iWaitAttachIndex);

			//�Đ����x�����Z
			this->fWaitPlayTime += 1.0f;

			//�Đ����Ԃ��Z�b�g����
			MV1SetAttachAnimTime(this->iModelHandle, this->iWaitAttachIndex, this->fWaitPlayTime);

			//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
			if (this->fWaitPlayTime >= this->fWaitTotalTime)
			{
				//�A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
				//�Đ����Ԃ�����������
				this->fWaitPlayTime = 0.0f;
			}

			// �v���C���[�̕����������悤�ɃG�l�~�[�̌������`
			VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

			if (VRot.y <= vecRotation.y)
			{
				this->vecRotation = VGet(vecRotation.x, vecRotation.y - 0.2, vecRotation.z);
			}
			if (VRot.y >= vecRotation.y)
			{
				this->vecRotation = VGet(vecRotation.x, vecRotation.y + 0.2, vecRotation.z);
			}
			if (VRot.x == vecRotation.x && VRot.y == vecRotation.y)
			{
				//�G�l�~�[�̌�����ݒ�
				this->vecRotation = VRot;
			}
		}
	}

	//�G�l�~�[���ǂɓ����������̃t���O���L�����m�F
	if (this->bWallHitFlg == true)
	{
		//�G�l�~�[���ǂɓ��������ꍇ
		//�ҋ@�J�E���g�����Z
		this->iReturnCount--;

		// ���郂�[�V�������f�^�b�`����
		MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);

		// �ҋ@���[�V�������A�^�b�`����
		this->iWaitAttachIndex = MV1AttachAnim(this->iModelHandle, 3, -1, FALSE);

		// �ҋ@���[�V�����̑��Đ����Ԃ��擾����
		this->fWaitTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iWaitAttachIndex);

		//�Đ����x�����Z
		this->fWaitPlayTime += 1.0f;

		//�Đ����Ԃ��Z�b�g����
		MV1SetAttachAnimTime(this->iModelHandle, this->iWaitAttachIndex, this->fWaitPlayTime);

		//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
		if (this->fWaitPlayTime >= this->fWaitTotalTime)
		{
			//�A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
			//�Đ����Ԃ�����������
			this->fWaitPlayTime = 0.0f;
		}

		//�ҋ@�J�E���g��0�ȉ����m�F
		if (this->iReturnCount < 0)
		{
			//�ҋ@�J�E���g��0�ȉ��̏ꍇ
			// �v���C���[�̕����ɂX�O�x�E�Ɏ���ړ�
			VECTOR directionToPlayer = VNorm(VSub(playerPos, this->vecPosition));
			VECTOR directionToPlayerRight = VCross(directionToPlayer, VGet(0, 1, 0));

			// �ǂ̖@���x�N�g���ƃv���C���[�̕����x�N�g���̓��ς��v�Z
			float dotProduct = VDot(wallNormal, directionToPlayerRight);

			// ���ς����Ȃ�E�ɉ�]�A���Ȃ獶�ɉ�]
			VECTOR VRot = VGet(0, 0, 0);
			if (dotProduct > 0)
			{
				vecPosition = VAdd(vecPosition, VScale(directionToPlayerRight, this->iEscapespeed));
				VRot.y = atan2f(directionToPlayerRight.x, -directionToPlayerRight.z);
			}
			else
			{
				vecPosition = VAdd(vecPosition, VScale(VScale(directionToPlayerRight, -1), this->iEscapespeed));
				VRot.y = atan2f(-directionToPlayerRight.x, directionToPlayerRight.z);
			}

			// �G�l�~�[�̌�����ݒ�
			this->vecRotation = VRot;
			MV1SetRotationXYZ(iModelHandle, VRot);

			//�ҋ@���[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);

			//���胂�[�V�������A�^�b�`����
			this->iRunAttachIndex = MV1AttachAnim(this->iModelHandle, 7, -1, FALSE);

			//���胂�[�V�����̑��Đ����Ԃ��擾����
			this->fRunTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iRunAttachIndex);

			//�Đ����x�����Z
			this->fRunPlayTime += 1.0f;

			//�Đ����Ԃ��Z�b�g����
			MV1SetAttachAnimTime(this->iModelHandle, this->iRunAttachIndex, this->fRunPlayTime);

			//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
			if (this->fRunPlayTime >= this->fRunTotalTime)
			{
				//�A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
				//�Đ����Ԃ�����������
				this->fRunPlayTime = 0.0f;
			}

			//�ċN���J�E���g�����Z
			this->iRestartCount--;

			//�G�l�~�[�̌�����ݒ�
			this->vecRotation = VRot;

			//�G�l�~�[�̌�����ݒ�
			MV1SetRotationXYZ(iModelHandle, VRot);
		}

		//�ăv���C�J�E���g��0�ȉ����m�F
		if (this->iRestartCount < 0)
		{
			//�ăv���C�J�E���g��0�ȉ��̏ꍇ
			//�ҋ@�J�E���g��������
			this->iReturnCount = 1;

			//�ăv���C�J�E���g��������
			this->iRestartCount = 10;

			//�ҋ@�J�E���g��������
			this->iWaitCount = 5;

			//�G�l�~�[�̕ǂɓ��������t���O�𖳌��ɂ���
			this->bWallHitFlg = false;

			//�����G�t�F�N�g�����t���O��L���ɂ���
			this->bEscapeEffectGenerated = true;
		}
	}
}

//�R���W�����`��
void Enemy_Escape::CollisionDraw()
{
	//�G�l�~�[�̐��������̓����蔻��p�̃R���W�����̕`��
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, GetColor(255, 0, 0));

	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

	DrawCapsule3D(this->stHorizontalCollision.vecCapsuleTop, this->stHorizontalCollision.vecCapsuleBottom, this->stHorizontalCollision.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
}

// �G�l�~�[���f���A�j���[�V����
void Enemy_Escape::Enemy_Model_Animation()
{
	if (this->iNowHp > 0)
	{
	this->fRunPlayTime += 1.0f;
	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(this->iModelHandle, this->iRunAttachIndex, this->fRunPlayTime);

	//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
	if (this->fRunPlayTime >= this->fRunTotalTime)
	{
		// �A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
		// �Đ����Ԃ�����������
		this->fRunPlayTime = 0.0f;
	}
}
}

// �ړ�����(��������)
void Enemy_Escape::Movement_Horizontal()
{
	/* �ړ���̍��W���擾(��������) */
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x + this->vecMove.x;
	vecNextPosition.y = this->vecPosition.y;
	vecNextPosition.z = this->vecPosition.z + this->vecMove.z;

	/* 1�t���[���ł̈ړ��ʂ𕪊����Ĕ��肷��� */
	/* ���ړ��ʂɉ����ĕ�����ݒ肷�� */
	int iMoveHitCheckCount = (int)VSize(VGet(this->vecMove.x, 0, this->vecMove.z));

	/* ���������ړ��� */
	VECTOR vecDevisionMove = VScale(this->vecMove, 1.0f / iMoveHitCheckCount);

	/* �������Ĉړ�������̍��W */
	VECTOR vecDevisionMovePosition = this->vecPosition;

	/* �����ŃI�u�W�F�N�g�ɐڐG���Ă��邩���� */

	{
		/* ������擾 */
		auto& PlatformList = ObjectList->GetPlatformList();

		/* ����ƐڐG���邩�m�F */
		for (auto* platform : PlatformList)
		{
			/* ����Ƃ̐ڐG���� */
			for (int i = 0; i < PLAYER_MOVE_COLLISION_MAX; i++)
			{
				/* �I�u�W�F�N�g�ƐڐG���Ă��邩�m�F */
				MV1_COLL_RESULT_POLY_DIM stHitPolyDim = platform->HitCheck_Capsule(this->stHorizontalCollision);

				/* �ڐG���Ă��邩�m�F */
				if (stHitPolyDim.HitNum > 0)
				{
					// �ڐG���Ă���ꍇ
					//�����G�t�F�N�g�����t���O�𖳌��ɂ���
					this->bEscapeEffectGenerated = false;

					//�ǂɓ����������̃t���O��L���ɂ���
					this->bWallHitFlg = true;

					//�ǂ̖@���x�N�g�����擾
					wallNormal = stHitPolyDim.Dim[0].Normal;
				}
			}
		}
	}
	/* �v���C���[�̍��W���ړ������� */
	this->vecPosition = vecNextPosition;
}

// �X�V
void Enemy_Escape::Update()
{
	/* SE���Đ��J�n�������̊m�F */
	if (this->bPlayeSeFlg == false)
	{
		// �Đ����Ă��Ȃ��ꍇ
		/* "�����L���L����"��SE�����[�v�Đ� */
		gpDataList_Sound->SE_PlaySound_Loop_3D(SE_ENEMY_RUN, this->vecPosition, SE_3D_SOUND_RADIUS);

		/* �Đ��t���O��L���ɂ��� */
		this->bPlayeSeFlg = true;
	}

	/* �o���b�g���X�g���擾 */
	auto& BulletList = ObjectList->GetBulletList();

	/* �v���C���[�U���ƐڐG���邩�m�F */
	for (auto* bullet : BulletList)
	{
		/* �I�u�W�F�N�g�^�C�v��"�e(�v���C���[)"���邢��"�ߐڍU��(�v���C���[)"�ł��邩�m�F */
		if ((bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER) || (bullet->iGetObjectType() == OBJECT_TYPE_MELEE_PLAYER))
		{
			// �e(�v���C���[)�̏ꍇ
			/* �e�Ƃ̐ڐG���� */
			if (bullet->HitCheck(this->stCollisionCapsule) == true)
			{
				// �ڐG���Ă���ꍇ
				/* �_���[�W���� */
				this->iNowHp -= 1;
			}
		}
	}

	/* �G�l�~�[�̈ړ����� */
	MoveEnemy();

	//�d�͏���
	Enemy_Gravity();

	//���������̈ړ�����
	Movement_Horizontal();

	/* HP��0�ȉ��ł��邩�m�F */
	if (this->iNowHp <= 0)
	{
		// HP��0�ȉ��ł���ꍇ
		/* "�����L���L����"��SE���~ */
		gpDataList_Sound->SE_PlaySound_Stop(SE_ENEMY_RUN);

		/* ���S�t���O��L���� */
		this->bDeadFlg = true;

		//�q�b�g�G�t�F�N�g���������t���O���������m�F
		if (this->bHitEffectGenerated == FALSE)
		{
			/* Hit�G�t�F�N�g�ǉ� */
			{
				/* ���Ԍo�߂ō폜�����G�t�F�N�g��ǉ� */
				EffectSelfDelete* AddEffect = new EffectSelfDelete();

				/* �G�t�F�N�g�ǂݍ��� */
				AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_hit/FX_hit")));

				/* �G�t�F�N�g�̍��W�ݒ� */
				AddEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

				/* �G�t�F�N�g�̉�]�ʐݒ� */
				AddEffect->SetRotation(this->vecRotation);

				/* �G�t�F�N�g�̍폜�����܂ł̎��Ԃ�ݒ� */
				AddEffect->SetDeleteCount(25);

				/* �G�t�F�N�g�̏����� */
				AddEffect->Initialization();

				/* ���X�g�ɓo�^ */
				{
					/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
					DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

					/* �G�t�F�N�g�����X�g�ɓo�^ */
					ObjectListHandle->SetEffect(AddEffect);
				}
				/* �U���q�b�g��SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_SLASH_HIT);

				//��e����
				DefeatAttack();

				//�q�b�g�G�t�F�N�g���������t���O��L���ɂ���
				this->bHitEffectGenerated = TRUE;
			}
		}

		//�����Œ�t���O�𖳌��ɂ���
		this->bDirectionFlg = false;

		//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
		MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);

		//���S���[�V�����̍Đ����Ԃ����Z
		this->fDiePlayTime += 2.5f;

		// ���S���[�V�������A�^�b�`
		this->iDieAttachIndex = MV1AttachAnim(this->iModelHandle, 6, -1, FALSE);

		//�A�^�b�`�������S���[�V�����̍Đ����Ԃ��Z�b�g
		MV1SetAttachAnimTime(this->iModelHandle, this->iDieAttachIndex, this->fDiePlayTime);

		// ���S���[�V�����̑��Đ����Ԃ��擾
		this->fDieTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iDieAttachIndex);


		// ���S���[�V�����̍Đ����Ԃ����Đ����ԂɒB�������m�F
		if (this->fDiePlayTime >= this->fDieTotalTime)
		{
			/* ���j���̏��������s */
			Defeat();

			//����SE�Đ�
			gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_DAMAGE, this->vecPosition, SE_3D_SOUND_RADIUS);
		}
		return;
	}
}
