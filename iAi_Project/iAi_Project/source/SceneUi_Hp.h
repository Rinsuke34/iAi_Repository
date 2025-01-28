/* 2025.01.28 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"

/* �f�[�^���X�g */
#include "DataList_PlayerStatus.h"
#include "DataList_GameStatus.h"

/* UI(HP)�N���X�̐錾 */

// UI(HP)�N���X
class SceneUi_Hp : public SceneBase
{
	public:
		SceneUi_Hp();					// �R���X�g���N�^
		virtual ~SceneUi_Hp();			// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_PlayerStatus* PlayerStatusList;	// �v���C���[��ԊǗ�
		DataList_GameStatus* GameStatusList;		// �Q�[����ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int iCgHandle_Hp_Frame;		// HP�t���[��
		int iCgHandle_Hp_Gauge;		// HP�Q�[�W
};

