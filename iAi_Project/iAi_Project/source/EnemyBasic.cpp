/* 2025.01.27 ��򕗏� �t�@�C���쐬 */

#include "EnemyBasic.h"

/* ��{�G�l�~�[�N���X�̒�` */

// �R���X�g���N�^
EnemyBasic::EnemyBasic() : EnemyBase()
{
	/* ������ */
	this->iPlayerLockOnType	= PLAYER_LOCKON_NONE;	// ���b�N�I������Ă��Ȃ���Ԃɂ���
	this->iCoreFrameNo		= -1;					// �R�A�t���[���ԍ���������
}

// �f�X�g���N�^
EnemyBasic::~EnemyBasic()
{
	/* �v���C���[�̃R���{�����Z���p�����ԃ��Z�b�g */
	{
		/* �f�[�^���X�g�擾 */
		DataList_Score* ScoreList = dynamic_cast<DataList_Score*>(gpDataListServer->GetDataList("DataList_Score"));

		/* �v���C���[�̃R���{�����Z */
		ScoreList->SetPlayerComboNowCount(ScoreList->iGetPlayerComboNowCount() + 1);

		/* �v���C���[�̃R���{�p�����ԃ��Z�b�g */
		ScoreList->SetPlayerComboDuration(PLAYER_COMBO_DURATION);
	}
}

// �R�A�t���[���ԍ��擾
void EnemyBasic::LoadCoreFrameNo()
{
	/* �R�A�t���[���ԍ����擾 */
	this->iCoreFrameNo = MV1SearchFrame(this->iModelHandle, "Core");
}
