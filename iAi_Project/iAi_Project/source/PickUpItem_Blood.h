/* 2025.03.14 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_GameResource.h"
#include "DataList_PlayerStatus.h"

/* �I�u�W�F�N�g */
#include "CharacterPlayer.h"

/* �u���b�h(�Q�[�����ʉ�/�s�b�N�A�b�v�A�C�e��)�N���X�̐錾 */

// �u���b�h(�Q�[�����ʉ�/�s�b�N�A�b�v�A�C�e��)�N���X
class PickUpItem_Blood : public PickUpItemBase
{
	public:
		PickUpItem_Blood();				// �R���X�g���N�^
		virtual ~PickUpItem_Blood() {};	// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		virtual void	Reset()				override;		// ���Z�b�g����

	private:
		/* �f�[�^���X�g */
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_GameResource*	GameResourceList;	// �Q�[�������\�[�X�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[���

		/* �ϐ� */
		CharacterPlayer*	pPlayer;					// �v���C���[
		int					iAddEffectDelay;			// �G�t�F�N�g�ǉ��ҋ@����
};

