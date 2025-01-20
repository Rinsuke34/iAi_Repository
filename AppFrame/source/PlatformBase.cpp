/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "PlatformBase.h"

/* ���ׂẴv���b�g�t�H�[���̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
PlatformBase::PlatformBase() : ObjectBase()
{
	/* ������ */
	this->iModelHandle		= -1;	// ���f���n���h��
	this->iCollisionFrameNo	= -2;	// �R���W�����̐ݒ肳�ꂽ���f���̃t���[���ԍ�	
	this->iLightFrameNo		= -2;	// ���������̐ݒ肳�ꂽ���f���̃t���[���ԍ�
}

// �f�X�g���N�^
PlatformBase::~PlatformBase()
{
	/* ���f���n���h���폜 */
	MV1DeleteModel(this->iModelHandle);
}

// ������
void PlatformBase::Initialization()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotate);

	/* ���f���g�� */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* �R���W�����t���[���ԍ��擾 */
	this->SetCollisionFrameNo(MV1SearchFrame(this->iModelHandle, "Collision"));

	/* �����t���[���ԍ��擾 */
	this->SetLightFrameNo(MV1SearchFrame(this->iModelHandle, "Light"));

	/* �R���W�������\�z */
	MV1SetupCollInfo(this->iModelHandle, this->iGetCollisionFrameNo(), 4, 4, 4);

	/* �R���W�����t���[�����\���ɐݒ� */
	MV1SetFrameVisible(this->iModelHandle, this->iGetCollisionFrameNo(), FALSE);
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
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stLine.vecLineStart, stLine.vecLineEnd);

	return stHitPolyDim;
}

// �`��
void PlatformBase::Draw()
{
	/* ���݂̃��f���̓����x�擾 */
	float OpacityRate = MV1GetOpacityRate(this->iModelHandle);

	/* �����x�m�F */
	if (OpacityRate > 0.f)
	{
		// ���S�ɓ����łȂ��ꍇ
		/* ���f���`�� */
		MV1DrawModel(this->iModelHandle);
	}
}

// �����`��
void PlatformBase::BloomDraw()
{
	/* �t���[�������擾 */
	int iBackUpFrames = MV1GetFrameNum(this->iModelHandle);

	/* ���̐F��ۑ� */
	std::vector<COLOR_F> vecOriginalDifColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalSpcColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalEmiColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalAmbColor(iBackUpFrames);

	for (int i = 0; i < iBackUpFrames; i++)
	{
		vecOriginalDifColor[i] = MV1GetFrameDifColorScale(this->iModelHandle, i);
		vecOriginalSpcColor[i] = MV1GetFrameSpcColorScale(this->iModelHandle, i);
		vecOriginalEmiColor[i] = MV1GetFrameEmiColorScale(this->iModelHandle, i);
		vecOriginalAmbColor[i] = MV1GetFrameAmbColorScale(this->iModelHandle, i);
	}

	/* �^�[�Q�b�g�ȊO�̐F�����ɐݒ� */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		if (i != this->iLightFrameNo)
		{
			MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameSpcColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameEmiColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameAmbColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
		}
	}

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);

	/* ���̐F�ɖ߂� */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		MV1SetFrameDifColorScale(this->iModelHandle, i, vecOriginalDifColor[i]);
		MV1SetFrameSpcColorScale(this->iModelHandle, i, vecOriginalSpcColor[i]);
		MV1SetFrameEmiColorScale(this->iModelHandle, i, vecOriginalEmiColor[i]);
		MV1SetFrameAmbColorScale(this->iModelHandle, i, vecOriginalAmbColor[i]);
	}
}
