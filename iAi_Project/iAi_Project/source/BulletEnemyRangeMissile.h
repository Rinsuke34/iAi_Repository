/* 2025.01.30 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "EffectManualDelete.h"


/* �ߐڍU��(��)�N���X�̐錾 */

// �ߐڍU��(��)
class BulletEnemyRangeMissile : public BulletBase
{
public:
	BulletEnemyRangeMissile();				// �R���X�g���N�^
	virtual ~BulletEnemyRangeMissile();		// �f�X�g���N�^

	virtual void	Initialization()	override;	// ������
	virtual void	Update()			override;	// �X�V

private:
	/* �I�u�W�F�N�g(�G�t�F�N�g)�̃n���h�� */
	EffectManualDelete* eEffect;

	int iDeleteCount;	// ���ǉ��̍폜�J�E���g

protected:
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
	void BulletEnemyRangeMissileMove();	// �G�̒e�̈ړ�����
};
