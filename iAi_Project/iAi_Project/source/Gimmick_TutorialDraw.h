/* 2025.03.27 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "GimmickDefine.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* �V�[�� */
#include "SceneUi_Tutorial.h"

/* �`���[�g���A���`�ʒn�_�N���X�̐錾 */

// �`���[�g���A���`�ʒn�_�N���X
class Gimmick_TutorialDraw : public PlatformBase
{
	public:
		Gimmick_TutorialDraw();					// �R���X�g���N�^
		virtual ~Gimmick_TutorialDraw() {};		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		virtual void	Draw()				override {};	// �`��
		virtual void	BloomDraw()			override {};	// �����`��
		virtual void	CollisionDraw()		override;		// �����蔻��`��

		/* �f�[�^�ݒ� */
		void SetDrawTutorialNo(int iDrawTutorialNo)	{ this->iDrawTutorialNo	=	iDrawTutorialNo; };		// �`�ʂ���`���[�g���A���ԍ���ݒ�

		/* �f�[�^�擾 */
		int iGetDrawTutorialNo()					{ return this->iDrawTutorialNo; };					// �`�ʂ���`���[�g���A���ԍ����擾

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Object* ObjectList;	// �I�u�W�F�N�g�Ǘ�

		/* �ϐ� */
		int					iDrawTutorialNo;	// �`�ʂ���`���[�g���A���ԍ�
		COLLISION_SQHERE	stCollisionSqhere;	// �����蔻��(����)
};
