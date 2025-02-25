/* 2025.01.28 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Combo.h"

/* UI(�R���{)�N���X�̒�` */

// �R���X�g���N�^
SceneUi_Combo::SceneUi_Combo() : SceneBase("UI_Combo", 103, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�v���C���[���"���擾 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList	= dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �R���{�t���[�� */
		this->piGrHandle_Combo_Frame	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/UI_Player_ComboGrade_frame_fix");

		/* �R���{�^�C�}�[ */
		this->piGrHandle_Combo_Timer	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/UI_Player_ComboTimer");

		/* �R���{�A���t�@�x�b�g */
		this->piGrHandle_Combo_Alphabet[0]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_D");
		this->piGrHandle_Combo_Alphabet[1]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_C");
		this->piGrHandle_Combo_Alphabet[2]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_B");
		this->piGrHandle_Combo_Alphabet[3]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_A");
		this->piGrHandle_Combo_Alphabet[4]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_B");
	}
}

// �f�X�g���N�^
SceneUi_Combo::~SceneUi_Combo()
{

}

// �v�Z
void SceneUi_Combo::Process()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ȊO�ł���Ȃ�V�[�����폜 */
	if (this->StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
		return;
	}

	/* �R���{�p�����Ԃ��I�����Ă��邩�m�F */
	if (this->PlayerStatusList->iGetPlayerComboDuration() > 0)
	{
		// �I�����Ă��Ȃ��ꍇ
		/* �R���{�p�����Ԃ����Z */
		this->PlayerStatusList->SetPlayerComboDuration(this->PlayerStatusList->iGetPlayerComboDuration() - 1);

		/* ���݂̃R���{�����ő�R���{����葽�����m�F */
		if (this->PlayerStatusList->iGetPlayerComboNowCount() > this->PlayerStatusList->iGetPlayerComboMaxCount())
		{
			// �����ꍇ
			/* �ő�R���{�����X�V */
			this->PlayerStatusList->SetPlayerComboMaxCount(this->PlayerStatusList->iGetPlayerComboNowCount());
		}
	}
	else
	{
		// �I�����Ă���ꍇ
		/* �R���{�������Z�b�g */
		this->PlayerStatusList->SetPlayerComboNowCount(0);
	}
}

// �`��
void SceneUi_Combo::Draw()
{
	/* �R���{�t���[���`��(��) */
	DrawGraph(100, 360, *this->piGrHandle_Combo_Frame, TRUE);

	/* �R���{�^�C�}�[�`��(��) */
	double dComboTimerPercent = (static_cast<double>(this->PlayerStatusList->iGetPlayerComboDuration()) / INIT_ATTRIBUTES_COMBO_DURATION) * 100.0;
	DrawCircleGauge(101 + (176 / 2), 360 + (176 / 2), dComboTimerPercent, *this->piGrHandle_Combo_Timer);

	/* ���݂̃R���{���`��(��) */
	DrawFormatString(400, 360 + 16 * 0, GetColor(255, 255, 255), "���݂̃R���{�� : %d", this->PlayerStatusList->iGetPlayerComboNowCount());

	/* �ő�R���{���`��(��) */
	DrawFormatString(400, 360 + 16 * 1, GetColor(255, 255, 255), "�ő�R���{�� :  %d", this->PlayerStatusList->iGetPlayerComboMaxCount());

	/* �R���{�̎c��p�����ԕ`��(��) */
	DrawFormatString(400, 360 + 16 * 2, GetColor(255, 255, 255), "�R���{�p������ : %d", this->PlayerStatusList->iGetPlayerComboDuration());
}
