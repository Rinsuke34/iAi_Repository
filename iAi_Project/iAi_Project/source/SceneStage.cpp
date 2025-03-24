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

		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList	= dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* �}�b�v�n���h���쐬 */
	// �摜�n���h��
	this->iMainScreenHandle					= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle				= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle_DownScale	= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iLightMapScreenHandle_Gauss		= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	// �V���h�E�}�b�v�n���h��
	this->iShadowMapScreenHandle_Actor		= MakeShadowMap(SHADOWMAP_SIZE_ACTOR, SHADOWMAP_SIZE_ACTOR);
	this->iShadowMapScreenHandle_Platform	= MakeShadowMap(SHADOWMAP_SIZE_PLATFORM, SHADOWMAP_SIZE_PLATFORM);

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
	this->iPlayerSlowTime				= 1;							// �v���C���[�̃X���[���[�V�������x
	this->bPlayBgmFlg					= false;						// BGM���Đ��ς݂��̃t���O
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
	DeleteShadowMap(this->iShadowMapScreenHandle_Actor);
	DeleteShadowMap(this->iShadowMapScreenHandle_Platform);
}

// ������
void SceneStage::Initialization()
{
	/* �Q�[����Ԃ�"�Q�[���J�n"�ɕύX */
	this->StageStatusList->SetGameStatus(GAMESTATUS_START);

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

			/* �o�ߎ��� */
			gpSceneServer->AddSceneReservation(new SceneUi_Time());

			/* ������� */
			gpSceneServer->AddSceneReservation(new SceneUi_OperationInstructions());
		}
	}

	/* �ŏ��ɃG�f�B�b�g��ʂ�ǉ����邩�m�F */
	if (this->StageStatusList->bGetFastEditFlg() == true)
	{
		// �ǉ�����ꍇ
		/* �Q�[����Ԃ�"�G�f�B�b�g"��ԂɕύX */
		this->StageStatusList->SetGameStatus(GAMESTATUS_EDIT);

		return;
	}

	/* �X�e�[�W�J�n���̎��Ԃ�ݒ� */
	this->StageStatusList->SetStartTime(GetNowCount());

	/* �X�g�b�v���̍��v���Ԃ������� */
	this->StageStatusList->SetStopTotalTime(0);

	/* �X�e�[�W�J�n���̏����u���b�h����ݒ� */
	this->GameResourceList->SetStartBlood(this->GameResourceList->iGetHaveBlood());

	/* �v���C���[�̃X�e�[�^�X���X�V */
	this->PlayerStatusList->StatusBuffUpdate();

	/* BGM���Đ����Ă��Ȃ���Ԃł��邩�m�F */
	if (this->bPlayBgmFlg == false)
	{
		// �Đ����Ă��Ȃ��ꍇ
		/* �Đ�����BGM�ԍ����擾 */
		int iBgmNo = BGM_STAGE_0;

		/* �X�e�[�W�ԍ��ɉ����čĐ�����BGM��ύX���� */
		switch (this->StageStatusList->iGetNowStageNo())
		{
			case STAGE_NO_1_1:
			case STAGE_NO_1_2:
			case STAGE_NO_1_3:
				iBgmNo = BGM_STAGE_0;
				break;

			case STAGE_NO_2_1:
			case STAGE_NO_2_2:
			case STAGE_NO_2_3:
				iBgmNo = BGM_STAGE_1;
				break;

			case STAGE_NO_3_1:
			case STAGE_NO_3_2:
				iBgmNo = BGM_STAGE_2;
				break;
				
			case STAGE_NO_3_3:
				iBgmNo = BGM_STAGE_3;
				break;
		}

		/* BGM���Đ� */
		gpDataList_Sound->BGM_SetHandle(iBgmNo);

		/* BGM���Đ��ς݂ɐݒ� */
		this->bPlayBgmFlg = true;
	}	
}

