/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ObjectBase.h"

/* ���O��ԏȗ� */
using namespace Struct_Collision;

/* ���ׂẴv���b�g�t�H�[���̃x�[�X�ƂȂ�N���X�̐錾 */

// �v���b�g�t�H�[���x�[�X�N���X
class PlatformBase : public ObjectBase
{
	public:
		PlatformBase();				// �R���X�g���N�^
		virtual ~PlatformBase();	// �f�X�g���N�^

		virtual void	Draw() {};	// �`��

		/* �ڐG���� */
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// ���f�� - �J�v�Z��
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// ���f�� - ����

		int		iGetModelHandle() { return this->iModelHandle; };		// ���f���n���h�����擾

		void	SetModelHandle(int iModelHandle) { this->iModelHandle = iModelHandle; };	// ���f���n���h����ݒ�

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		int		iModelHandle;		// ���f���n���h��
		int		iCollisionFrameNo;	// �R���W�����̐ݒ肳�ꂽ���f���̃t���[���ԍ�	
		VECTOR	vecRotate;		// ��]
		VECTOR	vecScale;		// �g��
};
