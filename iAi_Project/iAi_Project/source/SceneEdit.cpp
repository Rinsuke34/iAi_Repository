/* 2025.01.19 �t�@�C���쐬 ��򕗏� */

#include "SceneEdit.h"

/* �V�[��"�G�f�B�b�g"�N���X�̒�` */

// �R���X�g���N�^
SceneEdit::SceneEdit() : SceneBase("Edit", 100, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));

		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}
}

// �f�X�g���N�^
SceneEdit::~SceneEdit()
{

}

// ������
void SceneEdit::Initialization()
{

}

// �v�Z
void SceneEdit::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (iGameStatus)
	{
		/* "�G�f�B�b�g"��� */
		case GAMESTATUS_EDIT:
			/* ���肪���͂��ꂽ�� */
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				/* �Q�[����Ԃ�"���̃X�e�[�W�֑J��"�ɕύX���� */
				this->GameStatusList->SetGameStatus(GAMESTATUS_NEXTSTAGE);
			}
			break;

		/* "���̃X�e�[�W�֑J��"��� */
		case GAMESTATUS_NEXTSTAGE:
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
			break;
	}
}

// �`��
void SceneEdit::Draw()
{
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "����			�F���̃X�e�[�W��");
}