/* 2025.03.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* �z�Q�Ƒ΍�̐�s��` */
class DataList_Object;

/* �X�|�i�[�x�[�X�N���X�̐錾 */

// �X�|�i�[�x�[�X�N���X
class SpawnPoint_Base : public PlatformBase
{
	public:
		SpawnPoint_Base();					// �R���X�g���N�^
		virtual ~SpawnPoint_Base() {};		// �f�X�g���N�^

		virtual void	Reset()	override;		// ���Z�b�g����

	protected:
		/* �g�p����f�[�^���X�g */
		DataList_Object* ObjectList;	// �I�u�W�F�N�g�Ǘ�
};
