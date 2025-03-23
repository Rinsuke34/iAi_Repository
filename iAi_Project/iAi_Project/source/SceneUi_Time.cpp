/* 2025.03.22 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Time.h"

/* UI(����)�N���X�̒�` */
// �R���X�g���N�^
SceneUi_Time::SceneUi_Time() : SceneBase("UI_Time", 106, false)
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

		/* �e�L�X�g�t���[�� */
		this->piGrHandle_Text_Frame = ImageList->piGetImage("UI_Player_Blood/UI_Blood_Timer_Frame");
	}
}

// �v�Z
void SceneUi_Time::Process()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ȊO�ł���Ȃ�V�[�����폜 */
	if (this->StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
		return;
	}
	/* �X�e�[�W�J�n����̌o�ߎ��Ԃ��擾 */
	// ����~���Ԃ��܂߂�
	int iElapsedTime = GetNowCount() - this->StageStatusList->iGetStartTime() - this->StageStatusList->iGetStopTotalTime();

	/* ���݂̌o�ߎ��Ԃ̕��̒l���擾 */
	this->iTimeMinute = iElapsedTime / 1000 / 60;

	/* ���݂̌o�ߎ��Ԃ̕b�̒l���擾 */
	this->iTimeSecond = iElapsedTime / 1000 % 60;

	/* ���݂̌o�ߎ��Ԃ̏����b�̒l���擾 */
	this->iTimeFractionalSecond = iElapsedTime % 1000 / 10;
}

// �`��
void SceneUi_Time::Draw()
{
	/* �e�L�X�g�t���[����`�� */
	DrawGraph(60, 35, *this->piGrHandle_Text_Frame, true);

	/* ���݂̌o�ߎ��Ԃ�`�� */
	DrawFormatStringToHandle(60, 35, GetColor(0, 0, 0), giFontHandle_Medium, "%02d'%02d''%02d", this->iTimeMinute, this->iTimeSecond, this->iTimeFractionalSecond);
}
