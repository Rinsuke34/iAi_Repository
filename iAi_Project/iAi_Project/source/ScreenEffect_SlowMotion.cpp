/* 2025.03.12 ��򕗏� �t�@�C���쐬 */

#include "ScreenEffect_SlowMotion.h"

/* ��ʃG�t�F�N�g(�X���[���[�V����)�N���X�̒�` */
// �R���X�g���N�^
ScreenEffect_SlowMotion::ScreenEffect_SlowMotion() : ScreenEffect_Base()
{
	/* �g�p����f�[�^���X�g */
	this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
}

// �X�V
void ScreenEffect_SlowMotion::Update(int iGrHandle_Screen)
{
	// ����
	// iGrHandle_Screen : �`�ʂ���摜�̃n���h��

	/* ��ʃG�t�F�N�g�`�� */
	ScreenEffectDraw(iGrHandle_Screen);

	/* �X���[���[�V�����t���O�������ł��邩�m�F */
	if(StageStatusList->bGetGameSlowFlg() == false)
	{
		// �����ł���ꍇ
		/* �폜�t���O��L���� */
		this->bDeleteFlg = true;
	}
}

// ��ʃG�t�F�N�g�`��
void ScreenEffect_SlowMotion::ScreenEffectDraw(int iGrHandle_Screen)
{
	// ����
	// iGrHandle_Screen : �`�ʂ���摜�̃n���h��

	/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);

	/* ��ʑS�̂�F�ŕ`�� */
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 255), TRUE);

	/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
