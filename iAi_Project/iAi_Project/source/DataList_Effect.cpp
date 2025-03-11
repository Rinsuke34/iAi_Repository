/* 2025.01.29 ��򕗏� �t�@�C���쐬 */

#include "DataList_Effect.h"

/* �G�t�F�N�g���\�[�X�Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_Effect::DataList_Effect() : DataListBase("DataList_Effect")
{
	/* map���N���A���� */
	pEffectList.clear();
}

// �f�X�g���N�^
DataList_Effect::~DataList_Effect()
{
	/* ���X�g���̃G�t�F�N�g�n���h�����폜 */
	for (const auto& pair : pEffectList)
	{
		/* �G�t�F�N�g���폜 */
		DeleteEffekseerEffect(pair.second);
	}

	/* map���N���A���� */
	pEffectList.clear();
}

// �G�t�F�N�g���[�h(���O�ǂݍ��ݗp)
void DataList_Effect::LoadEffect(std::string effectName)
{
	// ����
	// effectName	: �G�t�F�N�g��

	/* �G�t�F�N�g��ǂݍ��� */
	// �������͍s��Ȃ�

	/* �Ώۂ̃G�t�F�N�g�����݂��邩�m�F */
	if (bCheckEffect(effectName) == false)
	{
		// ���݂��Ȃ��ꍇ
		/* �G�t�F�N�g�̃t�@�C���p�X���擾 */
		std::string FileName = "resource/EffectData/" + effectName + ".efkefc";

		/* �G�t�F�N�g��ǂݍ��� */
		int iReturn = LoadEffekseerEffect(FileName.c_str());

		/* �G�t�F�N�g�����X�g�ɒǉ� */
		this->pEffectList[effectName] = iReturn;
	}

	return;
}

// �G�t�F�N�g�擾
int DataList_Effect::iGetEffect(std::string effectName)
{
	// ����
	// effectName	: �G�t�F�N�g��
	// �߂�l
	// int			: �G�t�F�N�g�n���h��(�����������̂�n��)

	int iReturn = 0;

	/* �G�t�F�N�g���擾���� */
	// �����łɂ���Ȃ畡���A�Ȃ��Ȃ�ǂݍ���

	/* �Ώۂ̃G�t�F�N�g�����݂��邩�m�F */
	if (bCheckEffect(effectName) == false)
	{
		// ���݂��Ȃ��ꍇ
		/* �G�t�F�N�g��ǂݍ��� */

		/* �G�t�F�N�g�̃t�@�C���p�X���擾 */
		std::string FileName = "resource/EffectData/" + effectName + ".efkefc";

		/* �G�t�F�N�g��ǂݍ��� */
		iReturn = LoadEffekseerEffect(FileName.c_str());

		/* �G�t�F�N�g�����X�g�ɒǉ� */
		this->pEffectList[effectName] = iReturn;

		/* �ǂݍ��񂾃G�t�F�N�g�𕡐� */
		iReturn = PlayEffekseer3DEffect(iReturn);
	}
	else
	{
		// ���݂��Ă���ꍇ
		/* �Ώ��̃G�t�F�N�g�𕡐� */
		iReturn = PlayEffekseer3DEffect(this->pEffectList[effectName]);
	}

	return iReturn;
}

// �G�t�F�N�g���\�[�X���݊m�F
bool DataList_Effect::bCheckEffect(std::string effectName)
{
	// ����
	// effectName	: �G�t�F�N�g��
	// �߂�l
	// bool			: �G�t�F�N�g���o�^����Ă��邩(true:�o�^����Ă��� / false:�o�^����Ă��Ȃ�)

	/* �Ώۂ̃G�t�F�N�g�����X�g�ɓo�^����Ă��邩�m�F */

	bool bReturn = false;

	/* �Ώۂ̃G�t�F�N�g���o�^����Ă��邩 */
	if (this->pEffectList.count(effectName) != 0)
	{
		// �o�^����Ă���ꍇ
		bReturn = true;
	}

	return bReturn;
}
