/* 2025.03.05 ��򕗏� �t�@�C���쐬 */

#include "DataList_Option.h"

/* �I�v�V�����ݒ�Ǘ��N���X�̒�` */
// �R���X�g���N�^
DataList_Option::DataList_Option() : DataListBase("DataList_Option")
{
	/* ������(��) */
	abCameraInversion[0][0] = false;
	abCameraInversion[0][1] = false;
	abCameraInversion[1][0] = false;
	abCameraInversion[1][1] = false;

	afCameraSensitivity[0][0] = 1.f;
	afCameraSensitivity[0][1] = 0.5f;
	afCameraSensitivity[1][0] = 1.f;
	afCameraSensitivity[1][1] = 0.5f;
}
