/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "DataList_Object.h"

/* �I�u�W�F�N�g�Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_Object::DataList_Object() : DataListBase("DataList_Object")
{
	/* ������ */
	{
		this->pCharacterPlayer	=	nullptr;	// �v���C���[
		this->pSkySqhere		=	nullptr;	// �X�J�C�X�t�B�A
		this->pEnemyList.clear();				// �G�l�~�[
		this->pBulletList.clear();				// �e
		this->pEffectList.clear();				// �G�t�F�N�g
		this->pPlatformList.clear();			// �v���b�g�t�H�[��
		this->pEffectItemList.clear();			// �A�C�e��(���̂Ȃ�)
		this->pPickUpItemList.clear();			// �A�C�e��(���̂���)
		this->pEnemySpawnPointList.clear();		// �G�l�~�[�X�|�i�[
	}
}

// �f�X�g���N�^
DataList_Object::~DataList_Object()
{
	/* ��������� */
	{
		delete this->pCharacterPlayer;											// �v���C���[
		delete this->pSkySqhere;												// �X�J�C�X�t�B�A
		for (auto& pEnemy : this->pEnemyList)			{ delete pEnemy; }		// �G�l�~�[
		for (auto& pBullet : this->pBulletList)			{ delete pBullet; }		// �e		
		for (auto& pEffect : this->pEffectList)			{ delete pEffect; }		// �G�t�F�N�g
		for (auto& pPlatform : this->pPlatformList)		{ delete pPlatform; }	// �v���b�g�t�H�[��
		for (auto& pEffectItem : this->pEffectItemList)	{ delete pEffectItem; }	// �A�C�e��(���̂Ȃ�)
		for (auto& pPickUpItem : this->pPickUpItemList)	{ delete pPickUpItem; }	// �A�C�e��(���̂���)
	}
}

/* ���X�g���I�u�W�F�N�g������ */
// �S�I�u�W�F�N�g������
void DataList_Object::InitializationAll()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̏����� */
	InitializationPlayer();
	InitializationSkySqhere();
	InitializationEnemy();
	InitializationEffect();
	InitializationBullet();
	InitializationPlatform();
	InitializationEffectItem();
	InitializationPickUpItem();
	InitializationEnemySpawnPoint();
}

// �v���C���[������
void DataList_Object::InitializationPlayer()
{
	/* �v���C���[�����݂��邩�m�F */
	// �� �^�C�g����ʓ��v���C���[�����݂��Ȃ��ꍇ��nullptr�ƂȂ�
	if (this->pCharacterPlayer != nullptr)
	{
		// �v���C���[�����݂���ꍇ
		/* �v���C���[�̏��������� */
		this->pCharacterPlayer->Initialization();
		this->pCharacterPlayer->SetupInitialPosition();
	}
}

// �X�J�C�X�t�B�A������
void DataList_Object::InitializationSkySqhere()
{
	/* �X�J�C�X�t�B�A�̏��������� */
	this->pSkySqhere->Initialization();
	this->pSkySqhere->SetupInitialPosition();
}

// �G�l�~�[������
void DataList_Object::InitializationEnemy()
{
	/* ���ׂẴG�l�~�[�̏��������Ă� */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->Initialization();
		pEnemy->SetupInitialPosition();
	}
}

// �G�t�F�N�g������
void DataList_Object::InitializationEffect()
{
	/* ���ׂẴG�t�F�N�g�̏��������Ă� */
	for (auto& pEffect : this->pEffectList)
	{
		pEffect->Initialization();
		pEffect->SetupInitialPosition();
	}
}

// �e������
void DataList_Object::InitializationBullet()
{
	/* ���ׂĂ̒e�̏��������Ă� */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->Initialization();
		pBullet->SetupInitialPosition();
	}
}

