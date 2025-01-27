/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "CharacterBase.h"

/* ���ׂẴL�����N�^�[�̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
CharacterBase::CharacterBase() : ActorBase()
{
	/* ������ */
	this->stCollisionCapsule	= {};					// �R���W����(�J�v�Z��)
	this->iInvincibilityTime	= {};					// ���G����
}

// ������
void CharacterBase::Initialization()
{
	/* ��������t���[�����擾 */
	UpdataLightFrame();
}

// �����`��
void CharacterBase::BloomDraw()
{
	/* ���̐F��ۑ� */
	int iBackUpFrames = MV1GetFrameNum(this->iModelHandle);
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

	/* ���C�g�t���[��No�ɐݒ肳�ꂽ�ԍ��ȊO�����F�łɐݒ� */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		/* �����t���[���ł��邩�m�F */
		if (std::find(aiLightFrameNo.begin(), aiLightFrameNo.end(), i) != aiLightFrameNo.end())
		{
			// �����t���[���ł���ꍇ
			/* �ύX���s��Ȃ� */
		}
		else
		{
			// �����t���[���łȂ��ꍇ
			/* �Ώۃt���[�������F�ŕ`�� */
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

// �����蔻��`��
void CharacterBase::CollisionDraw()
{
	/* �����蔻���`�� */
	int iColor	= GetColor(255, 0, 0);
	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 16, iColor, iColor, FALSE);
}

// �`��
void CharacterBase::Draw()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
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

// �����̐ݒ肳�ꂽ�t���[�����擾
void CharacterBase::UpdataLightFrame()
{
	/* ���f���n���h������t���[�������擾 */
	int iFrameNum = MV1GetFrameNum(this->iModelHandle);

	/* ��������t���[���ԍ����擾���� */
	for (int i = 0; i < iFrameNum; i++)
	{
		/* �t���[�����擾 */
		const char* cFrameName = MV1GetFrameName(this->iModelHandle, i);

		/* �ŏ���5������"Light"�ł��邩�m�F */
		if (strncmp(cFrameName, "Light", 5) == 0)
		{
			/* �����t���[���ԍ����擾 */
			this->aiLightFrameNo.push_back(i);

			/* �����t���[���̐e�t���[���ԍ����擾 */
			int parentFrame = MV1GetFrameParent(this->iModelHandle, i);

			/* �����t���[���̐e�t���[�������݂���Ȃ�� */
			while (parentFrame >= 0)
			{
				// �e�t���[�������݂���ꍇ
				/* �e�t���[���ԍ���ǉ� */
				this->aiLightFrameNo.push_back(parentFrame);

				/* �e�t���[���ԍ��̐e�t���[�����擾 */
				parentFrame = MV1GetFrameParent(this->iModelHandle, parentFrame);
			}
		}
	}

	/* �����t���[���ԍ��������Ƀ\�[�g */
	std::sort(this->aiLightFrameNo.begin(), this->aiLightFrameNo.end());

	/* �d�����Ă���ԍ����폜 */
	this->aiLightFrameNo.erase(std::unique(this->aiLightFrameNo.begin(), this->aiLightFrameNo.end()), this->aiLightFrameNo.end());
}
