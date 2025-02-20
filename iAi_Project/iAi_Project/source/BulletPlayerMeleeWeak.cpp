/* 2025.01.24 ��򕗏� �t�@�C���쐬 */
/* 2025.02.20 �e�r�듹 �ߐڍU��(��)�����ǉ��E�C�� */

#include "BulletPlayerMeleeWeak.h"

/* �ߐڍU��(��)�N���X�̒�` */

// �R���X�g���N�^
BulletPlayerMeleeWeak::BulletPlayerMeleeWeak() : BulletBase()
{
	/* "�v���C���[���"���擾 */
	this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* �v���C���[�擾 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();

	/* ������ */
	this->iObjectType	= OBJECT_TYPE_BULLET_PLAYER;	// �I�u�W�F�N�g�̎�ނ�"�e(�v���C���[)"�ɐݒ�
	this->pMeleeWeakEffect = nullptr;						// �ߐڍU��(��)�G�t�F�N�g�̃n���h��
	ArrengementPositionPlayerFront();						// ���W�ݒ�(�v���C���[�̑O���ɐݒ�)

	/* ���ǉ� */
	iDeleteCount = 30;
}

// �f�X�g���N�^
BulletPlayerMeleeWeak::~BulletPlayerMeleeWeak()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
	this->pMeleeWeakEffect->SetDeleteFlg(true);
}

/* 2025.02.20 �e�r�듹 �ߐڍU��(��)�����C�� �J�n */
// ������
void BulletPlayerMeleeWeak::Initialization()
{
	/* �����蔻��ݒ� */
	{
		/* �����蔻��̈ʒu��ݒ� */
		this->stCollisionSqhere.vecSqhere		= this->vecPosition;
		/* �����蔻��͈̔͂�ݒ� */
		this->stCollisionSqhere.fSqhereRadius	= PLAYER_MELEE_WEAK_RADIUS;
	}

	/* �G�t�F�N�g�ǉ� */
	{
		/* �ߐڍU��(��)�̃G�t�F�N�g�𐶐� */
		this->pMeleeWeakEffect = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pMeleeWeakEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_slash/FX_slash")));

		/* �G�t�F�N�g�̍��W�ݒ�(�v���C���[�̍��W�ɐݒ�) */
		this->pMeleeWeakEffect->SetPosition(VGet(this->pCharacterPlayer->vecGetPosition().x, this->pCharacterPlayer->vecGetPosition().y + PLAYER_HEIGHT / 2,this->pCharacterPlayer->vecGetPosition().z));

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pMeleeWeakEffect->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̏����� */
		this->pMeleeWeakEffect->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->pMeleeWeakEffect);
		}
	}
}
/* 2025.02.20 �e�r�듹 �ߐڍU��(��)�����C�� �I�� */

/* 2025.02.20 �e�r�듹 �ߐڍU��(��)�����C�� �J�n */
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

	/* ���W�X�V(�v���C���[�̑O���ɐݒ�) */ 
	ArrengementPositionPlayerFront();
	
	/* �G�t�F�N�g�̍��W���X�V(�v���C���[�̍��W�ɐݒ�) */
	this->pMeleeWeakEffect->SetPosition((VGet(this->pCharacterPlayer->vecGetPosition().x, this->pCharacterPlayer->vecGetPosition().y + PLAYER_HEIGHT / 2, this->pCharacterPlayer->vecGetPosition().z)));

	/* �G�t�F�N�g�̉�]�ʐݒ�(�v���C���[�̌����ɐݒ�) */
	this->pMeleeWeakEffect->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* �����蔻��̈ʒu���X�V */
	this->stCollisionSqhere.vecSqhere = this->vecPosition;
}
/* 2025.02.20 �e�r�듹 �ߐڍU��(��)�����C�� �I�� */

/* 2025.02.20 �e�r�듹 �ߐڍU��(��)�����ǉ� �J�n */
// �o���b�g�̈ʒu���v���C���[�̑O���ɐݒ肷��
void BulletPlayerMeleeWeak::ArrengementPositionPlayerFront()
{
	/* �v���C���[���f���̏����̌�����Z���ɑ΂��ă}�C�i�X�����������Ă���Ƃ��� */
	VECTOR vecMeleeWeakVector = { 0,0,-1 };
	
	/* �v���C���[�̊p�x����Y���̉�]�s������߂� */
	MATRIX matPlayerRotation = MGetRotY(-(this->PlayerStatusList->fGetPlayerAngleX()));
	
	/* �v���C���[�̑O�̈ʒu�x�N�g�������߂� */
	vecMeleeWeakVector = VTransform(vecMeleeWeakVector, matPlayerRotation);
	vecMeleeWeakVector = VNorm(vecMeleeWeakVector);
	vecMeleeWeakVector = VScale(vecMeleeWeakVector, PLAYER_MELEE_WEAK_DISTANCE);
	vecMeleeWeakVector.y = PLAYER_HEIGHT / 2;
	
	/* �o���b�g���W��ݒ� */
	this->vecPosition = VAdd(this->pCharacterPlayer->vecGetPosition(), vecMeleeWeakVector);
}
/* 2025.02.20 �e�r�듹 �ߐڍU��(��)�����ǉ� �J�n */
