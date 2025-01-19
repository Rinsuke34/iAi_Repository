/* 2024.12.XX YYYY ZZZZ */

#include "SceneLoad.h"

/* �V�[���u���[�h�v�̒�` */

// �R���X�g���N�^
SceneLoad::SceneLoad() : SceneBase("Load", 9999, false)
{

}

// �f�X�g���N�^
SceneLoad::~SceneLoad()
{

}

// ������
void SceneLoad::Initialization()
{

}

// �v�Z
void SceneLoad::Process()
{
	/* �ʃX���b�h�ł̃��[�f�B���O���������s���ł��邩�m�F */
	size_t sLoadingSize			= gstLoadingThread.size();	// ���[�h��
	size_t sLoadCompleteSize	= 0;						// ���[�h������

	for (auto& Load : gstLoadingThread)
	{
		/* ���[�h���������Ă��邩 */
		if (Load.joinable() == true)
		{
			// �������Ă���ꍇ
			/* ���[�h�������𑝉� */
			sLoadCompleteSize++;
		}
	}

	/* ���[�h�����������[�h���Ɠ����ł��邩�m�F */
	if (sLoadingSize == sLoadCompleteSize)
	{
		// �������Ă���ꍇ
		/* ���ׂẴX���b�h���폜 */
		for (auto& Load : gstLoadingThread)
		{
			/* �X���b�h���폜 */
			Load.join();
		}

		/* ���[�h�f�[�^���N���A */
		gstLoadingThread.clear();

		/* �V�[���폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
	}

	return;
}

// �`��
void SceneLoad::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "�Ȃ���[�ł���");
}
