/* 2024.12.20 �t�@�C���ǉ� ��򕗏� */

#include "SceneLoad.h"

/* �V�[���u���[�h�v�̒�` */

// �R���X�g���N�^
SceneLoad::SceneLoad() : SceneBase("Load", 9999, true)
{
	/* ���[�h���t���O��L���ɂ��� */
	gbNowLoadingFlg = true;
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

}
