/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "PlatformBase.h"

/* ���ׂẴv���b�g�t�H�[���̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
PlatformBase::PlatformBase() : ObjectBase()
{
	/* ������ */
	this->iModelHandle = -1;	// ���f���n���h��
}

// �f�X�g���N�^
PlatformBase::~PlatformBase()
{
	/* ���f���n���h���폜 */
	MV1DeleteModel(this->iModelHandle);
}

/* �ڐG����(�Ȉ�) */
// ���f�� - �J�v�Z��
bool PlatformBase::HitCheck(COLLISION_CAPSULE	stCapsule)
{
	// ����
	// stCapsule	: ���肷��J�v�Z���R���W����
	// �߂�l
	// bool : �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	// �|���S���Ƃ̐ڐG���
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̃J�v�Z���R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* ���̃��f���̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius);

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
bool PlatformBase::HitCheck(COLLISION_SQHERE	stSqhere)
{
	// ����
	// stCapsule	: ���肷�鋅�̃R���W����
	// �߂�l
	// bool			: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	// �|���S���Ƃ̐ڐG���
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̋��̃R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* ���̃��f���̃R���W���� */
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
bool PlatformBase::HitCheck(COLLISION_LINE		stLine)
{
	// ����
	// stLine	: ���肷������R���W����
	// �߂�l
	// bool		: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	// �|���S���Ƃ̐ڐG���
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̐����R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Line(
		/* ���̃��f���̃R���W���� */
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
MV1_COLL_RESULT_POLY PlatformBase::HitCheck_Line(COLLISION_LINE	stLine)
{
	// ����
	// stLine				: ���肷������R���W����
	// �߂�l
	// MV1_COLL_RESULT_POLY	: �ڐG���

	// �|���S���Ƃ̐ڐG���
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̐����R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Line(
		/* ���̃��f���̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stLine.vecLineStart, stLine.vecLineEnd);

	return stHitPolyDim;
}
