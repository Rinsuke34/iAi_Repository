/* 2025.02.16 �t�@�C���쐬 ��򕗏� */

#include "SceneResult.h"

/* �V�[��"���U���g"�N���X�̒�` */

// �R���X�g���N�^
SceneResult::SceneResult() : SceneBase("Edit", 80, true)
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
SceneResult::~SceneResult()
{

}

// ������
void SceneResult::Initialization()
{

}

// �v�Z
void SceneResult::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (iGameStatus)
	{
		/* "���U���g"��� */
		case GAMESTATUS_RESULT:
			/* ���肪���͂��ꂽ�� */
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				/* �Q�[����Ԃ�"�G�f�B�b�g"�ɕύX���� */
				this->GameStatusList->SetGameStatus(GAMESTATUS_EDIT);
			}
			break;

		/* �Y������ */
		default:
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
			break;
	}
}

// �`��
void SceneResult::Draw()
{
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "����			�F�G�f�B�b�g��ʂ�");
}
