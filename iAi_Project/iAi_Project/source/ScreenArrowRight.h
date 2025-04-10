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

// �X�N���[���E���N���X
class ScreenArrowRight : public PlatformBase
{
public:
	ScreenArrowRight();				// �R���X�g���N�^
	virtual ~ScreenArrowRight();		// �f�X�g���N�^

	virtual void	Update()			override;		// �X�V

private:
	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;						// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;								// �v���C���[

	/* �֐� */
	void	Process();									// �X�V
	void	Draw();										// �`��

	/* �ϐ� */
	int iFirstCount;									// 1��ڂ̃J�E���g
	int iSecondCount;									// 2��ڂ̃J�E���g
	int iThirdCount;									// 3��ڂ̃J�E���g
	int iFourthCount;									// 4��ڂ̃J�E���g
	int iFifthCount;									// 5��ڂ̃J�E���g
	int iUICount;										//UI�̃J�E���g
	int iTextureArrowRightHandle1;						// �E���
	int iTextureArrowRightHandle2;						// �E���
	int iTextureArrowRightHandle3;						// �E���
	int iTextureArrowRightHandle4;						// �E���
	int iTextureArrowRightHandle5;						// �E���
	bool bArrowFlg;										// ���t���O
	bool bArrowFlg2;									// ���t���O2
	bool bArrowFlg3;									// ���t���O3
	bool bArrowFlg4;									// ���t���O4
	bool bArrowFlg5;									// ���t���O5
};
