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

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�


	/*�֐�*/
	void MoveEnemy(); // �G���ړ������郁�\�b�h��ǉ�


	/*�ϐ�*/
	int iXdistance;			// X���̋���

	int iZdistance;			// Z���̋���

	float fSpeed;			// �ړ����x

	int iDetonationRange;	//�N���͈͓�

	int iLastTime;			//�N���^�C�}�[

protected:
};
