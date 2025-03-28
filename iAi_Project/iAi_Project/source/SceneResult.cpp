/* 2025.02.16 �t�@�C���쐬 ��򕗏� */

#include "SceneResult.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �V�[��"���U���g"�N���X�̒�` */

// �R���X�g���N�^
SceneResult::SceneResult() : SceneBase("Edit", 80, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));

		/* "�v���C���[��ԊǗ�"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ���U���g��ʔw�i */
		this->piGrHandle_ResultBackGround	= ImageList->piGetImage("Result/UI_Result");

		/* �e�]���̃A���t�@�x�b�g */
		this->apiGrHandle_Alphabet_Section[RESULT_EVALUATION_S] = ImageList->piGetImage("Result/UI_Player_Grade_S_150");
		this->apiGrHandle_Alphabet_Section[RESULT_EVALUATION_A] = ImageList->piGetImage("Result/UI_Player_Grade_A_150");
		this->apiGrHandle_Alphabet_Section[RESULT_EVALUATION_B] = ImageList->piGetImage("Result/UI_Player_Grade_B_150");
		this->apiGrHandle_Alphabet_Section[RESULT_EVALUATION_C] = ImageList->piGetImage("Result/UI_Player_Grade_C_150");
		this->apiGrHandle_Alphabet_Section[RESULT_EVALUATION_D] = ImageList->piGetImage("Result/UI_Player_Grade_D_150");

		/* �����]���A���t�@�x�b�g(�R���{�p�̕��𗬗p) */
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_S]	= ImageList->piGetImage("Result/UI_Player_RankGrade_S_256");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_A]	= ImageList->piGetImage("Result/UI_Player_RankGrade_A_256");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_B]	= ImageList->piGetImage("Result/UI_Player_RankGrade_B_256");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_C]	= ImageList->piGetImage("Result/UI_Player_RankGrade_C_256");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_D]	= ImageList->piGetImage("Result/UI_Player_RankGrade_D_256");
	}

	/* ������ */
	this->iAddTextNo					= -1;
	this->iDrawFaze						= RESULT_DRAW_FAZE_CLEAR_TIME;
	this->iDrawTimeMinute				= 0;
	this->iDrawTimeSecond				= 0;
	this->iDrawTimeFractionalSecond		= 0;
	this->iDrawMaxCombo					= 0;
	this->iDrawTakeDamage				= 0;
	this->iDrawTotalGetBlood			= 0;
	this->iDrawDelayTime				= RESULT_DRAW_FAZE_DELAY_TIME;
	this->bPlaySoundCount				= false;

	/* �e�]������擾 */
	ResultCalculation_JsonLoad();

	/* �e�]���_���Z�o */
	ClearEvaluation();
}

// �v�Z
void SceneResult::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->StageStatusList->iGetGameStatus();

	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (iGameStatus)
	{
		/* "���U���g"��� */
		case GAMESTATUS_RESULT:
			/* ���C���̏��������{ */
			Process_Main();
			break;

		/* �Y������ */
		default:
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
			break;
	}
}

