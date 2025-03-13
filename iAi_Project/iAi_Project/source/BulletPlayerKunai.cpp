/* 2025.02.14 �e�r�듹 �t�@�C���쐬 */

#include "BulletPlayerKunai.h"

/* �N�i�C�N���X�̒�` */

// �R���X�g���N�^
BulletPlayerKunai::BulletPlayerKunai() : BulletBase()
{
	/* ������ */
	this->iObjectType					= OBJECT_TYPE_BULLET_PLAYER;		// �I�u�W�F�N�g�̎�ނ�"�e(�v���C���[)"�ɐݒ�
	this->vecKunaiTargetPosition		= VGet(0,0,0);						// �^�[�Q�b�g���W
	this->vecKunaiMoveDirection			= VGet(0, 0, 0);					// �N�i�C�̈ړ��������
	this->fKunaiTargetDistance			= 0.0f;								// �N�i�C�̔��˒n�_����^�[�Q�b�g�܂ł̋���
	this->fKunaiMoveDistance			= 0.0f;								// �N�i�C�̈ړ�����
	this->fKunaiAngleX					= 0.0f;								// �N�i�C��X����]�p�x
	this->fKunaiAngleY					= 0.0f;								// �N�i�C��Y����]�p�x
	this->iKunaiDeleteCount				= KUNAI_ATTACK_COUNT;				// �N�i�C�̍폜�J�E���g(�U������)
	this->bKunaiAttackFlg				= false;							// �N�i�C�̍U���t���O

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Bullet/Kunai_0218");
	}

	/* �f�[�^���X�g�擾 */
	{
		/* "���͊Ǘ�"���擾 */
		this->InputList = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));

		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
		
		/* "�v���C���[��ԊǗ�"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�X�e�[�W��ԊǗ�"���Ǘ� */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}
}

// �f�X�g���N�^
BulletPlayerKunai::~BulletPlayerKunai()
{
	
}

// ������
void BulletPlayerKunai::Initialization()
{

}

// �`��
void BulletPlayerKunai::Draw()
{
	
}

// �X�V
void BulletPlayerKunai::Update()
{
	
}

//void BulletPlayerKunai::Move()
//{
//	/* �^�[�Q�b�g�G�l�~�[�����݂��邩�m�F */
//	if (this->pTargetEnemy != nullptr)
//	{
//		// �^�[�Q�b�g�G�l�~�[�����݂���ꍇ
//		//�G�̌��Ƀ��[�v���A���j����
//		/* �N�i�C�̍��W���^�[�Q�b�g���W�ɌŒ� */
//		this->vecPosition = pTargetEnemy->vecGetPosition();
//
//		/* ���f�����\���ɐݒ� */
//		MV1SetVisible(this->iModelHandle, false);
//
//		/* �N�i�C�̍U���t���O�������Ă��Ȃ����m�F */
//		if (this->bKunaiAttackFlg == false)
//		{
//			/* �G�l�~�[�̊p�x����Y���̉�]�s������߂� */
//			MATRIX matEnemyrRotation = MGetRotY((pTargetEnemy->vecGetRotation().y));
//
//			/* �G�l�~�[�̌����̃x�N�g�� */
//			VECTOR vecEnemyDirection = VGet(0, 0, 1);
//
//			/* �s����x�N�g���ɕϊ� */
//			vecEnemyDirection = VTransform(vecEnemyDirection, matEnemyrRotation);
//
//			/* �G�l�~�[�̌����𐳋K�� */
//			vecEnemyDirection = VNorm(vecEnemyDirection);
//
//			/* �G�l�~�[�̌����̊p�x(���W�A��)���擾 */
//			float fEnemyRotate = -atan2f(vecEnemyDirection.x, vecEnemyDirection.z);
//
//			/* �v���C���[�̌�����G�Ƌt�ɐݒ� */
//			this->PlayerStatusList->SetPlayerAngleX(fEnemyRotate - PI);
//
//			/* �v���C���[�̃��[�v�ʒu��G�̌��ɐݒ� */
//			VECTOR vecPlayerWarpPotition = VScale(vecEnemyDirection, 250);
//			vecPlayerWarpPotition = VAdd(pTargetEnemy->vecGetPosition(), vecPlayerWarpPotition);
//
//			/* �v���C���[�̍��W�����[�v�ʒu�ɐݒ� */
//			this->ObjectList->GetCharacterPlayer()->SetPosition(vecPlayerWarpPotition);
//
//			/* �v���C���[�̍U����Ԃ��擾 */
//			int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();
//
//			/* �v���C���[�̍U����Ԃ��������U���\����Ԃł��邩�m�F */
//			if (iPlayerAttackState == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
//			{
//				// �������U���\����Ԃł���ꍇ
//				/* �������U���\����Ԃ��L�����Z������ */
//				this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
//			}
//
//			/* �v���C���[�̏�Ԃ�"���R���"�ɑJ�� */
//			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
//
//			/* �v���C���[�̃��[�V������"�ߋ����U��(��)(�I��)"�ɕύX */
//			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG_END);
//
//			
//			/* �����蔻��ݒ� */
//			{
//				/* �G�̈ʒu�ɓ����蔻���ݒ� */
//				this->stCollisionSqhere.vecSqhere = pTargetEnemy->vecGetPosition();
//
//				/* �����蔻��̔��a��ݒ� */
//				this->stCollisionSqhere.fSqhereRadius = 50;
//			}
//
//			/* �N�i�C�̍U���t���O��ݒ� */
//			this->bKunaiAttackFlg = true;
//			
//		}		
//	}
//	else
//	{
//		// �^�[�Q�b�g�G�l�~�[�����݂���ꍇ
//		// �^�[�Q�b�g���W�Ƀ��[�v����
//		/* �N�i�C�̍��W���^�[�Q�b�g���W�ɌŒ� */
//		this->vecPosition = this->vecKunaiTargetPosition;
//
//		/* �v���C���[���N�i�C�̍��W�Ɉړ� */
//		this->ObjectList->GetCharacterPlayer()->SetPosition(this->vecPosition);
//
//		/* �v���C���[�̍U����Ԃ��擾 */
//		int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();
//
//		/* �v���C���[�̍U����Ԃ��������U���\����Ԃł��邩�m�F */
//		if (iPlayerAttackState == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
//		{
//			// �������U���\����Ԃł���ꍇ
//			/* �v���C���[�̏�Ԃ�"���R���"�ɑJ�� */
//			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
//
//			/* �v���C���[�̃��[�V�����𖳂��ɐݒ� */
//			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
//
//			/* �������U���\����Ԃ��L�����Z������ */
//			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
//		}
//
//		/* �N�i�C�̍폜�t���O��ݒ� */
//		this->bDeleteFlg = true;
//	}
//	
//	/* �N�i�C�̍U���t���O�������Ă��邩�m�F */
//	if (this->bKunaiAttackFlg == true)
//	{
//		// �N�i�C�̍U���t���O�������Ă���ꍇ
//		// �N�i�C�̍폜����
//		/* �N�i�C�̍폜�J�E���g(�U������)���c���Ă����ꍇ */
//		if (iKunaiDeleteCount > 0)
//		{
//			/* �N�i�C�̍폜�J�E���g(�U������)�����Z */
//			iKunaiDeleteCount--;
//		}
//		/* �N�i�C�̍폜�J�E���g(�U������)��0�ɂȂ����ꍇ */
//		else
//		{
//			/* �N�i�C�̍폜�t���O��ݒ� */
//			this->bDeleteFlg = true;
//		}	
//	}
//}
