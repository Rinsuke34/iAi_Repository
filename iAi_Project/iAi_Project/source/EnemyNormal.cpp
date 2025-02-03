/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */
#include "EnemyNormal.h"

// �R���X�g���N�^
NormalEnemy::NormalEnemy() : EnemyBasic()
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy_Kari_0127");
	}

	this->eEffect = nullptr;
}

// �f�X�g���N�^
NormalEnemy::~NormalEnemy()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

// ������
void NormalEnemy::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();
}

void NormalEnemy::MoveEnemy()
{
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	VECTOR VRot = VGet(0, 0, 0); // ��]��
	VRot.y = atan2f(this->vecPosition.x -playerPos.x, this->vecPosition.z - playerPos.z); // �v���C���[�̕���������
	this->vecRotation = VRot; // ��]�ʂ�ݒ�
	if(CheckHitKey(KEY_INPUT_P))
	{
		Player_Range_Normal();
	}
}

void NormalEnemy::Player_Range_Normal()
{
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();
	this-> pBulletRangeNormal = new BulletEnemyRangeNormal;
	/* �U���̐��������̐ݒ� */
	/* �U�����W���Z�o */
	VECTOR vecAdd;
	// ����
	vecAdd.x = 0.f;
	vecAdd.y = 0.f;
	vecAdd.z = 0.f;
	vecAdd = VNorm(vecAdd);
	vecAdd = VScale(vecAdd, 100);
	// ����
	vecAdd.y = 100 / 2.f;
	vecAdd.x = PLAYER_WIDE / 2.f;

	// �U���������W���G�l�~�[�������Ă�������ɐݒ�
	this->pBulletRangeNormal->SetPosition(VAdd(this->vecPosition, vecAdd));

	// �U���̌�����ݒ�
	this->pBulletRangeNormal->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));
	
	//������
	this->pBulletRangeNormal->Initialization();

	//�o���b�g���X�g�ɒǉ�
	ObjectList->SetBullet(this->pBulletRangeNormal);


	
}

// �X�V
void NormalEnemy::Update()
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

	if (this->iGetNowHP() <= 0)
	{
		// �폜�t���O��L���ɂ���
		this->SetDeleteFlg(true);
	}

	MoveEnemy();

	//Player_Range_Normal();
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
