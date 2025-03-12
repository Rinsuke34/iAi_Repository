/* 2025.01.30 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Missile.h"

// �R���X�g���N�^
Enemy_Missile::Enemy_Missile() : Enemy_Basic()
{

	/* �I�u�W�F�N�g�̃n���h�� */
	this->pBulletRangeMissile = nullptr;	// �~�T�C���̒e
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Missile/Enemy_Missile");
	}


	this->pPlayer = ObjectList->GetCharacterPlayer();
	this->bHitEffectGenerated = false;	// �q�b�g�G�t�F�N�g�����t���O
	this->iFiringCount = ENEMY_MISSILE_INTERVAL;	// ���˃J�E���g
	/*���[�V�����֘A*/
	// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
	this->iMissileAttackAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, FALSE);
	// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
	this->fMissileAttackTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMissileAttackAttachIndex);

	this->bMissileAttackMotionFlg = false;			// �U�����[�V�����t���O
	this->bMissileAttackNowMotionFlg = false;		// �U�������[�V�����t���O
	this->bMissileAttackEndMotionFlg = false;		// �U���I�����[�V�����t���O
	this->bMissileAttackEndLoopMotionFlg = false;	// �U���I�����[�v���[�V�����t���O
}

// �f�X�g���N�^
Enemy_Missile::~Enemy_Missile()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

// ������
void Enemy_Missile::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();
}

// �G���ړ�������
void Enemy_Missile::MoveEnemy()
{
	// �v���C���[�̍��W���擾
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//�G�l�~�[�̌�����ݒ�
	this->vecRotation = VRot;

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);


	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x����z���̋�����1000�����̏ꍇ
	{
		// �v���C���[���T�m�͈͓��ɂ���ꍇ
		// �~�T�C�����˃J�E���g�����Z
		iFiringCount--;

		//���˃J�E���g��0�ȉ����m�F
		if (iFiringCount <= 0)
		{
			// ���˃J�E���g��0�ȉ��̏ꍇ

		// �~�T�C���𔭎˂���
		Player_Range_Missile_Shot();

			// ���˃J�E���g��������
			this->iFiringCount = ENEMY_MISSILE_INTERVAL;
		}
	}
}

// �~�T�C���e�̔���
void Enemy_Missile::Player_Range_Missile_Shot()
{
	//�U���I�����[�v���[�V�����t���O�𖳌���
	this->bMissileAttackEndLoopMotionFlg = false;

	//�U�����[�V�����t���O��L����
	this->bMissileAttackMotionFlg = true;

	
}

