/* 2024.12.15 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹 ����֘A�̊֐��ǉ� */
/* 2025.01.22 �e�r�듹 �U���֘A�̊֐��ǉ� */
/* 2025.01.27 �e�r�듹 �G�t�F�N�g�֘A�̕ϐ��ǉ� */
/* 2025.02.06 �e�r�듹 �G�t�F�N�g�֘A�C�� */
/* 2025.02.14 �e�r�듹 ��]�֘A�̊֐��ǉ� */
/* 2025.02.14 �e�r�듹 �N�i�C�֘A�̕ϐ��ǉ� */
/* 2025.02.19 �e�r�듹 �t���[���֘A�̕ϐ��ǉ� */
/* 2025.02.22 �e�r�듹 �ǃL�b�N�֘A�̕ϐ��ǉ� */
/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̊֐��E�ϐ��ǉ� */
/* 2025.03.08 ��򕗏� �V���f���Ή� */
/* 2025.03.11 �e�r�듹 ���[�V�����֘A�̕ϐ��ǉ� */
/* 2025.03.13 �e�r�듹 �N�i�C�֘A�̕ϐ��ǉ� */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_Input.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Object.h"
#include "DataList_Model.h"
#include "DataList_Effect.h"
#include "DataList_StageStatus.h"

/* �I�u�W�F�N�g */
#include "BulletPlayerMeleeWeak.h"
#include "BulletPlayerMeleeStrong.h"
#include "BulletPlayerKunaiAttack.h"
#include "BulletPlayerKunaiWarp.h"
#include "EffectSelfDelete.h"
#include "EffectSelfDelete_PlayerFollow.h"
#include "EffectManualDelete_PlayerFollow.h"
#include "EffectManualDelete_PlayerFollow_Frame.h"
#include "EffectSelfDelete_PlayerFollow_Frame.h"
#include "PlayerBulletDefine.h"
#include "Gimmick_CheckPoint.h"

/* �摜�G�t�F�N�g */
#include "ScreenEffect_Damage.h"
#include "ScreenEffect_SlowMotion.h"
#include "ScreenEffect_ConcentrationLine.h"

/* �z�Q�Ƒ΍�̐�s��` */
class ScreenEffect_Damage;
class ScreenEffect_SlowMotion;
class ScreenEffect_ConcentrationLine;
class Gimmick_CheckPoint;

/* �v���C���[�N���X�̐錾 */

// �v���C���[�N���X
class CharacterPlayer : public CharacterBase
{
	public:
		CharacterPlayer();				// �R���X�g���N�^
		virtual ~CharacterPlayer() {};	// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		virtual void	Draw()				override;		// �`��
		virtual void	CollisionDraw()		override;		// �����蔻��`��
		virtual void	Reset()				override;		// ���Z�b�g����

	private:
		/* �g�p����f�[�^���X�g */
		// ����f�[�^���X�g�T�[�o�[����擾����͔̂�����Ȃ��߁A�����ŕۑ����Ă���
		DataList_Input*			InputList;			// ���͊Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[���
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_Effect*		EffectList;			// �G�t�F�N�g���\�[�X�Ǘ�
		DataList_StageStatus*	StageStatusList;	// �X�e�[�W��ԃ��X�g

		/* �֐� */
		void	CollisionUpdate();						// �R���W�����X�V
		void	PlayerHitCheck();						// �����蔻�菈��
		void	RadianLimitAdjustment(float& fRadian);	// �p�x(���W�A��)�̐����ƕ␳	/* 2025.02.13 �e�r�듹 ��]�֘A�̊֐��ǉ� */
		void	UpdateCooldownTime();					// �N�[���^�C���̍X�V			/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̊֐��ǉ� */
		void	PlayerFallRecovery();					// ��������̕��A				/* 2025.03.02 ��򕗏� �������A�����쐬 */
		void	FastMotion();							// �Q�[���J�n���̃��[�V����
		void	MotionReset();							// ���[�V����������

		// �ړ��A�N�V����
		void	Player_Jump();				// �W�����v
		void	Player_Gravity();			// �d�͏���
		void	Player_Move();				// �ړ�
		void	Player_Dodg();				// ��� 2025.01.09 �e�r�듹 �֐��ǉ�
		void	Movement_Vertical();		// �ړ�����(��������)
		void	Movement_Horizontal();		// �ړ�����(��������)

		// �U���A�N�V����
		void	Player_Attack_Transition();			// �U����ԑJ�ڊǗ�
		void	Player_Melee_Posture();				// �ߐڍU��(�\��)
		void	Player_Melee_Weak();				// �ߐڍU��(��)
		void	Player_Charge_Attack();				// �v���C���[���ߍU���@2025.01.22 �e�r�듹 �֐��ǉ�  
		void	Player_Projectile_Posture();		// �������U��(�\��)
		void	Player_Projectile();				// �������U��

