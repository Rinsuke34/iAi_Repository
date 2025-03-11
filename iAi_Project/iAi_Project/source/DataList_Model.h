/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include <map>

/* 3D���f���Ǘ��N���X�̐錾 */

// 3D���f���Ǘ��N���X
class DataList_Model : public DataListBase
{
	public:
		DataList_Model();				// �R���X�g���N�^
		virtual ~DataList_Model();		// �f�X�g���N�^

		/* 3D���f���擾 */
		void	LoadModel(std::string modelName);			// 3D���f�����[�h(���O�ǂݍ��ݗp)
		int		iGetModel(std::string modelName);			// 3D���f���擾

	private:
		/* �Ǘ�����f�[�^ */
		// ���X�g
		std::map<std::string, int>	pModelHandleList;	// 3D���f�����X�g

		/* �֐� */
		bool	bCheckModel(std::string modelName);			// 3D���f�����݊m�F

	protected:
};
