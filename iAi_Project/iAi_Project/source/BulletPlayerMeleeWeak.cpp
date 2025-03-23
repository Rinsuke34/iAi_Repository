/* 2025.01.24 ��򕗏� �t�@�C���쐬 */
/* 2025.02.20 �e�r�듹 �ߐڍU��(��)�����ǉ��E�C�� */
/* 2025.03.13 ��򕗏� �e�p���B�쐬 */

#include "BulletPlayerMeleeWeak.h"

/* �ߐڍU��(��)�N���X�̒�` */

// �R���X�g���N�^
BulletPlayerMeleeWeak::BulletPlayerMeleeWeak() : BulletBase()
{
	/* "�v���C���[���"���擾 */
	this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* "�I�u�W�F�N�g�Ǘ�"���擾 */
	this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* "�G�t�F�N�g�Ǘ�"���擾 */
	this->EffectList = dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));

	/* �v���C���[�擾 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();

	/* ������ */
	this->iObjectType		= OBJECT_TYPE_MELEE_PLAYER;	// �I�u�W�F�N�g�̎�ނ�"�ߐڍU��(�v���C���[)"�ɐݒ�
	this->pMeleeWeakEffect	= nullptr;						// �ߐڍU��(��)�G�t�F�N�g�̃n���h��
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
/* 2025.03.13 ��򕗏� �e�p���B�쐬			�J�n */
// �X�V
void BulletPlayerMeleeWeak::Update()
{
	/* �e�p���B���� */
	for (auto& bullet : this->ObjectList->GetBulletList())
	{
		/* �p���B�t���O���L���ł��邩�m�F */
		if (bullet->bGetParryFlg() == true)
		{
			// �p���B�t���O���L���ł���ꍇ
			/* �ڐG���Ă��邩�m�F */
			if (bullet->HitCheck(this->stCollisionSqhere) == true)
			{
				// �ڐG���Ă���ꍇ
				/* �J�E���^�[�t���O���L���ł��邩�m�F */
				if (this->PlayerStatusList->bGetAddCounter() == true)
				{
					// �L���ł���ꍇ
					/* �p���B�t���O�𖳌��ɐݒ� */
					bullet->SetParryFlg(false);

					/* �I�u�W�F�N�g�^�C�v��e(�v���C���[)�ɕύX */
					bullet->SetObjectType(OBJECT_TYPE_BULLET_PLAYER);

					/* �ΏۃI�u�W�F�N�g�̈ړ��������擾 */
					VECTOR vecMoveDirection = bullet->vecGetMoveDirection();

					/* �ړ������𔽓] */
					vecMoveDirection = VScale(vecMoveDirection, -1);

					/* �ړ�������ݒ� */
					bullet->SetDirection(vecMoveDirection);

					/* �_���[�W�������G�t�F�N�g��`�� */
					{
						/* ��_���[�W�̏u�Ԃɔ�������G�t�F�N�g��ǉ� */
						EffectSelfDelete* pDamageEffect = new EffectSelfDelete();

						/* ���W��ݒ� */
						pDamageEffect->SetPosition(this->vecPosition);

						/* �G�t�F�N�g���擾 */
						pDamageEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_damaged/FX_damaged"));

						/* �g�嗦��ݒ� */
						pDamageEffect->SetScale(VGet(1.f, 1.f, 1.f));

						/* �폜�J�E���g��ݒ� */
						pDamageEffect->SetDeleteCount(60);

						/* �G�t�F�N�g���������� */
						pDamageEffect->Initialization();

						/* �I�u�W�F�N�g���X�g�ɓo�^ */
						this->ObjectList->SetEffect(pDamageEffect);
					}

					/* �U���q�b�g��SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_SLASH_HIT);
				}
				else
				{
					// �����ł���ꍇ
					/* �폜�t���O��L���ɂ��� */
					bullet->SetDeleteFlg(true);

					/* �U���z����SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_ABSORB);
				}
			}
		}
	}

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
/* 2025.03.13 ��򕗏� �e�p���B�쐬			�I��*/

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