// �`��
void SceneResult::Draw()
{
	/* ���U���g�p�̃t���[����`�� */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_ResultBackGround, FALSE);

	/* ����(�}�L�i�X�t�H���g�g�p����) */
	int iColorWhite = GetColor(255, 255, 255);
	int iColorBlack = GetColor(50, 50, 50);

	/* �����̕`�ʍ��W */
	st2DPosition astStringPos[8];
	for (int i = 0; i < 4; ++i)
	{
		astStringPos[i * 2] = { 80, 240 + i * 160 };
		astStringPos[i * 2 + 1] = { 80 + 600, 240 + i * 160 };
	}

	/* �����g�̕␳���W */
	st2DPosition astStringCorrectionPos[8];
	astStringCorrectionPos[0] = { -2,	-2	};
	astStringCorrectionPos[1] = { 0,	-2	};
	astStringCorrectionPos[2] = { +2,	-2	};
	astStringCorrectionPos[3] = { -2,	0	};
	astStringCorrectionPos[4] = { +2,	0	};
	astStringCorrectionPos[5] = { -2,	+2	};
	astStringCorrectionPos[6] = { 0,	+2	};
	astStringCorrectionPos[7] = { +2,	+2	};

	/* �����`��(�g) */
	for (int i = 0; i < 8; i++)
	{
		DrawFormatStringToHandle(astStringPos[0].ix + astStringCorrectionPos[i].ix, astStringPos[0].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "CLEAR TIME");
		DrawFormatStringToHandle(astStringPos[1].ix + astStringCorrectionPos[i].ix, astStringPos[1].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "%02d'%02d''%02d", this->iDrawTimeMinute, this->iDrawTimeSecond, iDrawTimeFractionalSecond);

		DrawFormatStringToHandle(astStringPos[2].ix + astStringCorrectionPos[i].ix, astStringPos[2].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "MAX COMBO");
		DrawFormatStringToHandle(astStringPos[3].ix + astStringCorrectionPos[i].ix, astStringPos[3].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "%d COMBO", this->iDrawMaxCombo);

		DrawFormatStringToHandle(astStringPos[4].ix + astStringCorrectionPos[i].ix, astStringPos[4].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "TAKE DAMAGE");
		DrawFormatStringToHandle(astStringPos[5].ix + astStringCorrectionPos[i].ix, astStringPos[5].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "%d DAMAGE", this->iDrawTakeDamage);

		DrawFormatStringToHandle(astStringPos[6].ix + astStringCorrectionPos[i].ix, astStringPos[6].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "GET BLOOD");
		DrawFormatStringToHandle(astStringPos[7].ix + astStringCorrectionPos[i].ix, astStringPos[7].iy + astStringCorrectionPos[i].iy, iColorWhite, giFontHandle_Large, "%d BLOOD", this->iDrawTotalGetBlood);
	}

	/* �����`��(���S) */
	DrawFormatStringToHandle(astStringPos[0].ix, astStringPos[0].iy, iColorBlack, giFontHandle_Large,	"CLEAR TIME");
	DrawFormatStringToHandle(astStringPos[1].ix, astStringPos[1].iy, iColorBlack, giFontHandle_Large,	"%02d'%02d''%02d", this->iDrawTimeMinute, this->iDrawTimeSecond, iDrawTimeFractionalSecond);

	DrawFormatStringToHandle(astStringPos[2].ix, astStringPos[2].iy, iColorBlack, giFontHandle_Large,	"MAX COMBO");
	DrawFormatStringToHandle(astStringPos[3].ix, astStringPos[3].iy, iColorBlack, giFontHandle_Large, "%d COMBO", this->iDrawMaxCombo);

	DrawFormatStringToHandle(astStringPos[4].ix, astStringPos[4].iy, iColorBlack, giFontHandle_Large, "TAKE DAMAGE");
	DrawFormatStringToHandle(astStringPos[5].ix, astStringPos[5].iy, iColorBlack, giFontHandle_Large, "%d DAMAGE", this->iDrawTakeDamage);

	DrawFormatStringToHandle(astStringPos[6].ix, astStringPos[6].iy, iColorBlack, giFontHandle_Large,	"GET BLOOD");
	DrawFormatStringToHandle(astStringPos[7].ix, astStringPos[7].iy, iColorBlack, giFontHandle_Large, "%d BLOOD", this->iDrawTotalGetBlood);

	/* �]���`�� */
	{
		/* �`�ʃt�F�[�Y��"�N���A�^�C���]���`��"�ȍ~�ł��邩 */
		if (this->iDrawFaze >= RESULT_DRAW_FAZE_CREAR_TIME_EVALUATION)
		{
			/* �]��(�N���A�^�C��) */
			DrawGraph(1500, 200, *this->apiGrHandle_Alphabet_Section[this->iClearEvaluation_Time], TRUE);
		}

		/* �`�ʃt�F�[�Y��"�R���{�]���`��"�ȍ~�ł��邩 */
		if (this->iDrawFaze >= RESULT_DRAW_FAZE_COMBO_EVALUATION)
		{
			/* �]��(�ő�R���{) */
			DrawGraph(1500, 360, *this->apiGrHandle_Alphabet_Section[this->iClearEvaluation_Combo], TRUE);
		}

		/* �`�ʃt�F�[�Y��"�_���[�W�]���`��"�ȍ~�ł��邩 */
		if (this->iDrawFaze >= RESULT_DRAW_FAZE_DAMAGE_EVALUATION)
		{
			/* �]��(��_���[�W) */
			DrawGraph(1500, 540, *this->apiGrHandle_Alphabet_Section[this->iClearEvaluation_Damage], TRUE);
		}

		/* �`�ʃt�F�[�Y��"�����]���`��"�ȍ~�ł��邩 */
		if (this->iDrawFaze >= RESULT_DRAW_FAZE_TOTAL_EVALUATION)
		{
			/* �]��(����) */
			DrawGraph(1550, 685, *this->apiGrHandle_Alphabet[this->iClearEvaluation_Total], TRUE);
		}
	}
}

