/* 2025.01.24 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_Effect.h"

/* �I�u�W�F�N�g */
#include "EffectManualDelete.h"

/* �ߐڍU��(��)�N���X�̐錾 */

// �ߐڍU��(��)
class BulletPlayerMeleeWeak : public BulletBase
{
	public:
		BulletPlayerMeleeWeak();				// �R���X�g���N�^
		virtual ~BulletPlayerMeleeWeak();		// �f�X�g���N�^

		virtual void	Initialization()	override;	// ������
		virtual void	Update()			override;	// �X�V

	private:
		/* �I�u�W�F�N�g(�G�t�F�N�g)�̃n���h�� */
		EffectManualDelete* pEffect;

		int iDeleteCount;	// ���ǉ��̍폜�J�E���g

	protected:
};
