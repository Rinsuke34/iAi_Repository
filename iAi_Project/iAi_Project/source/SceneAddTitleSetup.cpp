/* 2025.03.05 �t�@�C���쐬 ��򕗏� */

#include "SceneAddTitleSetup.h"

/* �V�[��"�^�C�g��"�ǉ��Z�b�g�A�b�v�̒�` */
// �R���X�g���N�^
SceneAddTitleSetup::SceneAddTitleSetup() : SceneBase("AddSceneTitleSetup", 10, true)
{

}

// �v�Z
void SceneAddTitleSetup::Process()
{
	/* �f�[�^���X�g"�X�e�[�W��ԊǗ�"���擾 */
	DataList_StageStatus* StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

	/* "�X�e�[�W��ԊǗ�"������������ */
	StageStatusList->Initialization();

	/* ���s�V�[���폜�t���O��L���� */
	gpSceneServer->SetDeleteCurrentSceneFlg(true);

	/* �V�[��"�^�C�g��"��ǉ� */
	gpSceneServer->AddSceneReservation(new SceneTitle());
}
