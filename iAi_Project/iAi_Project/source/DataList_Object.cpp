/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "DataList_Object.h"

/* �I�u�W�F�N�g�Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_Object::DataList_Object() : DataListBase("DataList_Object")
{
	/* ������ */
	// �v���C���[
	this->pCharacterPlayer	=	nullptr;

	// �G�l�~�[
	this->pEnemyList.clear();
	
	// �e
	this->pBulletList.clear();

	// �G�t�F�N�g
	this->pEffectList.clear();

	// �v���b�g�t�H�[��
	this->pPlatformList.clear();
}

// �f�X�g���N�^
DataList_Object::~DataList_Object()
{
	/* ��� */
	// ���X�g��vector�̂��߁A������������
	this->pCharacterPlayer	=	nullptr;
}

/* ���X�g���I�u�W�F�N�g������ */
// �S�I�u�W�F�N�g������
void DataList_Object::InitializationAll()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̏����� */
	InitializationPlayer();
	InitializationEnemy();
	InitializationEffect();
	InitializationBullet();
	InitializationPlatform();
}

// �v���C���[������
void DataList_Object::InitializationPlayer()
{
	/* �v���C���[�̏��������Ă� */
	this->pCharacterPlayer->Initialization();
}

// �G�l�~�[������
void DataList_Object::InitializationEnemy()
{
	/* ���ׂẴG�l�~�[�̏��������Ă� */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->Initialization();
	}
}

// �G�t�F�N�g������
void DataList_Object::InitializationEffect()
{
	/* ���ׂẴG�t�F�N�g�̏��������Ă� */
	for (auto& pEffect : this->pEffectList)
	{
		pEffect->Initialization();
	}
}

// �e������
void DataList_Object::InitializationBullet()
{
	/* ���ׂĂ̒e�̏��������Ă� */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->Initialization();
	}
}

// �v���b�g�t�H�[��������
void DataList_Object::InitializationPlatform()
{
	/* �ғ��v���b�g�t�H�[���̏��������Ă� */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->Initialization();
	}
}

/* ���X�g���I�u�W�F�N�g�X�V */
// �S�I�u�W�F�N�g�X�V
void DataList_Object::UpdateAll()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̍X�V */
	UpdatePlayer();
	UpdateEnemy();
	UpdateEffect();
	UpdateBullet();
	UpdatePlatform();
}

// �v���C���[�X�V
void DataList_Object::UpdatePlayer()
{
	/* �v���C���[�̍X�V���Ă� */
	this->pCharacterPlayer->Update();
}

// �G�l�~�[�X�V
void DataList_Object::UpdateEnemy()
{
	/* ���ׂẴG�l�~�[�̍X�V���Ă� */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->Update();
	}
}

// �G�t�F�N�g�X�V
void DataList_Object::UpdateEffect()
{
	/* ���ׂẴG�t�F�N�g�̍X�V���Ă� */
	for (auto& pEffect : this->pEffectList)
	{
		pEffect->Update();
	}
}

// �e�X�V
void DataList_Object::UpdateBullet()
{
	/* ���ׂĂ̒e�̍X�V���Ă� */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->Update();
	}
}

// �v���b�g�t�H�[���X�V
void DataList_Object::UpdatePlatform()
{
	/* �ғ��v���b�g�t�H�[���̍X�V���Ă�(�\��) */
}

/* ���X�g���I�u�W�F�N�g�`�� */
// �S�I�u�W�F�N�g�`��
void DataList_Object::DrawAll()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̕`�� */
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
	DrawPlatform();
}

// �v���C���[�`��
void DataList_Object::DrawPlayer()
{
	/* �v���C���[�̕`�ʂ��Ă� */
	this->pCharacterPlayer->Draw();
}

// �G�l�~�[�`��
void DataList_Object::DrawEnemy()
{
	/* ���ׂẴG�l�~�[�̕`�ʂ��Ă� */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->Draw();
	}
}

// �e�`��
void DataList_Object::DrawBullet()
{
	/* ���ׂĂ̋��̕`�ʂ��Ă� */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->Draw();
	}
}

// �v���b�g�t�H�[���`��
void DataList_Object::DrawPlatform()
{
	/* ���ׂẴv���b�g�t�H�[���̕`�ʂ��Ă� */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->Draw();
	}
}

