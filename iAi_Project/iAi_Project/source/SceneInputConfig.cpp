/* 2024.12.21 ��򕗏� �t�@�C���쐬 */

#include "SceneInputConfig.h"

/* �V�[���u���͐ݒ�v�̒�` */

// �R���X�g���N�^
SceneInputConfig::SceneInputConfig() : SceneBase("Option - InputConfig", 1, false)
{
	/* �񓯊��ǂݍ��݂�L�������� */
	SetUseASyncLoadFlag(true);

	/* �񓯊��ǂݍ��݂𖳌������� */
	SetUseASyncLoadFlag(false);
}

// �f�X�g���N�^
SceneInputConfig::~SceneInputConfig()
{

}

// �v�Z
void SceneInputConfig::Process()
{
	/* ���肪���͂��ꂽ�� */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// ���̃V�[���̍폜�t���O��L���ɂ���
		this->bDeleteFlg = true;
		return;
	}

	///* �����ꂩ�̃{�^�������͂��ꂽ��V�[�����폜 */
	//// ���쐬
	//if (gstInputData_Interaction.igRel != 0)
	//{
	//	// ���̃V�[���̍폜�t���O��L���ɂ���
	//	this->bDeleteFlg = true;
	//	return;
	//}
}

// �`��
void SceneInputConfig::Draw()
{

}
