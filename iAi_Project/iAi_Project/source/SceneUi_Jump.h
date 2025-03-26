/* 2025.03.26 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_PlayerStatus.h"
#include "DataList_StageStatus.h"
#include "DataList_Image.h"
#include "DataList_Object.h"

/* UI(�W�����v��)�N���X�̐錾 */

// UI(�W�����v��)�N���X
class SceneUi_Jump : public SceneBase
{
	public:
		SceneUi_Jump();					// �R���X�g���N�^
		virtual ~SceneUi_Jump() {};		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�
		DataList_StageStatus*	StageStatusList;	// �Q�[����ԊǗ�
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_Jump_Icon_Valid;	// �W�����v�A�C�R��(�L��)
		int* piGrHandle_Jump_Icon_Invalid;	// �W�����v�A�C�R��(����)
};
