/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* �I�u�W�F�N�g */
#include "CharacterPlayer.h"

/* �V�[���u�Q�[���v�̐錾 */

// �V�[�� "�Q�[�����"
class SceneGame : public SceneBase
{
	public:
		SceneGame();							// �R���X�g���N�^
		virtual ~SceneGame();					// �f�X�g���N�^

		void	Process()	override;			// �v�Z
		void	Draw()		override;			// �`��

	private:
		/* �g�p����f�[�^���X�g */
		// ����f�[�^���X�g�T�[�o�[����擾����͔̂�����Ȃ��߁A�����ŕۑ����Ă���
		DataList_Object* ObjectList;	// �I�u�W�F�N�g�Ǘ�

	protected:
};
