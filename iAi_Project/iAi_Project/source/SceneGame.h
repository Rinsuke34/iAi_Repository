/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �f�[�^���X�g */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* �I�u�W�F�N�g */
#include "CharacterPlayer.h"

/* �V�[�� */


/* �V�[���u�Q�[���v�̐錾 */

// �V�[�� "�Q�[�����"
class SceneGame : public SceneBase
{
	public:
		SceneGame();							// �R���X�g���N�^
		virtual ~SceneGame();					// �f�X�g���N�^

		void	Process()	override;			// �v�Z
		void	Draw()		override;			// �`��

	private:
		/* �g�p����f�[�^���X�g */
		// ����f�[�^���X�g�T�[�o�[����擾����͔̂�����Ȃ��߁A�����ŕۑ����Ă���
		DataList_Object* ObjectList;				// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus* PlayerStatusList;	// �v���C���[��ԊǗ�

		/* �֐� */
		void	LoadMapData();						// �}�b�v�f�[�^�̃��[�h
		void	SetCamera();						// �J�����ݒ�

		/* �J�����֘A */
		void	SetCamera_Free();					// �J�����ݒ�(�t���[���[�h)

	protected:
};
