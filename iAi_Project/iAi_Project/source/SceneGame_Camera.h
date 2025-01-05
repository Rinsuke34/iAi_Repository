/* 2024.01.02 ��򕗏� �t�@�C���ǉ� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* �I�u�W�F�N�g */
#include "CharacterPlayer.h"

/* �V�[���u�Q�[�� - �J�����v�̐錾 */

// �V�[�� "�Q�[����� - �J����"
class SceneGame_Camera : public SceneBase
{
	public:
		SceneGame_Camera();				// �R���X�g���N�^
		virtual ~SceneGame_Camera();	// �f�X�g���N�^

		void	Process()	override;			// �v�Z
		void	Draw()		override;			// �`��

	private:
		/* �g�p����f�[�^���X�g */
		// ����f�[�^���X�g�T�[�o�[����擾����͔̂�����Ȃ��߁A�����ŕۑ����Ă���
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�

	protected:
};
