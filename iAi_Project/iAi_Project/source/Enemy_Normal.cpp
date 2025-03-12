/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Normal.h"

// �R���X�g���N�^
Enemy_Normal::Enemy_Normal() : Enemy_Basic()
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Normal/Enemy_Normal");
	}

	this->pPlayer = ObjectList->GetCharacterPlayer();// �v���C���[

	this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;	// ���˃J�E���g
	this->iGuidanceCount = ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL;	// �U���J�E���g

	this->pEffectWarning = nullptr;	// �x���G�t�F�N�g
	this->bHitEffectGenerated = false;	// �q�b�g�G�t�F�N�g�����t���O

	/*���[�V�����֘A*/
	// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
	this->iNormalAttackAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, FALSE);
	// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
	this->fNormalAttackTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackAttachIndex);

	this->bNormalAttackMotionFlg = false;			// �U�����[�V�����t���O
	this->bNormalAttackNowMotionFlg = false;		// �U�������[�V�����t���O
	this->bNormalAttackEndMotionFlg = false;		// �U���I�����[�V�����t���O
	this->bNormalAttackEndLoopMotionFlg = false;	// �U���I�����[�v���[�V�����t���O
}

// �f�X�g���N�^
Enemy_Normal::~Enemy_Normal()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

// ������
void Enemy_Normal::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();
}

// �G���ړ�������
void Enemy_Normal::MoveEnemy()
{
	// �v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//�G�l�~�[�̌�����ݒ�
	this->vecRotation = VRot;

	//�G�l�~�[�̏c�������擾
	MV1SetRotationXYZ(iModelHandle, VRot);

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);


	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x����z���̋�����1000�����̏ꍇ
	{
		// �v���C���[���T�m�͈͓��ɂ���ꍇ
		iFiringCount--;	// ���˃J�E���g������

		//�U���J�E���g�����˃J�E���g���傫�����m�F
		if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
		{
			// �U���J�E���g�����˃J�E���g���傫���ꍇ
			/* �U���\���G�t�F�N�g�ǉ� */
			{
				/* �U���\���G�t�F�N�g�𐶐� */
				this->pEffectWarning = new EffectManualDelete();

				/* �G�t�F�N�g�̓ǂݍ��� */
				this->pEffectWarning->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet_warning/FX_e_bullet_warning")));

				/* �G�t�F�N�g�̍��W�ݒ� */
				this->pEffectWarning->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT, vecPosition.z));

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
		//���˃J�E���g��0�ȉ����m�F
		if (iFiringCount <= 0)
		{

			// ���f���̃t���[���O�Ԃ�\��
			MV1SetFrameVisible(iModelHandle, 0, TRUE);

			// ���f���̃t���[���Q�Ԃ�\��
			MV1SetFrameVisible(iModelHandle, 2, TRUE);
			// ���˃J�E���g��0�ȉ��̏ꍇ
			// �m�[�}���e�𔭎˂���
			Player_Range_Normal_Shot();

			// ���˃J�E���g��������
			this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;
		}
	}


}

// �m�[�}���e�̔���
void Enemy_Normal::Player_Range_Normal_Shot()
{
	// �v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	//�U���I�����[�v���[�V�����t���O�𖳌���
	this->bNormalAttackEndLoopMotionFlg = false;

	//�U�����[�V�����t���O��L����
	this->bNormalAttackMotionFlg = true;
}

// �G�l�~�[���f���A�j���[�V����
void Enemy_Normal::Enemy_Model_Animation()
{
	// �U�����[�V�����t���O���L�����m�F
	if (this->bNormalAttackMotionFlg)
	{
		// �U�����[�V�����t���O���L���̏ꍇ
		this->fNormalAttackPlayTime += 0.5f;
		// �Đ����Ԃ��Z�b�g����
		MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackAttachIndex, this->fNormalAttackPlayTime);

		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
		if (this->fNormalAttackPlayTime >= this->fNormalAttackTotalTime)
		{
			// �A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
			// �m�[�}���e�𐶐�
			this->pBulletRangeNormal = new BulletEnemyRangeNormal;
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
			this->pBulletRangeNormal->SetPosition(VAdd(this->vecPosition, vecAdd));

			// �ړ�����e�̌�����ݒ�
			this->pBulletRangeNormal->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));
	
			//������
			this->pBulletRangeNormal->Initialization();

			//�o���b�g���X�g�ɒǉ�
			ObjectList->SetBullet(this->pBulletRangeNormal);

			// �A�^�b�`�����U���A�j���[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, iNormalAttackAttachIndex);

			// �Đ����Ԃ�����������
			this->fNormalAttackPlayTime = 0.0f;

			// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
			this->iNormalAttackNowAttachIndex = MV1AttachAnim(this->iModelHandle, 1, -1, FALSE);

			// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
			this->fNormalAttackNowTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackNowAttachIndex);

			this->bNormalAttackNowMotionFlg = true;
			// �U�����[�V�����t���O�𖳌���
			this->bNormalAttackMotionFlg = false;
		}
	}

	if (this->bNormalAttackNowMotionFlg)
	{
		this->fNormalAttackNowPlayTime += 0.5f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackNowAttachIndex, this->fNormalAttackNowPlayTime);

		if (this->fNormalAttackNowPlayTime >= this->fNormalAttackNowTotalTime)
		{
			// �A�^�b�`�����A�j���[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, iNormalAttackNowAttachIndex);
			this->fNormalAttackNowPlayTime = 0.0f;
			// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
			this->iNormalAttackEndAttachIndex = MV1AttachAnim(this->iModelHandle, 4, -1, FALSE);
			// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
			this->fNormalAttackEndTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackEndAttachIndex);

			this->bNormalAttackNowMotionFlg = false;
			this->bNormalAttackEndMotionFlg = true;
		}
	}

	if (this->bNormalAttackEndMotionFlg)
	{
		this->fNormalAttackEndPlayTime += 0.5f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackEndAttachIndex, this->fNormalAttackEndPlayTime);

		if (this->fNormalAttackEndPlayTime >= this->fNormalAttackEndTotalTime)
		{
			// �A�^�b�`�����A�j���[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, iNormalAttackEndAttachIndex);
			this->fNormalAttackEndPlayTime = 0.0f;
			// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
			this->iNormalAttackEndLoopAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, TRUE);
			// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
			this->fNormalAttackEndLoopTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackEndLoopAttachIndex);

			this->bNormalAttackEndMotionFlg = false;
			this->bNormalAttackEndLoopMotionFlg = true;
		}
	}

	if (this->bNormalAttackEndLoopMotionFlg)
	{
		this->fNormalAttackEndLoopPlayTime += 0.5f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackEndLoopAttachIndex, this->fNormalAttackEndPlayTime);

		if (this->fNormalAttackEndPlayTime >= this->fNormalAttackEndLoopTotalTime)
		{
			this->fNormalAttackEndLoopPlayTime = 0.0f;
			this->bNormalAttackEndLoopMotionFlg = false;
			// �A�j���[�V�����̃��[�v���I��������A�ŏ��̍U�����[�V�����t���O���ēx�L����
			this->bNormalAttackMotionFlg = true;
		}
	}
}

// �X�V
void Enemy_Normal::Update()
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
		//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackNowAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackEndAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackEndLoopAttachIndex);

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
