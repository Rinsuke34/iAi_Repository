/* 2024.12.XX YYYY ZZZZ */

#include "SceneOption.h"

/* �V�[���u�I�v�V�����v�̒�` */

// �R���X�g���N�^
SceneOption::SceneOption() : SceneBase("Option", 0, false)
{

}

// �f�X�g���N�^
SceneOption::~SceneOption()
{

}

// ������
void SceneOption::Initialization()
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
