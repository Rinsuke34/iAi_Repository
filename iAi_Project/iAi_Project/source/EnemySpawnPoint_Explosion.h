/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �I�u�W�F�N�g */
#include "EnemySpawnPoint_Base.h"
#include "Enemy_Explosion.h"

/* �G�l�~�[(����)�X�|�i�[�N���X�̐錾 */

// �G�l�~�[(����)�X�|�i�[�N���X
class EnemySpawnPoint_Explosion : public EnemySpawnPoint_Base
{
	public:
		EnemySpawnPoint_Explosion();				// �R���X�g���N�^
		virtual ~EnemySpawnPoint_Explosion() {};	// �f�X�g���N�^

		virtual void	Initialization() override;	// ������
};
