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

	// �v���b�g�t�H�[��
	this->pPlatformList.clear();
}

// �f�X�g���N�^
DataList_Object::~DataList_Object()
{
	/* ��� */
	this->pCharacterPlayer	=	nullptr;
}

// Json����f�[�^�����[�h
void DataList_Object::JsonDataLoad()
{
	/* Json�t�@�C������f�[�^�ǂݍ��� */
	// ������͖�����
}


/* ���X�g���I�u�W�F�N�g�X�V */
// �S�I�u�W�F�N�g�X�V
void DataList_Object::UpdateAll()
{
	/* �o�^����Ă��邷�ׂẴI�u�W�F�N�g�̍X�V */
	UpdatePlayer();
	UpdateEnemy();
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