/* 2025.03.13 �e�r�듹 �t�@�C���쐬 */
#pragma once

/* �I�u�W�F�N�g */
#include "BulletPlayerKunai.h"

/* �N�i�C(����)�N���X�̐錾 */

// �N�i�C(����)
class BulletPlayerKunaiExplosion : public BulletPlayerKunai
{
public:
	BulletPlayerKunaiExplosion();				// �R���X�g���N�^
	virtual ~BulletPlayerKunaiExplosion();		// �f�X�g���N�^

	virtual void	Initialization()	override;			// ������
	virtual void	Update()			override;			// �X�V
	virtual void	Draw()				override;			// �`��	

	void	Explosion();								// ��������
	
private:
	
protected:

};

