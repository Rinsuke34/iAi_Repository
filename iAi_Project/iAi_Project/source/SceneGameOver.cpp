/* 2025.02.20 �t�@�C���쐬 ��򕗏� */

#include "SceneGameOver.h"

/* �V�[��"�Q�[���I�[�o�["�N���X�̒�` */

// �R���X�g���N�^
SceneGameOver::SceneGameOver() : SceneBase("GameOver", 200, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList	= dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �摜�擾 */
		this->piGrHandle_GameOver	= ImageList->piGetImage_Movie("GameOver/UI_GameOver");
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
	this->iBlendAlpha += FADE_ALPHA_CHANGE_SPEED;

	/* �A���t�@�u�����h�l���ő�l(255)�𒴂��Ă��邩�m�F */
	if (this->iBlendAlpha > ALPHA_MAX)
	{
		// �ő�l�𒴂��Ă���ꍇ
		/* �ő�l�𒴂��Ȃ��悤�ɕ␳���s�� */
		this->iBlendAlpha = ALPHA_MAX;

		/* "����"�����͂��ꂽ���m�F */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
		{
			// "����"�����͂��ꂽ�Ȃ��
			/* ���[�h�V�[���ǉ��t���O��L���� */
			gpSceneServer->SetAddLoadSceneFlg(true);

			/* ���s�V�[���폜�t���O��L���� */
			gpSceneServer->SetDeleteCurrentSceneFlg(true);

			/* �V�[��"�z�[��"��ǉ� */
			gpSceneServer->AddSceneReservation(new SceneTitle());
			return;
		}
	}
}

// �`��
void SceneGameOver::Draw()
{
	/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iBlendAlpha);

	/* ��ʑS�̂����F�ŕ`�� */
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

	/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	/* �A���t�@�u�����h�l���ő�l(255)�𒴂��Ă��邩�m�F */
	if (this->iBlendAlpha >= ALPHA_MAX)
	{
		// �ő�l�𒴂��Ă���ꍇ
		/* �Q�[���I�[�o�[��ʂ��Đ� */
		PlayMovieToGraph(*this->piGrHandle_GameOver);

		/* "�Q�[���I�[�o�["��`�� */
		DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_GameOver, TRUE);

		/* �Đ����I�����Ă��邩�m�F */
		if (GetMovieStateToGraph(*this->piGrHandle_GameOver) == FALSE)
		{
			// �Đ����I�����Ă���ꍇ
			/* ���[�r�[�̍Đ����Ԃ����������� */
			SeekMovieToGraph(*this->piGrHandle_GameOver, 0);
		}

	}
}

// ���C������
void SceneGameOver::Process_Main()
{

}
