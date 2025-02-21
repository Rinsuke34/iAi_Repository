/* 2024.12.XX YYYY ZZZZ */

#include "SceneTitle.h"
#include "SceneHome.h"

/* �V�[���u�^�C�g���v�̒�` */

// �R���X�g���N�^
SceneTitle::SceneTitle() : SceneBase("Title", 0, false)
{

	iTitleLogoHandle = LoadGraph("resource/ImageData/Test/TitleLogo.mp4");

	iTitleBackGroundHandle = LoadGraph("resource/ImageData/Test/skysphere1.png");


	/* ������ */
	Initialization();
}

// �f�X�g���N�^
SceneTitle::~SceneTitle()
{

}

// ������
void SceneTitle::Initialization()
{
	/* BGM��ݒ� */
	gpDataList_Sound->BGM_SetHandle(BGM_TITLE);
}

// �v�Z
void SceneTitle::Process()
{
	/* �����ꂩ�̃{�^�������͂��ꂽ��z�[����ǉ� */
	// ���쐬
	/* "����"�����͂��ꂽ���m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// "����"�����͂��ꂽ�Ȃ��
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
	
	// �^�C�g���w�i��`��
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, iTitleBackGroundHandle, FALSE);
	/* �^�C�g�����S��`�� */
	PlayMovieToGraph(iTitleLogoHandle);
	// ���[�r�[�f������ʂ����ς��ɕ`�悵�܂�
	DrawExtendGraph(100, 100, 1000, 600, iTitleLogoHandle, FALSE);


	//�Đ����I�����Ă��邩�m�F
	if (GetMovieStateToGraph(iTitleLogoHandle) == FALSE)
	{
		//�Đ����I�����Ă���ꍇ
		//���[�r�[���폜
		//DeleteGraph(iTitleLogoHandle);

		iTitleLogoHandle = LoadGraph("resource/ImageData/Test/TitleLogo.mp4");
		/* �^�C�g�����S��`�� */
		PlayMovieToGraph(iTitleLogoHandle);
		// ���[�r�[�f������ʂ����ς��ɕ`�悵�܂�
		DrawExtendGraph(100, 100, 1000, 600, iTitleLogoHandle, FALSE);
	}

}
