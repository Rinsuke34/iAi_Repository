/* 2025.01.22 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "PlatformBase.h"

/* ���O��ԏȗ� */
using namespace Struct_Collision;

/* �v���b�g�t�H�[���R���W�����̃x�[�X�ƂȂ�N���X�̐錾 */
// ���f�U�C�i�[�̕��S�΍�ɃR���W�����p�ƕ`�ʗp�Ń��f���𕪂���

// �v���b�g�t�H�[���R���W�����N���X
class CollisionBase : public PlatformBase
{
	public:
		CollisionBase();				// �R���X�g���N�^
		virtual ~CollisionBase() {};	// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	CollisionDraw();					// �����蔻��`��

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
		void	UpdateCollisionFrame();					// �R���W�����̐ݒ肳�ꂽ�t���[���̐ݒ�

		/* �ϐ� */
		int						iCollisionFrameNo;		// �R���W�����t���[���ԍ�(�����f���ɂ�1����)
};
