/* 2025.02.19 �e�r�듹 �t�@�C���쐬 */

#pragma once
#include "EffectSelfDelete.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "PlayerStatusDefine.h"

/* ���Ԍo�߂ō폜�����G�t�F�N�g�N���X�̐錾 */
// ���v���C���[�̃t���[���Ɏ����Ǐ]

// �G�t�F�N�g�N���X(�����폜/�v���C���[�t���[���Ǐ])
class EffectSelfDelete_PlayerFollow_Frame : public EffectSelfDelete
{
public:
	EffectSelfDelete_PlayerFollow_Frame(int iFrameHandle);		// �R���X�g���N�^
	virtual ~EffectSelfDelete_PlayerFollow_Frame() {};			// �f�X�g���N�^

	void	Update()	override;	// �X�V

private:
	/* �Ǐ]�Ώۂ̃v���C���[�N���X */
	CharacterBase* pCharacterPlayer;

	/* �ϐ� */
	int iFrameHandle;	// �t���[���n���h��
	int iModelHandle;	// ���f���n���h��
};
#pragma once
