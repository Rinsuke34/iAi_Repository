/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "PlatformBase.h"

/* ���ׂẴv���b�g�t�H�[���̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
PlatformBase::PlatformBase() : ObjectBase()
{
	/* ������ */
	this->iModelHandle		= 0;					// ���f���n���h��
	this->vecRotation		= VGet(0.f, 0.f, 0.f);	// ��]��
	this->iCollisionFrameNo = -1;					// �R���W�����t���[���ԍ�
}

// �f�X�g���N�^
PlatformBase::~PlatformBase()
{
	/* �R���W��������n�� */
	MV1TerminateCollInfo(this->iModelHandle, this->iCollisionFrameNo);

	/* ���f���n���h���폜 */
	MV1DeleteModel(this->iModelHandle);
}

// ������
void PlatformBase::Initialization()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* ���f���g�� */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* �R���W�����t���[���ݒ� */
	UpdateCollisionFrame();

	/* �����t���[���ԍ��擾 */
	UpdataLightFrame();
}

// �`��
void PlatformBase::Draw()
{
	/* �R���W�����t���[����`�ʂ��Ȃ���Ԃɐݒ� */
	DrawFrameCollisionSet(false);

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
		/* �t���[���̐F���擾 */
		vecOriginalDifColor[i] = MV1GetFrameDifColorScale(this->iModelHandle, i);
		vecOriginalSpcColor[i] = MV1GetFrameSpcColorScale(this->iModelHandle, i);
		vecOriginalEmiColor[i] = MV1GetFrameEmiColorScale(this->iModelHandle, i);
		vecOriginalAmbColor[i] = MV1GetFrameAmbColorScale(this->iModelHandle, i);
	}

	/* �^�[�Q�b�g�ȊO�̐F�����ɐݒ� */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		/* �����t���[���ł͂Ȃ����m�F */
		if (std::find(aiLightFrameNo.begin(), aiLightFrameNo.end(), i) != aiLightFrameNo.end() == false)
		{
			// �����t���[���ł͂Ȃ��ꍇ
			/* �t���[���̐F�����F�ɐݒ� */
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
		/* �t���[���̐F�����̐F�ɐݒ� */
		MV1SetFrameDifColorScale(this->iModelHandle, i, vecOriginalDifColor[i]);
		MV1SetFrameSpcColorScale(this->iModelHandle, i, vecOriginalSpcColor[i]);
		MV1SetFrameEmiColorScale(this->iModelHandle, i, vecOriginalEmiColor[i]);
		MV1SetFrameAmbColorScale(this->iModelHandle, i, vecOriginalAmbColor[i]);
	}
}

// �����蔻��`��
void PlatformBase::CollisionDraw()
{
	/* �R���W�����t���[����`�ʂ����Ԃɐݒ� */
	DrawFrameCollisionSet(true);

	/* �R���W�����̐ݒ肳�ꂽ�t���[����`�ʂ���悤�ݒ� */
	MV1SetFrameVisible(this->iModelHandle, this->iCollisionFrameNo, TRUE);

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
}

