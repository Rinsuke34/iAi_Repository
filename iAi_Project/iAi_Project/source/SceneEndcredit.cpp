/* 2025.03.24 �t�@�C���ǉ� ��򕗏� */

#include "SceneEndcredit.h"

/* �V�[��"�G���h�N���W�b�g"�̒�` */
// �R���X�g���N�^
SceneEndcredit::SceneEndcredit() : SceneBase("Endcredit", 500, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�v�V�����ݒ�Ǘ�"���擾 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ����A�C�R��(0:�R���g���[���[/1:�L�[�{�[�h) */
		this->piGrHandle_Icon_Button_Select[0] = ImageList->piGetImage("Input_Icon/XBOX/xbox_button_a");
		this->piGrHandle_Icon_Button_Select[1] = ImageList->piGetImage("Input_Icon/Keyboard/keyboard_z");

		/* �z�[���h�A�C�R�� */
		this->piGrHandle_Icon_Hold = ImageList->piGetImage("Conversation/HoldTimer");

		/* �G���h�N���W�b�g */
		this->piGrhandle_EndCredit = ImageList->piGetImage("Endcredit/Endcredit");
	}

	/* ������ */
	this->iElapsedTime		= 0;	// �o�ߎ���
	this->iScrollEndTime	= 0;	// �X�N���[���I������
	this->iHoldTimer		= 0;	// ����������

	/* �I�����Ԃ��Z�o */
	{
		/* �G���h�N���W�b�g�摜�̍������擾 */
		int iSizeX, iSizeY;
		GetGraphSize(*this->piGrhandle_EndCredit, &iSizeX, &iSizeY);

		/* �X�N���[���I�����Ԃ��Z�o */
		this->iScrollEndTime = iSizeY - SCREEN_SIZE_HEIGHT;
	}
}

// �f�X�g���N�^
SceneEndcredit::~SceneEndcredit()
{
	/* �V�[��"�^�C�g�����"��ǉ� */
	gpSceneServer->AddSceneReservation(new SceneAddTitleSetup());
}

// �v�Z
void SceneEndcredit::Process()
{
	/* "����"���z�[���h���͂���Ă��邩�m�F */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_HOLD, UI_DECID))
	{
		// ���͂���Ă���ꍇ
		/* ���������Ԃ����Z */
		this->iHoldTimer += 1;

		/* ���������Ԃ���莞�Ԃ𒴂������m�F */
		if (this->iHoldTimer >= 60)
		{
			// ��莞�Ԃ𒴂����ꍇ
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
		}
	}
	else
	{
		// ���͂���Ă��Ȃ��ꍇ
		/* ���������Ԃ����Z�b�g */
		this->iHoldTimer = 0;
	}

	/* �X�N���[���I�����Ԃ𒴂��Ă��邩�m�F */
	if (this->iElapsedTime >= this->iScrollEndTime)
	{
		// �����Ă���ꍇ
		/* �o�ߎ��Ԃ��X�N���[���I�����Ԃɐݒ� */
		this->iElapsedTime = this->iScrollEndTime;
	}
	else
	{
		// �����Ă��Ȃ��ꍇ
		/* �o�ߎ��Ԃ����Z���� */
		this->iElapsedTime += 1;
	}
}

// �`��
void SceneEndcredit::Draw()
{
	/* �G���h�N���W�b�g�`�� */
	DrawGraph(0, -this->iElapsedTime, *this->piGrhandle_EndCredit, FALSE);

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
