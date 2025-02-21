/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

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
class ExplosionEnemy : public EnemyBasic
{
public:
	ExplosionEnemy();				// �R���X�g���N�^
	virtual ~ExplosionEnemy();		// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

private:
	/* �G�t�F�N�g */
	EffectManualDelete* pEffect;

	//�N���G�t�F�N�g
	EffectManualDelete* pEffectDetonation;

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�


	DataList_PlayerStatus* PlayerStatusList;	// �v���C���[���
	/*�֐�*/
	void MoveEnemy(); // �G���ړ������郁�\�b�h��ǉ�
	void Enemy_Gravity(); // �d�͏������\�b�h��ǉ�


	/*�ϐ�*/
	int iXdistance;			// X���̋���

	int iZdistance;			// Z���̋���

	float fSpeed;			// �ړ����x

	int iDetonationRange;	//�N���͈͓�

	bool bEffectGenerated;	// �N���\���G�t�F�N�g�����t���O

	float fGravity;				// �d��

protected:
	COLLISION_LINE		stVerticalCollision;			// ���������̃R���W����

	VECTOR				vecMove;				// �ړ���
};
