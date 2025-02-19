/* 2024.01.29 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "EnemyBasic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeBeam.h"
#include "PlayerStatusDefine.h"

/* �e�X�g�p�G�N���X */

// �G�l�~�[�x�[�X�N���X
class BeamEnemy : public EnemyBasic
{
public:
	BeamEnemy();				// �R���X�g���N�^
	virtual ~BeamEnemy();		// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

private:

	//�G�t�F�N�g
	EffectManualDelete* pEffectWarning;					//�x���G�t�F�N�g

	BulletEnemyRangeBeam* pBulletRangeBeam;				// �r�[��

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;			// �v���C���[


	//�֐�
	void	MoveEnemy();					// �G���ړ������郁�\�b�h��ǉ�
	void	Player_Range_Beam_Shot();			// �r�[���̔���


	//�ϐ�
	int		iFiringCount;	// ���˃J�E���g

	int		iDurationCount;	// �r�[���̎����J�E���g

	int		iChargeCount;	// �r�[���̃`���[�W�J�E���g

	int		iModelFootHandle;	// �G�l�~�[�������f���n���h��

	bool	bEffectGenerated;							// �x���G�t�F�N�g�����t���O
protected:


};
