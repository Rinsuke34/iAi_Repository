/* 2025.03.22 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �I�u�W�F�N�g */
#include "SpawnPoint_Base.h"
#include "PickUpItem_Kunai.h"

/* �N�i�C(�s�b�N�A�b�v�A�C�e��)�X�|�i�[�N���X�̐錾 */

// �N�i�C(�s�b�N�A�b�v�A�C�e��)�X�|�i�[�N���X
class SpawnPoint_Kunai_PickupItem : public SpawnPoint_Base
{
	public:
		SpawnPoint_Kunai_PickupItem();						// �R���X�g���N�^
		virtual ~SpawnPoint_Kunai_PickupItem() {};			// �f�X�g���N�^

		virtual void	Initialization() override;	// ������
};
