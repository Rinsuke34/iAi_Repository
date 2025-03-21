/* 2024.03.19 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_Image.h"

/* �I�u�W�F�N�g */
#include "EffectManualDelete.h"
#include "PlayerStatusDefine.h"
#include "GimmickDefine.h"

/*�V�[��*/
#include "SceneTitle.h"

/* �e�X�g�p�G�N���X */

class TitlePlayer : public PlatformBase
{
public:
	TitlePlayer();				// �R���X�g���N�^
	virtual ~TitlePlayer();		// �f�X�g���N�^

	virtual void	Update()			override;		// �X�V

private:
	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;	// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;	// �v���C���[

	/* �֐� */
	void	Process();				// �X�V

	//�ϐ�

	//���[�V�����֌W�ϐ�
	int		iTitlePlayerWaitAttachIndex;	// �ҋ@���[�V�����A�^�b�`�C���f�b�N�X
	int		iTitlePlayerLandingAttachIndex;	// ���n���[�V�����A�^�b�`�C���f�b�N�X
	bool	bTitlePlayerWaitFlg;			// �ҋ@�t���O
	bool	bTitlePlayerLandingFlg;			// ���n�t���O
	float	fTitlePlayerWaitTotalTime;		// �ҋ@���[�V�����̑��Đ�����
	float	fTitlePlayerLandingTotalTime;	// ���n���[�V�����̑��Đ�����
	float	fTitlePlayerWaitNowTime;		// �ҋ@���[�V�����̌��݂̍Đ�����
	float	fTitlePlayerLandingNowTime;		// ���n���[�V�����̌��݂̍Đ�����

};
