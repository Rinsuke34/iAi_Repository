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

		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList	= dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "�I�v�V�����ݒ�Ǘ�"���擾 */
		this->OptionList		= dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* �}�b�v�n���h���쐬 */
	// �摜�n���h��
	this->iMainScreenHandle					= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle				= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle_DownScale	= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iLightMapScreenHandle_Gauss		= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	// �V���h�E�}�b�v�n���h��
	this->iShadowMapScreenHandle			= MakeShadowMap(1028 * 2, 1028 * 2);

	/* ������ */
	/* �J�����Œ���W�̏����� */
	for (int i = 0; i < CAMERA_FIXED_POSITION_MAX; ++i)
	{
		vecCameraPositionInfo[i].iNo			= i;
		vecCameraPositionInfo[i].bUseFlg		= false;
		vecCameraPositionInfo[i].vecPosition	= VGet(0, 0, 0);
		vecCameraPositionInfo[i].vecTarget		= VGet(0, 0, 0);
	}
	this->iNowCameraFixedPositionNo		= CAMERA_FIXED_POSITION_START;	// ���݂̃J�����Œ���W�ԍ�
	this->iOldCameraFixedPositionNo		= CAMERA_FIXED_POSITION_START;	// �ύX�O�̃J�����Œ���W�ԍ�
	this->iMaxCameraFixedPositionNo		= CAMERA_FIXED_POSITION_START;	// �J�����Œ���W�ԍ�����
	this->iBlendAlpha_StageClear_Fadein	= 0;							// �X�e�[�W�N���A���̃t�F�[�h�C���̃A���t�@�l
	this->iStageClear_Count				= 0;							// �X�e�[�W�N���A���̏����Ŏg�p����J�E���g
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
	// �V���h�E�}�b�v
	DeleteShadowMap(this->iShadowMapScreenHandle);
}

// ������
void SceneStage::Initialization()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ɕύX */
	this->StageStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);

	/* UI��ǉ����邩�m�F*/
	if (this->StageStatusList->bGetAddUiFlg() == true)
	{
		// �ǉ�����ꍇ
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
	}

	/* �ŏ��ɃG�f�B�b�g��ʂ�ǉ����邩�m�F */
	if (this->StageStatusList->bGetFastEditFlg() == true)
	{
		// �ǉ�����ꍇ
		/* �Q�[����Ԃ�"�G�f�B�b�g"��ԂɕύX */
		this->StageStatusList->SetGameStatus(GAMESTATUS_EDIT);
	}

	/* �X�e�[�W�J�n���̎��Ԃ�ݒ� */
	this->StageStatusList->SetStartTime(GetNowCount());

	/* �J�������[�h��"�t���[���[�h"�ɐݒ� */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_NORMAL);
}

