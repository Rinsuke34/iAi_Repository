/* 2024.02.10 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "EffectManualDelete.h"
#include "PlayerStatusDefine.h"
#include "GimmickDefine.h"
#include "GimmickDisappearSpawnPoint.h"

/* ��s��` */
class GimmickDisappearSpawnPoint;

/* �e�X�g�p�G�N���X */

// �����M�~�b�N�N���X
class GimmickDisappear : public PlatformBase
{
public:
	GimmickDisappear();				// �R���X�g���N�^
	virtual ~GimmickDisappear();		// �f�X�g���N�^

	virtual void	Update()			override;		// �X�V
	virtual void	Reset()				override;	// ���Z�b�g����

	void	SetSpawnPoint(GimmickDisappearSpawnPoint* pGimmickDisappearSpawnPoint) { this->pGimmickDisappearSpawnPoint = pGimmickDisappearSpawnPoint; }	// �R�Â����X�|�i�[�̐ݒ�

private:

	void ProcessGimmick();					// �M�~�b�N�̏������\�b�h��ǉ�

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;			// �v���C���[


	//�M�~�b�N�̏��Ŏ���
	int iDisappearTime;					// ���Ŏ���
	int iSpawnCount;					// �o���J�E���g
	int iDisappearTimeCount;			// ���Ŏ��ԃJ�E���g
	int iTextureFirstChangeCount;		// �e�N�X�`���ύX����
	int iTextureSecondChangeCount;		// �e�N�X�`���ύX����
	int iTextureRedHandle;				// �e�N�X�`���n���h��
	int iTextureOrangeHandle;			// �e�N�X�`���n���h��
	int iTextureYellowHandle;			// �e�N�X�`���n���h��
	int iBlinkTime;						// �_�Ŏ���

	/* �X�|�i�[�̃|�C���^ */
	GimmickDisappearSpawnPoint* pGimmickDisappearSpawnPoint;	// �����M�~�b�N�X�|�i�[

protected:
};
