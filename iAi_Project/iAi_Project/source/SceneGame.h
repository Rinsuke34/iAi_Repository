/* 2025.01.16 ��򕗏� �X�e�[�W�쐬 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_GameStatus.h"
#include "DataList_Model.h"
#include "DataList_Effect.h"
#include "DataList_GameResource.h"

/* �V�[�� */
#include "SceneHome.h"
#include "SceneStage.h"

/* �V�[���u�Q�[���v�̐錾 */

// �V�[�� "�Q�[�����"
class SceneGame : public SceneBase
{
	public:
		SceneGame();							// �R���X�g���N�^
		virtual ~SceneGame();					// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_GameStatus*	GameStatusList;	// �Q�[����ԊǗ�

	protected:
};
