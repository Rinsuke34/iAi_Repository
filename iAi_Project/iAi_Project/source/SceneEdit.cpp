/* 2025.01.19 �t�@�C���쐬 ��򕗏� */

#include "SceneEdit.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �V�[��"�G�f�B�b�g"�N���X�̒�` */

// �R���X�g���N�^
SceneEdit::SceneEdit() : SceneBase("Edit", 100, true)
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

	/* �摜���\�[�X�擾 */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �I���t���[��(0:�z�[���h�����A 1:�z�[���h����) */
		this->piGrHandle_SelectFrame[0]	= ImageList->piGetImage("Conversation/SelectFlame");
		this->piGrHandle_SelectFrame[1]	= ImageList->piGetImage("Conversation/SelectFlame_2");

		/* "����"�{�^�� */
		this->piGrHandle_SelectNext		= ImageList->piGetImage("Edit/Scene/UI_Nextbutton");

		/* �I�����ڂ̏�ԃt���[�� */
		this->apiGrHandle_SelectStatus[SELECT_STATUS_POSSIBLE_SET]		= ImageList->piGetImage("Edit/Scene/UI_Edit_Set");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_POSSIBLE_UPGRADE]	= ImageList->piGetImage("Edit/Scene/UI_Edit_Reinforce");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_INTERCHANGEABLE]	= ImageList->piGetImage("Edit/Scene/UI_Edit_Trade");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_IMPOSSIBLE]		= ImageList->piGetImage("Edit/Scene/UI_Edit_Unselectable");

		/* ���U���g�t���[�� */
		this->piGrHandle_ResultFrame		= ImageList->piGetImage("Result/UI_Result_Frame");

		/* ���݂̃G�f�B�b�g��� */
		this->piGrHandle_NowEdit_Under		= ImageList->piGetImage("Edit/Scene/UI_NowEdit_Under");

		/* ���݂̃G�f�B�b�g���̐����� */
		this->piGrHandle_UnderExplain_Under	= ImageList->piGetImage("Edit/Scene/UI_NowEditExplain_Under");

		/* �V�K�G�f�B�b�g��� */
		this->piGrHandle_NewEdit_Under		= ImageList->piGetImage("Edit/Scene/UI_NewEdit_Under");

		/* �L�[�v�G�f�B�b�g��� */
		this->piGrHandle_KeepEdit_Under		= ImageList->piGetImage("Edit/Scene/UI_Edit_Keep_Under");

		/* �L�[�v�A�C�R�� */
		this->piGrHandle_KeepIcon			= ImageList->piGetImage("Edit/Scene/UI_Edit_Keep");

		/* �L�[�v(����) */
		this->piGrHandle_Keep				= ImageList->piGetImage("Edit/Scene/UI_Moji_Keep");

		/* �폜 */
		this->piGrHandle_Delete				= ImageList->piGetImage("Edit/Scene/UI_Edit_Delete");

		/* NEW(����) */
		this->piGrHandle_New				= ImageList->piGetImage("Edit/Scene/UI_Moji_New");
	
		/* �J�X�^��(����) */
		this->piGrHandle_Custom				= ImageList->piGetImage("Edit/Scene/UI_Moji_Custom");

		/* �u���b�h�A�C�R�� */
		this->piGrHandle_Blood				= ImageList->piGetImage("UI_Player_Blood/Blood");

		/* �G�f�B�b�g���b�N����(0:B�����N, 1:A�����N) */
		this->apiGrHandle_EditLock[0]		= ImageList->piGetImage("Edit/Scene/UI_Edit_Lock_B");
		this->apiGrHandle_EditLock[1]		= ImageList->piGetImage("Edit/Scene/UI_Edit_Lock_A");
	}

	/* ������ */
	this->iSelectItem		= 0;					// �I�𒆂̍��ڂ̔ԍ�
	// �V�K�̃G�f�B�b�g���
	for (int i = 0; i < EDIT_UPGRADE_MAX; i++)
	{
		this->NewEditData[i].iEditRank		= EDIT_RANK_NONE;
		this->NewEditData[i].iEditEffect	= EDIT_EFFECT_NONE;
		this->NewEditData[i].iEditCost		= 0;
		this->NewEditData[i].aText			= "";
	}

	/* �z�[���h���̃G�f�B�b�g�̏�� */
	/* �z�[���h���̃G�f�B�b�g�������������� */
	this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
	this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
	this->HoldEditData.iEditCost	= 0;
	this->HoldEditData.aText		= "";
	this->iHoldSelectItemType		= SELECT_TYPE_NONE;
	this->iHoldSelectItemNo			= 0;

	/* �X�e�[�W�N���A���̑����]���ɉ����ĐV�K�G�f�B�b�g��ǉ� */
	{
		/* �X�e�[�W�N���A���̑����]���擾 */
		int	iClearEvaluation_Total = this->GameResourceList->iGetClearEvaluation();

		/* �����]���ɉ������擾 */
		this->iNewEditNumber = 0;						// �V�K�G�f�B�b�g��
		bool	bGoaldConfirmed = false;	// ���g�m��

		/* �����N�ɉ����Đݒ肷�� */
		switch (iClearEvaluation_Total)
		{
			case RESULT_EVALUATION_S:
				this->iNewEditNumber	= NEW_EDIT_NO_RANK_S;
				bGoaldConfirmed	= true;
				break;

			case RESULT_EVALUATION_A:
				this->iNewEditNumber = NEW_EDIT_NO_RANK_A;
				break;

			case RESULT_EVALUATION_B:
				this->iNewEditNumber = NEW_EDIT_NO_RANK_B;
				break;

			case RESULT_EVALUATION_C:
				this->iNewEditNumber = NEW_EDIT_NO_RANK_C;
				break;

			case RESULT_EVALUATION_D:
				this->iNewEditNumber = NEW_EDIT_NO_RANK_D;
				break;
		}

		/* �ŏ��ɃG�f�B�b�g��ʂ�ǉ����邩�m�F */
		if (this->StageStatusList->bGetFastEditFlg() == true)
		{
			// �ǉ�����ꍇ(�ŏ��̃G�f�B�b�g�`�ʂ̏ꍇ)
			/* �V�K�G�f�B�b�g�����Œ�̐ݒ�Ƃ��� */
			/* 1�g�� */
			{
				this->NewEditData[0].iEditEffect	= 2;
				this->NewEditData[0].iEditRank		= 2;
				this->NewEditData[0].iEditCost		= 500;
				this->NewEditData[0].aText			= "�u���b�h�擾�ʂ�5����";
			}
			/* 2�g�� */
			{
				this->NewEditData[1].iEditEffect	= 5;
				this->NewEditData[1].iEditRank		= 1;
				this->NewEditData[1].iEditCost		= 500;
				this->NewEditData[1].aText			= "�W�����v�\�񐔂�1�񑝉�";
			}
			/* 3�g�� */
			{
				this->NewEditData[2].iEditEffect	= 9;
				this->NewEditData[2].iEditRank		= 3;
				this->NewEditData[2].iEditCost		= 3000;
				this->NewEditData[2].aText			= "�ꕔ�̓G�U���𒵂˕Ԃ���悤�ɂȂ�";
			}
		}
		else
		{
			// �ǉ����Ȃ��ꍇ(�X�e�[�W�N���A���̃G�f�B�b�g�`�ʂ̏ꍇ)
			/* Json�t�@�C������G�f�B�b�g����ǂݍ���ŐV�K�G�f�B�b�g�ɓo�^ */
			{
				/* �擾��������ۑ�����z��̐錾 */
				std::vector<EDIT_LOTTERY> aEditLotteryList;

				/* �p�X�ƃt�@�C�����̐ݒ� */
				std::string FilePath = "resource/SetupData/";	// �ۑ��ꏊ
				std::string jsonFileName = "EditDataBase.json";		// �t�@�C����

				/* �t�@�C���W�J */
				std::ifstream inputFile(FilePath + jsonFileName);

				/* �t�@�C���̓W�J�������������m�F */
				if (inputFile.is_open())
				{
					// �t�@�C�������݂���ꍇ
					/* ���݂̃X�e�[�W�̊e�]���̊�l���擾���� */
					nlohmann::json	json;
					inputFile >> json;

					/* ���ׂĂ̗v�f��ǂݍ��� */
					for (auto& data : json)
					{
						/* �G�f�B�b�g�����擾 */
						EDIT_LOTTERY stEditLottery;
						data.at("Effect").get_to(stEditLottery.iEffect);
						data.at("Rank").get_to(stEditLottery.iRank);
						data.at("IncidenceRate").get_to(stEditLottery.iIncidenceRate);
						data.at("Cost").get_to(stEditLottery.iCost);
						data.at("Text").get_to(stEditLottery.aText);

						/* �ǂݍ��񂾕������UTF-8�`Shift-JIS�ɕϊ� */
						stEditLottery.aText = PUBLIC_PROCESS::aUtf8ToShiftJIS(stEditLottery.aText);

						/* �z��ɒǉ� */
						aEditLotteryList.push_back(stEditLottery);
					}

					/* �t�@�C������� */
					inputFile.close();
				}

				/* �G�f�B�b�g���������_���ȃG�f�B�b�g��I�� */
				{
					/* �S�v�f�̏o�������v�l���擾 */
					int iTotalRarity = 0;
					for (auto& edit : aEditLotteryList)
					{
						/* ���v�l�ɉ��Z */
						iTotalRarity += edit.iIncidenceRate;
					}

					/* �o�����Ɋ�Â��A�����_���ȃG�f�B�b�g��I�o */
					for (int i = 0; i < this->iNewEditNumber; i++)
					{
						/* �����_���Ȓl���擾���� */
						int iRandomValue = GetRand(iTotalRarity - 1);
						int iCurrentSum = 0;

						/* �����_���l�ɉ������G�f�B�b�g���擾���� */
						for (auto& edit : aEditLotteryList)
						{
							/* �o�����ɉ������l�����Z */
							iCurrentSum += edit.iIncidenceRate;

							/* �����_���l�����Z�l�������Ă��邩�m�F */
							if (iRandomValue < iCurrentSum)
							{
								// �����Ă���ꍇ
								/* �I�������G�f�B�b�g��V�K�G�f�B�b�g�ɓo�^ */
								this->NewEditData[i].iEditEffect = edit.iEffect;
								this->NewEditData[i].iEditRank = edit.iRank;
								this->NewEditData[i].iEditCost = edit.iCost;
								this->NewEditData[i].aText = edit.aText;
								break;
							}
						}
					}
				}
			}

			/* ���g�m��t���O���L���ł��邩 */
			if (bGoaldConfirmed == true)
			{
				// �L���ł���ꍇ
				/* NONE�ȊO�̃����_���ȃG�f�B�b�g�̃����N�����ɂ��� */
				// ���Œ�1�g�ł��邽�߁A���g�̃G�f�B�b�g�����I�ΏۂƂȂ��Ă��d�l��͖��Ȃ�
				this->NewEditData[GetRand(this->iNewEditNumber - 1)].iEditRank = EDIT_RANK_GOLD;
			}
		}
	}

	/* �e���ڂ̏���I�����ڂɐݒ� */
	{
		int i = 0;
		// �L�[�v���̃G�f�B�b�g���o�^
		{
			this->astSelectItemList[i].iSelectItemType	= SELECT_TYPE_KEEP_EDIT;
			this->astSelectItemList[i].pstEditData		= this->GameResourceList->pstGetKeepEditData();
			i++;
		}
		// �V�K�G�f�B�b�g���o�^
		for (int j = 0; j < EDIT_UPGRADE_MAX; j++)
		{
			this->astSelectItemList[i].iSelectItemType	= SELECT_TYPE_NEW_EDIT;
			this->astSelectItemList[i].pstEditData		= &this->NewEditData[j];
			i++;
		}
		// �폜���o�^
		{
			this->astSelectItemList[i].iSelectItemType	= SELECT_TYPE_DELETE_EDIT;
			this->astSelectItemList[i].pstEditData		= &this->DeleteEditData;
			i++;
		}
		// ���݂̃G�f�B�b�g���o�^
		for (int j = 0; j < EDIT_MAX; j++)
		{
			this->astSelectItemList[i].iSelectItemType	= SELECT_TYPE_NOW_EDIT;
			this->astSelectItemList[i].pstEditData		= this->GameResourceList->pstGetNowEditData(j);
			i++;
		}
		// ����
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_NEXT;
		}

		/* �`�ʍ��W�ꊇ�o�^ */
		{
			/* �`�ʍ��W�ݒ� */
			st2DPosition stSelectItemPos[SELECT_ITEM_MAX] =
			{
				{ 160, 210 },
				{ 435, 210 },
				{ 710, 210 },
				{ 985, 210 },
				{ 1260, 210 },
				{ 1535, 210 },
				{ 160, 650 },
				{ 435, 650 },
				{ 710, 650 },
				{ 985, 650 },
				{ 1260, 650 },
				{ 1535, 650 },
				{ 1415, 850 }
			};

			/* ���W�ݒ� */
			for (int l = 0; l < SELECT_ITEM_MAX; l++)
			{
				/* ���W�ݒ� */
				this->astSelectItemList[l].stDrawPos = stSelectItemPos[l];

				/* �I�����ڂ̏�Ԃ�"��Ԗ���"�ɐݒ�(���ł�) */
				this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_NONE;
			}
		}
	}

	/* BGM��ݒ� */
	gpDataList_Sound->BGM_SetHandle(BGM_EDIT);
}

