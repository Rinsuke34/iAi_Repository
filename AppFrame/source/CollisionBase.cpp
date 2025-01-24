/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "CollisionBase.h"

/* ���ׂẴv���b�g�t�H�[���̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
CollisionBase::CollisionBase() : PlatformBase()
{
	/* ������ */
	this->iCollisionFrameNo = -1;	// �R���W�����t���[���ԍ�
}

// ������
void CollisionBase::Initialization()
{
	PlatformBase::Initialization();

	/* �R���W�����t���[���ݒ� */
	UpdateCollisionFrame();
}

// �����蔻��`��
void CollisionBase::CollisionDraw()
{
	/* �R���W�����̐ݒ肳�ꂽ�t���[����`�ʂ���悤�ݒ� */
	MV1SetFrameVisible(this->iModelHandle, this->iCollisionFrameNo, TRUE);

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
}

/* �ڐG����(�Ȉ�) */
// ���f�� - �J�v�Z��
bool CollisionBase::HitCheck(COLLISION_CAPSULE	stCapsule)
{
	// ����
	// stCapsule	: ���肷��J�v�Z���R���W����
	// �߂�l
	// bool : �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �R���W�����t���[�������݂��Ȃ����m�F */
	if (this->iCollisionFrameNo < 0)
	{
		// ���݂��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		return false;
	}

	// �|���S���Ƃ̐ڐG���
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̃J�v�Z���R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius);

	/* �ڐG�����擾 */
	if (stHitPolyDim.HitNum > 0)
	{
		// �ڐG���Ă���ꍇ
		return true;
	}
	//�ڐG���Ă��Ȃ��ꍇ
	return false;
}

// ���f�� - ����
bool CollisionBase::HitCheck(COLLISION_SQHERE	stSqhere)
{
	// ����
	// stCapsule	: ���肷�鋅�̃R���W����
	// �߂�l
	// bool			: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �R���W�����t���[�������݂��Ȃ����m�F */
	if (this->iCollisionFrameNo < 0)
	{
		// ���݂��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		return false;
	}

	// �|���S���Ƃ̐ڐG���
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̋��̃R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stSqhere.vecSqhere, stSqhere.vecSqhere, stSqhere.fSqhereRadius);

	/* �ڐG�����擾 */
	if (stHitPolyDim.HitNum > 0)
	{
		// �ڐG���Ă���ꍇ
		return true;
	}
	// �ڐG���Ă��Ȃ��ꍇ
	return false;
}

// ���f�� - ����
bool CollisionBase::HitCheck(COLLISION_LINE		stLine)
{
	// ����
	// stLine	: ���肷������R���W����
	// �߂�l
	// bool		: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �R���W�����t���[�������݂��Ȃ����m�F */
	if (this->iCollisionFrameNo < 0)
	{
		// ���݂��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		return false;
	}

	// �|���S���Ƃ̐ڐG���
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̐����R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Line(
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stLine.vecLineStart, stLine.vecLineEnd);

	/* �ڐG�������m�F */
	if (stHitPolyDim.HitFlag == 1)
	{
		// �ڐG���Ă���ꍇ
		return true;
	}

	// �ڐG���Ă��Ȃ��ꍇ
	return false;
}

/* �ڐG����(�ڍ�) */
// ���f�� - ����
MV1_COLL_RESULT_POLY CollisionBase::HitCheck_Line(COLLISION_LINE	stLine)
{
	// ����
	// stLine				: ���肷������R���W����
	// �߂�l
	// MV1_COLL_RESULT_POLY	: �ڐG���

	// �|���S���Ƃ̐ڐG���
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* �R���W�����t���[�������݂��Ȃ����m�F */
	if (this->iCollisionFrameNo < 0)
	{
		// ���݂��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		stHitPolyDim.HitFlag = FALSE;
		return stHitPolyDim;
	}

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̐����R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Line(
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stLine.vecLineStart, stLine.vecLineEnd);

	return stHitPolyDim;
}

// �R���W�����̐ݒ肳�ꂽ�t���[���̐ݒ�
void CollisionBase::UpdateCollisionFrame()
{
	/* �R���W�����t���[���ԍ��擾 */
	this->iCollisionFrameNo = MV1SearchFrame(this->iModelHandle, "Collision");

	/* �R���W�����t���[���̎擾�������������m�F */
	if (this->iCollisionFrameNo >= 0)
	{
		// ��������(�ݒ肳��Ă���)�ꍇ
		/* �R���W�����̐ݒ肳�ꂽ�t���[���̃R���W�������\�z */
		MV1SetupCollInfo(this->iModelHandle, this->iCollisionFrameNo, 1, 1, 1);

		/* �R���W�����̐ݒ肳�ꂽ�t���[����`�ʂ��Ȃ��悤�ɐݒ� */
		MV1SetFrameVisible(this->iModelHandle, this->iCollisionFrameNo, FALSE);
	}
}