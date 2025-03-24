/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* �V�[���u�Q�[���v�̒�` */

// �R���X�g���N�^
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* �f�[�^���X�g�쐬 */
	{
		/* �f�[�^���X�g�T�[�o�[��"�Q�[�����\�[�X�Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_GameResource());
	}

	/* �f�[�^���X�g�擾 */
	{
		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* ������ */
	/* �ŏI�X�e�[�W�ԍ���ݒ� */
	this->StageStatusList->SetEndStageNo(STAGE_END);	
}

// �f�X�g���N�^
SceneGame::~SceneGame()
{
	/* �f�[�^���X�g�폜 */
	{
		/* �Q�[�����\�[�X�Ǘ� */
		gpDataListServer->DeleteDataList("DataList_StageResource");
	}
}

// ������
void SceneGame::Initialization()
{
	/* �ŏ��̃X�e�[�W�ԍ���ݒ� */
	int iStartStageNo = STAGE_START;

	/* ���f�f�[�^���c���Ă��邩�m�F */
	{
		/* �Z�[�u�f�[�^(���f��)�̃p�X�ݒ� */
		std::string SaveDataFileName = "resource/SaveData/SuspensionSaveData.json";

		/* �t�@�C���̑��݊m�F */
		std::ifstream inputFile(SaveDataFileName);

		/* �t�@�C�������݂��邩�m�F */
		if (inputFile.is_open())
		{
			// ���݂���ꍇ
			/* �Z�[�u�f�[�^���̏����擾���� */
			nlohmann::json	json;
			inputFile >> json;

			/* �����u���b�h��ǂݍ��� */
			int iBlood = 0;
			json.at("Blood").get_to(iBlood);
			this->GameResourceList->SetHaveBlood(iBlood);

			/* �X�e�[�W�ԍ���ǂݍ��� */
			json.at("StageNo").get_to(iStartStageNo);

			/* ���݂̃G�f�B�b�g����ǂݍ��� */
			int iIndex = 0;
			for (const auto& edit : json["EditData"])
			{
				/* �G�f�B�b�g�����擾 */
				EDIT_DATA stEditData;
				stEditData.iEditEffect	= edit["Effect"];
				stEditData.iEditCost	= edit["Cost"];
				stEditData.iEditRank	= edit["Rank"];
				stEditData.aText		= edit["Text"];

				/* �ǂݍ��񂾕������UTF-8�`Shift-JIS�ɕϊ� */
				stEditData.aText = PUBLIC_PROCESS::aUtf8ToShiftJIS(stEditData.aText);

				/* �G�f�B�b�g����ݒ� */
				this->GameResourceList->SetNowEditData(iIndex, stEditData);

				/* �C���f�b�N�X��+1���� */
				iIndex++;
			}

			/* �L�[�v���̃G�f�B�b�g����ǂݍ��� */
			EDIT_DATA stKeepEditData;
			stKeepEditData.iEditCost	= json["KeepEditData"]["Cost"];
			stKeepEditData.iEditEffect	= json["KeepEditData"]["Effect"];
			stKeepEditData.iEditRank	= json["KeepEditData"]["Rank"];
			stKeepEditData.aText		= json["KeepEditData"]["Text"];

			/* �ǂݍ��񂾕������UTF-8�`Shift-JIS�ɕϊ� */
			stKeepEditData.aText = PUBLIC_PROCESS::aUtf8ToShiftJIS(stKeepEditData.aText);

			/* �L�[�v���̃G�f�B�b�g����ݒ� */
			this->GameResourceList->SetKeepEditData(stKeepEditData);
		}
		else
		{
			// ���݂��Ȃ��ꍇ
			/* ��b�p�[�g(�I�[�v�j���O)�𐶐� */
			SceneConversation* pAddConversation = new SceneConversation();
			gpSceneServer->AddSceneReservation(pAddConversation);
			pAddConversation->SetTextFileNo(0);
			pAddConversation->Initialization();
		}
	}

	/* �X�e�[�W�ԍ���ݒ� */
	this->StageStatusList->SetNowStageNo(iStartStageNo);

	/* UI�ǉ��t���O��L���� */
	this->StageStatusList->SetAddUiFlg(true);

	/* �ŏ��ɃG�f�B�b�g��ʂ�ǉ������Ԃɂ��� */
	this->StageStatusList->SetFastEditFlg(true);

	/* "�ŏ��̃X�e�[�W�ԍ�"�̃X�e�[�W��ǂݍ��� */
	/* �V�[��"�X�e�[�W"���쐬 */
	SceneBase* pAddScene = new SceneStage();

	/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
	gpSceneServer->AddSceneReservation(pAddScene);

	/* �X�e�[�W�̓ǂݍ��݂��J�n */
	dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();

	/* ���������������s���� */
	pAddScene->Initialization();
}

