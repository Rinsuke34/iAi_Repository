/* 2025.01.22 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include "GameStatusDefine.h"

/* �Q�[����ԊǗ��N���X�̐錾 */

// �Q�[����ԊǗ��N���X
class DataList_GameStatus : public DataListBase
{
	public:
		DataList_GameStatus();				// �R���X�g���N�^
		virtual ~DataList_GameStatus() {};	// �f�X�g���N�^

		/* �f�[�^�擾 */
		int		iGetGameStatus()	{ return this->iGameStatus; };	// �Q�[����Ԃ��擾
		int		iGetNowStageNo()	{ return this->iNowStageNo; };	// ���݂̃X�e�[�W�ԍ����擾
		int		iGetEndStageNo()	{ return this->iEndStageNo; };	// �ŏI�X�e�[�W�ԍ����擾

		/* �f�[�^�ݒ� */
		void	SetGameStatus(int iGameStatus)	{ this->iGameStatus = iGameStatus; };	// �Q�[����Ԃ�ݒ�
		void	SetNowStageNo(int iNowStageNo)	{ this->iNowStageNo = iNowStageNo; };	// �Q�[����Ԃ�ݒ�
		void	SetEndStageNo(int iEndStageNo)	{ this->iEndStageNo = iEndStageNo; };	// �ŏI�X�e�[�W�ԍ���ݒ�

	private:
		/* �Ǘ�����f�[�^ */
		int		iGameStatus;	// �Q�[�����
		int		iNowStageNo;	// ���݂̃X�e�[�W�ԍ�
		int		iEndStageNo;	// �ŏI�X�e�[�W�ԍ�

	protected:
};
