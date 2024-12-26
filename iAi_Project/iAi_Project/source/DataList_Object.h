/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include <vector>

/* �I�u�W�F�N�g�Ǘ��N���X�̐錾 */

// �I�u�W�F�N�g�Ǘ��N���X
class DataList_Object : public DataListBase
{
	public:
		DataList_Object();				// �R���X�g���N�^
		virtual ~DataList_Object();		// �f�X�g���N�^

		void	JsonDataLoad();			// Json����f�[�^�����[�h"�����쐬"

		/* ���X�g���I�u�W�F�N�g�X�V */
		void	UpdateAll();			// �S�I�u�W�F�N�g�X�V
		void	UpdatePlayer();			// �v���C���[�X�V
		void	UpdateEnemy();			// �G�l�~�[�X�V
		void	UpdateBullet();			// �e�X�V
		void	UpdatePlatform();		// �v���b�g�t�H�[���X�V

		/* ���X�g���I�u�W�F�N�g�`�� */
		void	DrawAll();				// �S�I�u�W�F�N�g�`��
		void	DrawPlayer();			// �v���C���[�`��
		void	DrawEnemy();			// �G�l�~�[�`��
		void	DrawBullet();			// �e�`��
		void	DrawPlatform();			// �v���b�g�t�H�[���`��

		/* �f�[�^�擾 */
		CharacterBase* GetCharacterPlayer()	{ return this->pCharacterPlayer; }	// �v���C���[�擾
		
		/* �f�[�^�ݒ� */
		// �P��
		void	SetCharacterPlayer(CharacterBase* pCharacter)	{ this->pCharacterPlayer = pCharacter; }	// �v���C���[�ݒ�

		// ���X�g
		void	SetEnemy(EnemyBase* pEnemy)				{ pEnemyList.emplace_back(pEnemy); };			// �G�l�~�[�ǉ�
		void	SetBullet(BulletBase* pBullet)			{ pBulletList.emplace_back(pBullet); };			// �e�ǉ�
		void	SetPlatform(PlatformBase* pPlatform)	{ pPlatformList.emplace_back(pPlatform); };		// �v���b�g�t�H�[���ǉ�

	private:
		/* �Ǘ�����f�[�^ */
		// �P��
		CharacterBase*					pCharacterPlayer;	// �v���C���[

		// ���X�g
		std::vector<EnemyBase*>			pEnemyList;			// �G�l�~�[
		std::vector<BulletBase*>		pBulletList;		// �e
		std::vector<PlatformBase*>		pPlatformList;		// �v���b�g�t�H�[��

	protected:
};
