/* 2025.03.13 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Missile_Air.h"

// �R���X�g���N�^
Enemy_Missile_Air::Enemy_Missile_Air() : Enemy_Basic()
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
	// �G�l�~�[���f���ɋ󒆂̃A�j���[�V�������A�^�b�`����
	this->iMissileAirAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, FALSE);
	// �A�^�b�`�����󒆃A�j���[�V�����̑��Đ����Ԃ��擾����
	this->iMissileAirAttachIndex = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMissileAirAttachIndex);
	this->bDirectionFlg = true;					// �����Œ�t���O
}

// �f�X�g���N�^
Enemy_Missile_Air::~Enemy_Missile_Air()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

// ������
void Enemy_Missile_Air::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();
}

// �G���ړ�������
void Enemy_Missile_Air::MoveEnemy()
{

	// �v���C���[�̍��W���擾
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

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


	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerY < ENEMY_Y_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x����z���̋�����1000�����̏ꍇ
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
void Enemy_Missile_Air::Player_Range_Missile_Shot()
{

	// �~�T�C���𐶐�
	this->pBulletRangeMissile = new BulletEnemyRangeMissile;

	//���ʉ��Đ�
	gpDataList_Sound->SE_PlaySound(SE_ENEMY_IKURA_ATTACK);

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
}

// �X�V
void Enemy_Missile_Air::Update()
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
		this->bDirectionFlg = false;
		//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
		MV1DetachAnim(this->iModelHandle, this->iMissileAirAttachIndex);

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
