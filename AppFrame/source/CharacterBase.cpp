/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "CharacterBase.h"

/* ���ׂẴL�����N�^�[�̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
CharacterBase::CharacterBase() : ActorBase()
{
	/* ������ */
	this->stCollisionCapsule	= {};	// �R���W����(�J�v�Z��)
	this->vecDirection			= {};	// ����
	this->iInvincibilityTime	= {};	// ���G����
}

// ������
void CharacterBase::Initialization()
{
	/* ��������t���[�����擾 */
	UpdataLightFrame();
}

/* �ڐG����(�Ȉ�) */
// �J�v�Z�� - �J�v�Z��
bool CharacterBase::HitCheck(COLLISION_CAPSULE	stCapsule)
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
bool CharacterBase::HitCheck(COLLISION_SQHERE	stSqhere)
{
	// ����
	// stCapsule	: ���肷�鋅�̃R���W����
	// �߂�l
	// bool			: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �J�v�Z���Ƌ��̂��ڐG���Ă��邩�m�F */
	if(HitCheck_Sphere_Capsule(
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
bool CharacterBase::HitCheck(int iModelHandle, int iFrameIndex)
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

// �����̐ݒ肳�ꂽ�t���[����ݒ�
void CharacterBase::UpdataLightFrame()
{
	/* ���f���n���h������t���[�������擾 */
	int iFrameNum = MV1GetFrameNum(this->iModelHandle);

	/* ��������t���[���ԍ����擾���� */
	for (int i = 0; i < iFrameNum; i++)
	{
		/* �t���[�����擾 */
		char FrameName = MV1GetFrameName(this->iModelHandle, i);
	}


	///* �q�t���[�����甭���������擾 */
	//for (int i = 0; i < iFrameNum; i++)
	//{
	//	/* �q�t���[�������擾 */
	//	int iFrameChildNum = MV1GetFrameChildNum(this->iModelHandle, )
	//	/* ���f���n���h������q�t���[�������擾 */
	//	for(int j = 0; j < )
	//}
}