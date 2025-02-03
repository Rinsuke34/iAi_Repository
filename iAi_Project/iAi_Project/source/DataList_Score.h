/* 2025.01.30 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "ScoreDefine.h"

/* �X�R�A�֘A�Ǘ��f�[�^���X�g�̐錾 */

// �X�R�A�֘A�Ǘ��f�[�^���X�g
class DataList_Score : public DataListBase
{
	public:
		DataList_Score();				// �R���X�g���N�^
		virtual ~DataList_Score();		// �f�X�g���N�^

		int		iGetPlayerComboNowCount() { return this->iPlayerComboNowCount; }				// �v���C���[�̌��݂̃R���{�����擾
		int		iGetPlayerComboMaxCount() { return this->iPlayerComboMaxCount; }				// �v���C���[�̍ő�R���{�����擾
		int		iGetPlayerComboDuration() { return this->iPlayerComboDuration; }				// �v���C���[�̃R���{�̎c�莝�����Ԃ��擾

		void	SetPlayerComboNowCount(int iPlayerComboNowCount) { this->iPlayerComboNowCount = iPlayerComboNowCount; }				// �v���C���[�̌��݂̃R���{����ݒ�
		void	SetPlayerComboMaxCount(int iPlayerComboMaxCount) { this->iPlayerComboMaxCount = iPlayerComboMaxCount; }				// �v���C���[�̍ő�R���{����ݒ�
		void	SetPlayerComboDuration(int iPlayerComboDuration) { this->iPlayerComboDuration = iPlayerComboDuration; }				// �v���C���[�̃R���{�̎c�莝�����Ԃ�ݒ�

	private:
		/* �ϐ� */
		int		iPlayerComboNowCount;			// �v���C���[�̌��݂̃R���{��
		int		iPlayerComboMaxCount;			// �v���C���[�̍ő�R���{��
		int		iPlayerComboDuration;			// �v���C���[�̃R���{�̎c�莝������

};
