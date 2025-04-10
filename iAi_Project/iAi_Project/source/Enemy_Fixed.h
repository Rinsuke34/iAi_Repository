/* 2024.01.29 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "Enemy_Basic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeNormal.h"
#include "PlayerStatusDefine.h"

/* �Œ�C��G�l�~�[�y�䕔���N���X */

// �G�l�~�[�t�B�b�N�X�N���X
class Enemy_Fixed : public Enemy_Basic
{
public:
	Enemy_Fixed();				// �R���X�g���N�^
	virtual ~Enemy_Fixed();		// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

private:


	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;						// �I�u�W�F�N�g�Ǘ�

	//�֐�
	void	MoveEnemy();								// �G���ړ������郁�\�b�h��ǉ�

	//�ϐ�
	int		iModelturretHandle;							// ���f���n���h��
	int		iModelscaffoldHandle;						// ���f���n���h��




protected:


};