// �v�Z
void SceneGame::Process()
{
	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (this->StageStatusList->iGetGameStatus())
	{
		/* "���̃X�e�[�W�֑J��"��� */
		case GAMESTATUS_NEXTSTAGE:
			{
				/* ���݂̃X�e�[�W�ԍ����擾 */
				int iNowStageNo = this->StageStatusList->iGetNowStageNo();

				/* �X�e�[�W�ԍ���+1���� */
				iNowStageNo++;

				/* �X�e�[�W�ԍ����ŏI�X�e�[�W�ԍ��𒴂��Ă��Ȃ����m�F */
				if (iNowStageNo <= this->StageStatusList->iGetEndStageNo())
				{
					// �����Ă��Ȃ�(���̃X�e�[�W������)�ꍇ
					/* �X�e�[�W�ԍ���ݒ� */
					this->StageStatusList->SetNowStageNo(iNowStageNo);

					/* ���[�h�V�[���ǉ��t���O��L���� */
					gpSceneServer->SetAddLoadSceneFlg(true);

					/* �V�[��"�X�e�[�W"���쐬 */
					SceneBase* pAddScene = new SceneStage();

					/* ���������������{ */
					pAddScene->Initialization();

					/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
					gpSceneServer->AddSceneReservation(pAddScene);

					/* �X�e�[�W�̓ǂݍ��݂��J�n */
					dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();

					/* ���������������s���� */
					pAddScene->Initialization();
				}
				else
				{
					// �����Ă���(���̃X�e�[�W���Ȃ�)�ꍇ
					/* �V�[���폜�t���O��L���ɂ��� */
					this->bDeleteFlg = true;

					/* ���[�h��ʒǉ��t���O��L���� */
					gpSceneServer->SetAddLoadSceneFlg(true);

					/* ���s�V�[���폜�t���O��L���� */
					gpSceneServer->SetDeleteCurrentSceneFlg(true);

					/* �V�[��"�G���h�N���W�b�g"���V�[���T�[�o�[�ɒǉ� */
					gpSceneServer->AddSceneReservation(new SceneEndcredit());
				}
			}
			break;

		/* "�X�e�[�W�W�����v"��� */
		case GAMESTATUS_STAGE_JUMP:
			{
				/* �W�����v��̃X�e�[�W�ԍ����擾 */
				int iJumpStageNo = this->StageStatusList->iGetJumpStageNo();

				/* �X�e�[�W�ԍ���ݒ� */
				this->StageStatusList->SetNowStageNo(iJumpStageNo);

				/* ���[�h�V�[���ǉ��t���O��L���� */
				gpSceneServer->SetAddLoadSceneFlg(true);

				/* �V�[��"�X�e�[�W"���쐬 */
				SceneBase* pAddScene = new SceneStage();

				/* ���������������{ */
				pAddScene->Initialization();

				/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
				gpSceneServer->AddSceneReservation(pAddScene);

				/* �X�e�[�W�̓ǂݍ��݂��J�n */
				dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();
			}
			break;
	}
}

