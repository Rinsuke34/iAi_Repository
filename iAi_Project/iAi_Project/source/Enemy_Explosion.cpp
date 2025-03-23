/* 2025.01.28 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Explosion.h"

// �R���X�g���N�^
Enemy_Explosion::Enemy_Explosion() : Enemy_Basic()
{


	this->iXdistance = ENEMY_X_DISTANCE;		// X���̋���
	this->iZdistance = ENEMY_Z_DISTANCE;		// Z���̋���
	this->fSpeed = ENEMY_CHASE_SPEED;				// �ړ����x
	this->iDetonationRange = ENEMY_DETONATION_RANGE;	//�N���͈͓�
	this->fGravity = ENEMY_GRAVITY_SREED;				// �d��
	this->iBlastRange		= ENEMY_EXPLOSION_RANGE;	// �����͈͓�

	// HP��ݒ�
	this->iMaxHp = 1;
	this->iNowHp = 1;
	this->iObjectType = OBJECT_TYPE_ENEMY;	// �I�u�W�F�N�g�̎��

	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Explosion/Enemy_Explosion");
	}
	this->iStopCount = 0;
	this->pEffect = nullptr;
    this->bEffectGenerated = false;
	this->bFallFlg = true;
	this->bStopFlg = true;
	this->bCountFlg = false;
	this->bBlastFlg = false;
	this->bHitEffectGenerated = false;	// �q�b�g�G�t�F�N�g�����t���O
	this->bDirectionFlg = true;					// �����Œ�t���O
	this->bChaseFlg = true;						// �ǐՃt���O
}

// �f�X�g���N�^
Enemy_Explosion::~Enemy_Explosion()
{

}

// ������
void Enemy_Explosion::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();

	UpdataLightFrame();
}

void Enemy_Explosion::MoveEnemy()
{
	this->stHorizontalCollision.fCapsuleRadius = 50;
	this->stHorizontalCollision.vecCapsuleTop = VAdd(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z), VGet(0, 50, 0));
	this->stHorizontalCollision.vecCapsuleBottom = VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z);

	// �v���C���[�̍��W���擾
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//�G�l�~�[���������Ă��邩�m�F
	if (this->bFallFlg == false)
	{
		//�G�l�~�[���������Ă���ꍇ
		//�G�l�~�[���ړ����Ă��������̋t������10f�ړ�
		fSpeed = 40;
		this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(VSub(this->vecPosition, playerPos)), fSpeed));
		fSpeed = 0;
		this->bCountFlg = true;
	}
	if (this->bCountFlg = true)
	{
		iStopCount++;
	}
	if (iStopCount > 180)
	{
		this->bStopFlg = true;
		iStopCount = 0;
		this->fSpeed = ENEMY_CHASE_SPEED;
	}
	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	// �d�͏���
	this->vecMove.y -= ENEMY_GRAVITY_SREED;
	this->vecPosition.y += this->vecMove.y;

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	if (this->bDirectionFlg == true)
	{
	//�G�l�~�[�̌�����ݒ�
	this->vecRotation = VRot;
		//�G�l�~�[�̌������擾
		MV1SetRotationXYZ(iModelHandle, VRot);
	}

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	if (bChaseFlg == TRUE)
	{

	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerY < ENEMY_Y_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE && this->bStopFlg == true)  // x����z���̋�����1000����y��������500�����̏ꍇ
	{
		// �v���C���[���T�m�͈͓��ɂ���ꍇ
        // �T�m�͈͓��ɂ���G�l�~�[�̂ݏ������s��
        if (!bEffectGenerated)
		{
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


			// �G�l�~�[���v���C���[�ɋ߂Â���
			VECTOR direction = VNorm(VSub(playerPos, this->vecPosition));

			// �v���C���[�Ɍ����������Ƒ��x���擾
			this->vecPosition = VAdd(this->vecPosition, VScale(direction, fSpeed));

			// �v���C���[���G�l�~�[�̋N���͈͓��ɓ��������ǂ������m�F
			if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_DETONATION_RANGE)
			{
				this->bBlastFlg = true;
				
			}
		}
	}
	if (!bEffectGenerated)
	{
		if (this->bBlastFlg == true)
		{
				// �v���C���[���G�l�~�[�̋N���͈͓��ɓ������ꍇ
				//���胂�[�V�������f�^�b�`����
				MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);

				//�������[�V�������A�^�b�`����
				this->iExplosionAttachIndex = MV1AttachAnim(this->iModelHandle, 5, -1, FALSE);



                // �N���\���G�t�F�N�g�𐶐�
                this->pEffectDetonation = new EffectManualDelete();

                // �G�t�F�N�g�̓ǂݍ���
                this->pEffectDetonation->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_suicide_light/FX_e_suicide_light")));

                // �G�t�F�N�g�̍��W�ݒ�
                this->pEffectDetonation->SetPosition(this->vecPosition);

                // �G�t�F�N�g�̉�]�ʐݒ�
                this->pEffectDetonation->SetRotation(this->vecRotation);

                // �G�t�F�N�g�̏�����
                this->pEffectDetonation->Initialization();

                // �G�t�F�N�g�����X�g�ɓo�^
                {
                    // "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾
                    DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
                    // �G�t�F�N�g�����X�g�ɓo�^
                    ObjectListHandle->SetEffect(pEffectDetonation);
                }

				//�N��SE�Đ�
				gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_WARNING_EXPLOSION, this->vecPosition, SE_3D_SOUND_RADIUS);

                // �G�t�F�N�g�����t���O��ݒ�
                bEffectGenerated = true;
			}
		}
        else
		{
            // �G�t�F�N�g���Đ������ǂ����m�F
            if (IsEffekseer3DEffectPlaying(this->pEffectDetonation->iGetEffectHandle()))
			{
                // �G�t�F�N�g���Đ��I�����Ă���ꍇ
				/* ���j���̏��������s */
				Defeat();

				//�v���C���[�������͈͓��ɂ��邩�ǂ������m�F
				if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_EXPLOSION_RANGE)
				{
					//�v���C���[�������͈͓��ɂ���ꍇ
				//�v���C���[�𐁂���΂�
				this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);

				//�v���C���[��HP������
				this->PlayerStatusList->SetPlayerNowHp(this->PlayerStatusList->iGetPlayerNowHp() - 1);
				}
			}
		}
	}
	
}

