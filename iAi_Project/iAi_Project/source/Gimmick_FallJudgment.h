/* 2025.03.04 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "GimmickDefine.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* ��������N���X�̐錾 */

// ��������N���X
class Gimmick_FallJudgment : public PlatformBase
{
	public:
		Gimmick_FallJudgment();				// �R���X�g���N�^
		virtual ~Gimmick_FallJudgment() {};	// �f�X�g���N�^

		virtual void	Update()			override;	// �X�V

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�
};