// �v�Z
void SceneStage::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->StageStatusList->iGetGameStatus();

	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (iGameStatus)
	{
		/* "�Q�[�����s"��� */
		case GAMESTATUS_PLAY_GAME:
			Process_Main();
			break;

		/* "�X�e�[�W�N���A����"��� */
		case GAMESTATUS_STAGE_CLEAR_SETUP:
			Process_StageClear();
			break;

		/* "�X�e�[�W�N���A"��� */
		case GAMESTATUS_STAGE_CLEAR:
			{
				/* �V�[��"�X�e�[�W�N���A���"���쐬 */
				SceneBase* pAddScene = new SceneGameClear();

				/* �V�[��"�X�e�[�W�N���A���"���V�[���T�[�o�[�ɒǉ� */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "���U���g"��� */
		case GAMESTATUS_RESULT:
			{
				/* �V�[��"���U���g���"���쐬 */
				SceneBase* pAddScene = new SceneResult();

				/* �V�[��"���U���g���"���V�[���T�[�o�[�ɒǉ� */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "�G�f�B�b�g"��� */
		case GAMESTATUS_EDIT:
			/* �V�[��"�G�f�B�b�g���"���쐬 */
			{
				SceneBase* pAddScene = new SceneEdit();

				/* �V�[��"�G�f�B�b�g���"���V�[���T�[�o�[�ɒǉ� */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "���̃X�e�[�W�֑J��"��� */
		case GAMESTATUS_NEXTSTAGE:
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
			break;

		/* "�Q�[���I�[�o�["��� */
		case GAMESTATUS_GAMEOVER:
			{
				/* �V�[��"�Q�[���I�[�o�["���쐬 */
				SceneBase* pAddScene = new SceneGameOver();

				/* �V�[��"�Q�[���I�[�o�["���V�[���T�[�o�[�ɓo�^ */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "���Z�b�g"��� */
		case GAMESTATUS_RESET:
			/* ���ׂẴI�u�W�F�N�g�̃��Z�b�g���������s���� */
			ObjectList->ResetAll();

			/* �X�e�[�W��Ԃ����������� */
			Initialization();

			/* �Q�[����Ԃ�"�Q�[�����s"�ɕύX */
			StageStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
			break;

		/* "�Q�[���J�n"��� */
		case GAMESTATUS_START:
			Process_StageStart();
			break;

		/* �X�e�[�W�W�����v */
		case GAMESTATUS_STAGE_JUMP:
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
			break;
	}

	/* �J�����ݒ菀�� */
	SetCamera_Setup();

	/* �G�t�F�N�g�X�V */
	UpdateEffekseer3D();
}

// �v�Z(���C���̏���)
void SceneStage::Process_Main()
{
	/* 2025.03.12 �R�����g�A�E�g �e�r�듹 */
	/* �X���[���[�V�����t���O���L���ł��邩�m�F */
	//if (StageStatusList->bGetGameSlowFlg() == true)
	//{
	//	// �L���ł���ꍇ
	//	/* �X���[���[�V�����J�E���g���擾 */
	//	int iSlowCount = StageStatusList->iGetSlowCount();

	//	/* �X���[���[�V�����̃J�E���g��0�ł��邩�m�F */
	//	if (iSlowCount <= 0)
	//	{
	//		// 0�ł���ꍇ
	//		/* �J�E���g������������ */
	//		StageStatusList->SetSlowCount(SLOW_SPEED);
	//	}
	//	else
	//	{
	//		// 0�łȂ��ꍇ
	//		/* �J�E���g��-1���� */
	//		StageStatusList->SetSlowCount(iSlowCount - 1);

	//		/* �v�Z�������I������ */
	//		return;
	//	}
	//}

	/* ���ׂẴI�u�W�F�N�g�̍X�V */
	ObjectList->UpdateAll();

	/* �폜�t���O���L���ȃI�u�W�F�N�g�̍폜 */
	ObjectList->DeleteAll();

	/* �v���C���[�����݂��Ă��āA���S�t���O���L���ł��邩�m�F */
	if ((this->ObjectList->GetCharacterPlayer() != nullptr) && (this->PlayerStatusList->bGetPlayerDeadFlg() == true))
	{
		// �v���C���[�����݂����S�t���O���L���Ȃ��
		/* �Q�[����Ԃ�"�Q�[���I�[�o�["�ɕύX���� */
		this->StageStatusList->SetGameStatus(GAMESTATUS_GAMEOVER);
	}

	/* UI�ǉ��t���O���L���ł���(�Q�[�����ł���)���m�F */
	if (this->StageStatusList->bGetAddUiFlg() == true)
	{
		// �L���ł���ꍇ
		/* �I�v�V�����{�^����������Ă��邩 */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_PAUSE) == true)
		{
			// ������Ă���ꍇ
			/* �V�[��"�ꎞ��~"��ǉ� */
			gpSceneServer->AddSceneReservation(new ScenePause());
		}

		/* �G���^�[�L�[����͂��ꂽ���m�F */
		if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
		{
			/* �V�[��"�ꎞ��~"��ǉ� */
			gpSceneServer->AddSceneReservation(new SceneUi_Debug());
		}
	}
}

// �v�Z(�X�e�[�W�N���A���̏���)
void SceneStage::Process_StageClear()
{
	/* �J�������[�h��"�X�e�[�W�N���A"�ɐݒ� */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_STAGECLEAR);

	/* �N���A���J�E���g���J�n���̏�Ԃł��邩 */
	if (this->iStageClear_Count == STAGECLEAR_COUNT_START)
	{
		// �J�n���̏�Ԃł���ꍇ
		/* �X�e�[�W�N���A���̎��Ԃ�ݒ肷�� */
		this->StageStatusList->SetClearTime(GetNowCount());
	}

	/* �N���A���J�E���g���t�F�[�h�C���J�n�ɒB���Ă��邩�m�F */
	if (this->iStageClear_Count >= STAGECLEAR_COUNT_START_FADEIN)
	{
		// �B���Ă���ꍇ
		/* �t�F�[�h�C���̃A���t�@�u�����h�l�����Z */
		this->iBlendAlpha_StageClear_Fadein += FADE_ALPHA_CHANGE_SPEED;
	}

	/* �N���A���J�E���g�����U���g�J�n�ɒB���Ă��邩�m�F */
	if (this->iStageClear_Count >= STAGECLEAR_COUNT_START_RESULT)
	{
		// �B���Ă���ꍇ
		/* �Q�[����Ԃ�"�X�e�[�W�N���A"�ɕύX */
		StageStatusList->SetGameStatus(GAMESTATUS_STAGE_CLEAR);
	}

	/* �X�e�[�W�N���A�̃J�E���g�����Z */
	this->iStageClear_Count += 1;
}

// �v�Z(�X�e�[�W�J�n���̏���)
void SceneStage::Process_StageStart()
{
	/* �J�������[�h��"�X�e�[�W�J�n"�ɐݒ� */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_STAGESTART);

	/* �J�����Œ���W�̒l���ő�l�𒴂��Ă��邩�m�F */
	if (this->iNowCameraFixedPositionNo >= this->iMaxCameraFixedPositionNo - 1)
	{
		// �����Ă���ꍇ
		/* �X�e�[�W��Ԃ����������� */
		Initialization();

		return;
	}

	/* �v���C���[�A�G�l�~�[�ȊO�̃I�u�W�F�N�g�̍X�V */
	//ObjectList->UpdatePlayer();
	ObjectList->UpdateSkySqhere();
	ObjectList->UpdateEffect();
	ObjectList->UpdateBullet();
	ObjectList->UpdatePlatform();
	ObjectList->UpdateEffectItem();
	ObjectList->UpdatePickUpItem();
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