// �v���b�g�t�H�[��������
void DataList_Object::InitializationPlatform()
{
	/* �v���b�g�t�H�[���̏����� */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->Initialization();
		pPlatform->SetupInitialPosition();
	}
}

// �A�C�e��(���̂Ȃ�)������
void DataList_Object::InitializationEffectItem()
{
	/* ���ׂẴA�C�e��(���̂Ȃ�)�̏��������Ă� */
	for (auto& pEffectItem : this->pEffectItemList)
	{
		pEffectItem->Initialization();
		pEffectItem->SetupInitialPosition();
	}
}

// �A�C�e��(���̂���)������
void DataList_Object::InitializationPickUpItem()
{
	/* ���ׂẴA�C�e��(���̂���)�̏��������Ă� */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->Initialization();
		pPickUpItem->SetupInitialPosition();
	}
}

// �G�l�~�[�X�|�i�[������
void DataList_Object::InitializationEnemySpawnPoint()
{
	/* ���ׂẴG�l�~�[�X�|�i�[�̏��������Ă� */
	for (auto& pEnemySpawnPoint : this->pEnemySpawnPointList)
	{
		pEnemySpawnPoint->Initialization();
		pEnemySpawnPoint->SetupInitialPosition();
	}
}

/* ���X�g���I�u�W�F�N�g�X�V */
// �S�I�u�W�F�N�g�X�V
void DataList_Object::UpdateAll()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̍X�V */
	UpdatePlayer();
	UpdateSkySqhere();
	UpdateEnemy();
	UpdateEffect();
	UpdateBullet();
	UpdatePlatform();
	UpdateEffectItem();
	UpdatePickUpItem();
}

// �v���C���[�X�V
void DataList_Object::UpdatePlayer()
{
	/* �v���C���[�����݂��邩�m�F */
	// �� �^�C�g����ʓ��v���C���[�����݂��Ȃ��ꍇ��nullptr�ƂȂ�
	if (this->pCharacterPlayer != nullptr)
	{
		// �v���C���[�����݂���ꍇ
		/* �v���C���[�̍X�V���Ă� */
		this->pCharacterPlayer->Update();
	}
}

// �X�J�C�X�t�B�A�X�V
void DataList_Object::UpdateSkySqhere()
{
	/* �X�J�C�X�t�B�A�̍X�V���Ă� */
	this->pSkySqhere->Update();
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
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->Update();
	}
}

// �A�C�e��(���̂Ȃ�)�X�V
void DataList_Object::UpdateEffectItem()
{
	/* ���ׂẴA�C�e��(���̂Ȃ�)�̍X�V���Ă� */
	for (auto& pEffectItem : this->pEffectItemList)
	{
		pEffectItem->Update();
	}
}

// �A�C�e��(���̂���)�X�V
void DataList_Object::UpdatePickUpItem()
{
	/* ���ׂẴA�C�e��(���̂���)�̍X�V���Ă� */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->Update();
	}
}

/* ���X�g���I�u�W�F�N�g�`�� */
// �S�I�u�W�F�N�g�`��(�G�t�F�N�g������)
void DataList_Object::DrawAll()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̕`�� */
	DrawPlayer();
	DrawSkySqhere();
	DrawEnemy();
	DrawBullet();
	DrawPlatform();
	DrawEffectItem();
	DrawPickUpItem();
}

// �v���C���[�`��
void DataList_Object::DrawPlayer()
{
	/* �v���C���[�����݂��邩�m�F */
	// �� �^�C�g����ʓ��v���C���[�����݂��Ȃ��ꍇ��nullptr�ƂȂ�
	if (this->pCharacterPlayer != nullptr)
	{
		// �v���C���[�����݂���ꍇ
		/* �v���C���[�̕`�ʂ��Ă� */
		this->pCharacterPlayer->Draw();
	}
}

