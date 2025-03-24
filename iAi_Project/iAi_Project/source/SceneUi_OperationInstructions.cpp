/* 2025.03.24 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_OperationInstructions.h"

/* UI(�������)�N���X�̒�` */
// �R���X�g���N�^
SceneUi_OperationInstructions::SceneUi_OperationInstructions() : SceneBase("UI_OperationInstructions", 107, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�v�V�����ݒ�Ǘ�"���擾 */
		this->OptionList		= dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));

		/* "�v���C���[��ԊǗ�"���擾 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StatusStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ��������摜�x�[�X(0:�R���g���[���[�A1:�L�[�{�[�h) */
		this->piGrHandle_Base[0]	= ImageList->piGetImage("UI_Operation/UI_Guide_CS");
		this->piGrHandle_Base[1]	= ImageList->piGetImage("UI_Operation/UI_Guide_KM");

		/* �ʏ펞��������摜(0:�R���g���[���[�A1:�L�[�{�[�h) */
		this->piGrHandle_Attack[0]	= ImageList->piGetImage("UI_Operation/UI_Guide_CS_AttackOnly");
		this->piGrHandle_Attack[1]	= ImageList->piGetImage("UI_Operation/UI_Guide_KM_AttackOnly");

		/* �N�i�C�\������������摜(0:�R���g���[���[�A1:�L�[�{�[�h) */
		this->piGrHandle_Kunai[0]	= ImageList->piGetImage("UI_Operation/UI_Guide_CS_KunaiOnly");
		this->piGrHandle_Kunai[1]	= ImageList->piGetImage("UI_Operation/UI_Guide_KM_KunaiOnly");
	}

	/* ������ */
	this->iDrawTypeNo = 0;				// �`��^�C�v�ԍ�(0:�R���g���[���[�A1:�L�[�{�[�h)
}

// �v�Z
void SceneUi_OperationInstructions::Process()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ȊO�ł���Ȃ�V�[�����폜 */
	if (this->StatusStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
		return;
	}
}

// �`��
void SceneUi_OperationInstructions::Draw()
{
	/* �L�[�{�[�h�`�ʂł��邩�m�F */
	if (OptionList->bGetOperation_Keyboard() == true)
	{
		// �L�[�{�[�h�`�ʂł���ꍇ
		/* �`�ʃ^�C�v�ԍ����L�[�{�[�h�`�ʂɐݒ� */
		this->iDrawTypeNo = 1;
	}
	else
	{
		// �L�[�{�[�h�`�ʂłȂ��ꍇ
		/* �`�ʃ^�C�v�ԍ����R���g���[���[�`�ʂɐݒ� */
		this->iDrawTypeNo = 0;
	}

	/* ��������摜�x�[�X�`�� */
	DrawGraph(1330, 870, *this->piGrHandle_Base[this->iDrawTypeNo], TRUE);

	/* �v���C���[�̍U����Ԃ��������U���\����"�ł��邩�m�F */
	if (this->PlayerStatusList->iGetPlayerAttackState() == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
	{
		// �������U���\�����ł���ꍇ
		/* �N�i�C�\������������摜�`�� */
		DrawGraph(1330, 870, *this->piGrHandle_Kunai[this->iDrawTypeNo], TRUE);
	}
	else
	{
		// �������U���\�����łȂ��ꍇ
		/* �ʏ펞��������摜�`�� */
		DrawGraph(1330, 870, *this->piGrHandle_Attack[this->iDrawTypeNo], TRUE);
	}
}
