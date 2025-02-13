/* 2025.01.16 �t�@�C���쐬 ��򕗏� */

#include "SceneStage.h"

/* �X�e�[�W�N���X�̒�` */

// �R���X�g���N�^
SceneStage::SceneStage(): SceneBase("Stage", 1, true)
{
	/* �f�[�^���X�g�쐬 */
	{
		/* �f�[�^���X�g�T�[�o�[��"�v���C���[���"��ǉ� */
		gpDataListServer->AddDataList(new DataList_PlayerStatus());

		/* �f�[�^���X�g�T�[�o�[��"�I�u�W�F�N�g�Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_Object());
	}

	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�v���C���[���"���擾 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "3D���f���Ǘ�"���擾 */
		this->ModelList			= dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList	= dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* UI�ǉ� */
	{
		/* �N���X�w�A */
		gpSceneServer->AddSceneReservation(new SceneUi_Crosshairs());

		/* HP */
		gpSceneServer->AddSceneReservation(new SceneUi_Hp());

		/* �N�i�C */
		gpSceneServer->AddSceneReservation(new SceneUi_Kunai());

		/* �R���{ */
		gpSceneServer->AddSceneReservation(new SceneUi_Combo());

		/* �u���b�h */
		gpSceneServer->AddSceneReservation(new SceneUi_Blood());

		/* �G�f�B�b�g */
		gpSceneServer->AddSceneReservation(new SceneUi_Edit());
	}

	/* �}�b�v�n���h���쐬 */
	// �摜�n���h��
	this->iLightMapScreenHandle				= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle_DownScale	= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iLightMapScreenHandle_Gauss		= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iMainScreenHandle					= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iMainScreenEffectHandle			= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	// �V���h�E�}�b�v�n���h��
	this->iShadowMapScreenHandle			= MakeShadowMap(SHADOWMAP_SIZE, SHADOWMAP_SIZE);
	// �}�X�N�n���h��
	this->iMotionBlurMaskHandle				= LoadMask("resource/ImageData/Mask/Mask_MotionBlur.png");

	/* ������ */
	Initialization();
}

// �f�X�g���N�^
SceneStage::~SceneStage()
{
	/* �f�[�^���X�g�폜 */
	gpDataListServer->DeleteDataList("DataList_PlayerStatus");	// �v���C���[���
	gpDataListServer->DeleteDataList("DataList_Object");		// �I�u�W�F�N�g�Ǘ�

	/* �}�b�v�n���h���폜 */
	// �摜�n���h��
	DeleteGraph(this->iLightMapScreenHandle);
	DeleteGraph(this->iLightMapScreenHandle_DownScale);
	DeleteGraph(this->iLightMapScreenHandle_Gauss);
	DeleteGraph(this->iMainScreenHandle);
	DeleteGraph(this->iMainScreenEffectHandle);
	// �V���h�E�}�b�v
	DeleteShadowMap(this->iShadowMapScreenHandle);
	// �}�X�N�n���h��
	DeleteMask(this->iMotionBlurMaskHandle);
	// �V�F�[�_�[�n���h��
	DeleteShader(this->iSpeedLineShaderHandle);
}

// ������
void SceneStage::Initialization()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ɕύX */
	this->GameStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
}

// �v�Z
void SceneStage::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (iGameStatus)
	{
		/* "�Q�[�����s"��� */
		case GAMESTATUS_PLAY_GAME:
			/* ���ׂẴI�u�W�F�N�g�̍X�V */
			ObjectList->UpdateAll();

			/* �폜�t���O���L���ȃI�u�W�F�N�g�̍폜 */
			ObjectList->DeleteAll();
			break;

		/* "�G�f�B�b�g"��� */
		case GAMESTATUS_EDIT:
			/* �G�f�B�b�g��ʍ쐬���� */
			{
				/* �J�������[�h��"�Œ�"�ɕύX */
				this->PlayerStatusList->SetCameraMode(CAMERA_MODE_LOCK);

				/* �V�[��"�G�f�B�b�g���"���쐬 */
				SceneBase* pAddScene = new SceneEdit();

				/* �V�[��"�G�f�B�b�g���"���V�[���T�[�o�[�ɒǉ� */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "���̃X�e�[�W�֑J��"��� */
		case GAMESTATUS_NEXTSTAGE:
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;

			/* �Q�[����Ԃ�"�Q�[�����s"�ɕύX���� */
			this->GameStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
			break;
	}

	// �f�o�b�O���j���[���o��(�G���^�[�L�[)
	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
	{
		gpSceneServer->AddSceneReservation(new SceneUi_Debug());
	}
}

// �f�o�b�O�`��
void SceneStage::DrawDebug()
{
	int iDrawCount = 0;

	/* �V���h�E�}�b�v�`�� */
	if (gbDrawShadowMapFlg == true)
	{
		TestDrawShadowMap(iShadowMapScreenHandle, SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1));
		iDrawCount++;
	}

	/* ���C�g�}�b�v�`�� */
	if (gbDrawLightMapFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1), this->iLightMapScreenHandle, FALSE);
		iDrawCount++;
	}

	/* ���C�g�}�b�v(�k��)�`�� */
	if (gbDrawLightMapDownScaleFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1), this->iLightMapScreenHandle_DownScale, FALSE);
		iDrawCount++;
	}

	/* ���C�g�}�b�v(�ڂ���)�`�� */
	if (gbDrawLightMapGaussFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1), this->iLightMapScreenHandle_Gauss, FALSE);
		iDrawCount++;
	}
}
