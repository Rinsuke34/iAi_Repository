/* 2025.02.14 �e�r�듹 �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_StageStatus.h"

/* �I�u�W�F�N�g */
#include "PlayerBulletDefine.h"
#include "EffectSelfDelete_PlayerFollow.h"

/* �萔 */
#include "PublicInclude.h"

/* �N�i�C�N���X�̐錾 */

// �N�i�C
class BulletPlayerKunai : public BulletBase
{
	public:
		BulletPlayerKunai();				// �R���X�g���N�^
		virtual ~BulletPlayerKunai();		// �f�X�g���N�^

		virtual void	Initialization()	override;	// ������
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��	

		VECTOR	GetKunaiTargetPosition()							{ return this->vecKunaiTargetPosition; }					// �N�i�C�̃^�[�Q�b�g���W���擾
		void	SetKunaiTargetPosition(VECTOR vecTargetPosition)	{ this->vecKunaiTargetPosition = vecTargetPosition; }		// �N�i�C�̃^�[�Q�b�g���W��ݒ�

	private:
		
	protected:
		VECTOR			vecKunaiTargetPosition;			// �^�[�Q�b�g���W
		VECTOR			vecKunaiMoveDirection;			// �N�i�C�̈ړ��������
		float			fKunaiTargetDistance;			// �N�i�C�̔��˒n�_����^�[�Q�b�g�܂ł̋���
		float			fKunaiMoveDistance;				// �N�i�C�̈ړ�����
		float			fKunaiAngleX;					// �N�i�C��X����]�p�x
		float			fKunaiAngleY;					// �N�i�C��Y����]�p�x
		int				iKunaiDeleteCount;				// �N�i�C�̍폜�J�E���g
		bool			bKunaiAttackFlg;				// �N�i�C�̍U���t���O

		/* �g�p����f�[�^���X�g */
		DataList_Input* InputList;						// ���͊Ǘ�
		DataList_Object* ObjectList;					// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus* PlayerStatusList;		// �v���C���[���
		DataList_StageStatus* StageStatusList;			// �X�e�[�W��ԊǗ�
		DataList_Effect* EffectList;					// �G�t�F�N�g���\�[�X�Ǘ�
};

