/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �I�u�W�F�N�g */
#include "SpawnPoint_Base.h"
#include "Enemy_Missile.h"
#include "Enemy_Fixed.h"
#include "Enemy_Fixed_Turret.h"

/* �G�l�~�[(�~�T�C��)�X�|�i�[�N���X�̐錾 */

// �G�l�~�[(�~�T�C��)�X�|�i�[�N���X
class EnemySpawnPoint_Missile : public SpawnPoint_Base
{
	public:
		EnemySpawnPoint_Missile();					// �R���X�g���N�^
		virtual ~EnemySpawnPoint_Missile() {};		// �f�X�g���N�^

		virtual void	Initialization() override;	// ������
};
