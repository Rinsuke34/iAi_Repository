/* 2025.01.28 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Combo.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* UI(�R���{)�N���X�̒�` */

// �R���X�g���N�^
SceneUi_Combo::SceneUi_Combo() : SceneBase("UI_Combo", 103, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�v���C���[���"���擾 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList	= dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �R���{�t���[�� */
		this->piGrHandle_Combo_Frame	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/UI_Player_ComboGrade_frame_fix");

		/* �R���{�^�C�}�[ */
		this->piGrHandle_Combo_Timer	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/UI_Player_ComboTimer");

		/* �R���{�A���t�@�x�b�g */
		this->piGrHandle_Combo_Alphabet[COMBO_RANK_S]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_S");
		this->piGrHandle_Combo_Alphabet[COMBO_RANK_A]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_A");
		this->piGrHandle_Combo_Alphabet[COMBO_RANK_B]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_B");
		this->piGrHandle_Combo_Alphabet[COMBO_RANK_C]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_C");
		this->piGrHandle_Combo_Alphabet[COMBO_RANK_D]	= ImageList->piGetImage("UI_Player_ComboGrade-Timer/alphabet/UI_Player_ComboGrade_D");
	}

	/* ������ */
	this->iPlayerComboRank = COMBO_RANK_NONE;

	/* �����N��擾 */
	RankBorder_JsonLoad();
}

// �����N��擾
void SceneUi_Combo::RankBorder_JsonLoad()
{
	/* Json�t�@�C���̓ǂݍ��� */
	// json�t�@�C������e�]���̊�_���擾

	/* �p�X�ƃt�@�C�����̐ݒ� */
	std::string FilePath = "resource/SetupData/";	// �ۑ��ꏊ
	std::string jsonFileName = "StageDataBase.json";		// �t�@�C����

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
			for (int i = 0; i < COMBO_RANK_MAX; i++)
			{
				this->iComboBorder[i] = Data.at(i);
			}
		}

		/* �t�@�C������� */
		inputFile.close();
	}
}

// �v�Z
void SceneUi_Combo::Process()
{
	/* ���݂̃R���{�����擾 */
	int iNowCombo = this->PlayerStatusList->iGetPlayerComboNowCount();

	/* �Q�[����Ԃ�"�Q�[�����s"�ȊO�ł���Ȃ�V�[�����폜 */
	if (this->StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
		return;
	}

	/* �R���{�p�����Ԃ��I�����Ă��邩�m�F */
	if (this->PlayerStatusList->iGetPlayerComboDuration() > 0)
	{
		// �I�����Ă��Ȃ��ꍇ
		/* �R���{�p�����Ԃ����Z */
		this->PlayerStatusList->SetPlayerComboDuration(this->PlayerStatusList->iGetPlayerComboDuration() - 1);

		/* ���݂̃R���{�����ő�R���{����葽�����m�F */
		if (iNowCombo > this->PlayerStatusList->iGetPlayerComboMaxCount())
		{
			// �����ꍇ
			/* �ő�R���{�����X�V */
			this->PlayerStatusList->SetPlayerComboMaxCount(iNowCombo);
		}
	}
	else
	{
		// �I�����Ă���ꍇ
		/* �R���{�������Z�b�g */
		this->PlayerStatusList->SetPlayerComboNowCount(0);

		/* �����N��"����"�ɐݒ� */
		this->iPlayerComboRank = COMBO_RANK_NONE;
	}

	/* �R���{����1�ȏ�ł��邩�m�F */
	if (iNowCombo > 0)
	{
		// 1�ȏ�ł���ꍇ
		/* ���݂̃R���{�����烉���N��ݒ肷�� */
		if (iNowCombo >= this->iComboBorder[COMBO_RANK_S])
		{
			// S�����N
			/* �����N��"S�����N"�ɐݒ� */
			this->iPlayerComboRank = COMBO_RANK_S;
		}
		else if (iNowCombo >= this->iComboBorder[COMBO_RANK_A])
		{
			// A�����N
			/* �����N��"A�����N"�ɐݒ� */
			this->iPlayerComboRank = COMBO_RANK_A;
		}
		else if (iNowCombo >= this->iComboBorder[COMBO_RANK_B])
		{
			// B�����N
			/* �����N��"B�����N"�ɐݒ� */
			this->iPlayerComboRank = COMBO_RANK_B;
		}
		else if (iNowCombo >= this->iComboBorder[COMBO_RANK_C])
		{
			// C�����N
			/* �����N��"C�����N"�ɐݒ� */
			this->iPlayerComboRank = COMBO_RANK_C;
		}
		else
		{
			// D�����N
			/* �����N��"D�����N"�ɐݒ� */
			this->iPlayerComboRank = COMBO_RANK_D;
		}
	}

	/* ���݂̃R���{�����N��ݒ� */
	this->PlayerStatusList->SetPlayerComboRunk(this->iPlayerComboRank);
}

// �`��
void SceneUi_Combo::Draw()
{
	/* ���݂̃R���{�����N��"����"�ȊO�ł��邩�m�F */
	if (this->iPlayerComboRank != COMBO_RANK_NONE)
	{
		// �����N��"����"�ȊO�ł���ꍇ
		/* �R���{�t���[���`��(��) */
		DrawGraph(100, 360, *this->piGrHandle_Combo_Frame, TRUE);

		/* �R���{�^�C�}�[�`�� */
		double dComboTimerPercent = (static_cast<double>(this->PlayerStatusList->iGetPlayerComboDuration()) / (INIT_ATTRIBUTES_COMBO_DURATION + this->PlayerStatusList->iGetAddComboTime())) * 100.0;
		DrawCircleGauge(189, 448, dComboTimerPercent, *this->piGrHandle_Combo_Timer);

		/* �����N��`�� */
		/* �`�ʗ\��̃A���t�@�x�b�g�̃T�C�Y���擾 */
		int iSizeX, iSizeY;
		GetGraphSize(*this->piGrHandle_Combo_Alphabet[this->iPlayerComboRank], &iSizeX, &iSizeY);

		/* �A���t�@�x�b�g�`�� */
		DrawGraph(189 - (iSizeX / 2), 448 - (iSizeY / 2), *this->piGrHandle_Combo_Alphabet[this->iPlayerComboRank], TRUE);
	}
}
