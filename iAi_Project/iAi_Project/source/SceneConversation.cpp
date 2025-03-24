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

		/* �X�L�b�v�m�F�E�B���h�E */
		this->piGrHandle_SkipWindow				= ImageList->piGetImage("Conversation/SkipWindow/UI_Window_Skip");

		/* �X�L�b�v�m�F�E�B���h�E_�{�^�� */
		this->apiGrHandle_SkipWindow_Yes[0]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_Yes_Selected");
		this->apiGrHandle_SkipWindow_Yes[1]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_Yes_NotSelected");
		this->apiGrHandle_SkipWindow_No[0]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_No_Selected");
		this->apiGrHandle_SkipWindow_No[1]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_No_NotSelected");

		/* ����A�C�R��(0:�R���g���[���[/1:�L�[�{�[�h) */
		this->piGrHandle_Icon_Button_Select[0]	= ImageList->piGetImage("Input_Icon/XBOX/xbox_button_a");
		this->piGrHandle_Icon_Button_Select[1]	= ImageList->piGetImage("Input_Icon/Keyboard/keyboard_z");

		/* �z�[���h�A�C�R�� */
		this->piGrHandle_Icon_Hold				= ImageList->piGetImage("Conversation/HoldTimer");

		/* �w�i */
		this->piGrhandle_BackGround				= ImageList->piGetImage("Conversation/Bg_Dialogue_Stage");

		/* �e�L�X�g�w�i */
		this->piGrHandle_TextBackGround			= ImageList->piGetImage("Conversation/UI_Dialogue_Frame");

		/* �v���C���[�����G */
		this->apiGrHandle_Standing_Player[0]	= ImageList->piGetImage("Conversation/Standing/Player/stand_player_01");
		this->apiGrHandle_Standing_Player[1]	= ImageList->piGetImage("Conversation/Standing/Player/stand_player_02");
		this->apiGrHandle_Standing_Player[2]	= ImageList->piGetImage("Conversation/Standing/Player/stand_player_03");

		/* ���m(�T�G�W�})�����G */
		this->apiGrHandle_Standing_Doctor[0]	= ImageList->piGetImage("Conversation/Standing/Doctor/stand_doctor_01");
		this->apiGrHandle_Standing_Doctor[1]	= ImageList->piGetImage("Conversation/Standing/Doctor/stand_doctor_02");
		this->apiGrHandle_Standing_Doctor[2]	= ImageList->piGetImage("Conversation/Standing/Doctor/stand_doctor_03");
	}

	/* ������ */
	this->iTextFileNo		=	-1;		// �e�L�X�g�t�@�C���ԍ�
	this->iTextDrawDelay	=	0;		// �e�L�X�g�X�V�ҋ@����
	this->iDrawText			=	0;		// �e�L�X�g�̕`�ʗ�
	this->iNowTextNo		=	0;		// ���݂̃e�L�X�g�ԍ�
	this->iHoldTimer		=	0;		// ����������
	this->bAddSkipCheckFlg	=	false;	// �X�L�b�v�m�F��ʂ�`�ʒ��ł��邩
	this->bSelectYes		=	false;	// YES��I�𒆂ł��邩(�X�L�b�v���)
}

// ������
void SceneConversation::Initialization()
{
	/* �e�L�X�g�t�@�C���ԍ���0(�I�[�v�j���O��b)�ł��邩�m�F */
	if (this->iTextFileNo == 0)
	{
		// �I�[�v�j���O��b�ł���ꍇ
		/* �w�i��ʂ̕��ɕύX���� */
		/* �摜�n���h���擾 */
		{
			/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
			DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

			/* �w�i */
			this->piGrhandle_BackGround = ImageList->piGetImage("Conversation/Bg_Dialogue_Op");
		}
	}

	/* ���݂̃e�L�X�g�t�@�C���ԍ��̃e�L�X�g��ǂݍ��� */
	LoadTextData();
}

