/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#include "EnemySpawnPoint_Normal.h"

/* �G�l�~�[(�m�[�}��)�X�|�i�[�N���X�̒�` */
// �R���X�g���N�^
EnemySpawnPoint_Normal::EnemySpawnPoint_Normal() : EnemySpawnPoint_Base()
{

}

// ������
void EnemySpawnPoint_Normal::Initialization()
{
	/* �G�l�~�[(�m�[�}��)�������� */
	{
		/* �G�l�~�[(�m�[�}��)���쐬 */
		NormalEnemy* AddEnemy = new NormalEnemy();

		/* ���������G�l�~�[(�m�[�}��)�����X�g�ɒǉ� */
		this->ObjectList->SetEnemy(AddEnemy);

		/* ���������G�l�~�[(�m�[�}��)�̍��W��ݒ� */
		AddEnemy->SetPosition(this->vecPosition);

		/* ���������G�l�~�[(�m�[�}��)�̉�]�ʂ�ݒ� */
		AddEnemy->SetRotation(this->vecRotation);

		/* ���������G�l�~�[(�m�[�}��)�̏��������� */
		AddEnemy->Initialization();
	}
}
