/* 2025.01.28 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"

/* �f�[�^���X�g */
#include "DataList_PlayerStatus.h"
#include "DataList_GameStatus.h"
#include "DataList_Score.h"

/* UI(�R���{)�N���X�̐錾 */

// UI(�R���{)�N���X
class SceneUi_Combo : public SceneBase
{
	public:
		SceneUi_Combo();					// �R���X�g���N�^
		virtual ~SceneUi_Combo();			// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�
		DataList_GameStatus*	GameStatusList;		// �Q�[����ԊǗ�
		DataList_Score*			ScoreList;			// �X�R�A�֘A�Ǘ�

		/* �g�p����摜�̃n���h�� */
		int iCgHandle_Combo_Frame;			// �R���{�t���[��
		int iCgHandle_Combo_Timer;			// �R���{�^�C�}�[
		int iCgHandle_Combo_Alphabet[5];	// �R���{�A���t�@�x�b�g
};