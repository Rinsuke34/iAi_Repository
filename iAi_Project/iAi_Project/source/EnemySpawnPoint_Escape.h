/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �I�u�W�F�N�g */
#include "SpawnPoint_Base.h"
#include "Enemy_Escape.h"

/* �G�l�~�[(����)�X�|�i�[�N���X�̐錾 */

// �G�l�~�[(����)�X�|�i�[�N���X
class EnemySpawnPoint_Escape : public SpawnPoint_Base
{
	public:
		EnemySpawnPoint_Escape();					// �R���X�g���N�^
		virtual ~EnemySpawnPoint_Escape() {};		// �f�X�g���N�^

		virtual void	Initialization() override;	// ������
};
