/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <vector>
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
		virtual void	Update()			override	{};	// �X�V
		virtual void	Draw();								// �`��
		virtual void	BloomDraw();						// �����`��

		/* �ڐG���� */
		// �ȈՓI�Ȍ���(�ڐG���Ă��邩�ǂ���)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// ���f�� - �J�v�Z��
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// ���f�� - ����
		bool	HitCheck(COLLISION_LINE		stLine);			// ���f�� - ����
		// �ڍׂȌ���(�ڐG�|���S�����A�ڐG�ʒu�Ȃ�)
		MV1_COLL_RESULT_POLY	HitCheck_Line(COLLISION_LINE	stLine);	// ���f�� - ����

		int		iGetModelHandle()		{ return this->iModelHandle; };			// ���f���n���h�����擾
		int		iGetCollisionFrameNo()	{ return this->iCollisionFrameNo; };	// �R���W�����̐ݒ肳�ꂽ���f���̃t���[���ԍ����擾
		int		iGetLightFrameNo()		{ return this->iLightFrameNo; };		// ���������̐ݒ肳�ꂽ���f���̃t���[���ԍ����擾
		VECTOR	vecGetRotate()			{ return this->vecRotate; };			// ��]�ʂ��擾
		VECTOR	vecGetScale()			{ return this->vecScale; };				// �g�嗦���擾

		void	SetModelHandle(int iModelHandle)			{ this->iModelHandle		= iModelHandle; };			// ���f���n���h����ݒ�
		void	SetCollisionFrameNo(int iCollisionFrameNo)	{ this->iCollisionFrameNo	= iCollisionFrameNo; };		// �R���W�����̐ݒ肳�ꂽ���f���̃t���[���ԍ���ݒ�
		void	SetLightFrameNo(int iLightFrameNo)			{ this->iLightFrameNo		= iLightFrameNo; };			// ���������̐ݒ肳�ꂽ���f���̃t���[���ԍ���ݒ�
		void	SetRotate(VECTOR vecRotate)					{ this->vecRotate			= vecRotate; };				// ��]�ʂ�ݒ�
		void	SetScale(VECTOR vecScale)					{ this->vecScale			= vecScale; };				// �g�嗦��ݒ�

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		int		iModelHandle;		// ���f���n���h��
		int		iCollisionFrameNo;	// �R���W�����̐ݒ肳�ꂽ���f���̃t���[���ԍ�
		int		iLightFrameNo;		// ���������̐ݒ肳�ꂽ���f���̃t���[���ԍ�
		VECTOR	vecRotate;			// ��]��(x,y,z�������ꂼ��̃��W�A��)
		VECTOR	vecScale;			// �g�嗦(x,y,z�������ꂼ��̊g��{��)
};
