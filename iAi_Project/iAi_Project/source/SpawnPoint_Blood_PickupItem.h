/* 2025.03.14 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �I�u�W�F�N�g */
#include "SpawnPoint_Base.h"
#include "PickUpItem_Blood.h"

/* �u���b�h(�s�b�N�A�b�v�A�C�e��)�X�|�i�[�N���X�̐錾 */

// �u���b�h(�s�b�N�A�b�v�A�C�e��)�X�|�i�[�N���X
class SpawnPoint_Blood_PickupItem : public SpawnPoint_Base
{
	public:
		SpawnPoint_Blood_PickupItem();						// �R���X�g���N�^
		virtual ~SpawnPoint_Blood_PickupItem() {};			// �f�X�g���N�^

		virtual void	Initialization() override;	// ������
};