		// ���[�V�����֘A
		void	Player_Motion_Transition();			// ���[�V�����J�ڊǗ��@2025.01.30 �e�r�듹 �֐��ǉ� 

		// �V�F�C�v�֘A
		void	Player_Shape();						// �V�F�C�v����

		/* �I�u�W�F�N�g�̃n���h�� */
		// ���v���C���[������폜�^�C�~���O���w�肷�邽�߂Ƀn���h��������
		BulletPlayerMeleeWeak*		pBulletMeleeWeak;	// �ߐڍU��(��)�̒e
		BulletPlayerKunaiWarp* 		pBulletKunaiWarp;			// �N�i�C(���[�v)�̒e			/* 2025.03.13 �e�r�듹 �N�i�C�֘A�̕ϐ��ǉ� */
		BulletPlayerKunaiAttack*	pBulletKunaiAttack;			// �N�i�C(�U��)�̒e				/* 2025.03.13 �e�r�듹 �N�i�C�֘A�̕ϐ��ǉ� */

		/* �G�t�F�N�g�̃n���h�� */
		EffectManualDelete_PlayerFollow_Frame*	pChargeEffect;			//���߃G�t�F�N�g		/* 2025.01.27 �e�r�듹 �G�t�F�N�g�֘A�̕ϐ��ǉ� */	/* 2025.02.06 �e�r�듹 �G�t�F�N�g�֘A�C�� */
		EffectManualDelete_PlayerFollow_Frame*	pChargeHoldEffect;		//���ߊ�����G�t�F�N�g	/* 2025.01.27 �e�r�듹 �G�t�F�N�g�֘A�̕ϐ��ǉ� */	/* 2025.02.06 �e�r�듹 �G�t�F�N�g�֘A�C�� */
		EffectManualDelete_PlayerFollow*		pDodgeEffect;			//����G�t�F�N�g		/* 2025.01.27 �e�r�듹 �G�t�F�N�g�֘A�̕ϐ��ǉ� */	/* 2025.02.06 �e�r�듹 �G�t�F�N�g�֘A�C�� */

		/* �t���[���ԍ� */
		int		iKatanaFrameNo;				// ���̃t���[���ԍ�								/* 2025.02.19 �e�r�듹 �t���[���֘A�̕ϐ��ǉ� */
		int		iKatanaFrameNo_Waist;		// ���̃t���[���ԍ�(�w��)						/* 2025.03.13 ��򕗏� �V���f���Ή� */
		int		iKatanaFrameNo_RightHand;	// ���̃t���[���ԍ�(�E��)						/* 2025.03.13 ��򕗏� �V���f���Ή� */
		int		iUpperBodyFrameNo;			// �㔼�g�̃t���[���ԍ�							/* 2025.03.08 ��򕗏� �V���f���Ή� */
		int		iKunaiHandFrameNo;			// �N�i�C������̃t���[���ԍ�					/* 2025.03.10 �e�r�듹 �t���[���֘A�̕ϐ��ǉ� */

		/* �V�F�C�v�֘A */
		int		iShapeNo_Blink;				// �V�F�C�v�ԍ�(�u��)
		float	fShapeRate;					// �V�F�C�v�K�p��

		/* �ϐ� */
		VECTOR				vecMove;				// �ړ���
		VECTOR				vecNormalSum;			// �v���C���[�ɐڐG����I�u�W�F�N�g�̖@���x�N�g���̍��v			/* 2025.02.22 �e�r�듹 �ǃL�b�N�֘A�̕ϐ��ǉ� */

		/* �ϐ�(�f�o�b�O�p) */
		COLLISION_LINE		stVerticalCollision;			// ���������̃R���W����
		COLLISION_CAPSULE	stHorizontalCollision[2];		// ���������R���W����(0:�㑤, 1:����)
		COLLISION_CAPSULE	stMeleeStrongMoveCollsion;		// �ߐڍU��(��)�̃R���W����(�ړ���̍��W)
		VECTOR				vecMoveSize;					// �ړ���(�f�o�b�O�p)		<- �����̕ϐ����Ȃ��ƃp�b�P�[�W������ۂɃL�[�{�[�h�ł̈ړ��̕s�����������(���)
		int					iFallingFrame;					// ������ԂɂȂ��Ă���̃t���[����(�Ӑ}���Ȃ����[�V�����؂�ւ���h�~���邽�߂Ɏg�p)		/* 2025.03.11 �e�r�듹 ���[�V�����֘A�̕ϐ��ǉ� */

		/* �N�[���^�C���֘A */
		int		iMeleeWeakCoolTime;		// �ߐڍU��(��)�N�[���^�C��		/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̕ϐ��ǉ� */
		int		iProjectileCoolTime;	// �������U���N�[���^�C��		/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̕ϐ��ǉ� */
		int		iDodgeCoolTime;			// ����N�[���^�C��				/* 2025.02.26 �e�r�듹 �N�[���^�C���֘A�̕ϐ��ǉ� */
};