// �X�J�C�X�t�B�A�`��
void DataList_Object::DrawSkySqhere()
{
	/* �X�J�C�X�t�B�A�̕`�ʂ��Ă� */
	this->pSkySqhere->Draw();
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
	/*�@�o�b�N�O�����h��\���t���O�������ł��邩�m�F */
	if (gbDrawDeleteBackGroundFlg == false)
	{
		// �����ł���ꍇ
		/* �v���b�g�t�H�[���̕`�ʂ��Ă� */
		for (auto& pPlatform : this->pPlatformList)
		{
			pPlatform->Draw();
		}
	}
}

// �G�t�F�N�g�`��
void DataList_Object::DrawEffect()
{
	/* ���ׂẴG�t�F�N�g�̕`�ʂ��Ă� */
	for (auto& pEffect : this->pEffectList)
	{
		pEffect->Draw();
	}
}

// �A�C�e��(���̂Ȃ�)�`��
void DataList_Object::DrawEffectItem()
{
	/* ���ׂẴA�C�e��(���̂Ȃ�)�̕`�ʂ��Ă� */
	for (auto& pEffectItem : this->pEffectItemList)
	{
		pEffectItem->Draw();
	}
}

// �A�C�e��(���̂���)�`��
void DataList_Object::DrawPickUpItem()
{
	/* ���ׂẴA�C�e��(���̂���)�̕`�ʂ��Ă� */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->Draw();
	}
}

/* ���X�g���I�u�W�F�N�g�R���W�����`�� */
// �S�I�u�W�F�N�g�R���W�����`��
void DataList_Object::DrawAll_Collision()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̃R���W�����`�� */
	DrawPlayer_Collision();
	DrawSkySqhere_Collision();
	DrawEnemy_Collision();
	DrawBullet_Collision();
	DrawPlatform_Collision();
	DrawEffectItem_Collision();
	DrawPickUpItem_Collision();
}

// �v���C���[�R���W�����`��
void DataList_Object::DrawPlayer_Collision()
{
	/* �v���C���[�����݂��邩�m�F */
	// �� �^�C�g����ʓ��v���C���[�����݂��Ȃ��ꍇ��nullptr�ƂȂ�
	if (this->pCharacterPlayer != nullptr)
	{
		// �v���C���[�����݂���ꍇ
		/* �v���C���[�R���W�����`�ʂ��Ă� */
		this->pCharacterPlayer->CollisionDraw();
	}
}

// �X�J�C�X�t�B�A�R���W�����`��
void DataList_Object::DrawSkySqhere_Collision()
{
	/* �X�J�C�X�t�B�A�R���W�����`�ʂ��Ă� */
	this->pSkySqhere->CollisionDraw();
}

// �G�l�~�[�R���W�����`��
void DataList_Object::DrawEnemy_Collision()
{
	/* ���ׂẴG�l�~�[�R���W�����`�ʂ��Ă� */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->CollisionDraw();
	}
}

// �e�R���W�����`��
void DataList_Object::DrawBullet_Collision()
{
	/* ���ׂĂ̒e�R���W�����`�ʂ��Ă� */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->CollisionDraw();
	}
}

// �v���b�g�t�H�[���R���W�����`��
void DataList_Object::DrawPlatform_Collision()
{
	// �L���ł���ꍇ
	/* �v���b�g�t�H�[���̕`�ʂ��Ă� */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->CollisionDraw();
	}
}

// �A�C�e��(���̂Ȃ�)�R���W�����`��
void DataList_Object::DrawEffectItem_Collision()
{
	// ���A�C�e��(���̂Ȃ�)�̓R���W�����������Ȃ����߁A�`�ʂ͍s��Ȃ��B
}

// �A�C�e��(���̂���)�R���W�����`��
void DataList_Object::DrawPickUpItem_Collision()
{
	/* ���ׂẴA�C�e��(���̂���)�̃R���W�����`�ʂ��Ă� */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->CollisionDraw();
	}
}

