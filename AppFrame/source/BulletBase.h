/* 2024.12.18 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ActorBase.h"
#include "AppStructDefine.h"

/* ���O��ԏȗ� */
using namespace Struct_Collision;

/* ���ׂĂ̒e�ۂ̃x�[�X�ƂȂ�N���X�̐錾 */

// �e�ۃx�[�X�N���X
class BulletBase : public ActorBase
{
	public:
		BulletBase();				// �R���X�g���N�^
		virtual ~BulletBase() {};	// �f�X�g���N�^

		virtual void	Update() {};		// �X�V
		virtual void	Draw() {};			// �`��

		/* �ڐG���� */
		// �ȈՓI�Ȍ���(�ڐG���Ă��邩�ǂ���)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// ���� - �J�v�Z��
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// ���� - ����
		bool	HitCheck(int iModelHandle, int iFrameIndex);	// ���� - ���f��

		COLLISION_SQHERE	stGetCollision_Sqhere() { return this->stCollisionSqhere; };		// �R���W����(����)���擾
		VECTOR				GetMoveDirection()		{ return this->vecMoveDirection; };			// �ړ��������擾

		void	SetCollision_Capsule(COLLISION_SQHERE stCollisionSqhere)	{ this->stCollisionSqhere	= stCollisionSqhere; };		// �R���W����(����)��ݒ�
		void	SetMoveDirection(VECTOR vecMoveDirection)					{ this->vecMoveDirection	= vecMoveDirection; };		// �ړ�������ݒ�

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		COLLISION_SQHERE			stCollisionSqhere;		// �R���W����(����)
		VECTOR vecMoveDirection;							// �ړ�����
};
