/* 2025.01.30 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "EffectManualDelete.h"
#include "EnemyBulletDefine.h"
#include "PlayerStatusDefine.h"


/*�~�T�C���e�N���X�̐錾 */

// �~�T�C���e
class BulletEnemyRangeMissile : public BulletBase
{
public:
	BulletEnemyRangeMissile();				// �R���X�g���N�^
	virtual ~BulletEnemyRangeMissile();		// �f�X�g���N�^

	virtual void	Initialization()	override;	// ������
	virtual void	Update()			override;	// �X�V
	virtual void	CollisionDraw()		override;	// �����蔻��`��
	virtual void	Draw()				override;	// �`��	

private:

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;			// �v���C���[


	/* �I�u�W�F�N�g(�G�t�F�N�g)�̃n���h�� */
	EffectManualDelete* pEffect;//�~�T�C���e�̃G�t�F�N�g

	EffectManualDelete* pEffectExplosion;//�~�T�C���e���e�G�t�F�N�g

	EffectManualDelete* pEffectGuidance;//�~�T�C���U���G�t�F�N�g


	void BulletEnemyRangeMissileMove();	// �~�T�C���e�̈ړ�����
	void BulletEnemyRangeMissileExplosion();// �~�T�C���e�̔�������

	int iDurationCount;			// �e�̎����J�E���g

	int iBulletUPCount;			// �~�T�C���e�ł��グ�J�E���g

	int iBulletDownCount;		// �~�T�C���e�ł������J�E���g

	int iBulletGuidanceCount;	// �~�T�C���U���J�E���g


	int iEnemyMissileDurationCount;	//�~�T�C���e�̎����J�E���g
	int iTextureHandle;				// �e�N�X�`���n���h��

	bool bPredictedLandingFlg;		//���e�\���t���O
	bool bSaveFlg;					//�Z�[�u�t���O

	VECTOR vecHitPosition;			//�q�b�g�|�W�V����
	VECTOR vecModelPosition;		//���e���f���̍��W
protected:

	COLLISION_LINE		stVerticalCollision;			// ���������̃R���W����
	COLLISION_LINE		stFallCollision;			// ���������̃R���W����
};
