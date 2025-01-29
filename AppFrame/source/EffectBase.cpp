/* 2025.01.08 ��򕗏� �t�@�C���쐬 */

#include "EffectBase.h"

/* ���ׂẴG�t�F�N�g�̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
EffectBase::EffectBase() : ObjectBase()
{
	/* ������ */
	this->iEffectHandle_Resource	= -1;	// �G�t�F�N�g�n���h��(���\�[�X)
	this->iEffectHandle_Play		= -1;	// �G�t�F�N�g�n���h��(���s)
}

// �f�X�g���N�^
EffectBase::~EffectBase()
{
	/* �G�t�F�N�g�̃��\�[�X���폜 */
	// ���G�t�F�N�g�̓��\�[�X�𕡐����Ċ��p���邱�Ƃ��o���Ȃ��̂œs�x���\�[�X��ǂݍ���
	StopEffekseer3DEffect(this->iEffectHandle_Play);
	DeleteEffekseerEffect(this->iEffectHandle_Resource);
}

// �X�V
void EffectBase::Update()
{
	/* �G�t�F�N�g���W�X�V */
	Effect_PosUpdate();

	/* �G�t�F�N�g��]�ʍX�V */
	Effect_RotationUpdate();
}


// �`��
void EffectBase::Draw()
{
	/* �G�t�F�N�g��`�� */
	DrawEffekseer3D_Draw(this->iEffectHandle_Play);
}


// �G�t�F�N�g�ǂݍ���
void EffectBase::Effect_Load(std::string effectName)
{
	// ����
	// effectName	: �G�t�F�N�g��

	// �� �G�t�F�N�g�̃��\�[�X�ۊǏꏊ�͉��L�̒ʂ�
	// �`��		: efkfc�t�@�C��
	// �ۑ��ꏊ	: resource/EffectData/�G�t�F�N�g�t�@�C��
	// �� ���\�[�X��ǂݍ��񂾎��_�őΏۂ̃G�t�F�N�g�͕K���`�ʂ���Ă��܂����߁A3D���f���̂悤�Ƀ��\�[�X�𕡐����Ďg���񂷂��Ƃ͎d�l��s�B
	//    ���̂��߁A�G�t�F�N�g���Ƀ��\�[�X�ǂݍ��݁��폜���s���B

	/* �G�t�F�N�g�̃t�@�C���p�X���擾 */
	std::string FileName = "resource/EffectData/" + effectName + ".efkefc";

	/* �G�t�F�N�g��ǂݍ��� */
	this->iEffectHandle_Resource = LoadEffekseerEffect(FileName.c_str());
}

// �G�t�F�N�g�ʒu�X�V
void EffectBase::Effect_PosUpdate()
{
	/* �G�t�F�N�g�̕`�ʍ��W�����݂�vecPosition�ɐݒ� */
	SetPosPlayingEffekseer3DEffect(this->iEffectHandle_Play, this->vecPosition.x, this->vecPosition.y, this->vecPosition.z);
}

// �G�t�F�N�g��]�ʍX�V
void EffectBase::Effect_RotationUpdate()
{
	SetRotationPlayingEffekseer3DEffect(this->iEffectHandle_Play, this->vecRotation.x, this->vecRotation.y, this->vecRotation.z);
}