// �v�Z
void SceneStage::Process()
{
	/* �G�t�F�N�g���ʏ����X�V�t���O */
	// ���L���Ȃ狤�ʏ����ŃG�t�F�N�g�X�V���s��
	bool bGrobalEffectUpdateFlg	= true;

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

			/* �G�t�F�N�g�X�V�t���O�𖳌��ɂ��� */
			bGrobalEffectUpdateFlg = false;
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
			/* ���݂̃X�e�[�W�ԍ����ŏI�X�e�[�W�łȂ����m�F */
			if (this->StageStatusList->iGetNowStageNo() < this->StageStatusList->iGetEndStageNo())
			{
				// �ŏI�X�e�[�W�łȂ��ꍇ
				/* �V�[��"�G�f�B�b�g���"���V�[���T�[�o�[�ɒǉ� */
				gpSceneServer->AddSceneReservation(new SceneEdit());
			}
			else
			{
				// �ŏI�X�e�[�W�ł���ꍇ
				/* �X�e�[�W��Ԃ�"���̃X�e�[�W�֑J��"�ɐݒ� */
				this->StageStatusList->SetGameStatus(GAMESTATUS_NEXTSTAGE);
			}
			break;

		/* "���̃X�e�[�W�֑J��"��� */
		case GAMESTATUS_NEXTSTAGE:
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
			break;

		/* "�Q�[���I�[�o�["��� */
		case GAMESTATUS_GAMEOVER:
			/* �V�[��"�Q�[���I�[�o�["���V�[���T�[�o�[�ɒǉ� */
			gpSceneServer->AddSceneReservation(new SceneGameOver());
			break;

		/* "���Z�b�g"��� */
		case GAMESTATUS_RESET:
			/* ���ׂẴI�u�W�F�N�g�̃��Z�b�g���������s���� */
			ObjectList->ResetAll();

			/* �����u���b�h���X�e�[�W�J�n���̐ݒ�ɖ߂� */
			this->GameResourceList->SetHaveBlood(this->GameResourceList->iGetStartBlood());

			/* �����N�i�C�����X�e�[�W�J�n���̐ݒ�ɖ߂� */
			this->PlayerStatusList->SetNowHaveKunai(this->PlayerStatusList->iGetStartHaveKunai());

			/* �v���C���[HP���X�e�[�W�J�n���̐ݒ�ɖ߂� */
			this->PlayerStatusList->SetPlayerNowHp(this->PlayerStatusList->iGetPlayerMaxHp());

			/* �X�e�[�W��Ԃ����������� */
			Initialization();
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

	/* �G�t�F�N�g���ʏ����X�V�t���O���L���ł��邩�m�F */
	if (bGrobalEffectUpdateFlg == true)
	{
		// �L���ł���ꍇ
		/* �G�t�F�N�g�X�V */
		UpdateEffekseer3D();
	}
}

// �v�Z(���C���̏���)
void SceneStage::Process_Main()
{
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

			/* "�|�[�Y���j���[�J��"��SE���Đ� */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_POSEMENU);
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

	/* �A�C�e���̍X�V���� */
	ObjectList->UpdateEffectItem();
	ObjectList->DeleteEffectItem();

	/* �v���C���[�̍X�V����(�����Âv���C���[�̃X���[���[�V�������x���グ��) */
	if (((this->iStageClear_Count % this->iPlayerSlowTime) == 0) && (this->iPlayerSlowTime < 120))
	{
		// �X���[���[�V�������x�̃J�E���g�����l�ɒB���Ă���ꍇ
		/* �v���C���[�̍X�V���� */
		ObjectList->UpdatePlayer();

		/* �G�t�F�N�g�X�V */
		UpdateEffekseer3D();

		/* �X���[���[�V�������x�����Z */
		this->iPlayerSlowTime = static_cast<int>(this->iPlayerSlowTime * 1.2f) + 1;
	}
}

