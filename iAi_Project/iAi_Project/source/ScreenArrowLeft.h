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

// �Q�[���������X�N���[���N���X
class ScreenArrowLeft : public PlatformBase
{
public:
	ScreenArrowLeft();				// �R���X�g���N�^
	virtual ~ScreenArrowLeft();		// �f�X�g���N�^

	virtual void	Update()			override;		// �X�V

private:
	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;						// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;								// �v���C���[

	/* �֐� */
	void	Process();									// �X�V
	void	Draw();										// �`��

	/* �ϐ� */
	int iFirstCount;									//�ŏ��̃J�E���g
	int iSecondCount;									//���ڂ̃J�E���g
	int iThirdCount;									//�O��ڂ̃J�E���g
	int iFourthCount;									//�l��ڂ̃J�E���g
	int iFifthCount;									//�܉�ڂ̃J�E���g
	int iUICount;										//UI�̃J�E���g
	int iTextureArrowLeftHandle1;						// �����
	int iTextureArrowLeftHandle2;						// �����
	int iTextureArrowLeftHandle3;						// �����
	int iTextureArrowLeftHandle4;						// �����
	int iTextureArrowLeftHandle5;						// �����
	bool bArrowFlg;										//���t���O
	bool bArrowFlg2;									//���t���O2
	bool bArrowFlg3;									//���t���O3
	bool bArrowFlg4;									//���t���O4
	bool bArrowFlg5;									//���t���O5
};