// �v�Z
void SceneConversation::Process()
{
	/* �e�L�X�g�t�@�C���ԍ�������(-1)�ł��邩�m�F */
	if (this->iTextFileNo == -1)
	{
		// �����ł���ꍇ
		/* ���̃V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
		return;
	}

	/* �X�L�b�v�m�F��ʂ�`�ʒ��ł��邩�m�F */
	if (this->bAddSkipCheckFlg == true)
	{
		// �`�ʒ��ł���ꍇ
		/* �X�L�b�v�m�F��ʂ̕`�ʏ��� */
		Process_SkipCheck();
	}
	else
	{
		// �`�ʒ��łȂ��ꍇ
		/* ��b�p�[�g�̕`�ʏ��� */
		Process_Conversation();
	}
}

// �`��
void SceneConversation::Draw()
{
	/* �w�i�`�� */
	DrawGraph(0, 0, *this->piGrhandle_BackGround, TRUE);

	/* �����G�`�� */
	DrawGraph(0,	0, *this->apiGrHandle_Standing_Player[this->astTextDataList[this->iNowTextNo].iLeftCharactorCg], TRUE);
	DrawGraph(840,	0, *this->apiGrHandle_Standing_Doctor[this->astTextDataList[this->iNowTextNo].iRightCharactorCg], TRUE);

	/* ��b�E�B���h�E�w�i�`�� */
	DrawGraph(0, 715, *this->piGrHandle_TextBackGround, TRUE);

	/* ���݂̃e�L�X�g��񂩂�`�ʃe�L�X�g���e���쐬 */
	std::string	aDrawText = PUBLIC_PROCESS::aCutShitfJisString(this->astTextDataList[this->iNowTextNo].aText, this->iDrawText);
	
	/* �����G����O�Ɏ����Ă���L�����N�^�[�ɉ����ăl�[���v���[�g�̖��̂�ύX */
	switch (this->astTextDataList[this->iNowTextNo].iFocusCharacter)
	{
		/* ���̃L�����N�^�[ */
		case 1:
			/* ����"�V��" */
			DrawFormatStringToHandle(200, 850, GetColor(0, 0, 255), giFontHandle_NotoSerifJP_SemiBold, "�V��");
			break;

		/* �E�̃L�����N�^�[ */
		case 2:
			/* ����"�T�G�W�}" */
			DrawFormatStringToHandle(200, 850, GetColor(0, 0, 255), giFontHandle_NotoSerifJP_SemiBold, "�T�G�W�}");
			break;

		/* ���� */
		/* ���� */
		default:
			/* �l�[���v���[�g�ɖ��O��`�ʂ��Ȃ� */
			break;
	}

	/* �e�L�X�g�`�� */
	DrawFormatStringToHandle(250, 900, GetColor(255, 255, 255), giFontHandle_NotoSerifJP_Medium, aDrawText.c_str());

	/* �X�L�b�v�m�F��ʂ�`�ʒ��ł��邩�m�F */
	if (this->bAddSkipCheckFlg == true)
	{
		// �`�ʒ��ł���ꍇ
		/* �X�L�b�v�m�F��ʂ�`�� */
		DrawGraph(570, 270, *this->piGrHandle_SkipWindow, TRUE);

		/* YES���I�𒆂ł��邩�m�F */
		if (this->bSelectYes == true)
		{
			// YES���I�𒆂̏ꍇ
			/* YES��I�𒆂Ƃ��ĕ`�� */
			DrawGraph(690, 560, *this->apiGrHandle_SkipWindow_Yes[0], TRUE);

			/* NO���I�𒆂Ƃ��ĕ`�� */
			DrawGraph(1020, 560, *this->apiGrHandle_SkipWindow_No[1], TRUE);
		}
		else
		{
			// YES���I�𒆂łȂ��ꍇ
			/* YES���I�𒆂Ƃ��ĕ`�� */
			DrawGraph(690, 560, *this->apiGrHandle_SkipWindow_Yes[1], TRUE);

			/* NO��I�𒆂Ƃ��ĕ`�� */
			DrawGraph(1020, 560, *this->apiGrHandle_SkipWindow_No[0], TRUE);
		}
	}

	/* �L�[�{�[�h�`�ʂł��邩�m�F */
	int iDrawTypeNo = 0;
	if (OptionList->bGetOperation_Keyboard() == true)
	{
		// �L�[�{�[�h�`�ʂł���ꍇ
		/* �`�ʃ^�C�v�ԍ����L�[�{�[�h�`�ʂɐݒ� */
		iDrawTypeNo = 1;
	}
	else
	{
		// �L�[�{�[�h�`�ʂłȂ��ꍇ
		/* �`�ʃ^�C�v�ԍ����R���g���[���[�`�ʂɐݒ� */
		iDrawTypeNo = 0;
	}

	/* A�{�^���`�� */
	DrawGraph(1820, 980, *this->piGrHandle_Icon_Button_Select[iDrawTypeNo], TRUE);
	double dComboTimerPercent = (static_cast<double>(this->iHoldTimer / 60.f) * 100.0);
	DrawCircleGauge(1820 + 32, 980 + 32, dComboTimerPercent, *this->piGrHandle_Icon_Hold);
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
			data.at("BgmNo").get_to(stTextData.iBgmNo);

			/* �ǂݍ��񂾕������UTF-8�`Shift-JIS�ɕϊ� */
			stTextData.aText = PUBLIC_PROCESS::aUtf8ToShiftJIS(stTextData.aText);

			/* �z��ɒǉ� */
			this->astTextDataList.push_back(stTextData);
		}

		/* �t�@�C������� */
		inputFile.close();
	}
	else
	{
		// �t�@�C�������݂��Ȃ��ꍇ
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
	}
}

