/* 2024.12.XX YYYY ZZZZ */

#include "SceneTitle.h"
#include "SceneHome.h"

/* �V�[���u�^�C�g���v�̒�` */

// �R���X�g���N�^
SceneTitle::SceneTitle() : SceneBase("Title", 0, false)
{

}

// �f�X�g���N�^
SceneTitle::~SceneTitle()
{

}

// ������
void SceneTitle::Initialization()
{
	/* SceneBase�̏����������{(���\�[�X�����΍�) */
	SceneBase::Initialization();
}

// �v�Z
void SceneTitle::Process()
{
	/* �����ꂩ�̃{�^�������͂��ꂽ��z�[����ǉ� */
	// ���쐬
	/* ���肪���͂��ꂽ�� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		/* ���[�h�V�[���ǉ��t���O��L���� */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* ���s�V�[���폜�t���O��L���� */
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* �V�[��"�z�[��"��ǉ� */
		gpSceneServer->AddSceneReservation(new SceneHome());
		return;
	}
}

// �`��
void SceneTitle::Draw()
{
	
}
