/* 2025.02.06 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"

/* ��{�X�J�C�X�t�B�A�N���X�̐錾 */

// ��{�X�J�C�X�t�B�A�N���X
class SkySqhereBasic : public SkySqhereBase
{
	public:
		SkySqhereBasic();				// �R���X�g���N�^
		virtual ~SkySqhereBasic();		// �f�X�g���N�^

		void Update() override;			// �X�V

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus* StageStatusList;	// �X�e�[�W��ԊǗ�

	protected:

};
