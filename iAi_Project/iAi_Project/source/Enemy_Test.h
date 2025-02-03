/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "EnemyBasic.h"
#include "EffectManualDelete.h"

/* �e�X�g�p�G�N���X */

// �G�l�~�[�x�[�X�N���X
class TestEnemy : public EnemyBasic
{
	public:
		TestEnemy();				// �R���X�g���N�^
		virtual ~TestEnemy();		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V

	private:
		EffectManualDelete* eEffect;
	protected:
		/* �g�p����f�[�^���X�g */
		DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
		void MoveEnemy(); // �G���ړ������郁�\�b�h��ǉ�

		int actioncount;
};
