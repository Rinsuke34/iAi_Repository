/* 2024.12.XX YYYY ZZZZ */

#include "SceneTitle.h"


/* �V�[���u�^�C�g���v�̒�` */

// �R���X�g���N�^
SceneTitle::SceneTitle() : SceneBase("Title", 10, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "���͊Ǘ�"���擾 */
		this->InputList = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	}

	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �^�C�g�����S */
		this->piGrHandle_TitleLogo = ImageList->piGetImage_Movie("Test/TitleLogo");
	}

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
	this->pSceneStage = new SceneStage();

	/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
	gpSceneServer->AddSceneReservation(this->pSceneStage);

	/* �X�e�[�W�̓ǂݍ��݂��J�n */
	dynamic_cast<SceneStage*>(this->pSceneStage)->LoadMapData();

	/* ���������� */
	this->pSceneStage->Initialization();

	this->UICount = 0;

	pSceneStage->iGetNowCameraFixedPositionNo();
	pSceneStage->SetNowCameraFixedPositionNo(0);
}

// �f�X�g���N�^
SceneTitle::~SceneTitle()
{
	
}

// ������
void SceneTitle::Initialization()
{
	
}

// �v�Z
void SceneTitle::Process()
{
	
	
	/* �L�[�{�[�h����ړ��������擾 */
	/* �O�i */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
	{
		UICount++;
		if (UICount >= CAMERA_FIXED_POSITION_MAX)
		{
			UICount = 1;
		}
	pSceneStage->iGetNowCameraFixedPositionNo();
		pSceneStage->SetNowCameraFixedPositionNo(UICount);
	}

	/* ��� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
	{
		UICount--;
		if (UICount < 0)
		{
			UICount = CAMERA_FIXED_POSITION_E;

		}
		pSceneStage->iGetNowCameraFixedPositionNo();
		pSceneStage->SetNowCameraFixedPositionNo(UICount);
	}
	

	/* �����ꂩ�̃{�^�������͂��ꂽ��V�[�����폜 */
	/* ���肪���͂��ꂽ�� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		/* ���[�h��ʒǉ��t���O��L���� */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* ���s�V�[���폜�t���O��L���� */
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* �V�[��"�Q�[��"��ǉ� */
		gpSceneServer->AddSceneReservation(new SceneAddStageSetup());
		return;
	}
}

// �`��
void SceneTitle::Draw()
{
	/* �`��u�����h���[�h�����Z�ɂ��� */
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	/* �^�C�g�����S���Đ� */
	PlayMovieToGraph(*this->piGrHandle_TitleLogo);

	/* ���[�r�[��`�� */
	DrawGraph(100, -100, *this->piGrHandle_TitleLogo, TRUE);

	/* �Đ����I�����Ă��邩�m�F */
	if (GetMovieStateToGraph(*this->piGrHandle_TitleLogo) == FALSE)
	{
		// �Đ����I�����Ă���ꍇ
		/* ���[�r�[�̍Đ����Ԃ����������� */
		SeekMovieToGraph(*this->piGrHandle_TitleLogo, 0);
	}

	/* �`��u�����h���[�h���u�����h�����ɖ߂� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/* �`�惂�[�h���A���X�g�ɖ߂� */
	SetDrawMode(DX_DRAWMODE_NEAREST);

	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "����			�F�X�e�[�W1_1��");
}
