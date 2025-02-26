/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* �V�[���u�Q�[���v�̒�` */

// �R���X�g���N�^
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* �f�[�^���X�g�쐬 */
	{
		/* �f�[�^���X�g�T�[�o�[��"�Q�[�����\�[�X�Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_GameResource());
	}

	/* �f�[�^���X�g�擾 */
	{
		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* ���[�f�B���O���̍쐬 */
	//gstLoadingFutures.push_back(std::async(std::launch::async, &SceneGame::Initialization, this));
	Initialization();
}

// �f�X�g���N�^
SceneGame::~SceneGame()
{
	/* �f�[�^���X�g�폜 */
	{
		/* �Q�[�����\�[�X�Ǘ� */
		gpDataListServer->DeleteDataList("DataList_StageResource");
	}
}

// ������
void SceneGame::Initialization()
{
	/* BGM��ݒ� */
	gpDataList_Sound->BGM_SetHandle(BGM_STAGE);

	/* ������ */
	// ���`���[�g���A���t���O�ɉ����ď����X�e�[�W��ύX

	/* �`���[�g���A���t���O���L���ł��邩�m�F */
	if (gbTutorialFlg == true)
	{
		// �`���[�g���A���t���O���L��
		/* �ŏ��̃X�e�[�W�ԍ���"�`���[�g���A���J�n"�ɐݒ� */
		this->StageStatusList->SetNowStageNo(STAGE_NO_TUTORIAL_START);

		/* �ŏI�X�e�[�W�ԍ���"�`���[�g���A���I��"�ɐݒ� */
		this->StageStatusList->SetEndStageNo(STAGE_NO_TUTORIAL_END);
	}
	else
	{
		// �`���[�g���A���t���O������
		/* �ŏ��̃X�e�[�W�ԍ���"���H�J�n"�ɐݒ� */
		this->StageStatusList->SetNowStageNo(STAGE_NO_PRACTICE_START);

		/* �ŏI�X�e�[�W�ԍ���"���H�I��"�ɐݒ� */
		this->StageStatusList->SetEndStageNo(STAGE_NO_PRACTICE_END);
	}

	/* �J�������[�h��"�t���["�ɐݒ� */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_FREE);

	/* UI�ǉ��t���O��L���� */
	this->StageStatusList->SetAddUiFlg(true);

	/* "�ŏ��̃X�e�[�W�ԍ�"�̃X�e�[�W��ǂݍ��� */
	/* �V�[��"�X�e�[�W"���쐬 */
	SceneBase* pAddScene = new SceneStage();

	/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
	gpSceneServer->AddSceneReservation(pAddScene);

	/* �X�e�[�W�̓ǂݍ��݂��J�n */
	dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();

	/* ���������� */
	pAddScene->Initialization();
}

// �v�Z
void SceneGame::Process()
{
	/* ���݂̃X�e�[�W�ԍ����擾 */
	int iNowStageNo = this->StageStatusList->iGetNowStageNo();

	/* �X�e�[�W�ԍ���+1���� */
	iNowStageNo++;

	/* �X�e�[�W�ԍ����ŏI�X�e�[�W�ԍ��𒴂��Ă��Ȃ����m�F */
	if (iNowStageNo <= this->StageStatusList->iGetEndStageNo())
	{
		// �����Ă��Ȃ�(���̃X�e�[�W������)�ꍇ
		/* �X�e�[�W�ԍ���ݒ� */
		this->StageStatusList->SetNowStageNo(iNowStageNo);

		/* ���[�h�V�[���ǉ��t���O��L���� */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* �V�[��"�X�e�[�W"���쐬 */
		SceneBase* pAddScene = new SceneStage();

		/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
		gpSceneServer->AddSceneReservation(pAddScene);

		/* �X�e�[�W�̓ǂݍ��݂��J�n */
		dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();
	}
	else
	{
		// �����Ă���(���̃X�e�[�W���Ȃ�)�ꍇ
		/* �V�[���폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;

		/* ���[�h��ʒǉ��t���O��L���� */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* ���s�V�[���폜�t���O��L���� */
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* �V�[��"�z�[�����"��ǉ� */
		gpSceneServer->AddSceneReservation(new SceneHome());
	}
}

// �`��
void SceneGame::Draw()
{
	/* ���݂̃X�e�[�W�ԍ����擾 */
	int iNowStageNo = this->StageStatusList->iGetNowStageNo();

	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "���݂̃X�e�[�W�ԍ� �F %d", iNowStageNo);
}

