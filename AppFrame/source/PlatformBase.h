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

		virtual void	Initialization()	override;		// ������
		virtual void	Draw();								// �`��
		virtual void	BloomDraw();						// �����`��
		virtual void	CollisionDraw();					// �����蔻��`��

		int		iGetModelHandle()		{ return this->iModelHandle; };			// ���f���n���h�����擾
		VECTOR	vecGetPlatformMove()	{ return this->vecPlatformMove; };		// �v���b�g�t�H�[���̈ړ��ʂ��擾

		void	SetModelHandle(int iModelHandle)			{ this->iModelHandle		= iModelHandle; };			// ���f���n���h����ݒ�
		void	SetPlatformMove(VECTOR vecPlatformMove)		{ this->vecPlatformMove		= vecPlatformMove; };		// �v���b�g�t�H�[���̈ړ��ʂ�ݒ�

		/* �ڐG���� */
		// �ȈՓI�Ȍ���(�ڐG���Ă��邩�ǂ���)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// ���f�� - �J�v�Z��
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// ���f�� - ����
		bool	HitCheck(COLLISION_LINE		stLine);			// ���f�� - ����
		// �ڍׂȌ���(�ڐG�|���S�����A�ڐG�ʒu�Ȃ�)
		MV1_COLL_RESULT_POLY		HitCheck_Line(COLLISION_LINE		stLine);	// ���f�� - ����
		MV1_COLL_RESULT_POLY_DIM	HitCheck_Capsule(COLLISION_CAPSULE	stCapsule);	// ���f�� - �J�v�Z��

	private:
	protected:
		/* �֐� */
		void	UpdateCollisionFrame();						// �R���W�����̐ݒ肳�ꂽ�t���[���̐ݒ�
		void	UpdataLightFrame();							// �����̐ݒ肳�ꂽ�t���[�����擾
		void	DrawFrameCollisionSet(bool bCollisionDraw);	// �R���W�����t���[����`�ʂ����Ԃɂ���

		/* �ϐ� */
		int						iModelHandle;			// ���f���n���h��
		std::vector<int>		aiLightFrameNo;			// �����t���[���ԍ�
		int						iCollisionFrameNo;		// �R���W�����t���[���ԍ�(�����f���ɂ�1����)
		VECTOR					vecCenterPosition;		// �I�u�W�F�N�g�̒��S���W(�R���W���������y�ʉ��p)
		float					fRoughRadius;			// �I�u�W�F�N�g�̑�܂��Ȕ��a(�R���W���������y�ʉ��p)
		VECTOR					vecPlatformMove;		// �v���b�g�t�H�[���̈ړ���
};
