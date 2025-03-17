/* 2025.03.16 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "GimmickDefine.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_Image.h"

/* ���ԃ|�C���g�N���X�̐錾 */

// ���ԃ|�C���g�N���X
class Gimmick_CheckPoint : public PlatformBase
{
	public:
		Gimmick_CheckPoint();					// �R���X�g���N�^
		virtual ~Gimmick_CheckPoint()	{};		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		virtual void	Reset()				override;		// ���Z�b�g
		virtual void	BloomDraw()			override;		// �����`��
		virtual void	CollisionDraw()		override;		// �����蔻��`��

		/* �f�[�^�ݒ� */
		void SetActiveFlg(bool bActiveFlg)					{ this->bActiveFlg			= bActiveFlg; };		// �A�N�e�B�u�t���O��ݒ�
		void SetStartPositionFlg(bool bStartPositionFlg)	{ this->bStartPositionFlg	= bStartPositionFlg; };	// �X�^�[�g�n�_�t���O��ݒ�

		/* �f�[�^�擾 */
		bool bGetActiveFlg()				{ return this->bActiveFlg; };			// �A�N�e�B�u�t���O���擾
		bool bGetStartPositionFlg()			{ return this->bStartPositionFlg; };	// �X�^�[�g�n�_�t���O���擾

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Object* ObjectList;	// �I�u�W�F�N�g�Ǘ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_NormalRight;			// �ʏ펞(��A�N�e�B�u��)�̔����F
		int* piGrHandle_ActiveRight;			// �A�N�e�B�u���̔����F

		/* �ϐ� */
		bool				bActiveFlg;			// �A�N�e�B�u�t���O(�L���Ȃ�`�F�b�N�|�C���g�Ƃ��ċ@�\)
		bool				bStartPositionFlg;	// �X�^�[�g�n�_�t���O(�L���Ȃ�X�^�[�g�n�_�Ƃ��ċ@�\)
		COLLISION_SQHERE	stCollisionSqhere;	// �����蔻��(����)
};