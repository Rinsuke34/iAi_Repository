/* 2025.03.22 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"

/* �f�[�^���X�g */
#include "DataList_Image.h"
#include "DataList_StageStatus.h"

/* UI(����)�N���X�̐錾 */

// UI(����)�N���X
class SceneUi_Time : public SceneBase
{
	public:
		SceneUi_Time();					// �R���X�g���N�^
		virtual ~SceneUi_Time() {};		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus*	StageStatusList;	// �X�e�[�W��ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_Text_Frame;					// �e�L�X�g�t���[��

		/* �ϐ� */
		int iTimeMinute;			// ���݂̌o�ߎ���(��)
		int iTimeSecond;			// ���݂̌o�ߎ���(�b)
		int iTimeFractionalSecond;	// ���݂̌o�ߎ���(�����b)
};
