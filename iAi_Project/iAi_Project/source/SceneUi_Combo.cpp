/* 2025.01.28 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Combo.h"

/* UI(�R���{)�N���X�̒�` */

// �R���X�g���N�^
SceneUi_Combo::SceneUi_Combo() : SceneBase("UI_Combo", 103, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �R���{�t���[�� */
		this->iCgHandle_Combo_Frame			= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/UI_Player_ComboGrade_frame.png");

		/* �R���{�^�C�}�[ */
		this->iCgHandle_Combo_Timer			= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/UI_Player_ComboTimer.png");

		/* �R���{�A���t�@�x�b�g */
		this->iCgHandle_Combo_Alphabet[0]	= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_D.png");
		this->iCgHandle_Combo_Alphabet[1]	= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_C.png");
		this->iCgHandle_Combo_Alphabet[2]	= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_B.png");
		this->iCgHandle_Combo_Alphabet[3]	= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_A.png");
		this->iCgHandle_Combo_Alphabet[4]	= LoadGraph("resource/ImageData/UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_S.png");
	}
}

// �f�X�g���N�^
SceneUi_Combo::~SceneUi_Combo()
{
	/* �摜�폜 */
	{
		/* �R���{�t���[�� */
		DeleteGraph(this->iCgHandle_Combo_Frame);

		/* �R���{�^�C�}�[ */
		DeleteGraph(this->iCgHandle_Combo_Timer);

		/* �R���{�A���t�@�x�b�g */
		DeleteGraph(this->iCgHandle_Combo_Alphabet[0]);
		DeleteGraph(this->iCgHandle_Combo_Alphabet[1]);
		DeleteGraph(this->iCgHandle_Combo_Alphabet[2]);
		DeleteGraph(this->iCgHandle_Combo_Alphabet[3]);
		DeleteGraph(this->iCgHandle_Combo_Alphabet[4]);
	}
}

// �v�Z
void SceneUi_Combo::Process()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ȊO�ł���Ȃ�V�[�����폜 */
	if (this->GameStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
		return;
	}
}

// �`��
void SceneUi_Combo::Draw()
{
	/* �R���{�t���[���`��(��) */
	DrawGraph(100, 360, this->iCgHandle_Combo_Frame, TRUE);

	/* �R���{�^�C�}�[�`��(��) */
	DrawGraph(100, 360, this->iCgHandle_Combo_Timer, TRUE);
}
