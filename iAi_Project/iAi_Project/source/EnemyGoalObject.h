/* 2025.01.21 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �S�[���I�u�W�F�N�g�N���X�̐錾 */
// ���G�l�~�[�Ƃ��č쐬����(��)

// �S�[���N���X
class EnemyGoalObject : public EnemyBase
{
	public:
		EnemyGoalObject();				// �R���X�g���N�^
		virtual ~EnemyGoalObject();		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V

	private:
	protected:
		/* �g�p����f�[�^���X�g */
		DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�

		/* �֐� */

		/* �ϐ� */
};
