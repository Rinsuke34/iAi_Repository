/* 2024.01.30 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "Enemy_Basic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeMissile.h"
#include "PlayerStatusDefine.h"

/* �e�X�g�p�G�N���X */

// �G�l�~�[�x�[�X�N���X
class Enemy_Missile : public Enemy_Basic
{
public:
	Enemy_Missile();				// �R���X�g���N�^
	virtual ~Enemy_Missile();		// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

private:

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;			// �v���C���[
	BulletEnemyRangeMissile* pBulletRangeMissile;		// �~�T�C���e
	EffectManualDelete* pEffectHit;						//�q�b�g�G�t�F�N�g
	EffectManualDelete* pEffectWarning;					//�x���G�t�F�N�g

	//�֐�
	void	MoveEnemy();					// �G���ړ������郁�\�b�h��ǉ�
	void	Player_Range_Missile_Shot();				// �~�T�C���e�U��
	void	Enemy_Model_Animation();					// �G�l�~�[���f���A�j���[�V����

	//�ϐ�
	int		iFiringCount;	// ���˃J�E���g
	bool	bHitEffectGenerated;						// �q�b�g�G�t�F�N�g�����t���O
	bool	bDirectionFlg;								// �����Œ�t���O
	bool	bShotFlg;									// �V���b�g�t���O
	bool	bWarningEffectFlg;							// �x���G�t�F�N�g�t���O


	//���[�V�����֘A�ϐ�
	int		iMissileAttackAttachIndex;					// �~�T�C���U�����[�V�����A�^�b�`�C���f�b�N�X
	int		iMissileAttackNowAttachIndex;				// �~�T�C���U�������[�V�����A�^�b�`�C���f�b�N�X
	int		iMissileAttackEndAttachIndex;				// �~�T�C���U���I�����[�V�����A�^�b�`�C���f�b�N�X
	int		iMissileAttackEndLoopAttachIndex;			// �~�T�C���U���I�����[�v���[�V�����A�^�b�`�C���f�b�N�X
	int		iDieAttachIndex;							// ���S���[�V�����A�^�b�`�C���f�b�N�X
	bool	bMissileAttackMotionFlg;					// �~�T�C���U�����[�V�����t���O
	bool	bMissileAttackNowMotionFlg;					// �~�T�C���U�������[�V�����t���O
	bool	bMissileAttackEndMotionFlg;					// �~�T�C���U���I�����[�V�����t���O
	bool	bMissileAttackEndLoopMotionFlg;				// �~�T�C���U���I�����[�v���[�V�����t���O
	float	fMissileAttackTotalTime;					// �~�T�C���U�����[�V�����̑�����
	float	fMissileAttackNowTotalTime;					// �~�T�C���U�������[�V�����̑�����
	float	fMissileAttackEndTotalTime;					// �~�T�C���U���I�����[�V�����̑�����
	float	fMissileAttackEndLoopTotalTime;				// �~�T�C���U���I�����[�v���[�V�����̑�����
	float	fDieTotalTime;								// ���S���[�V�����̑�����
	float	fMissileAttackPlayTime;						// �~�T�C���U���Đ�����
	float	fMissileAttackNowPlayTime;					// �~�T�C���U�����Đ�����
	float	fMissileAttackEndPlayTime;					// �~�T�C���U���I���Đ�����
	float	fMissileAttackEndLoopPlayTime;				// �~�T�C���U���I�����[�v�Đ�����
	float	fDiePlayTime;								// ���S�Đ�����

protected:

};
