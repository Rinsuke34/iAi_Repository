/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* �V�[���u�Q�[���v�̒�` */

// �R���X�g���N�^
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* �f�[�^���X�g�쐬 */
	{
		/* �f�[�^���X�g�T�[�o�[��"3D���f���Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_Model());

		/* �f�[�^���X�g�T�[�o�[��"�Q�[����ԊǗ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_GameStatus());

		/* �f�[�^���X�g�T�[�o�[��"�G�t�F�N�g���\�[�X�Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_Effect());

		/* �f�[�^���X�g�T�[�o�[��"�Q�[�����\�[�X�Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_GameResource());

		/* �f�[�^���X�g�T�[�o�[��"�摜���\�[�X�Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_Image());
	}

	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
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
		/* 3D���f���Ǘ� */
		gpDataListServer->DeleteDataList("DataList_Model");

		/* �Q�[����ԊǗ� */
		gpDataListServer->DeleteDataList("DataList_GameStatus");

		/* �G�t�F�N�g���\�[�X�Ǘ� */
		gpDataListServer->DeleteDataList("DataList_Effect");

		/* �Q�[�����\�[�X�Ǘ� */
		gpDataListServer->DeleteDataList("DataList_GameResource");

		/* �摜���\�[�X�Ǘ� */
		gpDataListServer->DeleteDataList("DataList_Image");
	}

	/* Effkseer�̎g�p���I������ */
	Effkseer_End();
}

// ������
void SceneGame::Initialization()
{
	/* BGM��ݒ� */
	gpDataList_Sound->BGM_SetHandle(BGM_STAGE);

	/* Effekseer���������� */
	if (Effekseer_Init(EFFECT_MAX_PARTICLE) == -1)
	{
		// �G���[���N�����璼���ɏI��
		DxLib_End();
		gbEndFlg = true;
		return;
	}

	/* ������ */
	// ���`���[�g���A���t���O�ɉ����ď����X�e�[�W��ύX

	/* �`���[�g���A���t���O���L���ł��邩�m�F */
	if (gbTutorialFlg == true)
	{
		// �`���[�g���A���t���O���L��
		/* �ŏ��̃X�e�[�W�ԍ���"�`���[�g���A���J�n"�ɐݒ� */
		this->GameStatusList->SetNowStageNo(STAGE_NO_TUTORIAL_START);

		/* �ŏI�X�e�[�W�ԍ���"�`���[�g���A���I��"�ɐݒ� */
		this->GameStatusList->SetEndStageNo(STAGE_NO_TUTORIAL_END);
	}
	else
	{
		// �`���[�g���A���t���O������
		/* �ŏ��̃X�e�[�W�ԍ���"���H�J�n"�ɐݒ� */
		this->GameStatusList->SetNowStageNo(STAGE_NO_PRACTICE_START);

		/* �ŏI�X�e�[�W�ԍ���"���H�I��"�ɐݒ� */
		this->GameStatusList->SetEndStageNo(STAGE_NO_PRACTICE_END);
	}

	/* "�ŏ��̃X�e�[�W�ԍ�"�̃X�e�[�W��ǂݍ��� */
	/* �V�[��"�X�e�[�W"���쐬 */
	SceneBase* pAddScene = new SceneStage();

	/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
	gpSceneServer->AddSceneReservation(pAddScene);

	/* �X�e�[�W�̓ǂݍ��݂��J�n */
	dynamic_cast<SceneStage*>(pAddScene)->LoadMapData();
}

// �v�Z
void SceneGame::Process()
{
	/* ���݂̃X�e�[�W�ԍ����擾 */
	int iNowStageNo = this->GameStatusList->iGetNowStageNo();

	/* �X�e�[�W�ԍ���+1���� */
	iNowStageNo++;

	/* �X�e�[�W�ԍ����ŏI�X�e�[�W�ԍ��𒴂��Ă��Ȃ����m�F */
	if (iNowStageNo <= this->GameStatusList->iGetEndStageNo())
	{
		// �����Ă��Ȃ�(���̃X�e�[�W������)�ꍇ
		/* �X�e�[�W�ԍ���ݒ� */
		this->GameStatusList->SetNowStageNo(iNowStageNo);

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
	int iNowStageNo = this->GameStatusList->iGetNowStageNo();

	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "���݂̃X�e�[�W�ԍ� �F %d", iNowStageNo);
}

