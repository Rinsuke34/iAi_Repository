/* 2025.02.06 ��򕗏� �t�@�C���쐬 */

#include "SkySqhereBasic.h"

/* ��{�X�J�C�X�t�B�A�N���X�̒�` */
// �R���X�g���N�^
SkySqhereBasic::SkySqhereBasic() : SkySqhereBase()
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
}

// �f�X�g���N�^
SkySqhereBasic::~SkySqhereBasic()
{

}

// �X�V
void SkySqhereBasic::Update()
{
	/* �v���C���[�̍��W�Ɉړ������� */
	// �������Č͂�Ȃ��悤�ɂ��邽�ߖ��t���[�����s
	this->vecPosition = this->ObjectList->GetCharacterPlayer()->vecGetPosition();
}
