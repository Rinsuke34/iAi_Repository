/* 2025.01.22 ��򕗏� �t�@�C���쐬 */

#include "BackGroundBase.h"

/* ���ׂẴv���b�g�t�H�[���̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
BackGroundBase::BackGroundBase() : PlatformBase()
{

}

// ������
void BackGroundBase::Initialization()
{
	PlatformBase::Initialization();

	/* �����t���[���ԍ��擾 */
	UpdataLightFrame();
}

// �`��
void BackGroundBase::Draw()
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
void BackGroundBase::BloomDraw()
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

// �����̐ݒ肳�ꂽ�t���[�����擾
void BackGroundBase::UpdataLightFrame()
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