/* ���X�g���I�u�W�F�N�g�����`�� */
// �S�I�u�W�F�N�g�����`��
void DataList_Object::DrawAll_Bloom()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̔����`�� */
	DrawPlayer_Bloom();
	DrawSkySqhere_Bloom();
	DrawEnemy_Bloom();
	DrawBullet_Bloom();
	DrawPlatform_Bloom();
	DrawEffectItem_Bloom();
	DrawPickUpItem_Bloom();
}

// �v���C���[�����`��
void DataList_Object::DrawPlayer_Bloom()
{
	/* �v���C���[�����݂��邩�m�F */
	// �� �^�C�g����ʓ��v���C���[�����݂��Ȃ��ꍇ��nullptr�ƂȂ�
	if (this->pCharacterPlayer != nullptr)
	{
		// �v���C���[�����݂���ꍇ
		/* �v���C���[�̔����`�ʂ��Ă� */
		this->pCharacterPlayer->BloomDraw();
	}
}

// �X�J�C�X�t�B�A�����`��
void DataList_Object::DrawSkySqhere_Bloom()
{
	/* �X�J�C�X�t�B�A�̔����`�ʂ��Ă� */
	this->pSkySqhere->BloomDraw();
}

// �G�l�~�[�����`��
void DataList_Object::DrawEnemy_Bloom()
{
	/* ���ׂẴG�l�~�[�̔����`�ʂ��Ă� */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->BloomDraw();
	}
}

// �e�����`��
void DataList_Object::DrawBullet_Bloom()
{
	/* ���ׂĂ̒e�̔����`�ʂ��Ă� */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->BloomDraw();
	}
}

// �v���b�g�t�H�[�������`��
void DataList_Object::DrawPlatform_Bloom()
{
	/*�@�o�b�N�O�����h��\���t���O�������ł��邩�m�F */
	if (gbDrawDeleteBackGroundFlg == false)
	{
		// �����ł���ꍇ
		/* �v���b�g�t�H�[���̔����`�ʂ��Ă� */
		for (auto& pPlatform : this->pPlatformList)
		{
			pPlatform->BloomDraw();
		}
	}
}

// �A�C�e��(���̂Ȃ�)�����`��
void DataList_Object::DrawEffectItem_Bloom()
{
	/* ���ׂẴA�C�e��(���̂Ȃ�)�̔����`�ʂ��Ă� */
	for (auto& pEffectItem : this->pEffectItemList)
	{
		pEffectItem->BloomDraw();
	}
}

// �A�C�e��(���̂���)�����`��
void DataList_Object::DrawPickUpItem_Bloom()
{
	/* ���ׂẴA�C�e��(���̂���)�̔����`�ʂ��Ă� */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->BloomDraw();
	}
}

