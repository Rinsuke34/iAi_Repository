/* 2024.03.17 �ΐ�q�� �t�@�C���쐬 */

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
#include "BulletEnemyRangeMissile.h"
/* �e�X�g�p�G�N���X */

// �G�l�~�[�x�[�X�N���X
class Enemy_Fixed_Turret : public Enemy_Basic
{
public:
	Enemy_Fixed_Turret();				// �R���X�g���N�^
	virtual ~Enemy_Fixed_Turret();		// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V
	virtual void	Draw()				override;		// �`��

private:

	EffectManualDelete* pEffectWarning;					//�x���G�t�F�N�g

	BulletEnemyRangeNormal* pBulletRangeNormal;			// �m�[�}���e
	BulletEnemyRangeMissile* pBulletRangeMissile;		// �~�T�C���e

	EffectManualDelete* pEffectHit;						//�q�b�g�G�t�F�N�g

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;			// �v���C���[

	VECTOR vecEffectPos; // �G�t�F�N�g�̍��W

	//�֐�
	void	MoveEnemy();					// �G���ړ������郁�\�b�h��ǉ�

	//�ϐ�
	int		iFiringCount;	// ���˃J�E���g
	int		iGuidanceCount;	// �U���J�E���g
	int		iModelturretHandle;	// ���f���n���h��
	int		iModelscaffoldHandle;	// ���f���n���h��
	int		iMaintainCount;	// �ێ��J�E���g
	int		iEffectWaitCount;	// �G�t�F�N�g�ҋ@�J�E���g

	float fTargetAngle;	// �^�[�Q�b�g�̊p�x
	float fCurrentAngle;	// ���݂̊p�x
	float fAngleDifference;	// �p�x�̍�

	bool	bEffectGenerated;							// �x���G�t�F�N�g�����t���O
	bool	bHitEffectGenerated;						// �q�b�g�G�t�F�N�g�����t���O
	bool	bDirectionFlg;								// �����Œ�t���O
	bool	bWarningEffectFlg;							// �x���G�t�F�N�g�t���O
	bool	bShotFlg;									// �V���b�g�t���O
	bool	bUpFlg;										// ��t���O
	bool	bDownFlg;									// ���t���O
	bool	bMissile;									// �~�T�C���t���O
	bool bTestFlg;									// �e�X�g�t���O
	bool bTestFlg2;									// �e�X�g�t���O2
	bool bTestFlg3;									// �e�X�g�t���O3




protected:


};
