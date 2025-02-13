/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "EffectItem_BloodDefine.h"

/* �V�[�� */
#include "DataList_Object.h"
#include "DataList_GameResource.h"

/* �z�Q�Ƒ΍�(��قǑ΍�͎��{) */
class DataList_Object;

/* �u���b�h(�Q�[�����ʉ�)�N���X�̐錾 */
// �� �����ʓ����Ǘ�����̂ł͂Ȃ��A��ɉ��o�Ŏg�p����

// �u���b�h�N���X
class EffectItem_Blood : public EffectItemBase
{
	public:
		EffectItem_Blood();				// �R���X�g���N�^
		virtual ~EffectItem_Blood();	// �f�X�g���N�^

		virtual void	Update()		override;	// �X�V
		virtual void	Draw()			override;	// �`��

		/* �f�[�^�ݒ� */
		void	SetMoveDirection(VECTOR vecMoveDirection) { this->vecMoveDirection = vecMoveDirection; }	// �ړ�������ݒ�

	private:
		/* �f�[�^���X�g */
		DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�

		/* �֐� */

		/* �ϐ� */
		VECTOR	vecMoveDirection;		// �ړ�����
		int		iMoveCount;				// �ړ��J�E���g
		int		iMoveFaze;				// �ړ��t�F�[�Y
};

