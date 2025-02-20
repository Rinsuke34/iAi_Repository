/* 2025.02.20 �t�@�C���쐬 ��򕗏� */

#include "SceneGameOver.h"

/* �V�[��"�Q�[���I�[�o�["�N���X�̒�` */

// �R���X�g���N�^
SceneGameOver::SceneGameOver() : SceneBase("GameOver", 200, false)
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
	/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iBlendAlpha);

	/* "�Q�[���I�[�o�["��`�� */
	DrawGraph(0, 0, this->iBlendAlpha, TRUE);

	/* �A���t�@�u�����h�l���ő�l�ɓ��B���Ă��邩�m�F */
	if (this->iBlendAlpha >= 255)
	{
		// �ő�l�𒴂��Ă���ꍇ
		/* ���ʃ��C���[�̌v�Z��~�t���O��L���ɂ��� */
		this->bLowerLayerStopFlg = true;
	}

	/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	/* �A���t�@�u�����h�l�����Z */
	this->iBlendAlpha += 3;

	/* �A���t�@�u�����h�l���ő�l(255)�𒴂��Ă��邩�m�F */
	if (this->iBlendAlpha > 255)
	{
		// �ő�l�𒴂��Ă���ꍇ
		/* �ő�l�𒴂��Ȃ��悤�ɕ␳���s�� */
		this->iBlendAlpha = 255;
	}
}

// �`��
void SceneGameOver::Draw()
{

}

// ���C������
void SceneGameOver::Process_Main()
{

}
