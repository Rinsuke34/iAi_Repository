/* 2025.03.10 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"
#include "GimmickDefine.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"

/* �ړ����N���X�̐錾 */

// �ړ����N���X����
class Gimmick_MoveFloor : public PlatformBase
{
	public:
		Gimmick_MoveFloor();				// �R���X�g���N�^
		virtual ~Gimmick_MoveFloor() {};	// �f�X�g���N�^

		virtual void	Update()			override;		// �X�V

		void	SetupMoveDirection(bool bVerticalDirection, int iMoveDistance);		// �ړ�������ݒ�

	private:
		/* �ϐ� */
		VECTOR	vecMovePos;			// �ړ����̈ړ�����W
		bool	bTargetMove;		// �ړ����̈ړ�����W�Ɍ������Ă��邩(true:�ړ�����W�� / false:�������W��)
};
