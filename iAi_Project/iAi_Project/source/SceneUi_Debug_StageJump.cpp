/* 2025.03.11 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Debug_StageJump.h"

/* UI(�f�o�b�O���j���[/�X�e�[�W�W�����v)�N���X�̒�` */
// �R���X�g���N�^
SceneUi_Debug_StageJump::SceneUi_Debug_StageJump() : SceneBase("UI_Debug_StageJump", 201, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* ������ */
	this->iJumpStageNo = 0;
}

// �v�Z
void SceneUi_Debug_StageJump::Process()
{
	/* �オ������Ă��邩�m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
	{
		// ������Ă���ꍇ
		/* �X�e�[�W�ԍ���+1���� */
		this->iJumpStageNo += 1;
	}

	/* ����������Ă��邩�m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		// ������Ă���ꍇ
		/* �X�e�[�W�ԍ���-1���� */
		this->iJumpStageNo -= 1;
	}

	/* ���肪������Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// ������Ă���ꍇ
		/* �X�e�[�W��Ԃ�"�X�e�[�W�W�����v"�ɐݒ� */
		this->StageStatusList->SetGameStatus(GAMESTATUS_STAGE_JUMP);

		/* �W�����v��X�e�[�W�ԍ���ݒ� */
		this->StageStatusList->SetJumpStageNo(this->iJumpStageNo);

		/* �V�[�����폜���� */
		this->bDeleteFlg = true;
	}

	/* �L�����Z����������Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
	{
		// ������Ă���ꍇ
		/* �V�[�����폜���� */
		this->bDeleteFlg = true;
	}

	/* �X�e�[�W�ԍ���͈͓��ɕύX */
	if (this->iJumpStageNo < 0)
	{
		// 0�����̏ꍇ
		/* �X�e�[�W�ԍ������������� */
		this->iJumpStageNo = 0;
	}
	else if (this->iJumpStageNo >= STAGE_MAX)
	{
		// �X�e�[�W���ȏ�̏ꍇ
		/* �X�e�[�W�ԍ����Ō�̃X�e�[�W�ɐݒ� */
		this->iJumpStageNo = STAGE_MAX - 1;
	}
}

// �`��
void SceneUi_Debug_StageJump::Draw()
{
	DrawBox(850, 350, 1400, 350 + 16 * 1, GetColor(0, 0, 0), TRUE);
	DrawFormatString(850, 350, GetColor(255, 255, 255), "�W�����v��X�e�[�W�ԍ� :");
	DrawFormatString(1200, 350, GetColor(255, 255, 255), STAGE_NAME[this->iJumpStageNo].c_str());
}
