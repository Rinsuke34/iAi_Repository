/* 2025.03.05 �t�@�C���ǉ� ��򕗏� */

#include "SceneOption.h"

/* �V�[���u�I�v�V�����v�̒�` */

// �R���X�g���N�^
SceneOption::SceneOption() : SceneBase("Option", 500, true)
{

}

// �f�X�g���N�^
SceneOption::~SceneOption()
{

}

// �v�Z
void SceneOption::Process()
{
	/* �����ꂩ�̃{�^�������͂��ꂽ��V�[�����폜 */
	// ���쐬
	/* ���肪���͂��ꂽ�� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// ���̃V�[���̍폜�t���O��L���ɂ���
		this->bDeleteFlg = true;
		return;
	}
}

// �`��
void SceneOption::Draw()
{
	
}