// �f�X�g���N�^
SceneEdit::~SceneEdit()
{
	/* �v���C���[�̃X�e�[�^�X���X�V */
	this->PlayerStatusList->StatusBuffUpdate();
}

// �v�Z
void SceneEdit::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->StageStatusList->iGetGameStatus();

	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (iGameStatus)
	{
		/* "�G�f�B�b�g"��� */
		case GAMESTATUS_EDIT:
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

// ���C������
void SceneEdit::Process_Main()
{
	/* ������͎��̏��� */
	Process_Decid();

	/* �������͎��̏��� */
	Process_Select();

	/* ���݂̃G�f�B�b�g���̍X�V */
	Process_NowEditUpdate();
}

// ������͎��̏���
void SceneEdit::Process_Decid()
{
	/* "����"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// ���͂���Ă���ꍇ
		/* �G�f�B�b�g���z�[���h���ł��邩�m�F */
		if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
		{
			// �z�[���h���ł���ꍇ
			/* �Ώۂ̑I�����ڂ̏�Ԃɉ����ď�����ύX���� */
			switch (this->astSelectItemList[this->iSelectItem].iSelectStatus)
			{
				/* �Z�b�g�\ */
				case SELECT_STATUS_POSSIBLE_SET:
					/* �z�[���h���̃G�f�B�b�g��"�L�[�v���̃G�f�B�b�g"���邢��"�V�K�̃G�f�B�b�g"�ł��邩�m�F */
					if ((this->iHoldSelectItemType == SELECT_TYPE_KEEP_EDIT) || (this->iHoldSelectItemType == SELECT_TYPE_NEW_EDIT))
					{
						// "�L�[�v���̃G�f�B�b�g"���邢��"�V�K�̃G�f�B�b�g"�ł���ꍇ
						/* �z�[���h���̃G�f�B�b�g�̃R�X�g�������u���b�h(�Q�[�����ʉ�)������ */
						this->GameResourceList->SetHaveBlood(this->GameResourceList->iGetHaveBlood() - this->HoldEditData.iEditCost);
					}

					/* �z�[���h���̃G�f�B�b�g�������݂̑I�����ڂɐݒ肷�� */
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= this->HoldEditData.iEditEffect;
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= this->HoldEditData.iEditRank;
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditCost	= this->HoldEditData.iEditCost;
					this->astSelectItemList[this->iSelectItem].pstEditData->aText		= this->HoldEditData.aText;

					/* �z�[���h���̃G�f�B�b�g�������������� */
					this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
					this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
					this->HoldEditData.iEditCost	= 0;
					this->HoldEditData.aText		= "";
					this->iHoldSelectItemType		= SELECT_TYPE_NONE;

					/* "����"��SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);
					break;

				/* �����\ */
				case SELECT_STATUS_POSSIBLE_UPGRADE:
					/* �z�[���h���̃G�f�B�b�g��"�L�[�v���̃G�f�B�b�g"���邢��"�V�K�̃G�f�B�b�g"�ł��邩�m�F */
					if ((this->iHoldSelectItemType == SELECT_TYPE_KEEP_EDIT) || (this->iHoldSelectItemType == SELECT_TYPE_NEW_EDIT))
					{
						// "�L�[�v���̃G�f�B�b�g"���邢��"�V�K�̃G�f�B�b�g"�ł���ꍇ
						/* �z�[���h���̃G�f�B�b�g�̃R�X�g�������u���b�h(�Q�[�����ʉ�)������ */
						this->GameResourceList->SetHaveBlood(this->GameResourceList->iGetHaveBlood() - this->HoldEditData.iEditCost);
					}

					/* �o�^����Ă���G�f�B�b�g�̃����N���㏸������ */
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank += 1;

					/* �z�[���h���̃G�f�B�b�g�������������� */
					this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
					this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
					this->HoldEditData.iEditCost	= 0;
					this->HoldEditData.aText		= "";
					this->iHoldSelectItemType		= SELECT_TYPE_NONE;

					/* "����"��SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);
					break;

				/* �����\ */
				case SELECT_STATUS_INTERCHANGEABLE:
					{
						/* ���ݓo�^����Ă���G�f�B�b�g����ϐ��ŕۑ� */
						EDIT_DATA stEditData = *this->astSelectItemList[this->iSelectItem].pstEditData;

						/* �z�[���h���̃G�f�B�b�g�������݂̑I�����ڂɐݒ肷�� */
						this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= this->HoldEditData.iEditEffect;
						this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= this->HoldEditData.iEditRank;
						this->astSelectItemList[this->iSelectItem].pstEditData->iEditCost	= this->HoldEditData.iEditCost;
						this->astSelectItemList[this->iSelectItem].pstEditData->aText		= this->HoldEditData.aText;

						/* �ϐ��ɕۑ������G�f�B�b�g�����z�[���h���̃G�f�B�b�g���ɐݒ肷�� */
						this->HoldEditData			= stEditData;
						this->iHoldSelectItemType	= this->astSelectItemList[this->iSelectItem].iSelectItemType;
					}
					/* "����"��SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

					break;

				/* �I��s�� */
				case SELECT_STATUS_IMPOSSIBLE:
					/* �������s��Ȃ�(�����o��) */
					/* "�L�����Z��"��SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_SYSTEM_CANCEL);
					break;
			}
		}
		else
		{
			// �z�[���h���ł͂Ȃ��ꍇ
			/* ���݂̑I�����ڂ�"����"�ł��邩 */
			if (this->iSelectItem == SELECT_ITEM_NEXT)
			{
				// "����"�ł���ꍇ
				/* "����"��SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

				/* �ŏ��ɃG�f�B�b�g��ʂ�ǉ����邩�m�F */
				if (this->StageStatusList->bGetFastEditFlg() == true)
				{
					// �ǉ�����ꍇ
					/* �Q�[����Ԃ�"���Z�b�g"�ɕύX���� */
					this->StageStatusList->SetGameStatus(GAMESTATUS_RESET);

					/* �ŏ��ɃG�f�B�b�g��ʂ�ǉ����Ȃ���Ԃɂ��� */
					this->StageStatusList->SetFastEditFlg(false);
				}
				else
				{
					// �ǉ����Ȃ��ꍇ
					/* �Q�[����Ԃ�"���̃X�e�[�W�֑J��"�ɕύX���� */
					this->StageStatusList->SetGameStatus(GAMESTATUS_NEXTSTAGE);
				}

				/* ���莞�̏������I������ */
				return;
			}
			else
			{
				// "����"�łȂ��ꍇ
				/* "����"��SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

				/* �o�^����Ă���G�f�B�b�g�̎擾���������{ */
				// �Ώۂ̃G�f�B�b�g�����݂��邩�m�F
				if (this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect != EDIT_EFFECT_NONE)
				{
					// ���݂���ꍇ
					/* �I�����ڂɐݒ肳�ꂽ�G�f�B�b�g�����z�[���h���̃G�f�B�b�g�ɑ������ */
					this->HoldEditData.iEditEffect	= this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect;
					this->HoldEditData.iEditRank	= this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank;
					this->HoldEditData.iEditCost	= this->astSelectItemList[this->iSelectItem].pstEditData->iEditCost;
					this->HoldEditData.aText		= this->astSelectItemList[this->iSelectItem].pstEditData->aText;

					/* �I�����ڂ̎�ނ�ݒ肷�� */
					this->iHoldSelectItemType = this->astSelectItemList[this->iSelectItem].iSelectItemType;

					/* �G�f�B�b�g������������I�����ڂ̃G�f�B�b�g�������������� */
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= EDIT_EFFECT_NONE;
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= EDIT_RANK_NONE;
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditCost	= 0;
					this->astSelectItemList[this->iSelectItem].pstEditData->aText		= "";
				}
			}
		}
	}
}

// �������͎��̏���
void SceneEdit::Process_Select()
{
	/* "��"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
	{
		// ���͂���Ă���ꍇ
		/* "�J�[�\���ړ�"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* �I�����ڂ���ɐi�߂� */
		this->iSelectItem -= 6;
	}

	/* "��"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		// ���͂���Ă���ꍇ
		/* "�J�[�\���ړ�"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* �I�����ڂ����ɐi�߂� */
		this->iSelectItem += 6;
	}

	/* "��"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		// ���͂���Ă���ꍇ
		/* "�J�[�\���ړ�"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* �I�����ڂ����ɐi�߂� */
		this->iSelectItem -= 1;
	}

	/* "�E"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		// ���͂���Ă���ꍇ
		/* "�J�[�\���ړ�"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* �I�����ڂ��E�ɐi�߂� */
		this->iSelectItem += 1;
	}

	/* �I�𒆂̍��ڂ̔ԍ���͈͓��Ɏ��߂� */
	if (this->iSelectItem < 0)
	{
		this->iSelectItem = 0;
	}
	else if (this->iSelectItem >= SELECT_ITEM_MAX)
	{
		this->iSelectItem = SELECT_ITEM_MAX - 1;
	}
}

