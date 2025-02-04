/* 2024.12.15 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹 ����֘A�̊֐��ǉ� */
/* 2025.01.22 �e�r�듹 �U���֘A�̊֐��ǉ� */
/* 2025.01.27 �e�r�듹 �G�t�F�N�g�֘A�̕ϐ��ǉ� */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Input.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Object.h"
#include "DataList_Model.h"
#include "DataList_Effect.h"

/* �I�u�W�F�N�g */
#include "BulletPlayerMeleeWeak.h"
#include "BulletPlayerMeleeStrong.h"
#include "EffectSelfDelete.h"

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

	private:
	protected:
		/* �g�p����f�[�^���X�g */
		// ����f�[�^���X�g�T�[�o�[����擾����͔̂�����Ȃ��߁A�����ŕۑ����Ă���
		DataList_Input*			InputList;			// ���͊Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[���
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_Effect*		EffectList;			// �G�t�F�N�g���\�[�X�Ǘ�

		/* �֐� */
		void	CollisionUpdate();		// �R���W�����X�V
		void	HitCheck();				// �����蔻�菈��

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

		/* �I�u�W�F�N�g�̃n���h�� */
		// ���v���C���[������폜�^�C�~���O���w�肷�邽�߂Ƀn���h��������
		BulletPlayerMeleeWeak* pBulletMeleeWeak;	// �ߐڍU��(��)�̒e

		/* 2025.01.27 �e�r�듹 �G�t�F�N�g�֘A�̕ϐ��ǉ� �J�n */
		/* �G�t�F�N�g�̃n���h�� */
		EffectManualDelete* pChargeEffect;			//���߃G�t�F�N�g
		EffectManualDelete* pChargeHoldEffect;		//���ߊ�����G�t�F�N�g
		EffectManualDelete*	pDodgeEffect;			//����G�t�F�N�g
		/* 2025.01.27 �e�r�듹 �G�t�F�N�g�֘A�̕ϐ��ǉ� �I�� */

		/* 2025.01.30 �e�r�듹 ���[�V�����֘A�̕ϐ��ǉ� �J�n */
		int		iMotionAttachIndex;		// �A�^�b�`����郂�[�V�����̃C���f�b�N�X
		int		iOldMotion;				// �ȑO�ɃA�^�b�`���ꂽ���[�V����
		float	fMotionTotalTime;		// ���[�V�����̑�����
		float	fMoionPlayTime;			// ���[�V�����̍Đ�����
		/* 2025.01.30 �e�r�듹 ���[�V�����֘A�̕ϐ��ǉ� �I�� */

		/* �ϐ� */
		VECTOR				vecMove;				// �ړ���

		/* �ϐ�(�f�o�b�O�p) */
		COLLISION_LINE		stVerticalCollision;			// ���������̃R���W����
		COLLISION_CAPSULE	stHorizontalCollision[2];		// ���������R���W����(0:�㑤, 1:����)
		COLLISION_CAPSULE	stMeleeStrongMoveCollsion;		// �ߐڍU��(��)�̃R���W����(�ړ���̍��W)

		/* �\����(�e�X�g�̂��߂����Œ�`) */
		// �ł��v���C���[����߂��G�l�~�[
		struct NearEnemy
		{
			EnemyBasic* pEnemy;		// �G�l�~�[�̃|�C���^
			float fDistance;		// ��ʒ��S����̋���(�y�ʉ��̂��ߍ��W�̍��̓��)
		};
};
