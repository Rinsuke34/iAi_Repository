/* 2025.03.05 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[�� */
#include "SceneTitle.h"

/* �V�[��"�^�C�g��"�ǉ��Z�b�g�A�b�v�̐錾 */

// �V�[�� "�^�C�g��"�ǉ��Z�b�g�A�b�v
// ���Q�[�� �� �^�C�g���ƑJ�ڂ��Ă��܂��ƈꕔ�f�[�^���X�g���폜���擾�ƂȂ��Ă��܂����߁A�΍��p�ɒǉ�
class SceneAddTitleSetup : public SceneBase
{
	public:
		SceneAddTitleSetup();				// �R���X�g���N�^
		virtual ~SceneAddTitleSetup() {};	// �f�X�g���N�^

		void	Process()			override;	// �v�Z
};
