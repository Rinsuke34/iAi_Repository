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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy");
	}


	this->pPlayer = ObjectList->GetCharacterPlayer();
	this->pEffect = nullptr;

	this->iFiringCount = ENEMY_MISSILE_INTERVAL;	// ���˃J�E���g
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

	/* HP��0�ȉ��ł��邩�m�F */
	if (this->iNowHp <= 0)
	{
		// HP��0�ȉ��ł���ꍇ
		/* ���j���̏��������s */
		Defeat();

		return;
	}

	// �G�l�~�[���ړ�������
	MoveEnemy();

	// �R���W�����Z�b�g
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
