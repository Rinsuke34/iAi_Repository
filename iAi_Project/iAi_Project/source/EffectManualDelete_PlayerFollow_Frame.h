/* 2025.02.19 �e�r�듹 �t�@�C���쐬 */

#pragma once
#include "EffectManualDelete.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* �蓮�ō폜�^�C�~���O��ݒ肷��G�t�F�N�g�N���X�̐錾 */
// ���v���C���[���f���̃t���[���Ɏ����Ǐ]

// �G�t�F�N�g�N���X(�蓮�폜/�v���C���[�Ǐ])
class EffectManualDelete_PlayerFollow_Frame : public EffectManualDelete
{
public:
	EffectManualDelete_PlayerFollow_Frame(int iFrameHandle);		// �R���X�g���N�^
	virtual ~EffectManualDelete_PlayerFollow_Frame() {};			// �f�X�g���N�^

	void	Update() override;	// �X�V

private:
	/* �Ǐ]�Ώۂ̃v���C���[�N���X */
	CharacterBase* pCharacterPlayer;

	/* �ϐ� */
	int iFrameHandle;	// �t���[���n���h��
	int iModelHandle;	// ���f���n���h��
}; 
