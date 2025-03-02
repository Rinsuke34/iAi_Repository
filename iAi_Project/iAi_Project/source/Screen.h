/* 2024.02.28 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "PlatformBasic.h"
#include "EffectManualDelete.h"
#include "PlayerStatusDefine.h"
#include "GimmickDefine.h"

/* �e�X�g�p�G�N���X */

// �X�N���[���N���X
class Screen : public PlatformBasic
{
public:
	Screen();				// �R���X�g���N�^
	virtual ~Screen();		// �f�X�g���N�^

	void	Update()			override;		// �X�V

	void			ScreenDraw();						// �`��
private:


	/* �g�p����f�[�^���X�g */
	DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�



	// �e�N�X�`���n���h����ǉ�
	int textureTitleHandle;

	int textureHomeHandle;


protected:
};
