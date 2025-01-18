/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#include "AppFrame.h"
#include "VariableDefine.h"

#include "SceneTitle.h"
#include "SceneLoad.h"

#include "DataList_Input.h"

/* AppFrame�Ŏg�p����֐��̒�` */

// �V�[���̐ݒ�
namespace SCENE_SET
{
	// �Q�[���N�����̃V�[�����Z�b�g
	void	SetFastScene()
	{
		/* ���[�h��ʒǉ��t���O��L���� */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* �^�C�g���V�[����ǉ� */
		gpSceneServer->AddSceneReservation(new SceneTitle());
	}

	// ���[�h�V�[�����Z�b�g
	void	SetLoadScene()
	{
		/* ���[�h�V�[����ǉ� */
		gpSceneServer->AddSceneReservation(new SceneLoad());
	}
}

// ������
namespace PROJECT_INIT
{
	// �v���W�F�N�g����������
	void	Init()
	{
		/* �f�[�^���X�g�T�[�o�[��"�v���C���[���͊Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_Input());

		/* ���ǉ�����"�v���C���[���͊Ǘ�"���擾 */
		gpDataList_Input = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	}
}
