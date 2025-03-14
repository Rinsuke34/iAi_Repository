/* 2025.03.13 �e�r�듹 �t�@�C���쐬 */
#pragma once

/* �I�u�W�F�N�g */
#include "BulletPlayerKunai.h"

/* �N�i�C(�U��)�N���X�̐錾 */

// �N�i�C(�U��)
class BulletPlayerKunaiWarp : public BulletPlayerKunai
{
public:
	BulletPlayerKunaiWarp();				// �R���X�g���N�^
	virtual ~BulletPlayerKunaiWarp();		// �f�X�g���N�^

	virtual void	Initialization()	override;			// ������
	virtual void	Update()			override;			// �X�V
	virtual void	Draw()				override;			// �`��	

	void	SetKunaiTargetEnemy(Enemy_Basic* pTargetEnemy) { this->pTargetEnemy = pTargetEnemy; }				// �N�i�C�̃^�[�Q�b�g�G�l�~�[��ݒ�
	void	Warp();																								// ���[�v����

private:
	Enemy_Basic* pTargetEnemy;						// �N�i�C�̃^�[�Q�b�g�G�l�~�[

protected:

};
