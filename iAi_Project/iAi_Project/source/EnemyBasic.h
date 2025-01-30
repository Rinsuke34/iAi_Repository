/* 2025.01.27 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_Score.h"
#include "DataList_Effect.h"

/* �G�t�F�N�g */
#include "EffectSelfDelete.h"

/* ��{�G�l�~�[�N���X�̐錾 */

// ��{�G�l�~�[�N���X
class EnemyBasic : public EnemyBase
{
	public:
		EnemyBasic();				// �R���X�g���N�^
		virtual ~EnemyBasic();		// �f�X�g���N�^

		void	LoadCoreFrameNo();	// �R�A�t���[���ԍ��擾

		int		iGetPlayerLockOnType()	{ return this->iPlayerLockOnType; }		// �v���C���[���_�ł̃��b�N�I����Ԃ��擾
		int		iGetCoreFrameNo()		{ return this->iCoreFrameNo; }			// �R�A�ƂȂ�t���[���ԍ����擾

		void	SetPlayerLockOnType(int iPlayerLockOnType)	{ this->iPlayerLockOnType	= iPlayerLockOnType; }	// �v���C���[���_�ł̃��b�N�I����Ԃ�ݒ�
		void	SetCoreFrameNo(int iCoreFrameNo)			{ this->iCoreFrameNo		= iCoreFrameNo; }		// �R�A�ƂȂ�t���[���ԍ���ݒ�

	private:
	protected:
		/* �ϐ� */
		int		iPlayerLockOnType;	// �v���C���[���_�ł̃��b�N�I�����
		int		iCoreFrameNo;		// �R�A�ƂȂ�t���[���ԍ�
};
