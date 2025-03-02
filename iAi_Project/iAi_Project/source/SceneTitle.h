/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[�� */
#include "SceneStage.h"
#include "SceneAddStageSetup.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"

/* �z�Q�Ƒ΍� */
class SceneStage;

/* �V�[���u�^�C�g���v�̐錾 */

// �V�[�� "�^�C�g�����"
class SceneTitle : public SceneBase
{
	public:
		SceneTitle();							// �R���X�g���N�^
		virtual ~SceneTitle();					// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus* StageStatusList;	// �Q�[����ԊǗ�

		/* �V�[��"�X�e�[�W"�̃|�C���^ */
		SceneStage* pSceneStage;

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_TitleLogo;		// �^�C�g�����S
};
