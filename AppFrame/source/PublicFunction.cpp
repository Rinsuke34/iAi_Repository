/* 2025.03.25 ��򕗏� �t�@�C���쐬 */

#include "AppFunctionDefine.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdio>

/* �ėp�I�Ɏg�p�ł���@�\�̒�` */
// �w��t�@�C�������S�ɍ폜����܂őҋ@
void PUBLIC_FUNCTION::FileDeletesAndStand(const std::string& filename)
{
	// ����
	// filename	<- �폜����t�@�C����

	/* �폜�����t���O */
	bool bDeleteCompleteFlg = false;

	/* �w��t�@�C�����폜 */
	std::remove(filename.c_str());

	/* �t�@�C�����폜�����܂őҋ@ */
	while (bDeleteCompleteFlg == false)
	{
		/* �t�@�C�����J���邩�m�F */
		std::ifstream file(filename);
		if (file.is_open())
		{
			// �t�@�C�����J����ꍇ
			/* �ҋ@ */
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		else
		{
			// �t�@�C�����J���Ȃ��ꍇ
			/* �폜�����t���O�𗧂Ă� */
			bDeleteCompleteFlg = true;
		}
	}
}
