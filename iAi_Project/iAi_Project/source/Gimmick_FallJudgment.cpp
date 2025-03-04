/* 2025.03.04 ��򕗏� �t�@�C���쐬 */

#include "Gimmick_FallJudgment.h"

/* ��������N���X�̒�` */
// �R���X�g���N�^
Gimmick_FallJudgment::Gimmick_FallJudgment() : PlatformBasic()
{
	/* �f�[�^���X�g���擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�v���C���[��ԊǗ�"���擾 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}
}

// �X�V
void Gimmick_FallJudgment::Update()
{
	/* �v���C���[�ƐڐG���Ă��邩�m�F */
	if (this->ObjectList->GetCharacterPlayer()->HitCheck(this->iModelHandle, this->iCollisionFrameNo))
	{
		// �ڐG���Ă���ꍇ
		/* �v���C���[�̗��������L���ɂ��� */
		this->PlayerStatusList->SetFallFlg(true);
	}
}
