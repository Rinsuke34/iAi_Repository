/* 2025.01.24 ��򕗏� �t�@�C���쐬 */
/* 2025.02.20 �e�r�듹 �֐��E�ϐ��ǉ� */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_Effect.h"

/* �I�u�W�F�N�g */
#include "EffectManualDelete.h"
#include "PlayerBulletDefine.h"

/* �ߐڍU��(��)�N���X�̐錾 */

// �ߐڍU��(��)
class BulletPlayerMeleeWeak : public BulletBase
{
	public:
		BulletPlayerMeleeWeak();							// �R���X�g���N�^
		virtual ~BulletPlayerMeleeWeak();					// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		void			ArrengementPositionPlayerFront();	// ���W�ݒ�						/* 2025.02.20 �e�r�듹 �֐��ǉ� */

	private:
		/* �g�p����f�[�^���X�g */
		DataList_PlayerStatus* PlayerStatusList;			// �v���C���[���				/* 2025.02.20 �e�r�듹 �ϐ��ǉ� */

		/* �I�u�W�F�N�g(�G�t�F�N�g)�̃n���h�� */
		EffectManualDelete* pMeleeWeakEffect;				// �ߐڍU��(��)�G�t�F�N�g

		/* �Ǐ]�Ώۂ̃v���C���[�N���X */
		CharacterBase* pCharacterPlayer;													/* 2025.02.20 �e�r�듹 �ϐ��ǉ� */

		int iDeleteCount;	// ���ǉ��̍폜�J�E���g

	protected:
};
