/* 2025.01.16 ��򕗏� �X�e�[�W�쐬 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_PlayerStatus.h"
#include "DataList_Model.h"

/* �X�e�[�W */
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

		/* �ϐ� */
		int		iNowStageNo;	// ���݂̃X�e�[�W�ԍ�
		int		iEndStageNo;	// �ŏI�X�e�[�W�ԍ�

	protected:
};
