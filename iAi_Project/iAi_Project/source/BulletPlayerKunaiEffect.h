/* 2025.02.14 �e�r�듹 �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"

/* �I�u�W�F�N�g */
#include "PlayerBulletDefine.h"
#include "DataList_Object.h"

/* �萔 */
#include "PublicInclude.h"

/* �N�i�C(�G�t�F�N�g)�N���X�̐錾 */

// �N�i�C(�G�t�F�N�g)
class BulletPlayerKunaiEffect : public BulletBase
{
public:
	BulletPlayerKunaiEffect();				// �R���X�g���N�^
	virtual ~BulletPlayerKunaiEffect();		// �f�X�g���N�^

	virtual void	Initialization()	override;	// ������
	virtual void	Update()			override;	// �X�V
	virtual void	Draw()				override;	// �`��	

	void	Attack();								// �U������

	VECTOR	GetKunaiTargetPosition()							{ return this->vecKunaiTargetPosition; }					// �N�i�C�̃^�[�Q�b�g���W���擾

	void	SetKunaiTargetPosition(VECTOR vecTargetPosition)	{ this->vecKunaiTargetPosition = vecTargetPosition; }		// �N�i�C�̃^�[�Q�b�g���W��ݒ�

private:
	VECTOR	vecKunaiTargetPosition;			// �^�[�Q�b�g���W
	VECTOR	vecKunaiMoveDirection;			// �N�i�C�̈ړ��������
	float	fKunaiTargetDistance;			// �N�i�C�̔��˒n�_����^�[�Q�b�g�܂ł̋���
	float	fKunaiMoveDistance;				// �N�i�C�̈ړ�����
	float	fKunaiAngleX;					// �N�i�C��X����]�p�x
	float	fKunaiAngleY;					// �N�i�C��Y����]�p�x
	int		iKunaiDeleteCount;				// �N�i�C�̍폜�J�E���g
	bool	bKunaiAttackFlg;				// �N�i�C�̍U���t���O

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�

protected:
};

