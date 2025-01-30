/* 2025.01.30 �ΐ�q�� �t�@�C���쐬 */

#include "BulletEnemyRangeMissile.h"

/* �ߐڍU��(��)�N���X�̒�` */

// �R���X�g���N�^
BulletEnemyRangeMissile::BulletEnemyRangeMissile() : BulletBase()
{
	/* ������ */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// �I�u�W�F�N�g�̎�ނ�"�e(�v���C���[)"�ɐݒ�
	this->eEffect = nullptr;

	/* ���ǉ� */
	iDeleteCount = 350;
}

// �f�X�g���N�^
BulletEnemyRangeMissile::~BulletEnemyRangeMissile()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
	this->eEffect->SetDeleteFlg(true);
}

// ������
void BulletEnemyRangeMissile::Initialization()
{
	/* �����蔻��ݒ� */
	{
		this->stCollisionSqhere.vecSqhere = this->vecPosition;
		this->stCollisionSqhere.fSqhereRadius = 50.0f;
	}
	/* �G�t�F�N�g�ǉ� */
	{
		/* �~�T�C���G�t�F�N�g�𐶐� */
		this->eEffect = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->eEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->eEffect->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->eEffect->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̏����� */
		this->eEffect->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->eEffect);
		}
	}
}

void BulletEnemyRangeMissile::BulletEnemyRangeMissileMove()
{
	CharacterBase* player = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();
	if (iDeleteCount >= 345)
	{
		playerPos.y += 60; // y���W��60����������
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition)); // �v���C���[�̈ʒu�Ɍ������������X�V
		this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 18));
	}
	else if(iDeleteCount >= 230)
	{
		this->vecDirection = VGet(0, 1, 0);
		//this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 30));
	}
	else if (iDeleteCount >= 190)
	{
		playerPos.y += 60; // y���W��60����������
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition)); // �v���C���[�̈ʒu�Ɍ������������X�V
		this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 70));
	}
	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 70));
	this->stCollisionSqhere.vecSqhere = this->vecPosition;
	this->eEffect->SetPosition(this->vecPosition);
}

// �X�V
void BulletEnemyRangeMissile::Update()
{
	/* ������ */
	// �{���̓v���C���[���ō폜�t���O��ݒ肷��\��
	if (iDeleteCount > 0)
	{
		iDeleteCount--;
	}
	else
	{
		this->bDeleteFlg = true;
	}
	BulletEnemyRangeMissileMove();
}
