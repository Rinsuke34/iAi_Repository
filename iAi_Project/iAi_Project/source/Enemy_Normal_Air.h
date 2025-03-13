/* 2024.03.13 �ΐ�q�� �t�@�C���쐬 */

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
class Enemy_Normal_Air : public Enemy_Basic
{
public:
	Enemy_Normal_Air();										// �R���X�g���N�^
	virtual ~Enemy_Normal_Air();							// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

private:

	EffectManualDelete* pEffectWarning;					//�x���G�t�F�N�g

	BulletEnemyRangeNormal* pBulletRangeNormal;			// �m�[�}���e

	EffectManualDelete* pEffectHit;						//�q�b�g�G�t�F�N�g

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;						// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;								// �v���C���[

	//�֐�
	void	MoveEnemy();								// �G���ړ������郁�\�b�h��ǉ�
	void	Player_Range_Normal_Shot();					// �m�[�}���e�̔���

	//�ϐ�
	int		iFiringCount;								// ���˃J�E���g
	int		iGuidanceCount;								// �U���J�E���g
	bool	bEffectGenerated;							// �x���G�t�F�N�g�����t���O
	bool	bHitEffectGenerated;						// �q�b�g�G�t�F�N�g�����t���O
	bool	bDirectionFlg;								// �����Œ�t���O

	//���[�V�����֘A�ϐ�
	int		iNormalAirAttachIndex;						// �󒆃��[�V�����A�^�b�`�C���f�b�N�X
	int		iDieAttachIndex;							// ���S���[�V�����A�^�b�`�C���f�b�N�X
	float	fNormalAirTotalTime;						// �󒆃��[�V�����̑�����
	float	fDieTotalTime;								// ���S���[�V�����̑�����
	float	fNormalAirPlayTime;							// �󒆍Đ�����
	float	fDiePlayTime;								// ���S�Đ�����

protected:
};
