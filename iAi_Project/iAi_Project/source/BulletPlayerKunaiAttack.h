/* 2025.03.13 �e�r�듹 �t�@�C���쐬 */
#pragma once

/* �I�u�W�F�N�g */
#include "BulletPlayerKunai.h"

/* �N�i�C(�U��)�N���X�̐錾 */

// �N�i�C(�U��)
class BulletPlayerKunaiAttack : public BulletPlayerKunai
{
public:
	BulletPlayerKunaiAttack();				// �R���X�g���N�^
	virtual ~BulletPlayerKunaiAttack();		// �f�X�g���N�^

	virtual void	Initialization()	override;			// ������
	virtual void	Update()			override;			// �X�V
	virtual void	Draw()				override;			// �`��	

	void	Attack();								// �U������
	

private:
	
protected:

};

