/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#include "EnemySpawnPoint_Missile.h"

/* �G�l�~�[(�~�T�C��)�X�|�i�[�N���X�̒�` */
// �R���X�g���N�^
EnemySpawnPoint_Missile::EnemySpawnPoint_Missile() : SpawnPoint_Base()
{

}

// ������
void EnemySpawnPoint_Missile::Initialization()
{
	/* �G�l�~�[(�~�T�C��)�������� */
	{
		/* �G�l�~�[(�~�T�C��)���쐬 */
		Enemy_Missile* AddEnemy = new Enemy_Missile();

		/* ���������G�l�~�[(�~�T�C��)�����X�g�ɒǉ� */
		this->ObjectList->SetEnemy(AddEnemy);

		/* ���������G�l�~�[(�~�T�C��)�̍��W��ݒ� */
		AddEnemy->SetPosition(this->vecPosition);

		/* ���������G�l�~�[(�~�T�C��)�̉�]�ʂ�ݒ� */
		AddEnemy->SetRotation(this->vecRotation);

		/* ���������G�l�~�[(�~�T�C��)�̏��������� */
		AddEnemy->Initialization();
	}
}
