/* 2025.01.29 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include <map>

/* �G�t�F�N�g���\�[�X�Ǘ��N���X�̐錾 */

// �G�t�F�N�g���\�[�X�Ǘ��N���X
class DataList_Effect : public DataListBase
{
	public:
		DataList_Effect();				// �R���X�g���N�^
		virtual ~DataList_Effect();		// �f�X�g���N�^

		/* �G�t�F�N�g���\�[�X�擾 */
		int		iGetEffect(std::string effectName);			// �G�t�F�N�g�擾

	private:
		/* �Ǘ�����f�[�^ */
		// ���X�g
		std::map<std::string, int>	pEffectList;	// �G�t�F�N�g���\�[�X���X�g

		/* �֐� */
		bool	bCheckEffect(std::string effectName);			// �G�t�F�N�g���\�[�X���݊m�F

	protected:
};
