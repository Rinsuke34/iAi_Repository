#include "SampleLoad.h"

// �R���X�g���N�^
SceneLoad::SceneLoad() : SceneBase("Loading", 9999, true)
{

}

// �f�X�g���N�^
SceneLoad::~SceneLoad()
{

}

// �v�Z
void SceneLoad::Process()
{
	/* �񓯊��ǂݍ��݂��������Ă��邩�m�F */
	if (GetASyncLoadNum() > 0)
	{
		/* �񓯊��ǂݍ��݂����s���̏ꍇ */
	}
	else
	{
		/* �񓯊��ǂݍ��݂��������Ă���ꍇ */
		// ���̃V�[���̍폜�t���O��L���ɂ���
		this->bDeleteFlg = true;
	}
}

// �`��
void SceneLoad::Draw()
{
	DrawFormatString(10, 50, GetColor(237, 26, 61), "�V�[�� : �V�[�����[�h��");
}
