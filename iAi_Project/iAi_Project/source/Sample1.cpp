#include "Sample1.h"
#include "SampleTitle.h"

// �R���X�g���N�^
SceneSample::SceneSample() : SceneBase("Sample", 1, false)
{
	/* �񓯊��ǂݍ��݂�L�������� */
	SetUseASyncLoadFlag(true);

	/* �񓯊��ǂݍ��݂𖳌������� */
	SetUseASyncLoadFlag(false);
}

// �f�X�g���N�^
SceneSample::~SceneSample()
{

}

// �v�Z
void SceneSample::Process()
{
	/* �����ꂩ�̃{�^�������͂��ꂽ��^�C�g���� */
	if (gstInputData.igRel != 0)
	{
		gpSceneServer->AddSceneReservation(new SceneTitle(), true);
	}
}

// �`��
void SceneSample::Draw()
{
	DrawFormatString(10, 30, GetColor(237, 26, 61), "�V�[�� : �T���v��");
}
