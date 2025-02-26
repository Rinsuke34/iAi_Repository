/* 2024.12.XX YYYY ZZZZ */

#include "SceneTitle.h"
#include "SceneHome.h"

/* �V�[���u�^�C�g���v�̒�` */

// �R���X�g���N�^
SceneTitle::SceneTitle() : SceneBase("Title", 10, false)
{
	iTitleLogoHandle = LoadGraph("resource/ImageData/Test/TitleLogo.mp4");

	//iTitleBackGroundHandle = LoadGraph("resource/ImageData/Test/skysphere1.png");

	/* �f�[�^���X�g�擾 */
	{
		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

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

	/* �ŏ��̃X�e�[�W�ԍ���"�^�C�g��/�z�[��"�ɐݒ� */
	this->StageStatusList->SetNowStageNo(STAGE_NO_TITLE);

	/* �J�������[�h��"�^�C�g��"�ɐݒ� */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_TITLE);

	/* UI�ǉ��t���O�𖳌��� */
	this->StageStatusList->SetAddUiFlg(false);

	/* "�^�C�g��"�̃X�e�[�W��ǂݍ��� */
	/* �V�[��"�^�C�g��"���쐬 */
	SceneBase* pAddScene = new SceneStage();

	/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
	gpSceneServer->AddSceneReservation(pAddScene);

	/* �X�e�[�W�̓ǂݍ��݂��J�n */
	dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();

	/* ���������� */
	pAddScene->Initialization();
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
	/* �`��u�����h���[�h�����Z�ɂ��� */
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	
	// �^�C�g���w�i��`��
	//DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, iTitleBackGroundHandle, FALSE);
	/* �^�C�g�����S��`�� */
	PlayMovieToGraph(iTitleLogoHandle);
	// ���[�r�[�f������ʂ����ς��ɕ`�悵�܂�
//	DrawExtendGraph(100, 100, 1000, 600, iTitleLogoHandle, TRUE);
	DrawGraph(100, -100, iTitleLogoHandle, TRUE);


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
		DrawExtendGraph(100, 100, 1000, 600, iTitleLogoHandle, TRUE);
	}

	/* �`��u�����h���[�h���u�����h�����ɖ߂� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/* �`�惂�[�h���A���X�g�ɖ߂� */
	SetDrawMode(DX_DRAWMODE_NEAREST);
}
