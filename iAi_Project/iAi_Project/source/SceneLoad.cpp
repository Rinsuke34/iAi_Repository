/* 2024.12.XX YYYY ZZZZ */

#include "SceneLoad.h"

/* �V�[���u���[�h�v�̒�` */

// �R���X�g���N�^
SceneLoad::SceneLoad() : SceneBase("Load", 9999, true)
{
	/* �e�X�g�p */
	this->iTestCount = 0;
}

// �f�X�g���N�^
SceneLoad::~SceneLoad()
{

}

// ������
void SceneLoad::Initialization()
{
	/* SceneBase�̏����������{(���\�[�X�����΍�) */
	SceneBase::Initialization();
}

// �v�Z
void SceneLoad::Process()
{
	/* ���[�h�X���b�h�������Ă��邩�m�F */
	if (gstLoadingFutures.empty())
	{
		// �X���b�h�������Ă��Ȃ��Ȃ��
		/* �V�[���폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;

		/* ���[�f�B���O�t���O�𖳌��ɂ��� */
		gbNowLoadingFlg = false;
		return;
	}

	/* ���[�f�B���O���������Ă��邩�m�F */
	for (auto load = gstLoadingFutures.begin(); load != gstLoadingFutures.end(); )
	{
		/* 100ms�ҋ@���� */
		auto status = load->wait_for(std::chrono::milliseconds(100));

		/* �Ώۂ̃X���b�h���������Ă��邩�m�F */
		if (status == std::future_status::ready)
		{
			// �X���b�h���������Ă���ꍇ
			/* �x�N�^�[����폜 */
			load = gstLoadingFutures.erase(load);
		}
		else
		{
			// �X���b�h���������Ă��Ȃ��ꍇ
			/* ���̃X���b�h���m�F */
			++load;
		}
	}

	/* �e�X�g�J�E���g */
	this->iTestCount++;

	/* ���[�f�B���O�t���O��L���ɂ��� */
	gbNowLoadingFlg = true;

	return;
}

// �`��
void SceneLoad::Draw()
{
	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "�Ȃ���[�ł���");
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "�J�E���g : %d", this->iTestCount);
}
