/* 2025.02.05 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "EffectSelfDelete.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "PlayerStatusDefine.h"

/* ���Ԍo�߂ō폜�����G�t�F�N�g�N���X�̐錾 */
// ���v���C���[�Ɏ����Ǐ]

// �G�t�F�N�g�N���X(�����폜/�v���C���[�Ǐ])
class EffectSelfDelete_PlayerFollow : public EffectSelfDelete
{
	public:
		EffectSelfDelete_PlayerFollow(bool bCenterFollowFlg);	// �R���X�g���N�^
		virtual ~EffectSelfDelete_PlayerFollow() {};			// �f�X�g���N�^

		void	Update()			override;	// �X�V

	private:
		/* �Ǐ]�Ώۂ̃v���C���[�N���X */
		CharacterBase* pCharacterPlayer;

		/* �ϐ� */
		bool bCenterFollowFlg;		// �����ł͂Ȃ������ɒǏ]���邩�̃t���O
};
