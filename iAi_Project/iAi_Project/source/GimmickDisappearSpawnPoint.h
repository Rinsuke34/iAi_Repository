/* 2025.03.19 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �I�u�W�F�N�g */
#include "SpawnPoint_Base.h"
#include "GimmickDisappear.h"

/* �����M�~�b�N�X�|�i�[�N���X�̐錾 */

// �����M�~�b�N�X�|�i�[�N���X
class GimmickDisappearSpawnPoint : public SpawnPoint_Base
{
public:
	GimmickDisappearSpawnPoint();						// �R���X�g���N�^
	virtual ~GimmickDisappearSpawnPoint() {};			// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V

	/* �֐� */
	void	SetAddobjectFlg(bool bAddObjectFlg) { this->bAddObjectFlg = bAddObjectFlg; }	// �I�u�W�F�N�g�����t���O�̐ݒ�

private:

	/* �ϐ� */
	bool	bAddObjectFlg;								// �I�u�W�F�N�g�������t���O
	int		iRespawnDelay;								//���X�|�[���J�E���g
};
