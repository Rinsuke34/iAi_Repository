/* 2025.01.22 ��򕗏� �t�@�C���쐬 */

#include "DataList_GameStatus.h"

/* �Q�[����ԊǗ��N���X�̒�` */

// �R���X�g���N�^
DataList_GameStatus::DataList_GameStatus() : DataListBase("DataList_GameStatus")
{
	/* ������ */
	{
		this->iGameStatus	= GAMESTATUS_PLAY_GAME;
		this->iNowStageNo	= 0;
		this->iEndStageNo	= 0;
	}
}
