/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#include "EnemySpawnPoint_Beam.h"

/* �G�l�~�[(�r�[��)�X�|�i�[�N���X�̒�` */
// �R���X�g���N�^
EnemySpawnPoint_Beam::EnemySpawnPoint_Beam() : EnemySpawnPoint_Base()
{

}

// ������
void EnemySpawnPoint_Beam::Initialization()
{
	/* �G�l�~�[(�r�[��)�������� */
	{
		/* �G�l�~�[(�r�[��)���쐬 */
		BeamEnemy* AddEnemy = new BeamEnemy();

		/* ���������G�l�~�[(�r�[��)�����X�g�ɒǉ� */
		this->ObjectList->SetEnemy(AddEnemy);

		/* ���������G�l�~�[(�r�[��)�̍��W��ݒ� */
		AddEnemy->SetPosition(this->vecPosition);

		/* ���������G�l�~�[(�r�[��)�̉�]�ʂ�ݒ� */
		AddEnemy->SetRotation(this->vecRotation);

		/* ���������G�l�~�[(�r�[��)�̏��������� */
		AddEnemy->Initialization();
	}
}
