/* 2024.03.13 �ΐ�q�� �t�@�C���쐬 */

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
class Enemy_Missile_Air : public Enemy_Basic
{
public:
	Enemy_Missile_Air();									// �R���X�g���N�^
	virtual ~Enemy_Missile_Air();							// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

private:

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;						// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;								// �v���C���[
	BulletEnemyRangeMissile* pBulletRangeMissile;		// �~�T�C���e
	EffectManualDelete* pEffectHit;						//�x���G�t�F�N�g

	//�֐�
	void	MoveEnemy();								// �G���ړ������郁�\�b�h��ǉ�
	void	Player_Range_Missile_Shot();				// �~�T�C���e�U��

	//�ϐ�
	int		iFiringCount;								// ���˃J�E���g
	bool	bHitEffectGenerated;						// �q�b�g�G�t�F�N�g�����t���O
	bool	bDirectionFlg;								// �����Œ�t���O


	//���[�V�����֘A�ϐ�
	int		iMissileAirAttachIndex;						// �󒆃��[�V�����A�^�b�`�C���f�b�N�X
	int		iDieAttachIndex;							// ���S���[�V�����A�^�b�`�C���f�b�N�X
	float	fNormalAirTotalTime;						// �󒆃��[�V�����̑�����
	float	fDieTotalTime;								// ���S���[�V�����̑�����
	float	fNormalAirPlayTime;							// �󒆍Đ�����
	float	fDiePlayTime;								// ���S�Đ�����

protected:

};
