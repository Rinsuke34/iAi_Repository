/* 2025.03.02 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* �V�[��"�Q�[���N���A"�N���X�̐錾 */

// �V�[��"�Q�[���N���A"
class SceneGameClear : public SceneBase
{
	public:
		SceneGameClear();						// �R���X�g���N�^
		virtual ~SceneGameClear();				// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus* StageStatusList;		// �Q�[����ԊǗ�

		/* �֐� */
		void	Process_Main();		// ���C������

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_GameClear;					// �Q�[���N���A
};
