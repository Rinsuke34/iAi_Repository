/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "EffectManualDelete.h"
#include "CharacterPlayer.h"
#include "EnemyBulletDefine.h"


/* �m�[�}���e�N���X�̐錾 */

// �m�[�}���e
class BulletEnemyRangeNormal : public BulletBase
{
public:
	BulletEnemyRangeNormal();				// �R���X�g���N�^
	virtual ~BulletEnemyRangeNormal();		// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

private:

	/* �G�t�F�N�g�E�g�p����f�[�^���X�g */
	DataList_Object* ObjectList;						// �I�u�W�F�N�g�Ǘ�
	EffectManualDelete* pEffect;						// �G�t�F�N�g	

	/* �֐� */
	void BulletEnemyRangeNormalMove();					// �m�[�}���e�̈ړ�����

	/* �ϐ� */
	int iDurationCount;									// �m�[�}���e�̎����J�E���g
	int iBulletCount;									// �m�[�}���e���˃J�E���g
	int iEnemyNormalDurationCount;						//�m�[�}���e�̎����J�E���g

protected:

};
