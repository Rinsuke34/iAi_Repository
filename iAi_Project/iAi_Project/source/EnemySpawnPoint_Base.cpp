/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#include "EnemySpawnPoint_Base.h"

/* �G�l�~�[�X�|�i�[�x�[�X�N���X�̒�` */
// �R���X�g���N�^
EnemySpawnPoint_Base::EnemySpawnPoint_Base() : PlatformBase()
{
	/* �f�[�^���X�g���擾 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
}

// ���Z�b�g����
void EnemySpawnPoint_Base::Reset()
{
	/* ���̃I�u�W�F�N�g�̏��������������s���� */
	Initialization();
}
