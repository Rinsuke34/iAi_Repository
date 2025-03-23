/* 2025.03.2 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* �I�u�W�F�N�g */
#include "CharacterPlayer.h"

/* �z�Q�Ƒ΍�(��قǑ΍�͎��{) */
class DataList_Object;
class CharacterPlayer;

/* �N�i�C(�s�b�N�A�b�v�A�C�e��)�N���X�̐錾 */

// �N�i�C(�s�b�N�A�b�v�A�C�e��)�N���X
class PickUpItem_Kunai : public PickUpItemBase
{
	public:
		PickUpItem_Kunai();				// �R���X�g���N�^
		virtual ~PickUpItem_Kunai() {};	// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		virtual void	Reset()				override;		// ���Z�b�g����

	private:
		/* �f�[�^���X�g */
		DataList_Object*		ObjectList;				// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;		// �v���C���[��ԊǗ�

		/* �ϐ� */
		CharacterPlayer*	pPlayer;					// �v���C���[
		int					iAddEffectDelay;			// �G�t�F�N�g�ǉ��ҋ@����
};

