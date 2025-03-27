/* 2025.02.11 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"

/* �f�[�^���X�g */
#include "DataList_GameResource.h"
#include "DataList_StageStatus.h"
#include "DataList_PlayerStatus.h"

/* UI(�u���b�h(�Q�[�����ʉ�))�N���X�̐錾 */

// UI(�u���b�h(�Q�[�����ʉ�))�N���X
class SceneUi_Blood : public SceneBase
{
	public:
		SceneUi_Blood();					// �R���X�g���N�^
		virtual ~SceneUi_Blood() {};		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_GameResource*	GameResourceList;	// �Q�[�������\�[�X�Ǘ�
		DataList_StageStatus*	StageStatusList;	// �X�e�[�W��ԊǗ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_Blood_Icon;					// �u���b�h�A�C�R��
		int* piGrHandle_Text_Frame;					// �e�L�X�g�t���[��
		int* piGrHandle_Text_Frame_Magnification;	// �e�L�X�g�t���[��(�{���p)
};
