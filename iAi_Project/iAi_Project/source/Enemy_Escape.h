/* 2024.01.28 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "Enemy_Basic.h"
#include "EnemyDefine.h"
#include "EffectManualDelete.h"

/* �e�X�g�p�G�N���X */

// �G�l�~�[�x�[�X�N���X
class Enemy_Escape : public Enemy_Basic
{
	public:
		Enemy_Escape();				// �R���X�g���N�^
		virtual ~Enemy_Escape();		// �f�X�g���N�^
	
		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
	virtual void	CollisionDraw()		override;	// �����蔻��`��
	private:
	/* �G�t�F�N�g */
		EffectSelfDelete* pEffect;							// �G�t�F�N�g

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�

	/* �֐� */
	void MoveEnemy();				// �G���ړ������郁�\�b�h��ǉ�
	void Enemy_Model_Animation();	// �G�l�~�[���f���A�j���[�V����
	void Movement_Horizontal();		// �����ړ�

	/* �ϐ� */
	int iXescapedistance;			// X���̋���

	int iZescapedistance;			// Z���̋���
	int iEscapespeed;			// �ړ����x
	int iWaitCount;					// �ҋ@�J�E���g
	float fGravity;				// �d��
	bool	bHitEffectGenerated;						// �q�b�g�G�t�F�N�g�����t���O
	bool bDirectionFlg;										// �����Œ�t���O
	bool bEscapeEffectGenerated;	// �����G�t�F�N�g�����t���O
	bool bWallHitFlg;				// �ǂɓ��������t���O
	bool bWallFlg;					// �ǃt���O

	//���[�V�����֌W�ϐ�
	int iWaitAttachIndex;			// �ҋ@���[�V�����A�^�b�`�C���f�b�N�X
	int iDieAttachIndex;			// ���S���[�V�����A�^�b�`�C���f�b�N�X
	int	iRunAttachIndex;		// ���胂�[�V�����A�^�b�`�C���f�b�N�X
	float fWaitTotalTime;			// �ҋ@���[�V�����̑�����
	float fDieTotalTime;			// ���S���[�V�����̑�����
	float fRunTotalTime;		// ���胂�[�V�����̑�����
	float fWaitPlayTime;			// �ҋ@�Đ�����
	float fDiePlayTime;				// ���S�Đ�����
	float fRunPlayTime;			// ����Đ�����


	VECTOR vecEscapeEffectPos;	// �����G�t�F�N�g�̍��W
protected:
	COLLISION_CAPSULE			stHorizontalCollision;		// ���������̃R���W����
	COLLISION_SQHERE			stSphere;					// ���̃R���W����
	VECTOR						vecNormalSum;				// �v���C���[�ɐڐG����I�u�W�F�N�g�̖@���x�N�g���̍��v

	bool						bPlayeSeFlg;				// SE���Đ��J�n�������̃t���O(�Q�[���J�n��Ɏ��s���Ȃ��Ƒ��̃V�[�����ɍĐ�����邽��)

};