/* �ڐG����(�Ȉ�) */
// ���f�� - �J�v�Z��
bool PlatformBase::HitCheck(COLLISION_CAPSULE	stCapsule)
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

	/* �I�u�W�F�N�g�̑�܂��ȃR���W�����ƐڐG���Ă��Ȃ����m�F */
	// �y�ʉ��̂��߁A�|���S���Ƃ̐ڐG�m�F�̑O�ɑ�܂��ȉ~�ƐڐG���Ă��邩���m�F����
	if (HitCheck_Sphere_Capsule(
		/* ���̃I�u�W�F�N�g�̃R���W����(��܂��ȉ~) */
		this->vecCenterPosition, this->fRoughRadius,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius) == FALSE)
	{
		// �ڐG���Ă��Ȃ��ꍇ
		return false;
	}

	/* �|���S���Ƃ̐ڐG��� */
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
bool PlatformBase::HitCheck(COLLISION_SQHERE	stSqhere)
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

	/* �I�u�W�F�N�g�̑�܂��ȃR���W�����ƐڐG���Ă��Ȃ����m�F */
	// �y�ʉ��̂��߁A�|���S���Ƃ̐ڐG�m�F�̑O�ɑ�܂��ȉ~�ƐڐG���Ă��邩���m�F����
	if (HitCheck_Sphere_Sphere(
		/* ���̃I�u�W�F�N�g�̃R���W����(��܂��ȉ~) */
		this->vecCenterPosition, this->fRoughRadius,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stSqhere.vecSqhere, stSqhere.fSqhereRadius) == FALSE)
	{
		// �ڐG���Ă��Ȃ��ꍇ
		return false;
	}

	/* �|���S���Ƃ̐ڐG��� */
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

	/* �R���W�����t���[�������݂��Ȃ����m�F */
	if (this->iCollisionFrameNo < 0)
	{
		// ���݂��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		return false;
	}

	/* �I�u�W�F�N�g�̑�܂��ȃR���W�����ƐڐG���Ă��Ȃ����m�F */
	// �y�ʉ��̂��߁A�|���S���Ƃ̐ڐG�m�F�̑O�ɑ�܂��ȉ~�ƐڐG���Ă��邩���m�F����
	if (HitCheck_Line_Sphere(
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stLine.vecLineStart, stLine.vecLineEnd,
		/* ���̃I�u�W�F�N�g�̃R���W����(��܂��ȉ~) */
		this->vecCenterPosition, this->fRoughRadius) == FALSE)
	{
		// �ڐG���Ă��Ȃ��ꍇ
		return false;
	}

	/* �|���S���Ƃ̐ڐG��� */
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

	/* �|���S���Ƃ̐ڐG��� */
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* �I�u�W�F�N�g�̑�܂��ȃR���W�����ƐڐG���Ă��Ȃ����m�F */
	// �y�ʉ��̂��߁A�|���S���Ƃ̐ڐG�m�F�̑O�ɑ�܂��ȉ~�ƐڐG���Ă��邩���m�F����
	if (HitCheck_Line_Sphere(
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stLine.vecLineStart, stLine.vecLineEnd,
		/* ���̃I�u�W�F�N�g�̃R���W����(��܂��ȉ~) */
		this->vecCenterPosition, this->fRoughRadius) == FALSE)
	{
		// �ڐG���Ă��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		stHitPolyDim.HitFlag = FALSE;
		return stHitPolyDim;
	}

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

// ���f�� - �J�v�Z��
MV1_COLL_RESULT_POLY_DIM PlatformBase::HitCheck_Capsule(COLLISION_CAPSULE	stCapsule)
{
	// ����
	// stCapsule				: ���肷��J�v�Z���R���W����
	// �߂�l
	// MV1_COLL_RESULT_POLY_DIM	: �ڐG���

	/* �|���S���Ƃ̐ڐG��� */
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* �I�u�W�F�N�g�̑�܂��ȃR���W�����ƐڐG���Ă��Ȃ����m�F */
	// �y�ʉ��̂��߁A�|���S���Ƃ̐ڐG�m�F�̑O�ɑ�܂��ȉ~�ƐڐG���Ă��邩���m�F����
	if (HitCheck_Sphere_Capsule(
		/* ���̃I�u�W�F�N�g�̃R���W����(��܂��ȉ~) */
		this->vecCenterPosition, this->fRoughRadius,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius) == FALSE)
	{
		// �ڐG���Ă��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		stHitPolyDim.HitNum = FALSE;
		return stHitPolyDim;
	}

	/* �R���W�����t���[�������݂��Ȃ����m�F */
	if (this->iCollisionFrameNo < 0)
	{
		// ���݂��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		stHitPolyDim.HitNum = FALSE;
		return stHitPolyDim;
	}

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̃J�v�Z���R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius);

	return stHitPolyDim;
}

