/* 2024.12.20 �t�@�C���ǉ� ��򕗏� */

#include "SceneLoad.h"

/* �V�[���u���[�h�v�̒�` */

// �R���X�g���N�^
SceneLoad::SceneLoad() : SceneBase("Load", 9999, true)
{
	/* �e�X�g�p */
	this->iTestCount = 0;

	/* ���[�h���t���O��L���ɂ��� */
	gbNowLoadingFlg = true;
}

// �f�X�g���N�^
SceneLoad::~SceneLoad()
{

}

// ������
void SceneLoad::Initialization()
{

}

// �v�Z
void SceneLoad::Process()
{
	/* �񓯊��ǂݍ��݂��������Ă��邩�m�F */
	if (GetASyncLoadNum() <= 0)
	{
		// �񓯊��ǂݍ��݂��������Ă���ꍇ
		/* �V�[���폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;

		/* ���[�h���t���O�𖳌��ɂ��� */
		gbNowLoadingFlg = false;
		return;
	}

	return;
}

// �`��
void SceneLoad::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "�Ȃ���[�ł���");
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "�J�E���g : %d", this->iTestCount);
}
