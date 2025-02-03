/* 2025.01.27 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_GameStatus.h"

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

		/* �\����(�����ł����g�p���Ȃ��̂ł����Œ�`) */
		// �ł���ʂ̒��S�_����߂��G�l�~�[
		struct NearEnemy
		{
			EnemyBasic* pEnemy;		// �G�l�~�[�̃|�C���^
			float fDistance;		// ��ʒ��S����̋���(�y�ʉ��̂��ߍ��W�̍��̓��)
		};
};

