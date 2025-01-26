/* 2025.01.27 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �ߐڍU��(��)�N���X�̐錾 */

// �ߐڍU��(��)
class BulletPlayerMeleeStrong : public BulletBase
{
	public:
		BulletPlayerMeleeStrong();				// �R���X�g���N�^
		virtual ~BulletPlayerMeleeStrong() {};	// �f�X�g���N�^

		virtual void	Update()			override;	// �X�V
		virtual void	CollisionDraw()		override;	// �����蔻��`��

		/* �ڐG���� */
		// �ȈՓI�Ȍ���(�ڐG���Ă��邩�ǂ���)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule)		override;	// ���� - �J�v�Z��
		bool	HitCheck(COLLISION_SQHERE	stSqhere)		override;	// ���� - ����
		bool	HitCheck(int iModelHandle, int iFrameIndex)	override;	// ���� - ���f��

		COLLISION_CAPSULE	stGetCollision_Capsule()	{ return this->stCollisionCapsule; };	// �R���W����(�J�v�Z��)���擾

		void	SetCollision_Capsule(COLLISION_CAPSULE stCollisionCapsule)	{ this->stCollisionCapsule = stCollisionCapsule; };		// �R���W����(�J�v�Z��)��ݒ�

	private:
		/* �ϐ� */
		COLLISION_CAPSULE	stCollisionCapsule;		// �R���W����(�J�v�Z��)

		int iDeleteCount;	// ���ǉ��̍폜�J�E���g
	protected:
};
