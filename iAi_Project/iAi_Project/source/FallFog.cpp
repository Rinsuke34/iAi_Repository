/* 2025.03.03 ��򕗏� �t�@�C���쐬 */

#include "FallFog.h"

/* ��(�����ʒu)�N���X�̒�` */
// �R���X�g���N�^
FallFog::FallFog() : PlatformBasic()
{
	/* �摜���\�[�X�擾 */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �� */
		this->piGrHandle_Fog = ImageList->piGetImage("Fog/Fog");
	}
}

// �`��
void FallFog::Draw()
{
	/* ���̉摜���r���{�[�h�Ƃ��ĕ`�ʂ��� */
	DrawBillboard3D(this->vecPosition, 0.5f, 0.5f, 650.0f, 0.f, *this->piGrHandle_Fog, TRUE);
}
