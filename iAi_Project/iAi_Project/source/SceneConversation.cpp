/* 2025.03.19 �t�@�C���ǉ� ��򕗏� */

#include "SceneConversation.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>

/* �V�[��"��b�p�[�g"�̒�` */
// �R���X�g���N�^
SceneConversation::SceneConversation() : SceneBase("Conversation", 400, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�v�V�����ݒ�Ǘ�"���擾 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* �摜�n���h���擾 */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �摜�n���h�� */
		//this->piGrHandle = ImageList->piGetImage("");
	}

	/* ������ */
	this->iTextFileNo	=	0;	// �e�L�X�g�t�@�C���ԍ�
	this->iDrawText		=	0;	// �e�L�X�g�̕`�ʗ�
	this->iNowTextNo	=	0;	// ���݂̃e�L�X�g�ԍ�
	this->iHoldTimer	=	0;	// ����������
}

// �f�X�g���N�^
SceneConversation::~SceneConversation()
{

}

// ������
void SceneConversation::Initialization()
{
	/* ���݂̃e�L�X�g�t�@�C���ԍ��̃e�L�X�g��ǂݍ��� */
	LoadTextData();
}

// �v�Z
void SceneConversation::Process()
{
	/* ���݂̃e�L�X�g�ԍ��̃e�L�X�g�����擾 */
	TEXT_DATA stTextData = this->astTextDataList[this->iNowTextNo];

	/* �e�L�X�g�`�ʗʂ����Z */
	this->iDrawText += stTextData.iSpeed;

	/* �e�L�X�g�`�ʗʂ����ʂ𒴂������m�F */
	if (this->iDrawText >= static_cast<int>(stTextData.aText.size()))
	{
		// ���ʂ𒴂����ꍇ
		/* �e�L�X�g�`�ʗʂ��e�L�X�g���ʂɐݒ� */
		this->iDrawText = static_cast<int>(stTextData.aText.size());

		/* "����"���g���K���͂���Ă��邩 */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			// ���͂���Ă���ꍇ
			/* �e�L�X�g�ԍ������Z */
			this->iNowTextNo += 1;

			/* �e�L�X�g�`�ʗʂ����Z�b�g */
			this->iDrawText = 0;

			/* �e�L�X�g�ԍ������ʂ𒴂������m�F */
			if (this->iNowTextNo >= static_cast<int>(this->astTextDataList.size()))
			{
				// ���ʂ𒴂����ꍇ
				/* �V�[���̍폜�t���O��L���ɂ��� */
				this->bDeleteFlg = true;
			}
		}
	}

	/* "����"���z�[���h���͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_HOLD, UI_DECID))
	{
		// ���͂���Ă���ꍇ
		/* ���������Ԃ����Z */
		this->iHoldTimer += 1;

		/* ���������Ԃ���莞�Ԃ𒴂������m�F */
		if (this->iHoldTimer >= 60)
		{
			// ��莞�Ԃ𒴂����ꍇ
			/* �X�L�b�v�m�F��ʂ�`�� */
		}
	}
	else
	{
		// ���͂���Ă��Ȃ��ꍇ
		/* ���������Ԃ����Z�b�g */
		this->iHoldTimer = 0;
	}
}

// �`��
void SceneConversation::Draw()
{
	/* ���݂̃e�L�X�g��񂩂�`�ʃe�L�X�g���e���쐬 */
	std::string	aDrawText = PUBLIC_PROCESS::aCutShitfJisString(this->astTextDataList[this->iNowTextNo].aText, this->iDrawText);
	
	/* ���݂̃e�L�X�g���ɉ����������҂̖��̂�`�� */

	/* �����G����O�Ɏ����Ă���L�����N�^�[�ɉ����ăl�[���v���[�g�̖��̂�ύX */
	switch (this->astTextDataList[this->iNowTextNo].iFocusCharacter)
	{
		/* ���̃L�����N�^�[ */
		case 1:
			/* ����"�V��" */
			DrawFormatStringToHandle(100, 500, GetColor(255, 255, 255), giFontHandle_NotoSerifJP_SemiBold, "�V��");
			break;

		/* �E�̃L�����N�^�[ */
		case 2:
			/* ����"�T�G�W�}" */
			DrawFormatStringToHandle(100, 500, GetColor(255, 255, 255), giFontHandle_NotoSerifJP_SemiBold, "�T�G�W�}");
			break;

		/* ���� */
		/* ���� */
		default:
			/* �l�[���v���[�g�ɖ��O��`�ʂ��Ȃ� */
			break;
	}

	/* �e�L�X�g�`�� */
	DrawFormatStringToHandle(100, 600, GetColor(255, 255, 255), giFontHandle_NotoSerifJP_Medium, aDrawText.c_str());
}

// �e�L�X�g�f�[�^�ǂݍ���
void SceneConversation::LoadTextData()
{
	/* �p�X�ƃt�@�C�����̐ݒ� */
	std::string strTextData = "resource/TextData/TextData_" + std::to_string(this->iTextFileNo) + ".json";

	/* �t�@�C���W�J */
	std::ifstream inputFile(strTextData);

	/* �t�@�C���̓W�J�������������m�F */
	if (inputFile.is_open())
	{
		// �t�@�C�������݂���ꍇ
		/* ��b�p�[�g�p�̃e�L�X�g�f�[�^���X�g���擾 */
		nlohmann::json	json;
		inputFile >> json;
		/* ���ׂĂ̗v�f��ǂݍ��� */
		for (auto& data : json)
		{
			/* �e�L�X�g�f�[�^���擾 */
			TEXT_DATA stTextData;
			data.at("Text").get_to(stTextData.aText);
			data.at("FocusChara").get_to(stTextData.iFocusCharacter);
			data.at("LeftCharaCg").get_to(stTextData.iLeftCharactorCg);
			data.at("RightCharaCg").get_to(stTextData.iRightCharactorCg);
			data.at("Speed").get_to(stTextData.iSpeed);
			data.at("VoiceNo").get_to(stTextData.iVoiceNo);

			/* �ǂݍ��񂾕������UTF-8�`Shift-JIS�ɕϊ� */
			stTextData.aText = PUBLIC_PROCESS::aUtf8ToShiftJIS(stTextData.aText);

			/* �z��ɒǉ� */
			this->astTextDataList.push_back(stTextData);
		}

		/* �t�@�C������� */
		inputFile.close();
	}
}
