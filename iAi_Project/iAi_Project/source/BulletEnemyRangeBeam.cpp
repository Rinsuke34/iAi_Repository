/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */

#include "BulletEnemyRangeBeam.h"

/* �r�[���N���X�̒�` */

// �R���X�g���N�^
BulletEnemyRangeBeam::BulletEnemyRangeBeam() : BulletBase()
{
	/* ������ */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// �I�u�W�F�N�g�̎�ނ�"�e(�G�l�~�[)"�ɐݒ�
	this->pEffect = nullptr;

	this->iDurationCount = ENEMY_NORMAL_DURATION_COUNT;		// �r�[���̎����J�E���g
	this->iBulletCount = ENEMY_NORMAL_BULLET_COUNT;			// �r�[�����˃J�E���g

	this->iEnemyBeamDurationCount = ENEMY_NORMAL_DURATION_COUNT;	//�r�[���̎����J�E���g
}

// �f�X�g���N�^
BulletEnemyRangeBeam::~BulletEnemyRangeBeam()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
	this->pEffect->SetDeleteFlg(true);
}

// ������
void BulletEnemyRangeBeam::Initialization()
{
	/* �����蔻��ݒ� */
	{
		this->stCollisionSqhere.vecSqhere = this->vecPosition;
		this->stCollisionSqhere.fSqhereRadius = 50.0f;
	}

	/* �G�t�F�N�g�ǉ� */
	{
		/* �r�[���G�t�F�N�g�𐶐� */
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

// �r�[���̈ړ�����
void BulletEnemyRangeBeam::BulletEnemyRangeBeamMove()
{
	/* �v���C���[�̍��W���擾 */
	CharacterBase* player = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	// �����J�E���g�����˃J�E���g�𒴂��Ă��邩�m�F
	if (iEnemyBeamDurationCount >= ENEMY_NORMAL_BULLET_COUNT)
	{
		//�����J�E���g�����˃J�E���g�𒴂��Ă���ꍇ
		// �v���C���[��y���W���擾
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// �v���C���[�̕����������悤�ɃG�l�~�[�̌������`
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));
	}

	// �r�[���̈ړ����W�ƌ����Ƒ��x���X�V
	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 18));

	// �r�[���̃R���W�������W���X�V
	this->stCollisionSqhere.vecSqhere = this->vecPosition;

	// �r�[���̃G�t�F�N�g���W���X�V
	this->pEffect->SetPosition(this->vecPosition);

}

// �X�V
void BulletEnemyRangeBeam::Update()
{

	// �����J�E���g��0���傫�����m�F
	if (iEnemyBeamDurationCount > 0)
	{
		// �����J�E���g��0���傫���ꍇ
		// �����J�E���g�����Z
		iEnemyBeamDurationCount--;
	}
	else
	{
		// �����J�E���g��0�ȉ��̏ꍇ
		// �폜�t���O��L����
		this->bDeleteFlg = true;
	}

	// �r�[���̈ړ�����
	BulletEnemyRangeBeamMove();
}
