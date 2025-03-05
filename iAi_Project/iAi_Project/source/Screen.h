/* 2024.02.10 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_Image.h"

/* �I�u�W�F�N�g */
#include "PlatformBasic.h"
#include "EffectManualDelete.h"
#include "PlayerStatusDefine.h"
#include "GimmickDefine.h"

/*�V�[��*/
#include "SceneStage.h"
#include "SceneTitle.h"

/* �e�X�g�p�G�N���X */

// �����M�~�b�N�N���X
class Screen : public PlatformBasic
{
public:
	Screen();				// �R���X�g���N�^
	virtual ~Screen();		// �f�X�g���N�^

	virtual void	Update()			override;		// �X�V
	

private:

	//�֐�
	void	Process();				// �X�V


	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
	CharacterBase* pPlayer;			// �v���C���[

	// �e�N�X�`���n���h����ǉ�
	int textureTitleHandle;			// �^�C�g��
	int textureNewgameHandle;		// �j���[�Q�[��
	int textureContinueHandle;		// �R���e�B�j���[
	int textureDateHandle;			// �f�[�^
	int textureConfigHandle;		// �R���t�B�O
	int textureStageHandle;			// �X�e�[�W

	bool StartFlg;	//�X�^�[�g�t���O	
	bool bHomeFlg;	//�z�[���t���O

	int UICount;	//UI�̃J�E���g
protected:
};
