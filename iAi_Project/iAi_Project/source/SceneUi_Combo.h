/* 2025.01.28 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

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
		DataList_StageStatus*	StageStatusList;		// �Q�[����ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_Combo_Frame;			// �R���{�t���[��
		int* piGrHandle_Combo_Timer;			// �R���{�^�C�}�[
		int* piGrHandle_Combo_Alphabet[5];		// �R���{�A���t�@�x�b�g

		/* �ϐ� */
		int iPlayerComboRank;					// ���݂̃R���{�����N
};