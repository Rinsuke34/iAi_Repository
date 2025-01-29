/* 2025.01.24 ��򕗏� �t�@�C���쐬 */

#include "BulletPlayerMeleeWeak.h"

/* �ߐڍU��(��)�N���X�̒�` */

// �R���X�g���N�^
BulletPlayerMeleeWeak::BulletPlayerMeleeWeak() : BulletBase()
{
	/* ������ */
	this->iObjectType	= OBJECT_TYPE_BULLET_PLAYER;	// �I�u�W�F�N�g�̎�ނ�"�e(�v���C���[)"�ɐݒ�
	this->pEffect		= nullptr;

	/* ���ǉ� */
	iDeleteCount = 30;
}

// �f�X�g���N�^
BulletPlayerMeleeWeak::~BulletPlayerMeleeWeak()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
	this->pEffect->SetDeleteFlg(true);
}

// ������
void BulletPlayerMeleeWeak::Initialization()
{
	/* �����蔻��ݒ� */
	{
		this->stCollisionSqhere.vecSqhere		= this->vecPosition;
		this->stCollisionSqhere.fSqhereRadius	= 100.0f;
	}

	/* �G�t�F�N�g�ǉ� */
	{
		/* �ߐڍU��(��)�̃G�t�F�N�g�𐶐� */
		this->pEffect = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_slash/FX_slash")));
		//this->pEffect->Effect_Load("FX_slash/FX_slash");

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->pEffect->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pEffect->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̏����� */
		this->pEffect->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->pEffect);
		}
	}
}

// �X�V
void BulletPlayerMeleeWeak::Update()
{
	/* ������ */
	// �{���̓v���C���[���ō폜�t���O��ݒ肷��\��
	if (iDeleteCount > 0)
	{
		iDeleteCount--;
	}
	else
	{
		this->bDeleteFlg = true;
	}
}
