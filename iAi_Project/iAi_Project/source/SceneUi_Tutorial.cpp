/* 2025.03.27 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Tutorial.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* UI(�`���[�g���A��)�N���X�̒�` */
// �R���X�g���N�^
SceneUi_Tutorial::SceneUi_Tutorial() : SceneBase("Tutorial", 400, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �`���[�g���A���E�B���h�E */
		this->piGrHandle_Tutorial_Window = ImageList->piGetImage("UI_Tutorial/Tutorial_Window");
	}

	/* ��~�J�n���̎��Ԃ��擾 */
	this->iTutorialNo		= 0;				// �`�ʂ���`���[�g���A���̔ԍ�
	this->iStopStartTime	= GetNowCount();	// ��~�J�n���̎���
	this->iMaxItemNo		= 0;				// ���݂̃`���[�g���A���̍ő區�ڐ�
	this->iNowItemNo		= 0;				// ���݂̃`���[�g���A���̕`�ʒ��̍��ڐ�
}

// �f�X�g���N�^
SceneUi_Tutorial::~SceneUi_Tutorial()
{
	/* ���݂̎��ԂƊJ�n���̎��Ԃ̍��ق��擾 */
	int iStopTime = GetNowCount() - this->iStopStartTime;

	/* �X�e�[�W��̒�~�������Ԃ��擾 */
	int iStopTotalTime = this->StageStatusList->iGetStopTotalTime();

	/* �X�e�[�W��̒�~�������Ԃɉ��Z���o�^ */
	this->StageStatusList->SetStopTotalTime(iStopTotalTime + iStopTime);

	/* "�|�[�Y���j���[�J��"��SE���Đ� */
	gpDataList_Sound->SE_PlaySound(SE_SYSTEM_POSEMENU);
}

// ������
void SceneUi_Tutorial::Initialization()
{
	/* ���݂̃`���[�g���A���ԍ��̕`�ʓ��e���擾 */
	{
		/* �擾�����摜����ۑ�����z��̐錾 */
		std::vector<std::string> aImageName;

		/* �p�X�ƃt�@�C�����̐ݒ� */
		std::string FilePath		= "resource/SetupData/";	// �ۑ��ꏊ
		std::string jsonFileName	= "TutorialData.json";		// �t�@�C����

		/* �t�@�C���W�J */
		std::ifstream inputFile(FilePath + jsonFileName);

		/* �t�@�C���̓W�J�������������m�F */
		if (inputFile.is_open())
		{
			// �t�@�C�������݂���ꍇ
			/* JSON �f�[�^���擾 */
			nlohmann::json json;
			inputFile >> json;

			/* �Ώۂ̃L�[�̃f�[�^���擾 */
			auto& value = json.at(std::to_string(this->iTutorialNo));

			/* �`�ʉ摜 */
			if (value.contains("DrawCg"))
			{
				// DrawCg���z��Ȃ̂ŁAstd::vector<std::string> �Ŏ擾����
				std::vector<std::string> drawCg = value.at("DrawCg").get<std::vector<std::string>>();

				// �z����̊e�v�f��aImageName�ɒǉ�
				aImageName.insert(aImageName.end(), drawCg.begin(), drawCg.end());
			}

			/* �`�ʃe�L�X�g */
			if (value.contains("Text"))
			{
				// Text���z��Ȃ̂ŁAstd::vector<std::string> �Ŏ擾����
				std::vector<std::string> text = value.at("Text").get<std::vector<std::string>>();

				// this->aText�ɒǉ�
				this->aText.insert(this->aText.end(), text.begin(), text.end());
			}

			/* �e�L�X�g��UTF-8����Shift-Jis�ɕϊ� */
			for (auto& name : this->aText)
			{
				/* �ϊ� */
				name = PUBLIC_PROCESS::aUtf8ToShiftJIS(name);
			}

			/* �t�@�C������� */
			inputFile.close();
		}

		/* �摜�ǂݍ��� */
		{
			/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
			DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

			/* �`���[�g���A���`�ʉ摜 */
			for (auto& name : aImageName)
			{
				/* �摜���擾 */
				std::string str = "UI_Tutorial/Image/" + name;
				int* iImageData = ImageList->piGetImage(str);

				/* �擾�����摜��ۑ� */
				this->apiGrHandle_Tutorial_Cg.push_back(iImageData);

				/* ���ڐ��ݒ� */
				this->iMaxItemNo++;
			}
		}
	}
}

// �v�Z
void SceneUi_Tutorial::Process()
{
	/* "����"�����͂��ꂽ���m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// ���͂��ꂽ�ꍇ
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
	}

	/* "��"�����͂��ꂽ���m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		// ���͂��ꂽ�ꍇ
		/* �`�ʍ��ڂ���߂�*/
		this->iNowItemNo -= 1;

		/* �`�ʍ��ڂ��ŏ��̍��ڂł��邩*/
		if (this->iNowItemNo <= 0)
		{
			// �ŏ��̍��ڂł���ꍇ
			/* �`�ʍ��ڂ��ŏ��̍��ڂɐݒ� */
			this->iNowItemNo = 0;
		}
	}

	/* "�E"�����͂��ꂽ���m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		// ���͂��ꂽ�ꍇ
		/* �`�ʍ��ڂ���i�߂�*/
		this->iNowItemNo += 1;

		/* �`�ʍ��ڂ��Ō�̍��ڂł��邩*/
		if (this->iNowItemNo >= this->iMaxItemNo)
		{
			// �Ō�̍��ڂł���ꍇ
			/* �`�ʍ��ڂ��Ō�̍��ڂɐݒ� */
			this->iNowItemNo = this->iMaxItemNo - 1;
		}
	}
}

// �`��
void SceneUi_Tutorial::Draw()
{
	/* ��ʑS�̂��Â����� */
	{
		/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

		/* ��ʑS�̂����F�ŕ`�� */
		DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

		/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	/* �`���[�g���A���E�B���h�E��`�� */
	//DrawGraph(522, 28, *this->piGrHandle_Tutorial_Window, TRUE);

	/* �`���[�g���A���`�ʉ摜��`�� */
	DrawGraph(522, 28, *this->apiGrHandle_Tutorial_Cg[this->iNowItemNo], TRUE);

	/* �e�L�X�g��`�� */
	std::string formattedText = PUBLIC_PROCESS::aInsertNewLine(this->aText[this->iNowItemNo], 26);
	DrawFormatStringToHandle(522 + 50, 28 + 512, GetColor(255, 255, 255), giFontHandle_Small, "%s", formattedText.c_str());
}

