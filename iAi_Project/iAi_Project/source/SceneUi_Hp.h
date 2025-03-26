/* 2025.01.28 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"

/* �f�[�^���X�g */
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* UI(HP)�N���X�̐錾 */

// UI(HP)�N���X
class SceneUi_Hp : public SceneBase
{
	public:
		SceneUi_Hp();					// �R���X�g���N�^
		virtual ~SceneUi_Hp() {};		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�
		DataList_StageStatus*	StageStatusList;	// �X�e�[�W��ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_Hp_Frame;		// HP�t���[��
		int* piGrHandle_Hp_Gauge;		// HP�Q�[�W
};

