/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */

#include "BulletEnemyRangeNormal.h"

/* �ߐڍU��(��)�N���X�̒�` */

// �R���X�g���N�^
BulletEnemyRangeNormal::BulletEnemyRangeNormal() : BulletBase()
{
	/* ������ */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// �I�u�W�F�N�g�̎�ނ�"�e(�v���C���[)"�ɐݒ�
	this->eEffect = nullptr;

	/* ���ǉ� */
	iDeleteCount = 130;
}

// �f�X�g���N�^
BulletEnemyRangeNormal::~BulletEnemyRangeNormal()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
	this->eEffect->SetDeleteFlg(true);
}

// ������
void BulletEnemyRangeNormal::Initialization()
{
	/* �����蔻��ݒ� */
	{
		this->stCollisionSqhere.vecSqhere = this->vecPosition;
		this->stCollisionSqhere.fSqhereRadius = 50.0f;
	}

	/* �G�t�F�N�g�ǉ� */
	{
		/* �ߐڍU��(��)�̃G�t�F�N�g�𐶐� */
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

void BulletEnemyRangeNormal::BulletEnemyRangeNormalMove()
{
	CharacterBase* player = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();
	if (iDeleteCount >= 120)
	{
		playerPos.y += 60; // y���W��60����������
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition)); // �v���C���[�̈ʒu�Ɍ������������X�V
	}

	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 18));
	this->stCollisionSqhere.vecSqhere = this->vecPosition;
	this->eEffect->SetPosition(this->vecPosition);
}

// �X�V
void BulletEnemyRangeNormal::Update()
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
	BulletEnemyRangeNormalMove();
}
