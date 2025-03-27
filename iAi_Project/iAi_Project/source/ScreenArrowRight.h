/* 2024.03.26 �ΐ�q�� �t�@�C���쐬 */

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
#include "SceneStage.h"

/* �e�X�g�p�G�N���X */

// �����M�~�b�N�N���X
class ScreenArrowRight : public PlatformBase
{
public:
	ScreenArrowRight();				// �R���X�g���N�^
	virtual ~ScreenArrowRight();		// �f�X�g���N�^

	virtual void	Update()			override;		// �X�V

private:
	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;	// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;	// �v���C���[

	/* �֐� */
	void	Process();				// �X�V
	void	Draw();					// �`��

	//�ϐ�
	int iFirstCount;
	int iSecondCount;
	int iThirdCount;
	int iFourthCount;
	int iFifthCount;
	int iUICount;	//UI�̃J�E���g

	int iTextureArrowRightHandle1;		// �����
	int iTextureArrowRightHandle2;		// �E���
	int iTextureArrowRightHandle3;		// �����
	int iTextureArrowRightHandle4;		// �E���
	int iTextureArrowRightHandle5;		// �����

	bool bArrowFlg;
	bool bArrowFlg2;
	bool bArrowFlg3;
	bool bArrowFlg4;
	bool bArrowFlg5;
};
