/* 2025.02.27 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[�� */
#include "SceneGame.h"

/* �f�[�^���X�g */
#include "DataList_Effect.h"

/* �V�[��"�Q�[��"�ǉ��Z�b�g�A�b�v�̐錾 */

// �V�[�� "�Q�[��"�ǉ��Z�b�g�A�b�v
// ���^�C�g�� �� �Q�[���ƑJ�ڂ��Ă��܂��ƈꕔ�f�[�^���X�g���폜���擾�ƂȂ��Ă��܂����߁A�΍��p�ɒǉ�
class SceneAddSceneGameSetup : public SceneBase
{
	public:
		SceneAddSceneGameSetup();				// �R���X�g���N�^
		virtual ~SceneAddSceneGameSetup()	{};	// �f�X�g���N�^

		void	Process()			override;	// �v�Z

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Effect*	EffectList;	// �G�t�F�N�g���X�g

		/* �֐� */
		void	PreloadAllEffects();	// �S�G�t�F�N�g�̎��O�ǂݍ���
};
