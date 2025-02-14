/* 2025.02.12 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include <map>

/* �摜���\�[�X�Ǘ��N���X�̐錾 */

// �摜���\�[�X�Ǘ��N���X
class DataList_Image : public DataListBase
{
	public:
		DataList_Image();				// �R���X�g���N�^
		virtual ~DataList_Image();		// �f�X�g���N�^

		/* �摜���\�[�X�擾 */
		int*	piGetImage(std::string imageName);		// �摜�擾(�|�C���^�ŕԂ�)

	private:
		/* �Ǘ�����f�[�^ */
		// ���X�g
		std::map<std::string, int>	pImageList;			// �摜���\�[�X���X�g

		/* �֐� */
		bool	bCheckImage(std::string imageName);		// �摜���\�[�X���݊m�F
};
