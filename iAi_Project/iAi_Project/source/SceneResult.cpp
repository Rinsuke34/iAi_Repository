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
		this->piGrHandle_ResultBackGround	= ImageList->piGetImage("Result/UI_ResultBackGround_mini");

		/* ���U���g��ʂ̕���(���U���g) */
		this->piGrHandle_String_Result		= ImageList->piGetImage("Result/UI_Moji_Result");

		/* ���U���g��ʂ̕���(�����N) */
		this->piGrHandle_String_Rank		= ImageList->piGetImage("Result/UI_Moji_Rank");

		/* ���U���g�t���[�� */
		this->piGrHandle_ResultFrame		= ImageList->piGetImage("Result/UI_Result_Frame");

		/* �A���t�@�x�b�g(�R���{�p�̕��𗬗p) */
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_S]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_S");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_A]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_A");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_B]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_B");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_C]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_C");
		this->apiGrHandle_Alphabet[RESULT_EVALUATION_D]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_D");
	}

	/* ������ */
	this->iAddTextNo	= -1;

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
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_ResultFrame, FALSE);

	/* ��ʂ̔w�i�`�� */
	DrawExtendGraph(0 + RESULT_BACKGROUND_POSITION_REDUCTION, 0 + RESULT_BACKGROUND_POSITION_REDUCTION, SCREEN_SIZE_WIDE - RESULT_BACKGROUND_POSITION_REDUCTION, SCREEN_SIZE_HEIGHT - RESULT_BACKGROUND_POSITION_REDUCTION, *this->piGrHandle_ResultBackGround, TRUE);

	/* �����`��(�摜����) */
	DrawGraph(RESULT_STRING_RESULT_POSITION_X, RESULT_STRING_RESULT_POSITION_Y, *this->piGrHandle_String_Result, TRUE);
	DrawGraph(RESULT_STRING_RANK_POSITION_X, RESULT_STRING_RANK_POSITION_Y, *this->piGrHandle_String_Rank, TRUE);
	
	/* ���� */
	DrawBox(RESULT_STRING_RESULT_LINE_LU, RESULT_STRING_RESULT_LINE_LD, RESULT_STRING_RESULT_LINE_RU, RESULT_STRING_RESULT_LINE_RD, GetColor(255, 255, 255), TRUE);
	DrawBox(RESULT_STRING_RANK_LINE_LU, RESULT_STRING_RANK_LINE_LD, RESULT_STRING_RANK_LINE_RU, RESULT_STRING_RANK_LINE_RD, GetColor(255, 255, 255), TRUE);

	/* ����(�}�L�i�X�t�H���g�g�p����) */
	DrawFormatStringToHandle(80, 240, GetColor(0, 0, 0), giFontHandle_Large,	"CLEAR TIME");
	DrawFormatStringToHandle(80 + 600, 240, GetColor(0, 0, 0), giFontHandle_Large,	"%d s", (StageStatusList->iGetClearTime() - StageStatusList->iGetStartTime()) / 1000);

	DrawFormatStringToHandle(80, 400, GetColor(0, 0, 0), giFontHandle_Large,	"MAX COMBO");
	DrawFormatStringToHandle(80 + 600, 400, GetColor(0, 0, 0), giFontHandle_Large, "%d COMBO", PlayerStatusList->iGetPlayerComboMaxCount());

	DrawFormatStringToHandle(80, 560, GetColor(0, 0, 0), giFontHandle_Large,	"TAKE DAMAGE");
	DrawFormatStringToHandle(80 + 600, 560, GetColor(0, 0, 0), giFontHandle_Large, "%d DAMAGE", PlayerStatusList->iGetPlayerDamageCount());

	DrawFormatStringToHandle(80, 720, GetColor(0, 0, 0), giFontHandle_Large,	"GET BLOOD");

	/* �]���`�� */
	{
		/* �]��(�N���A�^�C��) */
		DrawGraph(1500, 200, *this->apiGrHandle_Alphabet[this->iClearEvaluation_Time], TRUE);
		/* �]��(�ő�R���{) */
		DrawGraph(1500, 360, *this->apiGrHandle_Alphabet[this->iClearEvaluation_Combo], TRUE);
		/* �]��(��_���[�W) */
		DrawGraph(1500, 540, *this->apiGrHandle_Alphabet[this->iClearEvaluation_Damage], TRUE);
		/* �]��(����) */
		DrawGraph(1600, 720, *this->apiGrHandle_Alphabet[this->iClearEvaluation_Total], TRUE);
	}
}

// ���C������
void SceneResult::Process_Main()
{
	/* "����"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// ���͂���Ă���ꍇ
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
		else if (iEvaluationTotal >= 6)
		{
			// B
			this->iClearEvaluation_Total = RESULT_EVALUATION_B;
		}
		else if (iEvaluationTotal >= 9)
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