// �R���W�����̐ݒ肳�ꂽ�t���[���̐ݒ�
void PlatformBase::UpdateCollisionFrame()
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

		/* �R���W�����t���[���Ɋ܂܂�郁�b�V���ԍ����擾 */
		int iMeshNo = MV1GetFrameMesh(this->iModelHandle, this->iCollisionFrameNo, 0);

		/* �t���[���̃��[���h�ϊ��s����擾 */
		MATRIX frameMatrix = MV1GetFrameLocalWorldMatrix(this->iModelHandle, this->iCollisionFrameNo);

		/*�擾�������b�V���̍ő���W�ƍŏ����W���擾 */
		VECTOR vecMinPos = MV1GetMeshMinPosition(this->iModelHandle, iMeshNo);
		VECTOR vecMaxPos = MV1GetMeshMaxPosition(this->iModelHandle, iMeshNo);

		/* ���b�V���̍ő���W�ƍŏ����W�����[���h���W�ɕϊ� */
		vecMinPos = VTransform(vecMinPos, frameMatrix);
		vecMaxPos = VTransform(vecMaxPos, frameMatrix);

		/* ���b�V���̒��S���W(�R���W�����t���[���̒��S���W)���擾 */
		this->vecCenterPosition	= VScale(VAdd(vecMinPos, vecMaxPos), 0.5f);

		/* ���S���W����R���W�������ݍ��ޑ�܂��Ȕ��a���擾 */
		this->fRoughRadius		= VSize(VSub(vecMaxPos, vecMinPos)) * 0.5f;
	}
}

// �����̐ݒ肳�ꂽ�t���[�����擾
void PlatformBase::UpdataLightFrame()
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

// �R���W�����t���[����`�ʂ����Ԃɂ���
void PlatformBase::DrawFrameCollisionSet(bool bCollisionDraw)
{
	// ����
	// bCollisionDraw	: �R���W�����t���[����`�ʂ���(true) / �`�ʂ��Ȃ�(false)
	// ���R���W�����t���[����`�ʂ��Ȃ��ꍇ�A�R���W�����ȊO�̃t���[���̕`�ʂ�L���ɂ��܂�

	/* �t���[�������擾 */
	int iFrameNo = MV1GetFrameNum(this->iModelHandle);

	/* ���ׂẴt���[�����\���ɐݒ� */
	for (int i = 0; i < iFrameNo; i++)
	{
		/* �R���W�����t���[���ԍ��ł��邩 */
		if (i == this->iCollisionFrameNo)
		{
			// �R���W�����t���[���ԍ��ł���ꍇ
			/* �R���W�����t���[����`�ʂ���ݒ�ł��邩�m�F */
			if (bCollisionDraw == true)
			{
				// �`�ʂ���ݒ�ł���ꍇ
				/* �t���[����\���ɐݒ� */
				MV1SetFrameVisible(this->iModelHandle, i, TRUE);
			}
			else
			{
				// �`�ʂ��Ȃ��ݒ�ł���ꍇ
				/* �t���[�����\���ɐݒ� */
				MV1SetFrameVisible(this->iModelHandle, i, FALSE);
			}
		}
		else
		{
			// �R���W�����t���[���ԍ��łȂ��ꍇ
			/* �R���W�����t���[����`�ʂ���ݒ�ł��邩�m�F */
			if (bCollisionDraw == true)
			{
				// �`�ʂ���ݒ�ł���ꍇ
				/* �t���[�����\���ɐݒ� */
				MV1SetFrameVisible(this->iModelHandle, i, FALSE);
			}
			else
			{
				// �`�ʂ��Ȃ��ݒ�ł���ꍇ
				/* �t���[����\���ɐݒ� */
				MV1SetFrameVisible(this->iModelHandle, i, TRUE);
			}
		}
	}


}
