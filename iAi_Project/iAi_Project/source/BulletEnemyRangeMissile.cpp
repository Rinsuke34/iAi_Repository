/* 2025.01.30 �ΐ�q�� �t�@�C���쐬 */

#include "BulletEnemyRangeMissile.h"

/* �~�T�C���e�N���X�̒�` */

// �R���X�g���N�^
BulletEnemyRangeMissile::BulletEnemyRangeMissile() : BulletBase()
{
	/* ������ */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// �I�u�W�F�N�g�̎�ނ�"�e(�v���C���[)"�ɐݒ�
	this->pEffect = nullptr;

	this->iDurationCount = ENEMY_MISSILE_DURATION_COUNT;				// �~�T�C���e�̎����J�E���g
	this->iBulletUPCount = ENEMY_MISSILE_BULLET_UP_COUNT;				// �~�T�C���e�ł��グ�J�E���g
	this->iBulletDownCount = ENEMY_MISSILE_BULLET_DOWN_COUNT;			// �~�T�C���e�ł������J�E���g
	this->iBulletGuidanceCount = ENEMY_MISSILE_BULLET_GUIDANCE_COUNT;	// �~�T�C���U���J�E���g
	/* ���ǉ� */
	this->pPlayer = ObjectList->GetCharacterPlayer();					// �v���C���[�̎擾
}

// �f�X�g���N�^
BulletEnemyRangeMissile::~BulletEnemyRangeMissile()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
	this->pEffect->SetDeleteFlg(true);
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

// �~�T�C���e�̈ړ�����
void BulletEnemyRangeMissile::BulletEnemyRangeMissileMove()
{
	// �v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	// �����J�E���g���ł��グ�J�E���g�𒴂��Ă��邩�m�F
	if (ENEMY_MISSILE_DURATION_COUNT >= ENEMY_MISSILE_BULLET_UP_COUNT)
	{
		// �����J�E���g���ł��グ�J�E���g�𒴂��Ă���ꍇ

		// �v���C���[�̍����̔�����y���W���擾
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// �~�T�C���̈ړ��������v���C���[����������ɍX�V
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));

		// �~�T�C���̈ړ����W�ƈړ����x���X�V
		this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 18));
	}
	// �����J�E���g���ł������J�E���g�𒴂��Ă��邩�m�F
	else if (ENEMY_MISSILE_DURATION_COUNT >= ENEMY_MISSILE_BULLET_DOWN_COUNT)
	{
		// �����J�E���g���ł������J�E���g�𒴂��Ă���ꍇ

		// �~�T�C���̈ړ��������������ɐݒ�
		this->vecDirection = VGet(0, 1, 0);

		// �ēx�~�T�C���̈ړ����x���X�V
		//this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 30));
	}
	// �����J�E���g���U���J�E���g�𒴂��Ă��邩�m�F
	else if (ENEMY_MISSILE_DURATION_COUNT >= ENEMY_MISSILE_BULLET_GUIDANCE_COUNT)
	{
		// �����J�E���g���U���J�E���g�𒴂��Ă���ꍇ

		// �v���C���[�̍����̔�����y���W���擾
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// �~�T�C���̈ړ��������v���C���[����������ɍX�V
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));

		// �~�T�C���̈ړ����W�ƈړ����x���X�V
		this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 70));
	}

	// �~�T�C���̍��W���X�V
	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 70));
	// �~�T�C���̃R���W�������W���X�V
	this->stCollisionSqhere.vecSqhere = this->vecPosition;

	// �~�T�C���̃G�t�F�N�g���W���X�V
	this->pEffect->SetPosition(this->vecPosition);

	//�~�T�C�������ɓ��������炩�m�F
	if (this->vecPosition.y <= -1000)//�����̃}�W�b�N�i���o�[���Ə��ɓ����������̏����́A��ŏC�����܂�
	{
		// �~�T�C�������ɓ��������ꍇ
		// �~�T�C���̍폜�t���O��L����
		this->bDeleteFlg = true;


		/* �G�t�F�N�g�ǉ� */

		/*�����G�t�F�N�g�𐶐� */
		this->pEffectExplosion = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pEffectExplosion->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_missile_explosion/FX_e_missile_explosion")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->pEffectExplosion->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pEffectExplosion->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̏����� */
		this->pEffectExplosion->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->pEffectExplosion);
		}

	}
}

// �X�V
void BulletEnemyRangeMissile::Update()
{
	/* ������ */
	// �{���̓v���C���[���ō폜�t���O��ݒ肷��\��

	// �����J�E���g��0���傫�����m�F
	if (iEnemyMissileDurationCount > 0)
	{
		// �����J�E���g��0���傫���ꍇ

		// �����J�E���g�����Z
		iEnemyMissileDurationCount--;
	}
	else
	{
		// �����J�E���g��0�ȉ��̏ꍇ

		// �폜�t���O��L����
		this->bDeleteFlg = true;
	}
	// �~�T�C���̈ړ�����
	BulletEnemyRangeMissileMove();
}