void Enemy_Explosion::Enemy_Gravity()
{
	// �ړ���̍��W���擾(��������)
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z = this->vecPosition.z;

	// ��l���̏㕔���̓����蔻�肩�牺�����֌������������쐬
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 9999;

	// ������擾
	auto& PlatformList = ObjectList->GetPlatformList();

	//// ����ƐڐG���邩�m�F
	bool bHitFlg = false;
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// �ڐG���Ă��邩�m�F
		if (stHitPolyDim.HitFlag == 1)
		{
			// �ڐG���Ă���ꍇ
				this->vecPosition.y = stHitPolyDim.HitPosition.y;
				this->vecMove.y = 0; // �������x�����Z�b�g
			this->bFallFlg = true;
			this->bStopFlg = true;
			bHitFlg = true;//�ڐG�t���O��L���ɂ���
					break;
				}
		//�ڐG�t���O���������m�F
		if (!bHitFlg)
		{
			//�ڐG�t���O�������̏ꍇ
			this->fGravity = 0;
			this->vecMove.y = 0;
			this->bFallFlg = false;
			this->bStopFlg = false;
			}
		}
}

// �G�l�~�[�̐�������
void Enemy_Explosion::Movement_Horizontal()
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
					this->bChaseFlg = false;
					break;
				}
			}
		}
	}

	/* �v���C���[�̍��W���ړ������� */
	this->vecPosition = vecNextPosition;
}

// �X�V
void Enemy_Explosion::Update()
{
    // �o���b�g���X�g���擾
	auto& BulletList = ObjectList->GetBulletList();

    // �v���C���[�U���ƐڐG���邩�m�F
	for (auto* bullet : BulletList)
	{
		/* �I�u�W�F�N�g�^�C�v��"�e(�v���C���[)"���邢��"�ߐڍU��(�v���C���[)"�ł��邩�m�F */
		if ((bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER) || (bullet->iGetObjectType() == OBJECT_TYPE_MELEE_PLAYER))
		{
			// �e(�v���C���[)�̏ꍇ
            // �e�Ƃ̐ڐG����
			if (bullet->HitCheck(this->stCollisionCapsule) == true)
			{
				// �ڐG���Ă���ꍇ
                // �_���[�W����
				this->iNowHp -= 1;
			}
		}
	}

	if (this->iNowHp <= 0)
	{
		/* ���S�t���O��L���� */
		this->bDeadFlg = true;

		/* �����\���G�t�F�N�g����x�ł��������������m�F */
		if (this->pEffectDetonation != nullptr)
		{
			// ��x�ł����������ꍇ
			//�����\���G�t�F�N�g�̍폜�t���O��L����
			this->pEffectDetonation->SetDeleteFlg(true);

			//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
			MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);
			MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);
			MV1DetachAnim(this->iModelHandle, this->iExplosionAttachIndex);

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
			}
		}
	}

	/* HP��0�ȉ��ł��邩�m�F */
	if (this->iNowHp <= 0)
	{
		// HP��0�ȉ��ł���ꍇ

		if (this->bHitEffectGenerated == FALSE)
		{
			/* Hit�G�t�F�N�g�ǉ� */
			{
				/* ���Ԍo�߂ō폜�����G�t�F�N�g��ǉ� */
				EffectManualDelete* AddEffect = new EffectManualDelete();

				/* �G�t�F�N�g�ǂݍ��� */
				AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_hit/FX_hit")));

				/* �G�t�F�N�g�̍��W�ݒ� */
				AddEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

				/* �G�t�F�N�g�̉�]�ʐݒ� */
				AddEffect->SetRotation(this->vecRotation);

				/* �G�t�F�N�g�̏����� */
				AddEffect->Initialization();

				/* ���X�g�ɓo�^ */
				{
					/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
					DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
					/* �G�t�F�N�g�����X�g�ɓo�^ */
					ObjectListHandle->SetEffect(AddEffect);
		}


				this->bHitEffectGenerated = TRUE;
			}
		}
		this->bDirectionFlg = false;
		//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
		MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iExplosionAttachIndex);

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

	// �G�l�~�[���ړ�������
	MoveEnemy();

	Enemy_Gravity();

	Movement_Horizontal();

	CollisionDraw();

	// �R���W�����Z�b�g
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}



//�R���W�����`��
void Enemy_Explosion::CollisionDraw()
{
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, GetColor(255, 0, 0));

	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

	DrawCapsule3D(this->stHorizontalCollision.vecCapsuleTop, this->stHorizontalCollision.vecCapsuleBottom, this->stHorizontalCollision.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
}