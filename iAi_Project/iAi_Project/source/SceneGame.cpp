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

	/* BGM��ݒ� */
	gpDataList_Sound->BGM_SetHandle(BGM_STAGE);

	/* ������ */
	/* �ŏ��̃X�e�[�W�ԍ���ݒ� */
	this->StageStatusList->SetNowStageNo(STAGE_START);

	/* �ŏI�X�e�[�W�ԍ���ݒ� */
	this->StageStatusList->SetEndStageNo(STAGE_END);

	/* �J�������[�h��"�t���["�ɐݒ� */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_NORMAL);

	/* UI�ǉ��t���O��L���� */
	this->StageStatusList->SetAddUiFlg(true);

	/* �ŏ��ɃG�f�B�b�g��ʂ�ǉ������Ԃɂ��� */
	this->StageStatusList->SetFastEditFlg(true);

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

// �f�X�g���N�^
SceneGame::~SceneGame()
{
	/* �f�[�^���X�g�폜 */
	{
		/* �Q�[�����\�[�X�Ǘ� */
		gpDataListServer->DeleteDataList("DataList_StageResource");
	}
}

// �v�Z
void SceneGame::Process()
{
	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (this->StageStatusList->iGetGameStatus())
	{
		/* "���̃X�e�[�W�֑J��"��� */
		case GAMESTATUS_NEXTSTAGE:
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

					/* ���������������{ */
					pAddScene->Initialization();

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

					/* �V�[��"�^�C�g�����"��ǉ� */
					gpSceneServer->AddSceneReservation(new SceneAddTitleSetup());
				}
			}

			/* �Q�[����Ԃ�"�Q�[�����s"�ɕύX���� */
			this->StageStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
			break;

		/* "�X�e�[�W�W�����v"��� */
		case GAMESTATUS_STAGE_JUMP:
			{
				/* �W�����v��̃X�e�[�W�ԍ����擾 */
				int iJumpStageNo = this->StageStatusList->iGetJumpStageNo();

				/* �X�e�[�W�ԍ���ݒ� */
				this->StageStatusList->SetNowStageNo(iJumpStageNo);

				/* ���[�h�V�[���ǉ��t���O��L���� */
				gpSceneServer->SetAddLoadSceneFlg(true);

				/* �V�[��"�X�e�[�W"���쐬 */
				SceneBase* pAddScene = new SceneStage();

				/* ���������������{ */
				pAddScene->Initialization();

				/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
				gpSceneServer->AddSceneReservation(pAddScene);

				/* �X�e�[�W�̓ǂݍ��݂��J�n */
				dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();
			}
			break;
	}
}

// �`��
void SceneGame::Draw()
{
	/* ���݂̃X�e�[�W�ԍ����擾 */
	int iNowStageNo = this->StageStatusList->iGetNowStageNo();

	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "���݂̃X�e�[�W�ԍ� �F %d", iNowStageNo);
}

