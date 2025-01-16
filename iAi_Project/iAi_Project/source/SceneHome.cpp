/* 2024.12.XX YYYY ZZZZ */

#include "SceneHome.h"
#include "SceneGame.h"


/* �V�[���u�z�[���v�̒�` */

// �R���X�g���N�^
SceneHome::SceneHome() : SceneBase("Home", 0, false)
{
	/* �񓯊��ǂݍ��݂�L�������� */
	SetUseASyncLoadFlag(true);

	/* �񓯊��ǂݍ��݂𖳌������� */
	SetUseASyncLoadFlag(false);
}

// �f�X�g���N�^
SceneHome::~SceneHome()
{

}

// �v�Z
void SceneHome::Process()
{
	/* �����ꂩ�̃{�^�������͂��ꂽ��V�[�����폜 */
	/* ���肪���͂��ꂽ�� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		SceneGame* AddScene	= new SceneGame();
		gbTutorialFlg		= true;	// �`���[�g���A���t���O�L����
		gpSceneServer->AddSceneReservation(AddScene, true);
		return;
	}
	/* �L�����Z�������͂��ꂽ�� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
	{
		SceneGame* AddScene = new SceneGame();
		gpSceneServer->AddSceneReservation(AddScene, true);
		return;
	}
}

// �`��
void SceneHome::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "����			�F�X�e�[�W0_1(�`���[�g���A��)��");
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "�L�����Z��	�F�X�e�[�W1_1��");
}
