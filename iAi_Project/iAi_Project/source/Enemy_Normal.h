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

/* �e�X�g�p�G�N���X */

// �G�l�~�[�x�[�X�N���X
class Enemy_Normal : public Enemy_Basic
{
public:
	Enemy_Normal();				// �R���X�g���N�^
	virtual ~Enemy_Normal();		// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

private:
	//EffectManualDelete* pEffect;

	EffectManualDelete* pEffectWarning;					//�x���G�t�F�N�g

	BulletEnemyRangeNormal* pBulletRangeNormal;			// �m�[�}���e


	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;			// �v���C���[

	//�֐�
	void	MoveEnemy();					// �G���ړ������郁�\�b�h��ǉ�
	void	Player_Range_Normal_Shot();			// �m�[�}���e�̔���
	void	Enemy_Model_Animation();			// �G�l�~�[���f���A�j���[�V����

	//�ϐ�
	int		iFiringCount;	// ���˃J�E���g

	int		iGuidanceCount;	// �U���J�E���g

	//���[�V�����֘A�ϐ�
	int		iAttackAttachIndex;			// �U�����[�V�����A�^�b�`�C���f�b�N�X
	int		iAttackNowAttachIndex;		// �U�������[�V�����A�^�b�`�C���f�b�N�X
	int		iAttackEndAttachIndex;		// �U���I�����[�V�����A�^�b�`�C���f�b�N�X
	int		iAttackEndLoopAttachIndex;	// �U���I�����[�v���[�V�����A�^�b�`�C���f�b�N�X
	bool	bEffectGenerated;							// �x���G�t�F�N�g�����t���O
	bool	bAttackMotionFlg;			// �U�����[�V�����t���O
	bool	bAttackNowMotionFlg;		// �U�������[�V�����t���O
	bool	bAttackEndMotionFlg;		// �U���I�����[�V�����t���O
	bool	bAttackEndLoopMotionFlg;	// �U���I�����[�v���[�V�����t���O
	float	fAttackTotalTime;			// �U�����[�V�����̑�����
	float	fAttackNowTotalTime;		// �U�������[�V�����̑�����
	float	fAttackEndTotalTime;		// �U���I�����[�V�����̑�����
	float	fAttackEndLoopTotalTime;	// �U���I�����[�v���[�V�����̑�����
	float	fAttackPlayTime;			// �U���Đ�����
	float	fAttackNowPlayTime;			// �U�����Đ�����
	float	fAttackEndPlayTime;			// �U���I���Đ�����
	float	fAttackEndLoopPlayTime;		// �U���I�����[�v�Đ�����
	

protected:


};
