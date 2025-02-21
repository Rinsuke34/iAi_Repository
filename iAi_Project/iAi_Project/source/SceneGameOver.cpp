/* 2025.02.20 �t�@�C���쐬 ��򕗏� */

#include "SceneGameOver.h"

/* �V�[��"�Q�[���I�[�o�["�N���X�̒�` */

// �R���X�g���N�^
SceneGameOver::SceneGameOver() : SceneBase("GameOver", 200, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList	= dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �摜�擾 */
		this->piGrHandle_GameOver	= ImageList->piGetImage("GameOver/gameover_kari");
	}

	/* ������ */
	this->iBlendAlpha	= 0;	// �`�ʂ���摜�̃A���t�@�l(0�`255)
}

// �f�X�g���N�^
SceneGameOver::~SceneGameOver()
{

}

// �v�Z
void SceneGameOver::Process()
{
	/* �A���t�@�u�����h�l�����Z */
	this->iBlendAlpha += 3;

	/* �A���t�@�u�����h�l���ő�l(255)�𒴂��Ă��邩�m�F */
	if (this->iBlendAlpha > 255)
	{
		// �ő�l�𒴂��Ă���ꍇ
		/* �ő�l�𒴂��Ȃ��悤�ɕ␳���s�� */
		this->iBlendAlpha = 255;

		/* "����"�����͂��ꂽ���m�F */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
		{
			// "����"�����͂��ꂽ�Ȃ��
			/* ���[�h�V�[���ǉ��t���O��L���� */
			gpSceneServer->SetAddLoadSceneFlg(true);

			/* ���s�V�[���폜�t���O��L���� */
			gpSceneServer->SetDeleteCurrentSceneFlg(true);

			/* �V�[��"�z�[��"��ǉ� */
			gpSceneServer->AddSceneReservation(new SceneHome());
			return;
		}
	}
}

// �`��
void SceneGameOver::Draw()
{
	/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iBlendAlpha);

	/* "�Q�[���I�[�o�["��`�� */
	DrawGraph(0, 0, *this->piGrHandle_GameOver, TRUE);

	/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

// ���C������
void SceneGameOver::Process_Main()
{

}
