/* 2025.01.27 ��򕗏� �t�@�C���쐬 */

#include "EnemyBasic.h"

/* ��{�G�l�~�[�N���X�̒�` */

// �R���X�g���N�^
EnemyBasic::EnemyBasic() : EnemyBase()
{
	/* ������ */
	this->iPlayerLockOnType	= PLAYER_LOCKON_NONE;	// ���b�N�I������Ă��Ȃ���Ԃɂ���
	this->iCoreFrameNo		= -1;					// �R�A�t���[���ԍ���������
}

// �R�A�t���[���ԍ��擾
void EnemyBasic::LoadCoreFrameNo()
{
	/* �R�A�t���[���ԍ����擾 */
	this->iCoreFrameNo = MV1SearchFrame(this->iModelHandle, "Core");
}
