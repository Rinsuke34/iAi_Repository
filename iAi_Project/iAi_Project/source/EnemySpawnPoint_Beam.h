/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �I�u�W�F�N�g */
#include "SpawnPoint_Base.h"
#include "Enemy_Beam.h"

/* �G�l�~�[(�r�[��)�X�|�i�[�N���X�̐錾 */

// �G�l�~�[(�r�[��)�X�|�i�[�N���X
class EnemySpawnPoint_Beam : public SpawnPoint_Base
{
	public:
		EnemySpawnPoint_Beam();					// �R���X�g���N�^
		virtual ~EnemySpawnPoint_Beam() {};		// �f�X�g���N�^

		virtual void	Initialization() override;	// ������
};
