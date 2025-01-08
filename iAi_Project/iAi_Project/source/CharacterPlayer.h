/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Input.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Object.h"

/* �v���C���[�N���X�̐錾 */

// �v���C���[�N���X
class CharacterPlayer : public CharacterBase
{
	public:
		CharacterPlayer();				// �R���X�g���N�^
		virtual ~CharacterPlayer() {};	// �f�X�g���N�^

		virtual void	Update();	// �X�V
		virtual void	Draw();		// �`��

	private:
	protected:
		/* �g�p����f�[�^���X�g */
		// ����f�[�^���X�g�T�[�o�[����擾����͔̂�����Ȃ��߁A�����ŕۑ����Ă���
		DataList_Input*			InputList;			// ���͊Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[���
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�

		/* �֐� */
		void	Player_Gravity();		// �d��
		void	Player_Move();			// �ړ�
		void	Player_Jump();			// �W�����v

		void	CollisionUpdate();		// �R���W�����X�V
};
