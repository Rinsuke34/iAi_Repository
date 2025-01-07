/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include <vector>
#include <map>

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* 3D���f���Ǘ��N���X�̐錾 */

// 3D���f���Ǘ��N���X
class DataList_Model : public DataListBase
{
	public:
		DataList_Model();				// �R���X�g���N�^
		virtual ~DataList_Model();		// �f�X�g���N�^

		void	JsonDataLoad();			// Json����f�[�^�����[�h"�����쐬"

		/* 3D���f���擾 */
		int		iGetModel(std::string modelName, ObjectBase* pSetObject);	// 3D���f���擾

	private:
		/* �Ǘ�����f�[�^ */
		// ���X�g
		std::map<std::string, ObjectBase*>		pModelHandleList;	// 3D���f�����X�g(�A�N�^�ƃv���b�g�t�H�[����Ώ�)

		/* �֐� */
		bool	bCheckModel(std::string modelName);			// 3D���f�����݊m�F

	protected:
};