// �v�Z(�X�e�[�W�J�n���̏���)
void SceneStage::Process_StageStart()
{
	/* "����"���g���K���͂��ꂽ���m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID) == true)
	{
		// ���͂��ꂽ�ꍇ
		/* �J�����Œ���W�̒l���ő�l�ɐݒ� */
		this->iNowCameraFixedPositionNo = this->iMaxCameraFixedPositionNo - 1;
	}

	/* �J�����Œ���W�̒l���ő�l�𒴂��Ă��邩�m�F */
	if (this->iNowCameraFixedPositionNo >= this->iMaxCameraFixedPositionNo - 1)
	{
		// �����Ă���ꍇ
		/* �J�������[�h��"�X�e�[�W�J�n(�v���C���[�N���[�Y�A�b�v)"�ɐݒ� */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_STAGESTART_CLOSE_UP);

		/* �v���C���[��"�J�n�����[�V�����J�n�t���O"��L���� */
		this->PlayerStatusList->SetStartFastMotion(true);
		
		/* �N���[�Y�A�b�v�J�E���g���擾 */
		int iCloseUpCount = this->StageStatusList->iGetCloseUpCount();

		/* �N���[�Y�A�b�v�J�E���g���ő�l�𒴂��Ă��邩�m�F */
		if (iCloseUpCount >= CAMERA_CLOSEUP_COUNT_MAX)
		{
			// �����Ă���ꍇ
			/* �X�e�[�W��Ԃ����������� */
			Initialization();

			/* �Q�[����Ԃ�"�Q�[�����s"�ɕύX */
			this->StageStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
		}
		else
		{
			// �����Ă��Ȃ��ꍇ
			/* �N���[�Y�A�b�v�J�E���g�����Z */
			this->StageStatusList->SetCameraCloseUpCount(iCloseUpCount + 1);
		}
	}
	else
	{
		// �����Ă��Ȃ��ꍇ
		/* �J�������[�h��"�X�e�[�W�J�n"�ɐݒ� */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_STAGESTART);

		/* �N���[�Y�A�b�v�J�E���g�������� */
		this->StageStatusList->SetCameraCloseUpCount(0);
	}

	/* �G�l�~�[�ȊO�̃I�u�W�F�N�g�̍X�V */
	ObjectList->UpdatePlayer();
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
		TestDrawShadowMap(iShadowMapScreenHandle_Actor, SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1));
		iDrawCount++;
		TestDrawShadowMap(iShadowMapScreenHandle_Platform, SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1));
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

	/* ���͕`�ʃe�X�g */
	if (gbDrawInputTest == true)
	{
		/* �W�����v */
		if (gpDataList_Input->bGetGameInputAction(INPUT_HOLD, GAME_JUMP))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�W�����v����", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_TRG, GAME_JUMP))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�W�����v�g���K����", GetColor(255 ,0 ,0));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_REL, GAME_JUMP))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�W�����v�����[�X����", GetColor(255, 255, 255));
			iDrawCount++;
		}
		
		/* �U�� */
		if (gpDataList_Input->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�U������", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_TRG, GAME_ATTACK))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�U���g���K����", GetColor(255, 0, 0));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_REL, GAME_ATTACK))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�U���z�[���h����", GetColor(255, 255, 255));
			iDrawCount++;
		}

		/* �G�C��(�\��) */
		if (gpDataList_Input->bGetGameInputAction(INPUT_HOLD, GAME_AIM))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount,"�G�C��(�\��)����", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_TRG, GAME_AIM))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�G�C��(�\��)�g���K����", GetColor(255, 0, 0));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_REL, GAME_AIM))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�G�C��(�\��)�����[�X����", GetColor(255, 255, 255));
			iDrawCount++;
		}

		/* �J�������Z�b�g */
		if (gpDataList_Input->bGetGameInputAction(INPUT_HOLD, GAME_RESET))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�J�������Z�b�g����", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_TRG, GAME_RESET))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�J�������Z�b�g�g���K����", GetColor(255, 0, 0));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_REL, GAME_RESET))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "�J�������Z�b�g�����[�X����", GetColor(255, 255, 255));
			iDrawCount++;
		}

		/* ��� */
		if (gpDataList_Input->bGetGameInputAction(INPUT_HOLD, GAME_DODGE))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "������", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_TRG, GAME_DODGE))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "����g���K����", GetColor(255, 255, 255));
			iDrawCount++;
		}
		if (gpDataList_Input->bGetGameInputAction(INPUT_REL, GAME_DODGE))
		{
			DrawString(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT + 16 * iDrawCount, "��������[�X����", GetColor(255, 255, 255));
			iDrawCount++;
		}
	}
}
