/* 2025.01.19 �t�@�C���쐬 ��򕗏� */

#include "SceneEdit.h"

/* �V�[��"�G�f�B�b�g"�N���X�̒�` */

// �R���X�g���N�^
SceneEdit::SceneEdit() : SceneBase("Edit", 100, true)
{

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
	/* ���肪���͂��ꂽ�� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// ���̃V�[���̍폜�t���O��L���ɂ���
		this->bDeleteFlg = true;
		return;
	}
}

// �`��
void SceneEdit::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "����			�F���̃X�e�[�W��");
}