// �v�Z(�X�L�b�v��ʕ`�ʒ�)
void SceneConversation::Process_SkipCheck()
{
	/* "����"���g���K���͂���Ă��邩�m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// ���͂���Ă���ꍇ
		/* "����"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

		/* YES���I�𒆂ł��邩�m�F */
		if (this->bSelectYes == true)
		{
			// �I�𒆂ł���ꍇ
			/* �폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
		}
		else
		{
			// �I�𒆂łȂ��ꍇ
			/* �X�L�b�v�m�F��ʂ��`�ʒ��ɂ��� */
			this->bAddSkipCheckFlg = false;
		}
	}

	/* "�L�����Z��"���g���K���͂���Ă��邩�m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
	{
		// ���͂���Ă���ꍇ
		/* �X�L�b�v�m�F��ʂ��`�ʒ��ɂ��� */
		this->bAddSkipCheckFlg = false;
	}

	/* "��"���g���K���͂���Ă��邩�m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		// ���͂���Ă���ꍇ
		/* "�J�[�\���ړ�"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* YES��I�𒆂Ƃ��� */
		this->bSelectYes = true;
	}

	/* "�E"���g���K���͂���Ă��邩�m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		// ���͂���Ă���ꍇ
		/* "�J�[�\���ړ�"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* No��I�𒆂Ƃ��� */
		this->bSelectYes = false;
	}
}

// �v�Z(��b�p�[�g�`�ʒ�)
void SceneConversation::Process_Conversation()
{
	/* ���݂̃e�L�X�g�ԍ��̃e�L�X�g�����擾 */
	TEXT_DATA stTextData = this->astTextDataList[this->iNowTextNo];

	/* �e�L�X�g���`�ʂ��ꂽ����ł��邩 */
	if ((this->iDrawText == 0) && (this->iTextDrawDelay == 0))
	{
		// �`�ʂ��ꂽ����ł���ꍇ
		/* �{�C�X�ԍ����L���ł��邩�m�F */
		if (stTextData.iVoiceNo != -1)
		{
			// �L���ł���ꍇ
			/* �{�C�X�Đ� */
			gpDataList_Sound->VOICE_PlaySound(stTextData.iVoiceNo);
		}

		/* BGM�ԍ����L���ł��邩�m�F */
		if (stTextData.iBgmNo != -1)
		{
			// �L���ł���ꍇ
			/* BGM�Đ� */
			gpDataList_Sound->BGM_SetHandle(stTextData.iBgmNo);
		}
	}

	/* �e�L�X�g�X�V�ҋ@���Ԃ����Z */
	this->iTextDrawDelay += 1;

	/* �e�L�X�g�X�V�ҋ@���Ԃ��ݒ肳�ꂽ���Ԃ𒴂������m�F */
	if (this->iTextDrawDelay > stTextData.iSpeed)
	{
		// �������ꍇ
		/* �e�L�X�g�X�V�ҋ@���Ԃ����Z�b�g */
		this->iTextDrawDelay = 0;

		/* �e�L�X�g�`�ʗʂ����Z */
		this->iDrawText += 1;
	}

	/* �e�L�X�g�`�ʗʂ����ʂ𒴂������m�F */
	if (this->iDrawText >= static_cast<int>(stTextData.aText.size()))
	{
		// ���ʂ𒴂����ꍇ
		/* �e�L�X�g�`�ʗʂ��e�L�X�g���ʂɐݒ� */
		this->iDrawText = static_cast<int>(stTextData.aText.size());

		/* "����"���g���K���͂���Ă��邩�m�F */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			// ���͂���Ă���ꍇ
			/* "����"��SE���Đ� */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

			/* �e�L�X�g�ԍ������Z */
			this->iNowTextNo += 1;

			/* �e�L�X�g�X�V�ҋ@���Ԃ����Z�b�g */
			this->iTextDrawDelay = 0;

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
	else
	{
		// ���ʂ𒴂��Ă��Ȃ��ꍇ
		/* "����"���g���K���͂���Ă��邩�m�F */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			// ���͂���Ă���ꍇ
			/* "����"��SE���Đ� */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

			/* �e�L�X�g�`�ʗʂ��e�L�X�g���ʂɐݒ� */
			this->iDrawText = static_cast<int>(stTextData.aText.size());
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
			/* ���������Ԃ����Z�b�g */
			this->iHoldTimer = 0;

			/* �X�L�b�v�m�F��ʂ�`�ʒ��ɂ��� */
			this->bAddSkipCheckFlg = true;
		}
	}
	else
	{
		// ���͂���Ă��Ȃ��ꍇ
		/* ���������Ԃ����Z�b�g */
		this->iHoldTimer = 0;
	}
}
