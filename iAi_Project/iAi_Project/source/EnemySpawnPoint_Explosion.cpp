/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#include "EnemySpawnPoint_Explosion.h"

/* �G�l�~�[(����)�X�|�i�[�N���X�̒�` */
// �R���X�g���N�^
EnemySpawnPoint_Explosion::EnemySpawnPoint_Explosion() : EnemySpawnPoint_Base()
{

}

// ������
void EnemySpawnPoint_Explosion::Initialization()
{
	/* �G�l�~�[(����)�������� */
	{
		/* �G�l�~�[(����)���쐬 */
		Enemy_Explosion* AddEnemy = new Enemy_Explosion();

		/* ���������G�l�~�[(����)�����X�g�ɒǉ� */
		this->ObjectList->SetEnemy(AddEnemy);

		/* ���������G�l�~�[(����)�̍��W��ݒ� */
		AddEnemy->SetPosition(this->vecPosition);

		/* ���������G�l�~�[(����)�̉�]�ʂ�ݒ� */
		AddEnemy->SetRotation(this->vecRotation);

		/* ���������G�l�~�[(����)�̏��������� */
		AddEnemy->Initialization();
	}
}
