/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "EffectTest.h"
#include "Bullet.h"

/* �f�[�^���X�g */
#include "DataList_Input.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Object.h"
/* �e�X�g�p�G�N���X */

// �G�l�~�[�x�[�X�N���X
class TestEnemy : public EnemyBase
{
	public:
		TestEnemy();				// �R���X�g���N�^
		virtual ~TestEnemy();		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		virtual void	Draw()				override;		// �`��
		virtual void	BloomDraw()			override {};	// �����`��

	private:
	protected:
		/* �֐� */
		void FireBallFromEnemy(); // �G����ʂ𔭎˂��郁�\�b�h��ǉ�
		void FireBallFromEnemy2(); // �G����ʂ𔭎˂��郁�\�b�h��ǉ�
		void MoveEnemy(); // �G��ړ������郁�\�b�h��ǉ�
		void EnemyBulletMove(); // �G��ړ������郁�\�b�h��ǉ�



		/* �ϐ� */

		VECTOR _vInitPos;	// �����ʒu
		VECTOR _vDir;	// ����
		float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j

		float _total_time;
		float _play_time;


		bool _isVisible = true; // �`�搧��p�̃t���O
		bool _isActive = true; // �ǉ�: �����𐧌䂷��t���O


		int _handleEnemy; // �G�̃��f���n���h��
		VECTOR _vEnemyPos; // �G�̈ʒu
		VECTOR _vEnemyTargetPos; // _vEnemyTargetPos�̒�`��ǉ�


		int _handleEnemy3; // �G�̃��f���n���h��
		VECTOR _vEnemy3Pos; // �G�̈ʒu
		VECTOR _vEnemy3TargetPos; // _vEnemyTargetPos�̒�`��ǉ�


		int _handleEnemy2; // �G�̃��f���n���h��
		VECTOR _vEnemy2Pos; // �G�̈ʒu
		VECTOR _vEnemy2TargetPos; // _vEnemyTargetPos�̒�`��ǉ�

		int _handleEnemy4; // �G�̃��f���n���h��
		VECTOR _vEnemy4Pos; // �G�̈ʒu
		VECTOR _vEnemy4TargetPos; // _vEnemyTargetPos�̒�`��ǉ�

		int _handleEnemy5; // �G�̃��f���n���h��
		VECTOR _vEnemy5Pos; // �G�̈ʒu

		float _fireInterval; // �ʂ̔��ˊԊu
		float _fireInterval2; // �ʂ̔��ˊԊu
		float _timeSinceLastFire; // �Ō�ɔ��˂��Ă���̌o�ߎ���
		float _timeSinceLastFire2; // �Ō�ɔ��˂��Ă���̌o�ߎ���

		float _moveDuration; // �ړ��̎�������
		float _moveElapsedTime; // �ړ��̌o�ߎ���

		int textureHandle; // �e�N�X�`���n���h����ǉ�

		// �t���O��ǉ�
		bool _isFiringBall;
		bool _isFiringBall2;

		int _lastTime; // �ǉ�: _lastTime �����o�[�ϐ�
		int _lastMoveTime; // �ǉ�: _lastMoveTime �����o�[�ϐ�
		float _moveInterval; // �ǉ�: _moveInterval �����o�[�ϐ�
		// ��ѓ���p
		int	_cgBullet;
		int	_cgBullet2;


		std::vector<Bullet*> _vBullet;

		DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
};
