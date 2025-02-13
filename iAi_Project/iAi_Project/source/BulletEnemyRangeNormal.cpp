/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */

#include "BulletEnemyRangeNormal.h"

/* �m�[�}���e�N���X�̒�` */

// �R���X�g���N�^
BulletEnemyRangeNormal::BulletEnemyRangeNormal() : BulletBase()
{
	/* ������ */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// �I�u�W�F�N�g�̎�ނ�"�e(�G�l�~�[)"�ɐݒ�
	this->pEffect = nullptr;

	this->iDurationCount = ENEMY_NORMAL_DURATION_COUNT;		// �e�̎����J�E���g
	this->iBulletCount = ENEMY_NORMAL_BULLET_COUNT;			// �e���˃J�E���g

	this->iEnemyNormalDurationCount = ENEMY_NORMAL_DURATION_COUNT;	//�m�[�}���e�̎����J�E���g
}

// �f�X�g���N�^
BulletEnemyRangeNormal::~BulletEnemyRangeNormal()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
	this->pEffect->SetDeleteFlg(true);
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
		/* �m�[�}���e�G�t�F�N�g�𐶐� */
		this->pEffect = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->pEffect->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pEffect->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̏����� */
		this->pEffect->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->pEffect);
		}
	}
}

// �m�[�}���e�̈ړ�����
void BulletEnemyRangeNormal::BulletEnemyRangeNormalMove()
{
	/* �v���C���[�̍��W���擾 */
	CharacterBase* player = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	// �����J�E���g�����˃J�E���g�𒴂��Ă��邩�m�F
	if (iEnemyNormalDurationCount >= ENEMY_NORMAL_BULLET_COUNT)
	{
		//�����J�E���g�����˃J�E���g�𒴂��Ă���ꍇ
		// �v���C���[��y���W���擾
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// �v���C���[�̕����������悤�ɃG�l�~�[�̌������`
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));
	}

	// �m�[�}���e�̈ړ����W�ƌ����Ƒ��x���X�V
	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 18));

	// �m�[�}���e�̃R���W�������W���X�V
	this->stCollisionSqhere.vecSqhere = this->vecPosition;

	// �m�[�}���e�̃G�t�F�N�g���W���X�V
	this->pEffect->SetPosition(this->vecPosition);

}

// �X�V
void BulletEnemyRangeNormal::Update()
{

	// �����J�E���g��0���傫�����m�F
	if (iEnemyNormalDurationCount > 0)
	{
		// �����J�E���g��0���傫���ꍇ
		// �����J�E���g�����Z
		iEnemyNormalDurationCount--;
	}
	else
	{
		// �����J�E���g��0�ȉ��̏ꍇ
		// �폜�t���O��L����
		this->bDeleteFlg = true;
	}

	// �m�[�}���e�̈ړ�����
	BulletEnemyRangeNormalMove();
}