/* ���X�g���I�u�W�F�N�g�폜 */
// �폜�t���O���L���ȑS�I�u�W�F�N�g�폜
// ���P�Ƃ̃f�[�^�̓f�X�g���N�^�ŊJ������邽�߁A���X�g�ŊǗ����Ă���f�[�^�̂ݑΏۂƂ���B
void DataList_Object::DeleteAll()
{
	DeleteEnemy();
	DeleteEffect();
	DeleteBullet();
	DeletePlatform();
	DeleteEffectItem();
	DeletePickUpItem();
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

// �폜�t���O���L���ȃA�C�e��(���̂Ȃ�)���폜
void DataList_Object::DeleteEffectItem()
{
	/* �폜�t���O���L���ȃA�C�e��(���̂Ȃ�)���폜 */
	pEffectItemList.erase(std::remove_if(pEffectItemList.begin(), pEffectItemList.end(), [](EffectItemBase* pEffectItem)
	{
		/* �폜�t���O���L���ł��邩�m�F�@*/
		if (pEffectItem->bGetDeleteFlg() == true)
		{
			// �L���ł���ꍇ
			/* ��������� */
			delete pEffectItem;
			return true;
		}
		else
		{
			// �����ł���ꍇ
			return false;
		}
	}), pEffectItemList.end());
}

// �폜�t���O���L���ȃA�C�e��(���̂���)���폜
void DataList_Object::DeletePickUpItem()
{
	/* �폜�t���O���L���ȃA�C�e��(���̂���)���폜 */
	pPickUpItemList.erase(std::remove_if(pPickUpItemList.begin(), pPickUpItemList.end(), [](PickUpItemBase* pPickUpItem)
	{
		/* �폜�t���O���L���ł��邩�m�F�@*/
		if (pPickUpItem->bGetDeleteFlg() == true)
		{
			// �L���ł���ꍇ
			/* ��������� */
			delete pPickUpItem;
			return true;
		}
		else
		{
			// �����ł���ꍇ
			return false;
		}
	}), pPickUpItemList.end());
}

// �S�I�u�W�F�N�g���Z�b�g����
void DataList_Object::ResetAll()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̃��Z�b�g���� */
	ResetPlayer();
	ResetSkySqhere();
	ResetEnemy();
	ResetEffect();
	ResetBullet();
	ResetPlatform();
	ResetEffectItem();
	ResetPickUpItem();
	ResetEnemySpawnPoint();
}

// �v���C���[���Z�b�g����
void DataList_Object::ResetPlayer()
{
	/* �v���C���[�����݂��邩�m�F */
	// �� �^�C�g����ʓ��v���C���[�����݂��Ȃ��ꍇ��nullptr�ƂȂ�
	if (this->pCharacterPlayer != nullptr)
	{
		// �v���C���[�����݂���ꍇ
		/* �v���C���[�̃��Z�b�g�������Ă� */
		this->pCharacterPlayer->Reset();
	}
}

// �X�J�C�X�t�B�A���Z�b�g����
void DataList_Object::ResetSkySqhere()
{
	/* �X�J�C�X�t�B�A�̃��Z�b�g�������Ă� */
	this->pSkySqhere->Reset();
}

// �G�l�~�[���Z�b�g����
void DataList_Object::ResetEnemy()
{
	/* ���ׂẴG�l�~�[�̃��Z�b�g�������Ă� */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->Reset();
	}
}

// �G�t�F�N�g���Z�b�g����
void DataList_Object::ResetEffect()
{
	/* ���ׂẴG�t�F�N�g�̃��Z�b�g�������Ă� */
	for (auto& pEffect : this->pEffectList)
	{
		pEffect->Reset();
	}
}

// �e���Z�b�g����
void DataList_Object::ResetBullet()
{
	/* ���ׂĂ̒e�̃��Z�b�g�������Ă� */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->Reset();
	}
}

// �v���b�g�t�H�[�����Z�b�g����
void DataList_Object::ResetPlatform()
{
	/* ���ׂẴv���b�g�t�H�[���̃��Z�b�g���� */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->Reset();
	}
}

// �A�C�e��(���̂Ȃ�)���Z�b�g����
void DataList_Object::ResetEffectItem()
{
	/* ���ׂẴA�C�e��(���̂Ȃ�)�̃��Z�b�g�������Ă� */
	for (auto& pEffectItem : this->pEffectItemList)
	{
		pEffectItem->Reset();
	}
}

// �A�C�e��(���̂���)���Z�b�g����
void DataList_Object::ResetPickUpItem()
{
	/* ���ׂẴA�C�e��(���̂���)�̃��Z�b�g�������Ă� */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->Reset();
	}
}

// �G�l�~�[�X�|�i�[���Z�b�g����
void DataList_Object::ResetEnemySpawnPoint()
{
	/* ���ׂẴG�l�~�[�X�|�i�[�̃��Z�b�g�������Ă� */
	for (auto& pEnemySpawnPoint : this->pEnemySpawnPointList)
	{
		pEnemySpawnPoint->Reset();
	}
}
