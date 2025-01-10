/* 2024.12.18 ��򕗏� �t�@�C���쐬 */

#include "BulletBase.h"

/* ���ׂĂ̒e�ۂ̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
BulletBase::BulletBase() : ActorBase()
{
	/* ������ */
	this->stCollisionSqhere = {};	// �R���W����(����)
	this->vecMoveDirection	= {};	// �ړ�����
}

/* �ڐG���� */
// ���� - �J�v�Z��
bool BulletBase::HitCheck(COLLISION_CAPSULE	stCapsule)
{
	// ����
	// stCapsule	: ���肷��J�v�Z���R���W����
	// �߂�l
	// bool : �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �J�v�Z���ƐڐG���Ă��邩�m�F */
	if (HitCheck_Capsule_Capsule
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		(stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius,
		/* �e�̃R���W���� */
		this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius))
	{
		// �ڐG���Ă���ꍇ
		return true;
	}
	// �ڐG���Ă��Ȃ��ꍇ
	return false;
}

// ���� - ����
bool BulletBase::HitCheck(COLLISION_SQHERE	stSqhere)
{
	// ����
	// stCapsule	: ���肷�鋅�̃R���W����
	// �߂�l
	// bool			: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �J�v�Z���Ƌ��̂��ڐG���Ă��邩�m�F */
	if (HitCheck_Capsule_Capsule
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		(stSqhere.vecSqhere, stSqhere.vecSqhere, stSqhere.fSqhereRadius,
		/* �e�̃R���W���� */
		this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius))
	{
		// �ڐG���Ă���ꍇ
		return true;
	}
	// �ڐG���Ă��Ȃ��ꍇ
	return false;
}

// ���� - ���f��
bool BulletBase::HitCheck(int iModelHandle, int iFrameIndex)
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
		/* �e�̃R���W���� */
		this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius);

	/* �ڐG�����擾 */
	if (stHitPolyDim.HitNum > 0)
	{
		// �ڐG���Ă���ꍇ
		return true;
	}
	// �ڐG���Ă��Ȃ��ꍇ
	return false;
}