// �G�l�~�[���f���A�j���[�V����
void Enemy_Missile::Enemy_Model_Animation()
{
	// �U�����[�V�����t���O���L�����m�F
	if (this->bMissileAttackMotionFlg)
	{
		// �U�����[�V�����t���O���L���̏ꍇ
		this->fMissileAttackPlayTime += 0.5f;
		// �Đ����Ԃ��Z�b�g����
		MV1SetAttachAnimTime(this->iModelHandle, this->iMissileAttackAttachIndex, this->fMissileAttackPlayTime);

		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
		if (this->fMissileAttackPlayTime >= this->fMissileAttackTotalTime)
		{
			// �A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
	// �~�T�C���𐶐�
	this->pBulletRangeMissile = new BulletEnemyRangeMissile;

	/* �U���̐��������̐ݒ� */
	/* �U�����W���Z�o */

	//�G�l�~�[�̌�����������
	VECTOR vecAdd = VGet(0, 0, 0);

	// ���˂����������ݒ�
	vecAdd = VNorm(vecAdd);

	// ���˂����鍂���ƕ���ݒ�
	vecAdd.y = PLAYER_HEIGHT / 2.f;
	vecAdd.x = PLAYER_WIDE / 2.f;

	// �U���������W���G�l�~�[�������Ă�������ɐݒ�
	this->pBulletRangeMissile->SetPosition(VAdd(this->vecPosition, vecAdd));

	// �ړ�����e�̌�����ݒ�
	this->pBulletRangeMissile->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));

	//������
	this->pBulletRangeMissile->Initialization();

	//�o���b�g���X�g�ɒǉ�
	ObjectList->SetBullet(this->pBulletRangeMissile);
			// �A�^�b�`�����U���A�j���[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, iMissileAttackAttachIndex);
			// �Đ����Ԃ�����������
			this->fMissileAttackPlayTime = 0.0f;
			// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
			this->iMissileAttackNowAttachIndex = MV1AttachAnim(this->iModelHandle, 1, -1, FALSE);
			// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
			this->fMissileAttackNowTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMissileAttackNowAttachIndex);

			this->bMissileAttackNowMotionFlg = true;
			// �U�����[�V�����t���O�𖳌���
			this->bMissileAttackMotionFlg = false;
		}
	}

	if (this->bMissileAttackNowMotionFlg)
	{
		this->fMissileAttackNowPlayTime += 0.5f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iMissileAttackNowAttachIndex, this->fMissileAttackNowPlayTime);

		if (this->fMissileAttackNowPlayTime >= this->fMissileAttackNowTotalTime)
		{
			// �A�^�b�`�����A�j���[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, iMissileAttackNowAttachIndex);
			this->fMissileAttackNowPlayTime = 0.0f;
			// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
			this->iMissileAttackEndAttachIndex = MV1AttachAnim(this->iModelHandle, 4, -1, FALSE);
			// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
			this->fMissileAttackEndTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMissileAttackEndAttachIndex);

			this->bMissileAttackNowMotionFlg = false;
			this->bMissileAttackEndMotionFlg = true;
		}
	}

	if (this->bMissileAttackEndMotionFlg)
	{
		this->fMissileAttackEndPlayTime += 0.5f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iMissileAttackEndAttachIndex, this->fMissileAttackEndPlayTime);

		if (this->fMissileAttackEndPlayTime >= this->fMissileAttackEndTotalTime)
		{
			// �A�^�b�`�����A�j���[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, iMissileAttackEndAttachIndex);
			this->fMissileAttackEndPlayTime = 0.0f;
			// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
			this->iMissileAttackEndLoopAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, TRUE);
			// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
			this->fMissileAttackEndLoopTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMissileAttackEndLoopAttachIndex);

			this->bMissileAttackEndMotionFlg = false;
			this->bMissileAttackEndLoopMotionFlg = true;
		}
	}

	if (this->bMissileAttackEndLoopMotionFlg)
	{
		this->fMissileAttackEndLoopPlayTime += 0.5f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iMissileAttackEndLoopAttachIndex, this->fMissileAttackEndPlayTime);

		if (this->fMissileAttackEndPlayTime >= this->fMissileAttackEndLoopTotalTime)
		{
			this->fMissileAttackEndLoopPlayTime = 0.0f;
			this->bMissileAttackEndLoopMotionFlg = false;
			// �A�j���[�V�����̃��[�v���I��������A�ŏ��̍U�����[�V�����t���O���ēx�L����
			this->bMissileAttackMotionFlg = true;
		}
	}
}

// �X�V
void Enemy_Missile::Update()
{
	/* �o���b�g���X�g���擾 */
	auto& BulletList = ObjectList->GetBulletList();

	/* �v���C���[�U���ƐڐG���邩�m�F */
	for (auto* bullet : BulletList)
	{
		/* �I�u�W�F�N�g�^�C�v��"�e(�v���C���[)"�ł��邩�m�F */
		if (bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER)
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

	// �G�l�~�[���f���A�j���[�V����
	Enemy_Model_Animation();

	/* HP��0�ȉ��ł��邩�m�F */
	if (this->iNowHp <= 0)
	{
		/* ���S�t���O��L���� */
		this->bDeadFlg = true;

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
		//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
		MV1DetachAnim(this->iModelHandle, this->iMissileAttackAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iMissileAttackNowAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iMissileAttackEndAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iMissileAttackEndLoopAttachIndex);

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
			gpDataList_Sound->SE_PlaySound(SE_ENEMY_DAMAGE);
		}
		return;
	}

	// �R���W�����Z�b�g
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
