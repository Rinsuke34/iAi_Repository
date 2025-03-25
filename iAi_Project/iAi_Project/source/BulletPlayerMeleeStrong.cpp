/* 2025.01.27 ��򕗏� �t�@�C���쐬 */

#include "BulletPlayerMeleeStrong.h"

// �R���X�g���N�^
BulletPlayerMeleeStrong::BulletPlayerMeleeStrong() : BulletBase()
{
	/* ������ */
	this->iObjectType			= OBJECT_TYPE_MELEE_PLAYER;	// �I�u�W�F�N�g�̎�ނ�"�ߐڍU��(�v���C���[)"�ɐݒ�
	this->stCollisionCapsule	= {};

	/*  */
	iDeleteCount = 30;
}

// �X�V
void BulletPlayerMeleeStrong::Update()
{ 
	if (iDeleteCount > 0)
	{
		iDeleteCount--;
	}
	else
	{
		this->bDeleteFlg = true;
	}
}

// �����蔻��`��
void BulletPlayerMeleeStrong::CollisionDraw()
{
	/* �����蔻���`�� */
	int Color = GetColor(255, 0, 0);
	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 16, Color, Color, FALSE);
}

/* �ڐG����(�Ȉ�) */
// �J�v�Z�� - �J�v�Z��
bool BulletPlayerMeleeStrong::HitCheck(COLLISION_CAPSULE	stCapsule)
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
bool BulletPlayerMeleeStrong::HitCheck(COLLISION_SQHERE	stSqhere)
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
bool BulletPlayerMeleeStrong::HitCheck(int iModelHandle, int iFrameIndex)
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
