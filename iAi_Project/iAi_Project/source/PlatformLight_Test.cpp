/* 2024.01.13 ��򕗏� �t�@�C���쐬 */

#include "PlatformLight_Test.h"

/* ��������v���b�g�t�H�[���N���X(�e�X�g)�̒�` */

// �R���X�g���N�^
PlatformLight_Test::PlatformLight_Test() : PlatformBase()
{

}

// �f�X�g���N�^
PlatformLight_Test::~PlatformLight_Test()
{

}

// ������
void PlatformLight_Test::Initialization()
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

// �`��
void PlatformLight_Test::Draw()
{
	/* ���݂̃��f���̓����x�擾 */
	float OpacityRate = MV1GetOpacityRate(this->iModelHandle);

	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_UP] == TRUE)
	{		
		/* �����x���グ�� */
		OpacityRate += 0.01f;
		MV1SetOpacityRate(this->iModelHandle, OpacityRate);
	}
	else if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_DOWN] == TRUE)
	{
		/* �����x�������� */
		OpacityRate -= 0.01f;
		MV1SetOpacityRate(this->iModelHandle, OpacityRate);
	}

	/* �����x�m�F */
	if (OpacityRate > 0.f)
	{
		// ���S�ɓ����łȂ��ꍇ
		/* ���f���`�� */
		MV1DrawModel(this->iModelHandle);
	}
}

// �����`��
void PlatformLight_Test::BloomDraw()
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
