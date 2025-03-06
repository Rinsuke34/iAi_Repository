/* 2024.12.15 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "EnemyBasic.h"
#include "EnemyDefine.h"
#include "EffectManualDelete.h"
#include "CharacterPlayer.h"

/* �e�X�g�p�G�N���X */

// �G�l�~�[�x�[�X�N���X
class ExplosionEnemy : public EnemyBasic
{
public:
	ExplosionEnemy();				// �R���X�g���N�^
	virtual ~ExplosionEnemy();		// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

private:
	/* �G�t�F�N�g */
	EffectManualDelete* pEffect;

	//�N���G�t�F�N�g
	EffectManualDelete* pEffectDetonation;

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�


	DataList_PlayerStatus* PlayerStatusList;	// �v���C���[���
	/*�֐�*/
	void MoveEnemy(); // �G���ړ������郁�\�b�h��ǉ�
	void Enemy_Gravity(); // �d�͏������\�b�h��ǉ�
	void CliffFallCheck();	// �R�ɗ����邩�ǂ����̔��胁�\�b�h��ǉ�


	/*�ϐ�*/
	int iXdistance;			// X���̋���

	int iZdistance;			// Z���̋���
	int iDetonationRange;			//�N���͈͓�
	int iBlastRange;				//�����͈͓�
	int iStopCount;			// ��~�J�E���g
	float fSpeed;			// �ړ����x
	float fGravity;						// �d��


	bool bEffectGenerated;	// �N���\���G�t�F�N�g�����t���O
	bool bFallFlg;			// �����t���O
	bool bStopFlg;			// ��~�t���O
	bool bCountFlg;			//�J�E���g�t���O
	bool bBlastFlg;			//�����t���O


	VECTOR vecLastRotation;	// �Ō�̉�]��
protected:
	COLLISION_LINE		stVerticalCollision;			// ���������̃R���W����

	VECTOR				vecMove;				// �ړ���
};
