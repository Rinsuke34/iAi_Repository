/* 2025.01.27 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"
#include "EnemyDefine.h"

/* �f�[�^���X�g */
#include "DataList_Effect.h"
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_GameResource.h"
#include "DataList_StageStatus.h"
#include "DataList_Option.h"

/* �G�t�F�N�g */
#include "EffectSelfDelete.h"

/* �I�u�W�F�N�g */
#include "EffectItem_Blood.h"

/* ��{�G�l�~�[�N���X�̐錾 */

// ��{�G�l�~�[�N���X
class Enemy_Basic : public EnemyBase
{
	public:
		Enemy_Basic();				// �R���X�g���N�^
		virtual ~Enemy_Basic() {};	// �f�X�g���N�^

		virtual void	BloomDraw()			override;	// �����`��
		virtual void	CollisionDraw()		override;	// �����蔻��`��
		virtual void	Draw()				override;	// �`��
		virtual void	Reset();						// ���Z�b�g����

		void	Defeat();			// �G���j���̏���
		void	LoadCoreFrameNo();	// �R�A�t���[���ԍ��擾

		/* �f�[�^�擾 */
		int		iGetPlayerLockOnType()	{ return this->iPlayerLockOnType; }		// �v���C���[���_�ł̃��b�N�I����Ԃ��擾
		int		iGetCoreFrameNo()		{ return this->iCoreFrameNo; }			// �R�A�ƂȂ�t���[���ԍ����擾

		/* �f�[�^�ݒ� */
		void	SetPlayerLockOnType(int iPlayerLockOnType)	{ this->iPlayerLockOnType	= iPlayerLockOnType; }	// �v���C���[���_�ł̃��b�N�I����Ԃ�ݒ�
		void	SetCoreFrameNo(int iCoreFrameNo)			{ this->iCoreFrameNo		= iCoreFrameNo; }		// �R�A�ƂȂ�t���[���ԍ���ݒ�

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus*	StageStatusList;	// �X�e�[�W���
		DataList_Option*		OptionList;			// �I�v�V����

		/* �ϐ� */
		int		iPlayerLockOnType;	// �v���C���[���_�ł̃��b�N�I�����
		int		iCoreFrameNo;		// �R�A�ƂȂ�t���[���ԍ�
};
