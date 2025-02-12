/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "CharacterBase.h"

/* ���ׂĂ̎��̂̂Ȃ��A�C�e���̃x�[�X�ƂȂ�N���X�̐錾 */

// ���̂Ȃ��A�C�e���N���X
class EffectItemBase : public CharacterBase
{
	public:
		EffectItemBase();				// �R���X�g���N�^
		virtual ~EffectItemBase() {};	// �f�X�g���N�^

		virtual void	Initialization()	override {};	// ������
		virtual void	BloomDraw()			override {};	// �����`��
		virtual void	CollisionDraw()		override {};	// �����蔻��`��
		virtual void	Draw()				override {};	// �`��

		/* �ڐG���� */
		// ���g�p���Ȃ��̂ł��ׂ�false��Ԃ�
		bool	HitCheck(COLLISION_CAPSULE	stCapsule)		{ return false; };	// �J�v�Z�� - �J�v�Z��
		bool	HitCheck(COLLISION_SQHERE	stSqhere)		{ return false; };	// �J�v�Z�� - ����
		bool	HitCheck(int iModelHandle, int iFrameIndex)	{ return false; };	// �J�v�Z�� - ���f��

	private:
	protected:

};
