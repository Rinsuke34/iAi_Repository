/* 2025.02.06 ��򕗏� �t�@�C���쐬 */

#include "SkySqhereBasic.h"

/* ��{�X�J�C�X�t�B�A�N���X�̒�` */
// �R���X�g���N�^
SkySqhereBasic::SkySqhereBasic() : SkySqhereBase()
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}
}

// �f�X�g���N�^
SkySqhereBasic::~SkySqhereBasic()
{

}

// �X�V
void SkySqhereBasic::Update()
{
	/* �J�����̒����_�Ɉړ������� */
	this->vecPosition = this->StageStatusList->vecGetCameraTarget();
}
