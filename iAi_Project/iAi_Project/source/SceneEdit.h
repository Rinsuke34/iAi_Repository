/* 2025.01.19 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include "SceneEditDefine.h"

/* �f�[�^���X�g */
#include "DataList_GameStatus.h"
#include "DataList_GameResource.h"
#include "DataList_Image.h"

/* �V�[��"�G�f�B�b�g"�N���X�̐錾 */

// �V�[��"�G�f�B�b�g"
class SceneEdit : public SceneBase
{
	public:
		SceneEdit();							// �R���X�g���N�^
		virtual ~SceneEdit();					// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_GameStatus* GameStatusList;		// �Q�[����ԊǗ�
		DataList_GameResource* GameResourceList;	// �Q�[�������\�[�X�Ǘ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_SelectFrame;						// �I���t���[��
		int* piGrHandle_SelectNext;							// ���X�e�[�W�J�ڃ{�^��
		int* apiGrHandle_SelectStatus[SELECT_STATUS_MAX];	// �I�����ڂ̏�ԃt���[��

		/* �֐� */
		void	Process_Main();				// ���C������
		void	Process_Decid();			// ������͎��̏���
		void	Process_Select();			// �������͎��̏���
		void	Process_NowEditUpdate();	// ���݂̃G�f�B�b�g���̍X�V

		/* �ϐ� */
		EDIT_SELECT_ITEM	astSelectItemList[SELECT_ITEM_MAX];		// �I�����ڈꗗ
		int					iUpgradeRate;							// �A�b�v�O���[�h�̃��[�g(0�`10)
		int					iSelectItem;							// �I�𒆂̍��ڂ̔ԍ�
		int					iHoldSelectItemNo;						// �z�[���h���̑I�����ڂ̔ԍ�
		int					iHoldSelectItemType;					// �z�[���h���̑I�����ڂ̎��
		EDIT_DATA			HoldEditData;							// �z�[���h���̃G�f�B�b�g���
		EDIT_DATA			NewEditData[EDIT_UPGRADE_MAX];			// �V�K�̃G�f�B�b�g���
		EDIT_DATA			DeleteEditData;							// �폜�\��̃G�f�B�b�g���
};
