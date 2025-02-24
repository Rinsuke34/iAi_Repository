/* 2025.01.22 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include "GameStatusDefine.h"

/* ��ʃG�t�F�N�g */
#include "ScreenEffect_Base.h"

/* �Q�[����ԊǗ��N���X�̐錾 */

// �Q�[����ԊǗ��N���X
class DataList_GameStatus : public DataListBase
{
	public:
		DataList_GameStatus();				// �R���X�g���N�^
		virtual ~DataList_GameStatus() {};	// �f�X�g���N�^

		/* �f�[�^�擾 */
		// ���X�g
		std::vector<ScreenEffect_Base*>& GetScreenEffectList() { return this->pScreenEffectList; }		// ��ʃG�t�F�N�g���X�g�擾
		// �P��
		int		iGetGameStatus()	{ return this->iGameStatus; };	// �Q�[����Ԃ��擾
		int		iGetNowStageNo()	{ return this->iNowStageNo; };	// ���݂̃X�e�[�W�ԍ����擾
		int		iGetEndStageNo()	{ return this->iEndStageNo; };	// �ŏI�X�e�[�W�ԍ����擾
		bool	bGetGameSlowFlg()	{ return this->bGameSlowFlg; };	// �X���[���[�V�����t���O���擾		/*2025.02.05 �e�r�듹 �X���[���[�V�����Ɋւ���֐��ǉ� */

		/* �f�[�^�ݒ� */
		// ���X�g
		void	SetScreenEffect(ScreenEffect_Base* pScreenEffect)	{ pScreenEffectList.emplace_back(pScreenEffect); };			// �G�l�~�[�ǉ�
		// �P��
		void	SetGameStatus(int iGameStatus)		{ this->iGameStatus		= iGameStatus; };	// �Q�[����Ԃ�ݒ�
		void	SetNowStageNo(int iNowStageNo)		{ this->iNowStageNo		= iNowStageNo; };	// �Q�[����Ԃ�ݒ�
		void	SetEndStageNo(int iEndStageNo)		{ this->iEndStageNo		= iEndStageNo; };	// �ŏI�X�e�[�W�ԍ���ݒ�
		void	SetGameSlowFlg(bool bGameSlowFlg)	{ this->bGameSlowFlg	= bGameSlowFlg; };	// �X���[���[�V�����t���O��ݒ�		/*2025.02.05 �X���[���[�V�����Ɋւ���e�r�듹 �֐��ǉ� */

	private:
		/* �Ǘ�����f�[�^���X�g */
		std::vector<ScreenEffect_Base*>	pScreenEffectList;	// ��ʃG�t�F�N�g���X�g

		/* �Ǘ�����f�[�^ */
		int		iGameStatus;	// �Q�[�����
		int		iNowStageNo;	// ���݂̃X�e�[�W�ԍ�
		int		iEndStageNo;	// �ŏI�X�e�[�W�ԍ�
		bool	bGameSlowFlg;	// �X���[���[�V�����t���O		/*2025.02.05 �e�r�듹 �ϐ��ǉ� */
};