// ���݂̃G�f�B�b�g���̍X�V
void SceneEdit::Process_NowEditUpdate()
{
	/* �G�f�B�b�g���z�[���h���ł��邩�m�F */
	if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
	{
		// �z�[���h���ł���ꍇ
		/* ���݃z�[���h���̑I�����ڂ̎�ނɉ����ď�����ύX���� */
		switch (this->iHoldSelectItemType)
		{
			/* �L�[�v���̃G�f�B�b�g */
			case SELECT_TYPE_KEEP_EDIT:
			/* �V�K�̃G�f�B�b�g */
			case SELECT_TYPE_NEW_EDIT:
				/* �L�[�v���̃G�f�B�b�g�����ւ��\�Ƃ��� */
				this->astSelectItemList[SELECT_TYPE_KEEP_EDIT].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;

				/* �V�K�̃G�f�B�b�g�����ւ��\�Ƃ��� */
				for (int i = SELECT_ITEM_NEW_EDIT_START; i <= SELECT_ITEM_NEW_EDIT_END; i++)
				{
					this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
				}

				/* �폜��I��s�Ƃ��� */
				this->astSelectItemList[SELECT_ITEM_DELETE].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;

				/* ���݂̃G�f�B�b�g�������t���Z�b�g�\�A����ւ��\�A�A�b�v�O���[�h�\�Ƃ���Ƃ��� */
				for (int i = SELECT_ITEM_NOW_EDIT_START; i <= SELECT_ITEM_NOW_EDIT_END; i++)
				{
					/* �����u���b�h���z�[���h���̃G�f�B�b�g�̃R�X�g�����ł���Ȃ�I��s�ɐݒ� */
					if (this->GameResourceList->iGetHaveBlood() < this->HoldEditData.iEditCost)
					{
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
						continue;
					}

					/* �G�f�B�b�g���o�^����Ă��Ȃ��Ȃ�Z�b�g�\�Ƃ��� */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == EDIT_EFFECT_NONE)
					{
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_SET;
						continue;;
					}

					/* ���ʂ�����ł��邩�m�F */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == this->HoldEditData.iEditEffect)
					{
						// ���ʂ�����ł���Ȃ��
						/* �����N������ł��邩�m�F */
						if (this->astSelectItemList[i].pstEditData->iEditRank == this->HoldEditData.iEditRank)
						{
							// �����N������ł���Ȃ��
							/* �����N�����ȊO�ł��邩 */
							if (this->astSelectItemList[i].pstEditData->iEditRank != EDIT_RANK_GOLD)
							{
								/* �����\�ɐݒ� */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_UPGRADE;
							}
							else
							{
								/* �����\�ɐݒ� */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
							}
						}
					}
					else
					{
						/* �����\�ɐݒ� */
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
					}
				}

				/* ���ւ�I��s�Ƃ��� */
				this->astSelectItemList[SELECT_ITEM_NEXT].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				break;

			/* �폜 */
			case SELECT_TYPE_DELETE_EDIT:
			/* ���݂̃G�f�B�b�g */
			case SELECT_TYPE_NOW_EDIT:
				/* �L�[�v���̃G�f�B�b�g��I��s�Ƃ��� */
				this->astSelectItemList[SELECT_TYPE_KEEP_EDIT].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;

				/* �V�K�̃G�f�B�b�g��I��s�Ƃ��� */
				for (int i = SELECT_ITEM_NEW_EDIT_START; i <= SELECT_ITEM_NEW_EDIT_END; i++)
				{
					this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				}

				/* �폜���Z�b�g�\�Ƃ��� */
				this->astSelectItemList[SELECT_ITEM_DELETE].iSelectStatus = SELECT_STATUS_POSSIBLE_SET;

				/* ���݂̃G�f�B�b�g���Z�b�g�\�A����ւ��\�A�A�b�v�O���[�h�\�Ƃ��� */
				for (int i = SELECT_ITEM_NOW_EDIT_START; i <= SELECT_ITEM_NOW_EDIT_END; i++)
				{
					/* �G�f�B�b�g���o�^����Ă��Ȃ��Ȃ�Z�b�g�\�Ƃ��� */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == EDIT_EFFECT_NONE)
					{
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_SET;
						continue;;
					}

					/* ���ʂ�����ł��邩�m�F */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == this->HoldEditData.iEditEffect)
					{
						// ���ʂ�����ł���Ȃ��
						/* �����N������ł��邩�m�F */
						if (this->astSelectItemList[i].pstEditData->iEditRank == this->HoldEditData.iEditRank)
						{
							// �����N������ł���Ȃ��
							/* �����N�����ȊO�ł��邩 */
							if (this->astSelectItemList[i].pstEditData->iEditRank != EDIT_RANK_GOLD)
							{
								/* �����\�ɐݒ� */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_UPGRADE;
							}
							else
							{
								/* �����\�ɐݒ� */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
							}
						}
					}
					else
					{
						/* �����\�ɐݒ� */
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
					}
				}

				/* ���ւ�I��s�Ƃ��� */
				this->astSelectItemList[SELECT_ITEM_NEXT].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				break;
		}

		/* ���b�N���ɉ����đΏۂ̃G�f�B�b�g����I��s�ɐݒ� */
		switch (this->iNewEditNumber)
		{
			/* �V�K�G�f�B�b�g����"5��"�̏ꍇ */
			case NEW_EDIT_NO_RANK_S:
				/* ���b�N�͐ݒ肵�Ȃ� */
				break;

			/* �V�K�G�f�B�b�g����"4��"�̏ꍇ */
			case NEW_EDIT_NO_RANK_B:
				/* �V�K�̃G�f�B�b�g��5�ڂ�ݒ�s�� */
				this->astSelectItemList[SELECT_ITEM_NEW_EDIT_END].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				break;

			/* �V�K�G�f�B�b�g����"3��"�̏ꍇ */
			case NEW_EDIT_NO_RANK_C:
				/* �V�K�̃G�f�B�b�g��5�ڂ�4�ڂ�ݒ�s�� */
				this->astSelectItemList[SELECT_ITEM_NEW_EDIT_END].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				this->astSelectItemList[SELECT_ITEM_NEW_EDIT_END - 1].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				break;
		}
	}
	else
	{
		// �z�[���h���ł͂Ȃ��ꍇ
		/* �S�Ă̑I�����ڂ̏�Ԃ�"�I�����ڂȂ�"�ɐݒ� */
		for (int i = 0; i < SELECT_ITEM_MAX; i++)
		{
			/* �e�X�g���� */
			this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_NONE;
		}
	}
}

