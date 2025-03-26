/* 2025.01.19 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include "SceneEditDefine.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"
#include "DataList_GameResource.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Image.h"

/* �V�[��"�G�f�B�b�g"�N���X�̐錾 */

// �V�[��"�G�f�B�b�g"
class SceneEdit : public SceneBase
{
	public:
		SceneEdit();							// �R���X�g���N�^
		virtual ~SceneEdit();					// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus* StageStatusList;		// �Q�[����ԊǗ�
		DataList_GameResource* GameResourceList;	// �Q�[�������\�[�X�Ǘ�
		DataList_PlayerStatus* PlayerStatusList;	// �v���C���[��ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_SelectFrame[2];						// �I���t���[��(0:�z�[���h�����A 1:�z�[���h����)
		int* apiGrHandle_SelectStatus[SELECT_STATUS_MAX];	// �I�����ڂ̏�ԃt���[��
		int* piGrHandle_SelectNext;							// ���X�e�[�W�J�ڃ{�^��
		int* piGrHandle_ResultFrame;						// ���U���g�t���[��
		int* piGrHandle_ResultBackGround;					// ���U���g��ʔw�i(���p)
		int* piGrHandle_NowEdit_Under;						// ���݂̃G�f�B�b�g���
		int* piGrHandle_UnderExplain_Under;					// ���݂̃G�f�B�b�g���̐�����
		int* piGrHandle_NewEdit_Under;						// �V�K�G�f�B�b�g���̐�����
		int* piGrHandle_KeepEdit_Under;						// �L�[�v�G�f�B�b�g���̐�����
		int* piGrHandle_KeepIcon;							// �L�[�v�A�C�R��
		int* piGrHandle_Keep;								// �L�[�v(����)
		int* piGrHandle_Delete;								// �폜
		int* piGrHandle_New;								// NEW(����)
		int* piGrHandle_Custom;								// �J�X�^��(����)
		int* piGrHandle_Blood;								// �u���b�h
		int* apiGrHandle_EditLock[2];						// �G�f�B�b�g���b�N����(0:B�����N, 1:A�����N)

		/* �֐� */
		void	Process_Main();				// ���C������
		void	Process_Decid();			// ������͎��̏���
		void	Process_Select();			// �������͎��̏���
		void	Process_NowEditUpdate();	// ���݂̃G�f�B�b�g���̍X�V

		/* �ϐ� */
		EDIT_SELECT_ITEM	astSelectItemList[SELECT_ITEM_MAX];		// �I�����ڈꗗ
		int					iSelectItem;							// �I�𒆂̍��ڂ̔ԍ�
		int					iHoldSelectItemNo;						// �z�[���h���̑I�����ڂ̔ԍ�
		int					iHoldSelectItemType;					// �z�[���h���̑I�����ڂ̎��
		EDIT_DATA			HoldEditData;							// �z�[���h���̃G�f�B�b�g���
		EDIT_DATA			NewEditData[EDIT_UPGRADE_MAX];			// �V�K�̃G�f�B�b�g���
		EDIT_DATA			DeleteEditData;							// �폜�\��̃G�f�B�b�g���
		int					iNewEditNumber;							// �V�K�G�f�B�b�g��
};
