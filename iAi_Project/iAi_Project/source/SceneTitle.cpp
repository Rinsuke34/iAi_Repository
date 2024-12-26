/* 2024.12.XX YYYY ZZZZ */

#include "SceneTitle.h"
#include "SceneHome.h"

#include "SceneInputConfig.h"

/* �V�[���u�^�C�g���v�̒�` */

// �R���X�g���N�^
SceneTitle::SceneTitle() : SceneBase("Title", 0, false)
{
	/* �񓯊��ǂݍ��݂�L�������� */
	SetUseASyncLoadFlag(true);

	/* �񓯊��ǂݍ��݂𖳌������� */
	SetUseASyncLoadFlag(false);
}

// �f�X�g���N�^
SceneTitle::~SceneTitle()
{

}

// �v�Z
void SceneTitle::Process()
{
	/* �����ꂩ�̃{�^�������͂��ꂽ��z�[����ǉ� */
	// ���쐬
	/* ���肪���͂��ꂽ�� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		gpSceneServer->AddSceneReservation(new SceneHome(), true);
		//gpSceneServer->AddSceneReservation(new SceneInputConfig(), true);
		return;
	}
}

// �`��
void SceneTitle::Draw()
{
	
}
