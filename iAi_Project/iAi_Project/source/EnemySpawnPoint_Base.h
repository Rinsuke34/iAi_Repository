/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* �z�Q�Ƒ΍�̐�s��` */
class DataList_Object;

/* �G�l�~�[�X�|�i�[�x�[�X�N���X�̐錾 */

// �G�l�~�[�X�|�i�[�x�[�X�N���X
class EnemySpawnPoint_Base : public PlatformBase
{
	public:
		EnemySpawnPoint_Base();					// �R���X�g���N�^
		virtual ~EnemySpawnPoint_Base() {};		// �f�X�g���N�^

		virtual void	Reset()	override;		// ���Z�b�g����

	protected:
		/* �g�p����f�[�^���X�g */
		DataList_Object* ObjectList;	// �I�u�W�F�N�g�Ǘ�
};