// ���C������
void SceneResult::Process_Main()
{
	/* �����_��"���U���g"SE���Đ����ł��邩��ێ� */
	bool bPlaySound = this->bPlaySoundCount;

	/* ���݂̕`�ʒx�����Ԋ������擾 */
	float fDrawDelayTimePercent = (static_cast<float>(RESULT_DRAW_FAZE_DELAY_TIME) - static_cast<float>(this->iDrawDelayTime)) / static_cast<float>(RESULT_DRAW_FAZE_DELAY_TIME);

	/* �t�F�[�Y�ɉ����ĕ`�ʗp�̐��l��ݒ� */
	switch (this->iDrawFaze)
	{
		/* �N���A�^�C���`�� */
		case RESULT_DRAW_FAZE_CLEAR_TIME:
			{
				/* �����N���A�^�C�����擾 */
				int iClearTime = StageStatusList->iGetClearTime() - StageStatusList->iGetStartTime() - StageStatusList->iGetStopTotalTime();

				/* �N���A�^�C���̕��̒l���擾 */
				int iTimeMinute = iClearTime / 1000 / 60;

				/* �N���A�^�C���̕b�̒l���擾 */
				int iTimeSecond = iClearTime / 1000 % 60;

				/* �N���A�^�C���̏����b�̒l���擾 */
				int iTimeFractionalSecond = iClearTime % 1000 / 10;

				/* �擾�����l��(�`�ʒx�����ԍő�l/�`�ʒx������)�̒l��`�ʒl�Ƃ��Đݒ� */
				this->iDrawTimeMinute			= iTimeMinute * fDrawDelayTimePercent;
				this->iDrawTimeSecond			= iTimeSecond * fDrawDelayTimePercent;
				this->iDrawTimeFractionalSecond	= iTimeFractionalSecond * fDrawDelayTimePercent;

				/* "���U���g"��SE���Đ����ɐݒ� */
				this->bPlaySoundCount = true;
			}
			break;

		/* �N���A�^�C���]���`�� */
		case RESULT_DRAW_FAZE_CREAR_TIME_EVALUATION:
			/* "���U���g"��SE���Đ����ɐݒ� */
			this->bPlaySoundCount = false;

			/* �`�ʊJ�n����ł��邩 */
			if (this->iDrawDelayTime == RESULT_DRAW_FAZE_DELAY_TIME)
			{
				// �J�n����ł���ꍇ
				/* "���U���g���]��"��SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_SYSTEM_RESULT_RANK_SMALL);
			}
			break;

		/* �R���{�`�� */
		case RESULT_DRAW_FAZE_COMBO:
			/* �R���{����(�`�ʒx�����ԍő�l/�`�ʒx������)�̒l��`�ʒl�Ƃ��Đݒ� */
			this->iDrawMaxCombo = static_cast<int>(PlayerStatusList->iGetPlayerComboMaxCount() * fDrawDelayTimePercent);

			/* "���U���g"��SE���Đ����ɐݒ� */
			this->bPlaySoundCount = true;
			break;

		/* �R���{�]���`�� */
		case RESULT_DRAW_FAZE_COMBO_EVALUATION:
			/* "���U���g"��SE���Đ����ɐݒ� */
			this->bPlaySoundCount = false;

			/* �`�ʊJ�n����ł��邩 */
			if (this->iDrawDelayTime == RESULT_DRAW_FAZE_DELAY_TIME)
			{
				// �J�n����ł���ꍇ
				/* "���U���g���]��"��SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_SYSTEM_RESULT_RANK_SMALL);
			}
			break;

		/* �_���[�W�`�� */
		case RESULT_DRAW_FAZE_DAMAGE:
			/* �_���[�W����(�`�ʒx�����ԍő�l/�`�ʒx������)�̒l��`�ʒl�Ƃ��Đݒ� */
			this->iDrawTakeDamage = static_cast<int>(PlayerStatusList->iGetPlayerDamageCount() * fDrawDelayTimePercent);

			/* "���U���g"��SE���Đ����ɐݒ� */
			this->bPlaySoundCount = true;
			break;

		/* �_���[�W�]���`�� */
		case RESULT_DRAW_FAZE_DAMAGE_EVALUATION:
			/* "���U���g"��SE���Đ����ɐݒ� */
			this->bPlaySoundCount = false;

			/* �`�ʊJ�n����ł��邩 */
			if (this->iDrawDelayTime == RESULT_DRAW_FAZE_DELAY_TIME)
			{
				// �J�n����ł���ꍇ
				/* "���U���g���]��"��SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_SYSTEM_RESULT_RANK_SMALL);
			}
			break;

		/* �擾�u���b�h�`�� */
		case RESULT_DRAW_FAZE_GETBLOOD:
			/* �l���u���b�h����(�`�ʒx������/�`�ʒx�����ԍő�l)�̒l��`�ʒl�Ƃ��Đݒ� */
			this->iDrawTotalGetBlood = static_cast<int>((this->GameResourceList->iGetHaveBlood() - this->GameResourceList->iGetStartBlood()) * fDrawDelayTimePercent);

			/* "���U���g"��SE���Đ����ɐݒ� */
			this->bPlaySoundCount = true;
			break;

		/* �����]���`�� */
		case RESULT_DRAW_FAZE_TOTAL_EVALUATION:
			/* "���U���g"��SE���Đ����ɐݒ� */
			this->bPlaySoundCount = false;

			/* �`�ʊJ�n����ł��邩 */
			if (this->iDrawDelayTime == RESULT_DRAW_FAZE_DELAY_TIME)
			{
				// �J�n����ł���ꍇ
				/* �����]���ɉ������{�C�X���Đ����� */
				switch (this->iClearEvaluation_Total)
				{
					/* S�]�� */
					case RESULT_EVALUATION_S:
						/* "�ō�"�{�C�X���Đ����� */
						gpDataList_Sound->VOICE_PlaySound(VOICE_DOCTOR_PRAISE_S);
						break;

					/* A�]�� */
					case RESULT_EVALUATION_A:
						/* "����A"�{�C�X���Đ����� */
						gpDataList_Sound->VOICE_PlaySound(VOICE_DOCTOR_RESULT_A);
						break;

					/* BC�]�� */
					case RESULT_EVALUATION_B:
					case RESULT_EVALUATION_C:
						/* "����BC"�{�C�X���Đ����� */
						gpDataList_Sound->VOICE_PlaySound(VOICE_DOCTOR_RESULT_BC);
						break;

					/* D�]�� */
					case RESULT_EVALUATION_D:
						/* "����D"�{�C�X���Đ����� */
						gpDataList_Sound->VOICE_PlaySound(VOICE_DOCTOR_RESULT_D);
						break;
				}
			}
			break;

		/* �`�ʏI�� */
		case RESULT_DRAW_END:
			/* "���U���g"��SE���Đ����ɐݒ� */
			this->bPlaySoundCount = false;
			break;
	}

	/* �`�ʒx�����Ԃ����� */
	this->iDrawDelayTime -= 1;

	/* "���U���g"��SE���Đ��J�n���邩�m�F */
	if ((bPlaySound == false) && (this->bPlaySoundCount == true))
	{
		// �Đ��J�n����ꍇ
		/* "���U���g"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound_Loop(SE_SYSTEM_RESULT_COUNT);
	}
	else if ((bPlaySound == true) && (this->bPlaySoundCount == false))
	{
		// �Đ���~����ꍇ
		/* "���U���g"��SE���~ */
		gpDataList_Sound->SE_PlaySound_Stop(SE_SYSTEM_RESULT_COUNT);
	}

	/* �`�ʒx�����Ԃ�0�ȉ��ł��邩�m�F */
	if (this->iDrawDelayTime <= 0)
	{
		// 0�ȉ��ł���ꍇ
		/* �`�ʒx�����Ԃ����Z�b�g */
		this->iDrawDelayTime = RESULT_DRAW_FAZE_DELAY_TIME;

		/* �`�ʃt�F�[�Y��i�߂� */
		this->iDrawFaze += 1;
	}

	/* "����"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// ���͂���Ă���ꍇ
		/* "����"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

		/* �����]���`�ʂ��I�����Ă��邩�m�F */
		if (this->iDrawFaze > RESULT_DRAW_END)
		{
			// �I�����Ă���ꍇ
			/* �Q�[����Ԃ�"�G�f�B�b�g"�ɕύX���� */
			this->StageStatusList->SetGameStatus(GAMESTATUS_EDIT);

			/* �e�]���̑����l���Q�[�������\�[�X�T�[�o�[�ɓo�^ */
			this->GameResourceList->SetClearEvaluation(this->iClearEvaluation_Total);

			/* �e�L�X�g�ԍ�������(-1)�ȊO�ł��邩�m�F */
			if (this->iAddTextNo != -1)
			{
				// �e�L�X�g�ԍ����L���ȏꍇ
				/* �V�[��"��b�p�[�g"��ǉ� */
				SceneConversation* pAddScene = new SceneConversation();
				gpSceneServer->AddSceneReservation(pAddScene);

				/* �V�[��"��b�p�[�g"�Ƀe�L�X�g�ԍ���ݒ� */
				pAddScene->SetTextFileNo(this->iAddTextNo);

				/* ���������������{ */
				pAddScene->Initialization();
			}
		}
		else
		{
			// �I�����Ă��Ȃ��ꍇ
			/* �`�ʃt�F�[�Y��"�`�ʏI��"�܂Ői�߂� */
			this->iDrawFaze = RESULT_DRAW_END;
		}
	}
}

// �]����擾
void SceneResult::ResultCalculation_JsonLoad()
{
	/* Json�t�@�C���̓ǂݍ��� */
	// json�t�@�C������e�]���̊�_���擾

	/* �p�X�ƃt�@�C�����̐ݒ� */
	std::string FilePath		= "resource/SetupData/";	// �ۑ��ꏊ
	std::string jsonFileName	= "StageDataBase.json";		// �t�@�C����

	/* �t�@�C���W�J */
	std::ifstream inputFile(FilePath + jsonFileName);

	/* �t�@�C���̓W�J�������������m�F */
	if (inputFile.is_open())
	{
		// �t�@�C�������݂���ꍇ
		/* ���݂̃X�e�[�W�����擾 */
		std::string StageName = STAGE_NAME[StageStatusList->iGetNowStageNo()];

		/* ���݂̃X�e�[�W�̊e�]���̊�l���擾���� */
		nlohmann::json	json;
		inputFile >> json;

		/* �]���(�R���{��)�擾 */
		{
			/* json�t�@�C������ǂݍ��� */
			std::string GetName = "Combo";
			nlohmann::json Data = json.at(StageName).at(GetName);
			
			/* �ǂݍ��񂾒l��z��ɑ�� */
			for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
			{
				this->Calculation_Combo[i] = Data.at(i);
			}			
		}
		
		/* �]���(�N���A�^�C��)�擾 */
		{
			/* json�t�@�C������ǂݍ��� */
			std::string GetName = "Time";
			nlohmann::json Data = json.at(StageName).at(GetName);

			/* �ǂݍ��񂾒l��z��ɑ�� */
			for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
			{
				this->Calculation_Time[i] = Data.at(i);
			}
		}

		/* �]���(��_���[�W��)�擾 */
		{
			/* json�t�@�C������ǂݍ��� */
			std::string GetName = "Damage";
			nlohmann::json Data = json.at(StageName).at(GetName);
			/* �ǂݍ��񂾒l��z��ɑ�� */
			for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
			{
				this->Calculation_Damage[i] = Data.at(i);
			}
		}

		/* ��b�p�[�g�ԍ����擾 */
		{
			/* json�t�@�C������ǂݍ��� */
			std::string GetName = "Conversation";
			nlohmann::json Data = json.at(StageName).at(GetName);

			/* �ǂݍ��񂾒l��ϐ��ɕۑ� */
			this->iAddTextNo = Data;
		}

		/* �t�@�C������� */
		inputFile.close();
	}
}

// �]���Z�o
void SceneResult::ClearEvaluation()
{
	/* �ő�R���{���̕]���Z�o */
	{
		/* �ő�R���{�����擾 */
		int iMaxCombo = PlayerStatusList->iGetPlayerComboMaxCount();

		/* ������Ԃł͕]�����Œ�ɐݒ肵�Ă��� */
		this->iClearEvaluation_Combo = RESULT_EVALUATION_D;

		/* �]���Z�o */
		for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
		{
			/* �]����𒴂��Ă��邩�m�F */
			if (iMaxCombo >= this->Calculation_Combo[i])
			{
				// �Y���̕]����𒴂��Ă���ꍇ
				this->iClearEvaluation_Combo = i;
				break;
			}
		}
	}

	/* �N���A�^�C���̕]���Z�o */
	{
		/* �N���A�^�C�����擾 */
		// ���]�����͏����_�ȉ��؂�̂�
		int iClearTime = (StageStatusList->iGetClearTime() - StageStatusList->iGetStartTime()) / 1000;

		/* ������Ԃł͕]�����Œ�ɐݒ肵�Ă��� */
		this->iClearEvaluation_Time = RESULT_EVALUATION_D;

		/* �]���Z�o */
		for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
		{
			/* �]����ȉ��̒l�ł��邩�m�F */
			if (iClearTime <= this->Calculation_Time[i])
			{
				// �Y���̕]����𒴂��Ă���ꍇ
				this->iClearEvaluation_Time = i;
				break;
			}
		}
	}

	/* ��_���[�W���̕]���Z�o */
	{
		/* ��_���[�W�����擾 */
		int iDamage = PlayerStatusList->iGetPlayerDamageCount();

		/* ������Ԃł͕]�����Œ�ɐݒ肵�Ă��� */
		this->iClearEvaluation_Damage = RESULT_EVALUATION_D;

		/* �]���Z�o */
		for (int i = 0; i < RESULT_EVALUATION_MAX; i++)
		{
			/* �]����𒴂��Ă��邩�m�F */
			if (iDamage <= this->Calculation_Damage[i])
			{
				// �Y���̕]����𒴂��Ă���ꍇ
				this->iClearEvaluation_Damage = i;
				break;
			}
		}
	}

	/* �����]���̎Z�o */
	{
		/* �e�]�������Z */
		int iEvaluationTotal = 0;
		iEvaluationTotal += this->iClearEvaluation_Combo;
		iEvaluationTotal += this->iClearEvaluation_Time;
		iEvaluationTotal += this->iClearEvaluation_Damage;

		/* �����l�ɉ����Đݒ� */
		// �� �����]���͉��L�̒ʂ�
		//	���Z�l,	 �]��
		//	�`  0 : S
		//	�`  3 : A
		//	�`  6 : B
		//	�`  9 : C
		//  10 �` : D

		if (iEvaluationTotal <= 0)
		{
			// S
			this->iClearEvaluation_Total = RESULT_EVALUATION_S;
		}
		else if (iEvaluationTotal <= 3)
		{
			// A
			this->iClearEvaluation_Total = RESULT_EVALUATION_A;
		}
		else if (iEvaluationTotal <= 6)
		{
			// B
			this->iClearEvaluation_Total = RESULT_EVALUATION_B;
		}
		else if (iEvaluationTotal <= 9)
		{
			// C
			this->iClearEvaluation_Total = RESULT_EVALUATION_C;
		}
		else
		{
			// D
			this->iClearEvaluation_Total = RESULT_EVALUATION_D;
		}
	}
}
