/* 2024.01.07 ��򕗏� �t�@�C���쐬 */

#include "PlatformBasic.h"

/* ��{�v���b�g�t�H�[���N���X�̐錾 */

// �R���X�g���N�^
PlatformBasic::PlatformBasic() : PlatformBase()
{

}

// �f�X�g���N�^
PlatformBasic::~PlatformBasic()
{

}

// ������
void PlatformBasic::Initialization()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotate);

	/* ���f���g�� */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* �R���W�����t���[���ԍ��擾 */
	//this->SetCollisionFrameNo(MV1SearchFrame(this->iModelHandle, "Collision"));
	this->SetCollisionFrameNo(-1);

	/* �����t���[���ԍ��擾 */
	this->SetLightFrameNo(MV1SearchFrame(this->iModelHandle, "Light"));

	/* �R���W�������\�z */
	MV1SetupCollInfo(this->iModelHandle, this->iGetCollisionFrameNo(), 4, 4, 4);

	/* �R���W�����t���[�����\���ɐݒ� */
	MV1SetFrameVisible(this->iModelHandle, this->iGetCollisionFrameNo(), FALSE);
}

// �`��
void PlatformBasic::Draw()
{
	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
}

// �����`��
void PlatformBasic::BloomDraw()
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
