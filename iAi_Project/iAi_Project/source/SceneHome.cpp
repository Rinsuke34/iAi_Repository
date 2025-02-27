/* 2024.12.XX YYYY ZZZZ */

#include "SceneHome.h"
#include "SceneGame.h"


/* �V�[��"�z�[�����"�̒�` */

// �R���X�g���N�^
SceneHome::SceneHome() : SceneBase("Home", 0, true)
{
	/* BGM��ݒ� */
	gpDataList_Sound->BGM_SetHandle(BGM_HOME);
}

// �f�X�g���N�^
SceneHome::~SceneHome()
{

}

// ������
void SceneHome::Initialization()
{
	
}

// �v�Z
void SceneHome::Process()
{
	/* �����ꂩ�̃{�^�������͂��ꂽ��V�[�����폜 */
	/* ���肪���͂��ꂽ�� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		/* �`���[�g���A���t���O��L���� */
		gbTutorialFlg = true;

		/* ���[�h��ʒǉ��t���O��L���� */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* ���s�V�[���폜�t���O��L���� */
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* �V�[��"�Q�[��"��ǉ� */
		gpSceneServer->AddSceneReservation(new SceneGame());
		return;
	}
	/* �L�����Z�������͂��ꂽ�� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
	{
		/* �`���[�g���A���t���O�𖳌��� */
		gbTutorialFlg = false;

		/* ���[�h��ʒǉ��t���O��L���� */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* ���s�V�[���폜�t���O��L���� */
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* �V�[��"�Q�[��"��ǉ� */
		gpSceneServer->AddSceneReservation(new SceneGame());
		return;
	}
}

// �`��
void SceneHome::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "����			�F�X�e�[�W0_1(�`���[�g���A��)��");
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "�L�����Z��	�F�X�e�[�W1_1��");
}
