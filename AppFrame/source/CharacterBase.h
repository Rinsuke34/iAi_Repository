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

		virtual void	Update() {};		// �X�V
		virtual void	Draw() {};			// �`��

		/* �ڐG���� */
		// �ȈՓI�Ȍ���(�ڐG���Ă��邩�ǂ���)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// �J�v�Z�� - �J�v�Z��
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// �J�v�Z�� - ����
		bool	HitCheck(int iModelHandle, int iFrameIndex);	// �J�v�Z�� - ���f��

		COLLISION_CAPSULE	stGetCollision_Capsule()	{ return this->stCollisionCapsule; };		// �R���W����(�J�v�Z��)���擾
		VECTOR				GetDirection()				{ return this->vecDirection; };				// �������擾

		void	SetCollision_Capsule(COLLISION_CAPSULE stCollisionCapsule)	{ this->stCollisionCapsule	= stCollisionCapsule; };	// �R���W����(�J�v�Z��)��ݒ�
		void	SetDirection(VECTOR vecDirection)							{ this->vecDirection		= vecDirection; };			// ������ݒ�

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		COLLISION_CAPSULE		stCollisionCapsule;		// �R���W����(�J�v�Z��)
		VECTOR vecDirection;							// ����
};
