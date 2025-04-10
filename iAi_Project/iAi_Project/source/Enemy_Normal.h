/* 2024.01.29 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* �I�u�W�F�N�g */
#include "Enemy_Basic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeNormal.h"
#include "PlayerStatusDefine.h"

/* �n��m�[�}���G�l�~�[�N���X */

// �G�l�~�[�m�[�}���N���X
class Enemy_Normal : public Enemy_Basic
{
public:
	Enemy_Normal();				// �R���X�g���N�^
	virtual ~Enemy_Normal();		// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

private:

	/* �G�t�F�N�g�E�g�p����I�u�W�F�N�g���X�g */
	DataList_Object* ObjectList;						// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;								// �v���C���[
	EffectManualDelete* pEffectWarning;					//�x���G�t�F�N�g
	BulletEnemyRangeNormal* pBulletRangeNormal;			// �m�[�}���e
	EffectManualDelete* pEffectHit;						//�q�b�g�G�t�F�N�g

	//�֐�
	void	MoveEnemy();								// �G���ړ������郁�\�b�h��ǉ�
	void	Player_Range_Normal_Shot();					// �m�[�}���e�̔���
	void	Enemy_Model_Animation();					// �G�l�~�[���f���A�j���[�V����

	//�ϐ�
	int		iFiringCount;								// ���˃J�E���g
	int		iGuidanceCount;								// �U���J�E���g
	bool	bEffectGenerated;							// �x���G�t�F�N�g�����t���O
	bool	bHitEffectGenerated;						// �q�b�g�G�t�F�N�g�����t���O
	bool	bDirectionFlg;								// �����Œ�t���O
	bool	bWarningEffectFlg;							// �x���G�t�F�N�g�t���O
	bool	bShotFlg;									// �V���b�g�t���O
	
	//���[�V�����֘A�ϐ�
	int		iNormalAttackAttachIndex;					// �U�����[�V�����A�^�b�`�C���f�b�N�X
	int		iNormalAttackNowAttachIndex;				// �U�������[�V�����A�^�b�`�C���f�b�N�X
	int		iNormalAttackEndAttachIndex;				// �U���I�����[�V�����A�^�b�`�C���f�b�N�X
	int		iNormalAttackEndLoopAttachIndex;			// �U���I�����[�v���[�V�����A�^�b�`�C���f�b�N�X
	int		iDieAttachIndex;							// ���S���[�V�����A�^�b�`�C���f�b�N�X
	bool	bNormalAttackMotionFlg;						// �U�����[�V�����t���O
	bool	bNormalAttackNowMotionFlg;					// �U�������[�V�����t���O
	bool	bNormalAttackEndMotionFlg;					// �U���I�����[�V�����t���O
	bool	bNormalAttackEndLoopMotionFlg;				// �U���I�����[�v���[�V�����t���O
	float	fNormalAttackTotalTime;						// �U�����[�V�����̑�����
	float	fNormalAttackNowTotalTime;					// �U�������[�V�����̑�����
	float	fNormalAttackEndTotalTime;					// �U���I�����[�V�����̑�����
	float	fNormalAttackEndLoopTotalTime;				// �U���I�����[�v���[�V�����̑�����
	float	fDieTotalTime;								// ���S���[�V�����̑�����
	float	fNormalAttackPlayTime;						// �U���Đ�����
	float	fNormalAttackNowPlayTime;					// �U�����Đ�����
	float	fNormalAttackEndPlayTime;					// �U���I���Đ�����
	float	fNormalAttackEndLoopPlayTime;				// �U���I�����[�v�Đ�����
	float	fDiePlayTime;								// ���S�Đ�����

protected:


};
