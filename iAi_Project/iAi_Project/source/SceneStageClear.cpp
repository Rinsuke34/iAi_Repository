/* 2025.03.02 �t�@�C���쐬 ��򕗏� */

#include "SceneStageClear.h"

/* �V�[��"�Q�[���N���A"�N���X�̒�` */
// �R���X�g���N�^
SceneGameClear::SceneGameClear() : SceneBase("GameClear", 200, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}
	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �摜�擾 */
		this->piGrHandle_GameClear = ImageList->piGetImage_Movie("GameClear/UI_GameClear");
	}
}

// �f�X�g���N�^
SceneGameClear::~SceneGameClear()
{

}

// �v�Z
void SceneGameClear::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->StageStatusList->iGetGameStatus();

	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (iGameStatus)
	{
		/* "�X�e�[�W�N���A"��� */
		case GAMESTATUS_STAGE_CLEAR:
			/* ���C���̏��������{ */
			Process_Main();
			break;

		/* �Y������ */
		default:
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
			break;
	}
}

// �`��
void SceneGameClear::Draw()
{
	/* �`��u�����h���[�h�����Z�ɂ��� */
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	/* �X�e�[�W�N���A��ʂ��Đ� */
	PlayMovieToGraph(*this->piGrHandle_GameClear);

	/* "�Q�[���I�[�o�["��`�� */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_GameClear, TRUE);

	/* �Đ����I�����Ă��邩�m�F */
	if (GetMovieStateToGraph(*this->piGrHandle_GameClear) == FALSE)
	{
		// �Đ����I�����Ă���ꍇ
		/* ���[�r�[�̍Đ����Ԃ����������� */
		SeekMovieToGraph(*this->piGrHandle_GameClear, 0);
	}

	/* �`��u�����h���[�h���u�����h�����ɖ߂� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/* �`�惂�[�h���A���X�g�ɖ߂� */
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

// ���C������
void SceneGameClear::Process_Main()
{
	/* "����"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// ���͂���Ă���ꍇ
		/* �Q�[����Ԃ�"���U���g"�ɕύX���� */
		this->StageStatusList->SetGameStatus(GAMESTATUS_RESULT);
	}
};
