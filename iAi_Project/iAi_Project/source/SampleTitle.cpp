#include "SampleTitle.h"
#include "Sample1.h"

// �R���X�g���N�^
SceneTitle::SceneTitle() : SceneBase("Title", 0, false)
{
	/* �񓯊��ǂݍ��݂�L�������� */
	SetUseASyncLoadFlag(true);

	/* �񓯊��ǂݍ��݂𖳌������� */
	SetUseASyncLoadFlag(false);
}

// �f�X�g���N�^
SceneTitle::~SceneTitle()
{

}

// �v�Z
void SceneTitle::Process()
{
	/* �����ꂩ�̃{�^�������͂��ꂽ�烁�j���[��ǉ� */
	if (gstInputData.igRel != 0)
	{
		gpSceneServer->AddSceneReservation(new SceneSample(), true);
	}
}

// �`��
void SceneTitle::Draw()
{
	DrawFormatString(10, 10, GetColor(237, 26, 61), "�V�[�� : �^�C�g��");
}
