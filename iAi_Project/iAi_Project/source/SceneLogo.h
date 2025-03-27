/* 2025.03.28 �t�@�C���ǉ� ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_Image.h"

/* �V�[���u���S�v�̐錾 */

// �V�[�� "���S"
class SceneLogo : public SceneBase
{
	public:
		SceneLogo();				// �R���X�g���N�^
		virtual ~SceneLogo() {};	// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �摜�n���h�� */
		int* piGrHandle_Logo_School;	// ���S�摜(�w�Z)
		int* piGrHandle_Logo_Team;		// ���S�摜(�`�[��)

		/* �ϐ� */
		int		iDrawFaze;		// �`�ʃt�F�C�Y(0:�w�Z���S, 1:�`�[�����S)
		int		iAlpha;			// �`�ʂ̃A���t�@�l
		bool	bFadeInFlg;		// �t�F�[�h�C������J�n���邩�̃t���O
};
