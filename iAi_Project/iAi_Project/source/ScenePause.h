/* 2025.03.05 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include "ScenePauseDefine.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"
#include "DataList_GameResource.h"

/* �V�[�� */
#include "SceneOption.h"
#include "SceneAddTitleSetup.h"

/* �ꎞ��~�N���X�̐錾 */

// �ꎞ��~�N���X
class ScenePause : public SceneBase
{
	public:
		ScenePause();				// �R���X�g���N�^
		virtual ~ScenePause();		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus*	StageStatusList;	// �X�e�[�W��ԊǗ�
		DataList_GameResource*	GameResourceList;	// �Q�[�������\�[�X�Ǘ�

		/* �ϐ� */
		int	iSelectItem;			// �I�𒆂̍��ڂ̔ԍ�
		int iStopStartTime;			// ��~�J�n���̎���

		/* �֐� */
		void	SaveDataCreate();	// �Z�[�u�f�[�^�쐬
};
