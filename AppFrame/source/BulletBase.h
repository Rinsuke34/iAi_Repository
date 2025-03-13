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

		virtual void	CollisionDraw();					// �����蔻��`��

		/* �ڐG���� */
		// �ȈՓI�Ȍ���(�ڐG���Ă��邩�ǂ���)
		virtual bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// ���� - �J�v�Z��
		virtual bool	HitCheck(COLLISION_SQHERE	stSqhere);			// ���� - ����
		virtual bool	HitCheck(int iModelHandle, int iFrameIndex);	// ���� - ���f��

		COLLISION_SQHERE	stGetCollision_Sqhere() { return this->stCollisionSqhere; };		// �R���W����(����)���擾
		VECTOR				vecGetMoveDirection()	{ return this->vecDirection; };				// �������擾
		float				fGetMoveSpeed()			{ return this->fMoveSpeed; };				// �ړ����x���擾
		int					iGetTargetType()		{ return this->iTargetObjectType; };		// �ڐG����Ώۂ̃^�C�v���擾
		bool				bGetParryFlg()			{ return this->bParryFlg; };				// �p���B�t���O(���˂ł��邩)���擾

		void	SetCollision_Sqhere(COLLISION_SQHERE stCollisionSqhere)		{ this->stCollisionSqhere	= stCollisionSqhere; };		// �R���W����(����)��ݒ�
		void	SetDirection(VECTOR vecDirection)							{ this->vecDirection		= vecDirection; };			// ������ݒ�
		void	SetMoveSpeed(float fMoveSpeed)								{ this->fMoveSpeed			= fMoveSpeed; };			// �ړ����x��ݒ�
		void	SetTargetType(int iTargetType)								{ this->iTargetObjectType	= iTargetType; };			// �ڐG����Ώۂ̃^�C�v��ݒ�
		void	SetParryFlg(bool bParryFlg)									{ this->bParryFlg			= bParryFlg; };				// �p���B�t���O(���˂ł��邩)��ݒ�

	protected:
		/* �ϐ� */
		COLLISION_SQHERE			stCollisionSqhere;		// �R���W����(����)
		VECTOR						vecDirection;			// ����
		float						fMoveSpeed;				// �ړ����x
		int							iTargetObjectType;		// �ڐG����Ώۂ̃^�C�v
		bool						bParryFlg;				// �p���B�t���O(���˂ł��邩)
		int							iBulletType;			// �e�ۂ̎��(���ˉ\�ł��邩)
};
