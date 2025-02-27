/* 2024.01.28 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "EnemyBasic.h"
#include "EnemyDefine.h"
#include "EffectManualDelete.h"

/* �e�X�g�p�G�N���X */

// �G�l�~�[�x�[�X�N���X
class EscapeEnemy : public EnemyBasic
{
	public:
		EscapeEnemy();				// �R���X�g���N�^
		virtual ~EscapeEnemy();		// �f�X�g���N�^
	
		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
	virtual void	CollisionDraw()		override;	// �����蔻��`��
	private:
	/* �G�t�F�N�g */
	EffectManualDelete* pEffect;

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�

	/* �֐� */
	void MoveEnemy(); // �G���ړ������郁�\�b�h��ǉ�
	void Enemy_Gravity(); // �d�͏������\�b�h��ǉ�

	/* �ϐ� */
	int iXescapedistance;			// X���̋���

	int iZescapedistance;			// Z���̋���
	int iEscapespeed;			// �ړ����x
	float fGravity;				// �d��


	VECTOR vecEscapeEffectPos;	// �����G�t�F�N�g�̍��W
protected:
	COLLISION_LINE		stVerticalCollision;			// ���������̃R���W����

	VECTOR				vecMove;				// �ړ���

};
