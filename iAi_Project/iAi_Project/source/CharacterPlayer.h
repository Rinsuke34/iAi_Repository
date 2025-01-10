/* 2024.12.15 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��E�萔�ǉ� */


#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Input.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Object.h"

/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ��J�n */

//�v���C���[�Ɋւ���ݒ�l
namespace PLAYER_STATUS
{

	//�ړ��֌W
	const float PLAYER_WALK_MOVE_SPEED = 1.0f; //�v���C���[�̕����̈ړ����x
	const float PLAER_DASH_NOMAL_SPEED = 5.0f; //�v���C���[�̑���i�ʏ�j�̈ړ����x
	const float PLAER_DASH_MAX_SPEED = 10.0f; //�v���C���[�̑���i�ő�j�̈ړ����x
	const int FLAME_COUNT_TO_MAX_SPEED = 180; //�v���C���[�̑���̒ʏ큨�ő�ɂȂ�t���[����
	const int STICK_TILT_PLAER_DASH = 700; //�v���C���[�������ԂɂȂ�X�e�B�b�N�̌X���@�i�͈́F�O�`�P�O�O�O�j

	//�W�����v�֌W
	const float PLAYER_JUMP_SPEED = 50.0f; //�v���C���[�̃W�����v�̑��x
	const float GRAVITY_SREED = -9.8f; //�d�͂̑��x�@Y���̉������Ȃ̂Ń}�C�i�X�Ƃ���
	const float GRAVITY_BUFFER = 0.1f; //�L�����N�^�[�ɂ�����d�͒����@�P���傫���Əd���Ȃ�@�P��菬�����ƌy���Ȃ�
	const int PLAYER_JUMPING_IN_AIR_LIMIT = 1;//�v���C���[���󒆃W�����v�ł����
	//����֌W
	const float PLAYER_DODGE_SPEED = 3000.0f;//�v���C���[�̉�𑬓x
}

//�Q�[���S�ʂ̐ݒ�Ɋւ���ݒ�l
namespace GAME_SETTING
{
	const float STICK_DEAD_ZONE = 100; //�X�e�B�b�N���͂̃f�b�h�]�[���i�͈́F�O�`�P�O�O�O�j
	const int GAME_FRAMES_PER_SECOND = 60; //�Q�[���̐ݒ�FPS
}

using namespace GAME_SETTING;

// �v�Z�p�}�N��
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )
#define	ACCELERATION(x)	( (x) / GAME_FRAMES_PER_SECOND * GAME_FRAMES_PER_SECOND ) //�����x�v�Z�}�N��


/* 2025.01.09 �e�r�듹 �ړ��֘A�̒萔�ǉ��I�� */



/* �v���C���[�N���X�̐錾 */

// �v���C���[�N���X
class CharacterPlayer : public CharacterBase
{
	public:
		CharacterPlayer();				// �R���X�g���N�^
		virtual ~CharacterPlayer() {};	// �f�X�g���N�^

		virtual void	Update();	// �X�V
		virtual void	Draw();		// �`��

	private:
	protected:
		/* �g�p����f�[�^���X�g */
		// ����f�[�^���X�g�T�[�o�[����擾����͔̂�����Ȃ��߁A�����ŕۑ����Ă���
		DataList_Input*	InputList;	// ���͊Ǘ�

		/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ��J�n */

		VECTOR vecPlayerDirection;	// �v���C���[�̌���
		
		//�ړ��֌W�i�����E���蓙�j
		float fPlayerMoveSpeed; //�v���C���[�ړ����x
		VECTOR vecPlayerOldVector; //�v���C���[�̈ړ����̃x�N�g����ۑ�����i�W�����v�������Ɏg�p�j
		float fPlayerOldRadian;  //�v���C���[�̈ړ����̊p�x��ێ����遦�P�ʂ̓��W�A���i�����]�������Ɏg�p�j
		int iPlayerNormalDashFlameCount; //�ʏ�_�b�V�����o�߃t���[�����i�����_�b�V���ւ̈ڍs�Ɏg�p�j

		//�W�����v�֌W
		bool bPlayerJumpingFlag = false; //�v���C���[���W�����v�����̃t���O
		int iPlayerJumpCount = 0; //�v���C���[�W�����v��
		float fPlayerJumpSpeed = 0.0f; //�v���C���[�W�����v���x

		//����֌W
		bool bPlayerDodgingFlag = false; //�v���C���[����𒆂��̃t���O
		float fPlayerDodgeProgress = 0.0f; // �v���C���[������[�V�����i�s�� (�͈́F0.0�`1.0)
		float fPlayerDodgeTime = 0.3f; // �v���C���[������� 
		VECTOR vecPlayerDodgeDirection = VGet(0, 0, 0); // �v���C���[������
		float fPlayerDodgeSpeed = 0.0f; //�v���C���[��𑬓x
		int iPlayerDodgeWhileJumpingCount; //�v���C���[�W�����v���̉����
		bool bPlayerAfterDodgeFlag;//�v���C���[�̉����t���O



		/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ��I�� */

		DataList_Input*			InputList;			// ���͊Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[���
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�

		/* �֐� */
		void	Player_Gravity();		// �d��
		void	Player_Move();			// �ړ�
		void	Player_Jump();			// �W�����v

		void	CollisionUpdate();		// �R���W�����X�V
};
