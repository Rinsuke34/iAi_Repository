/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "EffectManualDelete.h"
#include "CharacterPlayer.h"
#include "EnemyBulletDefine.h"

/* �r�[���N���X�̒�` */

// �r�[��
class BulletEnemyRangeBeam : public BulletBase
{
public:
	BulletEnemyRangeBeam();				// �R���X�g���N�^
	virtual ~BulletEnemyRangeBeam();		// �f�X�g���N�^

	virtual void	Initialization()	override;	// ������
	virtual void	Update()			override;	// �X�V
	virtual void	CollisionDraw()		override;	// �����蔻��`��

private:
	/* �I�u�W�F�N�g(�G�t�F�N�g)�̃n���h�� */
	EffectManualDelete* pEffect;

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�

	/* �����蔻�� */
	COLLISION_CAPSULE stCollisionCapsule;	// �J�v�Z���^�̓����蔻��

	void BulletEnemyRangeBeamMove();	// �r�[���̈ړ�����

	int iChargeCount;		// �r�[���̃`���[�W�J�E���g	

	int iBulletCount;		// �r�[�����˃J�E���g

	int iEnemyBeamDurationCount;		//�r�[���̎����J�E���g

	VECTOR vecEnemyPosition; // �G�l�~�[�̈ʒu��ێ����郁���o�ϐ���ǉ�

	VECTOR vecPlayerDirection; // �v���C���[�̕�����ێ����郁���o�ϐ���ǉ�

protected:

};
