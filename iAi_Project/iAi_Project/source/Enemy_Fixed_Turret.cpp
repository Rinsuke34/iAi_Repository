/* 2025.03.17 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Fixed_Turret.h"

// �R���X�g���N�^
Enemy_Fixed_Turret::Enemy_Fixed_Turret() : Enemy_Basic()
{

	/* �I�u�W�F�N�g�̃n���h�� */
	this->pBulletRangeNormal = nullptr;	// �ߐڍU��(��)�̒e
	// HP��ݒ�
	this->iMaxHp = 1;
	this->iNowHp = 1;
	this->iObjectType = OBJECT_TYPE_ENEMY;	// �I�u�W�F�N�g�̎��

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
		this->iModelHandle = this->iModelturretHandle = ModelListHandle->iGetModel("Enemy/Enemy_EyeBall/Enemy_EyeBall");

	}

	this->pPlayer = ObjectList->GetCharacterPlayer();// �v���C���[

	this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;	// ���˃J�E���g
	this->iGuidanceCount = ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL;	// �U���J�E���g
	this->bHitEffectGenerated = false;	// �q�b�g�G�t�F�N�g�����t���O
	this->bWarningEffectFlg = true;				// �x���G�t�F�N�g�t���O
	this->bShotFlg = false;						// �V���b�g�t���O

	this->bDirectionFlg = true;					// �����Œ�t���O
	this->bUpFlg = false;						// ��t���O
	this->bDownFlg = false;						// ���t���O
	this->bMissile = false;						// �~�T�C���t���O

	//�ێ��J�E���g��������
	this->iMaintainCount = 60;
}

// �f�X�g���N�^
Enemy_Fixed_Turret::~Enemy_Fixed_Turret()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

// ������
void Enemy_Fixed_Turret::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();
	
	UpdataLightFrame();
}



