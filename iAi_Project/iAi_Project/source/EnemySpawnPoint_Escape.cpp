/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#include "EnemySpawnPoint_Escape.h"

/* �G�l�~�[(����)�X�|�i�[�N���X�̒�` */
// �R���X�g���N�^
EnemySpawnPoint_Escape::EnemySpawnPoint_Escape() : EnemySpawnPoint_Base()
{

}

// ������
void EnemySpawnPoint_Escape::Initialization()
{
	/* �G�l�~�[(����)�������� */
	{
		/* �G�l�~�[(����)���쐬 */
		EscapeEnemy* AddEnemy = new EscapeEnemy();

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
