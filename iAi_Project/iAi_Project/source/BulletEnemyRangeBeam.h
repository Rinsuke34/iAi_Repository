/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "EffectManualDelete.h"
#include "CharacterPlayer.h"
#include "EnemyBulletDefine.h"


/* �r�[���N���X�̐錾 */

// �r�[��
class BulletEnemyRangeBeam : public BulletBase
{
public:
	BulletEnemyRangeBeam();				// �R���X�g���N�^
	virtual ~BulletEnemyRangeBeam();		// �f�X�g���N�^

	virtual void	Initialization()	override;	// ������
	virtual void	Update()			override;	// �X�V

private:
	/* �I�u�W�F�N�g(�G�t�F�N�g)�̃n���h�� */
	EffectManualDelete* pEffect;

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�


	void BulletEnemyRangeBeamMove();	// �r�[���̈ړ�����

	int iDurationCount;	// �r�[���̎����J�E���g

	int iBulletCount;		// �r�[�����˃J�E���g


	int iEnemyBeamDurationCount;		//�r�[���̎����J�E���g
protected:

};
