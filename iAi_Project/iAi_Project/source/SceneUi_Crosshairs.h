/* 2025.01.27 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_GameStatus.h"
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
		DataList_GameStatus*	GameStatusList;		// �Q�[����ԊǗ�

		/* �֐� */
		void	Draw_RockOn();		// �`��(���b�N�I���G�l�~�[)
		void	Draw_Move();		// �`��(���ߍU���̈ړ�����W)

		/* �ϐ� */
		int*	ipCgHandle_Flont;			// ���S�N���X�w�A
		int*	ipCgHandle_Target_Main;		// ���b�N�I���Ώ�(���C��)�N���X�w�A
		int*	ipCgHandle_Target_Sub;		// ���b�N�I���Ώ�(�T�u)�N���X�w�A
};

