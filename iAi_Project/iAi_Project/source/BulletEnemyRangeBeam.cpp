/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */

#include "BulletEnemyRangeBeam.h"

/* �r�[���N���X�̒�` */

// �R���X�g���N�^
BulletEnemyRangeBeam::BulletEnemyRangeBeam() : BulletBase()
{
	/* ������ */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// �I�u�W�F�N�g�̎�ނ�"�e(�G�l�~�[)"�ɐݒ�
	this->pEffect = nullptr;

	this->iChargeCount = ENEMY_BEAM_CHARGE_COUNT;		// �r�[���`���[�W�J�E���g

	this->iBulletCount = ENEMY_BEAM_BULLET_COUNT;			// �r�[�����˃J�E���g

	this->iEnemyBeamDurationCount = ENEMY_BEAM_DURATION_COUNT;	//�r�[���̎����J�E���g
	// �G�l�~�[�̈ʒu��������
	this->vecEnemyPosition = VGet(0, 0, 0);
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
		this->stCollisionCapsule.fCapsuleRadius = 50.0f;
		this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(100, 0, 0)); // ���ɐݒ�
		this->stCollisionCapsule.vecCapsuleBottom = VGet(0, 0, 0); // ������
	}

	/* �G�t�F�N�g�ǉ� */
	{
		/* �r�[���G�t�F�N�g�𐶐� */
		this->pEffect = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_beam/FX_e_beam")));

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

	//�G�l�~�[�̈ʒu��ݒ�
	this->vecEnemyPosition = this->vecPosition;
}

// �r�[���̈ړ�����
void BulletEnemyRangeBeam::BulletEnemyRangeBeamMove()
{
	/* �v���C���[�̍��W���擾 */
	CharacterBase* player = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	iChargeCount--;	// �`���[�W�J�E���g�����Z
	if (iChargeCount <= 0)
	{
        // �G�t�F�N�g���Đ������ǂ����m�F
        if (IsEffekseer3DEffectPlaying(this->pEffect->iGetEffectHandle()))
        {
            // �G�t�F�N�g���Đ��I�����Ă���ꍇ
            // �G�l�~�[�̍폜�t���O��L���ɂ���
            this->bDeleteFlg = true;
        }
	// �����J�E���g�����˃J�E���g�𒴂��Ă��邩�m�F
	if (iEnemyBeamDurationCount >= ENEMY_NORMAL_BULLET_COUNT)
	{
		//�����J�E���g�����˃J�E���g�𒴂��Ă���ꍇ
		// �v���C���[��y���W���擾
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// �v���C���[�̕����������悤�ɃG�l�~�[�̌������`
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));

			//�`���[�W�J�E���g��������
			iChargeCount = ENEMY_BEAM_CHARGE_COUNT;
		}
	}

	// �r�[���̈ړ����W�ƌ����Ƒ��x���X�V
    this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 30));

	// �G�l�~�[�̃��X�g���擾
	auto& enemyList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetEnemyList();

	// �r�[���̃R���W�������W���X�V
    this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition; // �I���n�_���X�V

    // �R���W�����̒������v�Z
    float collisionLength = VSize(VSub(this->stCollisionCapsule.vecCapsuleBottom, this->vecEnemyPosition));
    const float maxCollisionLength = 2200.0f; // �ő�R���W��������

    // �R���W�����̒������ő咷���𒴂��Ȃ��悤�ɒ���
    if (collisionLength > maxCollisionLength)
    {
        VECTOR direction = VNorm(VSub(this->stCollisionCapsule.vecCapsuleBottom, this->vecEnemyPosition));
        this->stCollisionCapsule.vecCapsuleBottom = VAdd(this->vecEnemyPosition, VScale(direction, maxCollisionLength));
    }

    this->stCollisionCapsule.vecCapsuleTop = this->vecEnemyPosition; // �J�n�n�_���G�l�~�[�̈ʒu�ɌŒ�

	// �r�[���̃G�t�F�N�g�̌�����ݒ�
	VECTOR rotation = VGet(atan2(this->vecDirection.y, this->vecDirection.z), atan2(this->vecDirection.x, this->vecDirection.z), 0);

    // �r�[���̃G�t�F�N�g�̔��Ό�����ݒ�
    VECTOR rotation2 = VGet(rotation.x, rotation.y + DX_PI_F, rotation.z);

	// �G�t�F�N�g�̌�����ݒ肷��O�ɁA�K�v�ȉ�]�����ǂꂩ���m�F
    if (this->vecDirection.z > 0)
    {
        // ���ʂ������Ă���ꍇ
        this->pEffect->SetRotation(rotation2);
    }
    else
    {
        // ���ʂ������Ă��Ȃ��ꍇ
	this->pEffect->SetRotation(rotation);
}
}

/* �ڐG����(�Ȉ�) */
// �J�v�Z�� - �J�v�Z��
bool BulletEnemyRangeBeam::HitCheck(COLLISION_CAPSULE	stCapsule)
{
	// ����
	// stCapsule	: ���肷��J�v�Z���R���W����
	// �߂�l
	// bool : �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �J�v�Z�����m���ڐG���Ă��邩�m�F */
	if (HitCheck_Capsule_Capsule
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		(stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius,
			/* ���̃I�u�W�F�N�g�̃R���W���� */
			this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius))
	{
		// �ڐG���Ă���ꍇ
		return true;
	}
	// �ڐG���Ă��Ȃ��ꍇ
	return false;
}

// �J�v�Z�� - ����
bool BulletEnemyRangeBeam::HitCheck(COLLISION_SQHERE	stSqhere)
{
	// ����
	// stCapsule	: ���肷�鋅�̃R���W����
	// �߂�l
	// bool			: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �J�v�Z���Ƌ��̂��ڐG���Ă��邩�m�F */
	if (HitCheck_Sphere_Capsule(
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stSqhere.vecSqhere, stSqhere.fSqhereRadius,
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius))
	{
		// �ڐG���Ă���ꍇ
		return true;
	}
	// �ڐG���Ă��Ȃ��ꍇ
	return false;
}

// �J�v�Z�� - ���f��
bool BulletEnemyRangeBeam::HitCheck(int iModelHandle, int iFrameIndex)
{
	// ����
	// iModelHandle	: ���肷�郂�f���̃n���h��
	// iFrameIndex	: ���肷�郂�f���̃t���[���ԍ�
	// �߂�l
	// bool			: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	// �|���S���Ƃ̐ڐG���
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* �v���C���[�ƑΏۂ̃��f�����ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		iModelHandle, iFrameIndex,
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius);

	/* �ڐG�����擾 */
	if (stHitPolyDim.HitNum > 0)
	{
		// �ڐG���Ă���ꍇ
		return true;
	}
	// �ڐG���Ă��Ȃ��ꍇ
	return false;
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

// �R���W�����`��
void BulletEnemyRangeBeam::CollisionDraw()
{
	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 12, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}