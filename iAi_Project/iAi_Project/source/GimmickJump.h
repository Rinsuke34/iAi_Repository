/* 2024.02.10 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* �I�u�W�F�N�g */
#include "PlatformBasic.h"
#include "EffectManualDelete.h"
#include "GimmickDefine.h"

/* �e�X�g�p�G�N���X */

// �����M�~�b�N�N���X
class GimmickJump : public PlatformBasic
{
public:
	GimmickJump();				// �R���X�g���N�^
	virtual ~GimmickJump();		// �f�X�g���N�^

	virtual void	Update()			override;		// �X�V

private:

	void ProcessGimmick();					// �M�~�b�N�̏������\�b�h��ǉ�

	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;			// �v���C���[
	DataList_PlayerStatus* PlayerStatusList;	// �v���C���[���


	//�M�~�b�N�̏��Ŏ���
	int iDisappearTime;

	//�M�~�b�N�̏��Ŏ��ԃJ�E���g
	int iDisappearTimeCount;

	//�M�~�b�N�e�N�X�`���ύX�J�E���g	
	int iTextureChangeCount;

	// �e�N�X�`���n���h����ǉ�
	int textureHandle;

protected:
};
