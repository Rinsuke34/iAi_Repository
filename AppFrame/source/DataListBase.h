/* 2024.12.12 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <string>

/* ���ׂẴf�[�^���䏈���̃x�[�X�ƂȂ�N���X�̐錾 */

// �f�[�^���X�g�x�[�X�N���X
class DataListBase
{
	public:
		DataListBase(const std::string& cName);		// �R���X�g���N�^
		virtual ~DataListBase() {};					// �f�X�g���N�^

		std::string	stGetSceneName()	{ return this->stDataListName; }	// �f�[�^���X�g���̂��擾

	private:
	protected:

		/* �ϐ� */
		// DataListServer�ł̊Ǘ��p�f�[�^
		std::string		stDataListName;			// �f�[�^���X�g����
};
