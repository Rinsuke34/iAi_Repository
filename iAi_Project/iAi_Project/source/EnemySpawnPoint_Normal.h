/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �I�u�W�F�N�g */
#include "EnemySpawnPoint_Base.h"
#include "Enemy_Normal.h"

/* �G�l�~�[(�m�[�}��)�X�|�i�[�N���X�̐錾 */

// �G�l�~�[(�m�[�}��)�X�|�i�[�N���X
class EnemySpawnPoint_Normal : public EnemySpawnPoint_Base
{
	public:
		EnemySpawnPoint_Normal();						// �R���X�g���N�^
		virtual ~EnemySpawnPoint_Normal() {};			// �f�X�g���N�^

		virtual void	Initialization() override;	// ������
};
