/* 2025.02.05 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "EffectManualDelete.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "PlayerStatusDefine.h"

/* �蓮�ō폜�^�C�~���O��ݒ肷��G�t�F�N�g�N���X�̐錾 */
// ���v���C���[�Ɏ����Ǐ]

// �G�t�F�N�g�N���X(�蓮�폜/�v���C���[�Ǐ])
class EffectManualDelete_PlayerFollow : public EffectManualDelete
{
	public:
		EffectManualDelete_PlayerFollow(bool bCenterFollowFlg);		// �R���X�g���N�^
		virtual ~EffectManualDelete_PlayerFollow() {};				// �f�X�g���N�^

		void	Update() override;	// �X�V

	private:
		/* �Ǐ]�Ώۂ̃v���C���[�N���X */
		CharacterBase* pCharacterPlayer;

		/* �ϐ� */
		bool bCenterFollowFlg;		// �����ł͂Ȃ������ɒǏ]���邩�̃t���O
};