// �G���ړ�������
void Enemy_Fixed_Turret::MoveEnemy()
{

	// �v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);
	VECTOR VYRot = VGet(0, 0, 0);

	// �v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VECTOR centerPos = VGet(playerPos.x, playerPos.y, playerPos.z);
	float deltaX = this->vecPosition.x - centerPos.x;
	float deltaZ = this->vecPosition.z - centerPos.z;


	VRot.y = atan2f(deltaX, deltaZ);
	VYRot.y = atan2f(deltaX, deltaZ);
	//���݌��Ă���������擾
	VECTOR vecRot = MV1GetRotationXYZ(iModelHandle);
	if (vecPosition.z > centerPos.z)
	{
		VRot.x = atan2f(this->vecPosition.y - centerPos.y, this->vecPosition.z - centerPos.z) * -1;
	}
	else if (vecPosition.z < centerPos.z)
	{
		VRot.x = atan2f(centerPos.y - this->vecPosition.y, centerPos.z - this->vecPosition.z);
	}

	if (this->bShotFlg == false)
	{
		if (VRot.x >= -0.5)
		{
			this->vecRotation = VRot;
			MV1SetRotationXYZ(iModelHandle, VRot);
		}
		if (VRot.x <= 0.9)
		{
			this->vecRotation = VRot;
			MV1SetRotationXYZ(iModelHandle, VRot);
		}
		if (VRot.x > 0.9 && VRot.x > 0)
		{
			//���݂�VRot.x�̒l��ۑ�
			float fVRotX = VRot.x;
			this->vecRotation = VGet(1, VYRot.y, VYRot.z);
		}
		if (VRot.x < -0.5 && VRot.x < 0)
		{
			//���݂�VRot.x�̒l��ۑ�
			float fVRotX = VRot.x;
			this->vecRotation = VGet(-0.5,VYRot.y,VYRot.z);
		}
		
	}

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);


	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerY < ENEMY_Y_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x����z���̋�����1000�����̏ꍇ
	{
		// �v���C���[���T�m�͈͓��ɂ���ꍇ
		iFiringCount--;	// ���˃J�E���g������

		//�U���J�E���g�����˃J�E���g���傫�����m�F
		if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
		{
			// �U���J�E���g�����˃J�E���g���傫���ꍇ
			if (this->bWarningEffectFlg == true)	// �x���G�t�F�N�g�t���O���L���̏ꍇ
			{
				this->bWarningEffectFlg = false;




			

				/* �U���\���G�t�F�N�g�ǉ� */
				{
					/* �U���\���G�t�F�N�g�𐶐� */
					this->pEffectWarning = new EffectManualDelete();

					/* �G�t�F�N�g�̓ǂݍ��� */
					this->pEffectWarning->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet_warning/FX_e_bullet_warning")));

					this->vecEffectPos = MV1GetFramePosition(this->iModelHandle, 2);

					/* �G�t�F�N�g�̍��W�ݒ� */
					this->pEffectWarning->SetPosition(VGet(vecEffectPos.x, vecEffectPos.y, vecEffectPos.z));

					/* �G�t�F�N�g�̉�]�ʐݒ� */
					this->pEffectWarning->SetRotation(this->vecRotation);

					/* �G�t�F�N�g�̏����� */
					this->pEffectWarning->Initialization();

					/* �G�t�F�N�g�����X�g�ɓo�^ */
					{
						/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
						DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
						/* �G�t�F�N�g�����X�g�ɓo�^ */
						ObjectListHandle->SetEffect(this->pEffectWarning);
					}
				}
			}
				//�ێ��J�E���g�����Z
				this->iMaintainCount--;

				if (iMaintainCount <= 0)
			{
					this->bShotFlg = true;

					this->bUpFlg = true;

					this->bTestFlg = false;

					this->iMaintainCount = 60;
				}
			}
		}

	if (bUpFlg == true)
	{
		this->vecRotation = VGet(vecRotation.x+0.1, vecRotation.y, vecRotation.z);

		if (vecRotation.x >= 1.5)
		{
			this->vecRotation = VGet(1.5, vecRotation.y, vecRotation.z);

			this->bMissile = true;
			if (this->bMissile == true && iMaintainCount == 60)
			{
				// �~�T�C���𐶐�
				this->pBulletRangeMissile = new BulletEnemyRangeMissile;

				// ���ʉ��Đ�
				gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_IKURA_ATTACK, this->vecPosition, SE_3D_SOUND_RADIUS);

				/* �U���̐��������̐ݒ� */
				/* �U�����W���Z�o */

				//�G�l�~�[�̌�����������
				VECTOR vecAdd = VGet(0, 0, 0);

				// ���˂����������ݒ�
				vecAdd = VNorm(vecAdd);

				//���f���̂Q�Ԗڂ̃t���[���̈ʒu���擾
				VECTOR vecFramePos = MV1GetFramePosition(iModelHandle, 2);

				// ���˂����鍂���ƕ���ݒ�
				vecAdd.y += PLAYER_HEIGHT / 2.f;
				//vecAdd.x = PLAYER_WIDE / 2.f;

				// �U���������W���G�l�~�[�������Ă�������ɐݒ�
				this->pBulletRangeMissile->SetPosition(VAdd(vecFramePos, vecAdd));

				// �ړ�����e�̌�����ݒ�
				this->pBulletRangeMissile->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));

				//������
				this->pBulletRangeMissile->Initialization();

				//�o���b�g���X�g�ɒǉ�
				ObjectList->SetBullet(this->pBulletRangeMissile);

				this->bMissile = false;

				this->bUpFlg = false;

				this->bTestFlg2 = true;
			}
		}
	}

	if (this->bTestFlg2 == true)
	{
		this->vecRotation = VGet(vecRotation.x - 0.1, vecRotation.y, vecRotation.z);

		//�G�l�~�[�̂��������v���C���[�̂��������덷��0.1�ȏ�܂���0.1�ȉ����m�F
		if (vecRotation.x < VRot.x)
		{
			this->vecRotation = VGet(VRot.x, vecRotation.y, vecRotation.z);

			this->bTestFlg3 = true;

			this->bTestFlg2 = false;

		}
		}

	if (this->bTestFlg3 == true)
		{
		// �v���C���[�̍��W���擾
		VECTOR playerPos = pPlayer->vecGetPosition();

		// �v���C���[�̕������������߂̊p�x���v�Z
		this->fTargetAngle = atan2f(playerPos.x - this->vecPosition.x, playerPos.z - this->vecPosition.z);

		// 180�x���΂������悤�Ɋp�x�𒲐�
		this->fTargetAngle += DX_PI_F;

		// ���݂̃G�l�~�[�̌���
		this->fCurrentAngle = this->vecRotation.y;
		
		// ��]����������
		this->fAngleDifference = this->fTargetAngle - this->fCurrentAngle;
		if (this->fAngleDifference > DX_PI_F) this->fAngleDifference -= 2 * DX_PI_F;
		if (this->fAngleDifference < -DX_PI_F) this->fAngleDifference += 2 * DX_PI_F;

		// �E��肩����肩�𔻒f���ĉ�]
		if (this->fAngleDifference > 0)
		{
			this->vecRotation.y += 0.1f; // �E���
}
		else
		{
			this->vecRotation.y -= 0.1f; // �����
		}

		// �G�l�~�[���v���C���[�̕��������S�Ɍ��������m�F
		if (fabs(this->fAngleDifference) < 0.1f)
{
			this->vecRotation.y = fTargetAngle;
			this->bTestFlg3 = false;
	this->bWarningEffectFlg = true;
			this->bShotFlg = false;
		}
}
}


// �X�V
void Enemy_Fixed_Turret::Update()
{
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
	// �G�l�~�[���ړ�������
	MoveEnemy();

	Enemy_Gravity();

	/* HP��0�ȉ��ł��邩�m�F */
	if (this->iNowHp <= 0)
	{
		// HP��0�ȉ��ł���ꍇ
		/* ���S�t���O��L���� */
		this->bDeadFlg = true;

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
		/* ���j���̏��������s */
		Defeat();

		//����SE�Đ�
		gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_DAMAGE, this->vecPosition, SE_3D_SOUND_RADIUS);
	}


	// �R���W�����Z�b�g
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

// �`��
void Enemy_Fixed_Turret::Draw()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
}