/* ���X�g���I�u�W�F�N�g�����`�� */
// �S�I�u�W�F�N�g�����`��
void DataList_Object::BloomDrawAll()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̔����`�� */
	BloomDrawPlayer();
	BloomDrawEnemy();
	BloomDrawBullet();
	BloomDrawPlatform();
}

// �v���C���[�����`��
void DataList_Object::BloomDrawPlayer()
{
	/* �v���C���[�̔����`�ʂ��Ă� */
	this->pCharacterPlayer->BloomDraw();
}

// �G�l�~�[�����`��
void DataList_Object::BloomDrawEnemy()
{
	/* ���ׂẴG�l�~�[�̔����`�ʂ��Ă� */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->BloomDraw();
	}
}

// �e�����`��
void DataList_Object::BloomDrawBullet()
{
	/* ���ׂĂ̒e�̔����`�ʂ��Ă� */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->BloomDraw();
	}
}

// �v���b�g�t�H�[�������`��
void DataList_Object::BloomDrawPlatform()
{
	/* ���ׂẴv���b�g�t�H�[���̔����`�ʂ��Ă� */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->BloomDraw();
	}
}

/* ���X�g���I�u�W�F�N�g�폜 */
// �폜�t���O���L���ȑS�I�u�W�F�N�g�폜
void DataList_Object::DeleteAll()
{
	DeleteEnemy();
	DeleteEffect();
	DeleteBullet();
	DeletePlatform();
}

// �폜�t���O���L���ȃG�l�~�[���폜
void DataList_Object::DeleteEnemy()
{
	/* �폜�t���O���L���ȃG�l�~�[���폜 */
	pEnemyList.erase(std::remove_if(pEnemyList.begin(), pEnemyList.end(), [](EnemyBase* pEnemy)
		{
			/* �폜�t���O���L���ł��邩�m�F�@*/
			if (pEnemy->bGetDeleteFlg() == true)
			{
				// �L���ł���ꍇ
				delete pEnemy;
				return true;
			}
			else
			{
				// �����ł���ꍇ
				return false;
			}
		}), pEnemyList.end());
}

// �폜�t���O���L���ȃG�t�F�N�g���폜
void DataList_Object::DeleteEffect()
{
	/* �폜�t���O���L���ȃG�t�F�N�g���폜 */
	pEffectList.erase(std::remove_if(pEffectList.begin(), pEffectList.end(), [](EffectBase* pEffect)
		{
			/* �폜�t���O���L���ł��邩�m�F�@*/
			if (pEffect->bGetDeleteFlg() == true)
			{
				// �L���ł���ꍇ
				/* ��������� */
				delete pEffect;
				return true;
			}
			else
			{
				// �����ł���ꍇ
				return false;
			}
		}), pEffectList.end());
}

// �폜�t���O���L���Ȓe���폜
void DataList_Object::DeleteBullet()
{
	/* �폜�t���O���L���Ȓe���폜 */
	pBulletList.erase(std::remove_if(pBulletList.begin(), pBulletList.end(), [](BulletBase* pBullet)
		{
			/* �폜�t���O���L���ł��邩�m�F�@*/
			if (pBullet->bGetDeleteFlg() == true)
			{
				// �L���ł���ꍇ
				/* ��������� */
				delete pBullet;
				return true;
			}
			else
			{
				// �����ł���ꍇ
				return false;
			}
		}), pBulletList.end());
}

// �폜�t���O���L���ȃv���b�g�t�H�[�����폜
void DataList_Object::DeletePlatform()
{
	/* �폜�t���O���L���ȃv���b�g�t�H�[�����폜 */
	pPlatformList.erase(std::remove_if(pPlatformList.begin(), pPlatformList.end(), [](PlatformBase* pPlatform)
		{
			/* �폜�t���O���L���ł��邩�m�F�@*/
			if (pPlatform->bGetDeleteFlg() == true)
			{
				// �L���ł���ꍇ
				/* ��������� */
				delete pPlatform;
				return true;
			}
			else
			{
				// �����ł���ꍇ
				return false;
			}
		}), pPlatformList.end());
}
