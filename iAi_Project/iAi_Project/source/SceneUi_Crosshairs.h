/* 2025.01.27 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* UI(�N���X�w�A)�N���X�̐錾 */

// UI(�N���X�w�A)�N���X
class SceneUi_Crosshairs : public SceneBase
{
	public:
		SceneUi_Crosshairs();					// �R���X�g���N�^
		virtual ~SceneUi_Crosshairs()	{};		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�
		DataList_StageStatus*	StageStatusList;		// �X�e�[�W��ԊǗ�

		/* �֐� */
		void	Draw_RockOn_Melee();	// �`��(�ߐڍU���̗��ߎ��̃��b�N�I���G�l�~�[)
		void	Draw_RockOn_Kunai();	// �`��(�������U���̗��ߎ��̃��b�N�I���G�l�~�[)
		void	Draw_Move();			// �`��(���ߍU���̈ړ�����W)

		/* �g�p����摜�̃n���h�� */
		int*	piGrHandle_Flont;			// ���S�N���X�w�A
		int*	piGrHandle_Target_Main;		// ���b�N�I���Ώ�(���C��)�N���X�w�A
		int*	piGrHandle_Target_Sub;		// ���b�N�I���Ώ�(�T�u)�N���X�w�A
};

