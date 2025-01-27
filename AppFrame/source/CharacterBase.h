/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ActorBase.h"

/* ���O��ԏȗ� */
using namespace Struct_Collision;

/* ���ׂẴL�����N�^�[�̃x�[�X�ƂȂ�N���X�̐錾 */

// �L�����N�^�[�x�[�X�N���X
class CharacterBase : public ActorBase
{
	public:
		CharacterBase();	// �R���X�g���N�^
		virtual ~CharacterBase() {};		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	BloomDraw()			override;		// �����`��
		virtual void	CollisionDraw()		override;		// �����蔻��`��
		virtual void	Draw()				override;		// �`��

		/* �ڐG���� */
		// �ȈՓI�Ȍ���(�ڐG���Ă��邩�ǂ���)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// �J�v�Z�� - �J�v�Z��
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// �J�v�Z�� - ����
		bool	HitCheck(int iModelHandle, int iFrameIndex);	// �J�v�Z�� - ���f��

		COLLISION_CAPSULE	stGetCollision_Capsule()	{ return this->stCollisionCapsule; };		// �R���W����(�J�v�Z��)���擾
		int					iGetInvincibilityTime()		{ return this->iInvincibilityTime; };		// ���G���Ԃ��擾

		void	SetCollision_Capsule(COLLISION_CAPSULE stCollisionCapsule)	{ this->stCollisionCapsule	= stCollisionCapsule; };	// �R���W����(�J�v�Z��)��ݒ�
		void	SetInvincibilityTime(int iInvincibilityTime)				{ this->iInvincibilityTime	= iInvincibilityTime; };	// ���G���Ԃ�ݒ�

	private:
	protected:
		/* �֐� */
		void	UpdataLightFrame();						// �����̐ݒ肳�ꂽ�t���[�����擾

		/* �ϐ� */
		COLLISION_CAPSULE		stCollisionCapsule;		// �R���W����(�J�v�Z��)
		int						iInvincibilityTime;		// ���G����
		std::vector<int>		aiLightFrameNo;			// �����t���[���ԍ�
};
