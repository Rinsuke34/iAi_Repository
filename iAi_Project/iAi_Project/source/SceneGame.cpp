/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* �V�[���u�Q�[���v�̒�` */

// �R���X�g���N�^
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* ������ */
	this->iNowStageNo	= 0;	// ���݂̃X�e�[�W�ԍ�
	this->iEndStageNo	= 0;	// �ŏI�X�e�[�W�ԍ�

	/* ���[�f�B���O���̍쐬 */
	//gstLoadingFutures.push_back(std::async(std::launch::async, &SceneGame::Initialization, this));
	Initialization();
}

// �f�X�g���N�^
SceneGame::~SceneGame()
{
	/* �f�[�^���X�g�폜 */
	gpDataListServer->DeleteDataList("DataList_PlayerStatus");	// �v���C���[���
	gpDataListServer->DeleteDataList("DataList_Model");			// 3D���f���Ǘ�

	/* Effkseer�̎g�p���I������ */
	Effkseer_End();
}

// ������
void SceneGame::Initialization()
{
	/* SceneBase�̏����������{(���\�[�X�����΍�) */
	SceneBase::Initialization();

	/* Effekseer���������� */
	if (Effekseer_Init(EFFECT_MAX_PARTICLE) == -1)
	{
		// �G���[���N�����璼���ɏI��
		DxLib_End();
		gbEndFlg = true;
		return;
	}

	/* �f�[�^���X�g�쐬 */
	{
		/* �f�[�^���X�g�T�[�o�[��"�v���C���[���"��ǉ� */
		gpDataListServer->AddDataList(new DataList_PlayerStatus());

		/* �f�[�^���X�g�T�[�o�[��"3D���f���Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_Model());
	}

	/* ������ */
	// ���`���[�g���A���t���O�ɉ����ď����X�e�[�W��ύX

	/* �`���[�g���A���t���O���L���ł��邩�m�F */
	if (gbTutorialFlg == true)
	{
		// �`���[�g���A���t���O���L��
		/* �ŏ��̃X�e�[�W�ԍ���"�`���[�g���A���J�n"�ɐݒ� */
		this->iNowStageNo = STAGE_NO_TUTORIAL_START;

		/* �ŏI�X�e�[�W�ԍ���"�`���[�g���A���I��"�ɐݒ� */
		this->iEndStageNo = STAGE_NO_TUTORIAL_END;
	}
	else
	{
		// �`���[�g���A���t���O������
		/* �ŏ��̃X�e�[�W�ԍ���"���H�J�n"�ɐݒ� */
		this->iNowStageNo = STAGE_NO_PRACTICE_START;

		/* �ŏI�X�e�[�W�ԍ���"���H�I��"�ɐݒ� */
		this->iEndStageNo = STAGE_NO_PRACTICE_END;
	}

	/* "�ŏ��̃X�e�[�W�ԍ�"�̃X�e�[�W��ǂݍ��� */
	///* ���[�h�V�[���ǉ��t���O��L���� */
	//gpSceneServer->SetAddLoadSceneFlg(true);

	/* �V�[��"�X�e�[�W"���쐬 */
	SceneBase* pAddScene = new SceneStage();

	/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
	gpSceneServer->AddSceneReservation(pAddScene);

	/* �X�e�[�W�̓ǂݍ��݂��J�n */
	dynamic_cast<SceneStage*>(pAddScene)->LoadMapData(this->iNowStageNo);
}

// �v�Z
void SceneGame::Process()
{

}

// �`��
void SceneGame::Draw()
{

}

