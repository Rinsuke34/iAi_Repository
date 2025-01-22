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

		/* ���X�g���I�u�W�F�N�g������ */
		void	InitializationAll();		// �S�I�u�W�F�N�g������
		void	InitializationPlayer();		// �v���C���[������
		void	InitializationEnemy();		// �G�l�~�[������
		void	InitializationEffect();		// �G�t�F�N�g������
		void	InitializationBullet();		// �e������
		void	InitializationPlatform();	// �v���b�g�t�H�[��������

		/* ���X�g���I�u�W�F�N�g�X�V */
		void	UpdateAll();			// �S�I�u�W�F�N�g�X�V
		void	UpdatePlayer();			// �v���C���[�X�V
		void	UpdateEnemy();			// �G�l�~�[�X�V
		void	UpdateEffect();			// �G�t�F�N�g�X�V
		void	UpdateBullet();			// �e�X�V
		void	UpdatePlatform();		// �v���b�g�t�H�[���X�V

		/* ���X�g���I�u�W�F�N�g�`�� */
		void	DrawAll();				// �S�I�u�W�F�N�g�`��
		void	DrawPlayer();			// �v���C���[�`��
		void	DrawEnemy();			// �G�l�~�[�`��
		void	DrawBullet();			// �e�`��
		void	DrawPlatform();			// �v���b�g�t�H�[���`��

		/* ���X�g���I�u�W�F�N�g�����`�� */
		void	BloomDrawAll();			// �S�I�u�W�F�N�g�����`��
		void	BloomDrawPlayer();		// �v���C���[�����`��
		void	BloomDrawEnemy();		// �G�l�~�[�����`��
		void	BloomDrawBullet();		// �e�����`��
		void	BloomDrawPlatform();	// �v���b�g�t�H�[�������`��

		/* �I�u�W�F�N�g�폜 */
		void	DeleteAll();			// �폜�t���O���L���ȑS�I�u�W�F�N�g�폜
		void	DeleteEnemy();			// �폜�t���O���L���ȃG�l�~�[���폜
		void	DeleteEffect();			// �폜�t���O���L���ȃG�t�F�N�g���폜
		void	DeleteBullet();			// �폜�t���O���L���Ȓe���폜
		void	DeletePlatform();		// �폜�t���O���L���ȃv���b�g�t�H�[�����폜

		/* �f�[�^�擾 */
		// �P��
		CharacterBase* GetCharacterPlayer()	{ return this->pCharacterPlayer; }	// �v���C���[�擾

		// ���X�g
		std::vector<EnemyBase*>&	GetEnemyList()		{ return this->pEnemyList; }		// �G�l�~�[�擾
		std::vector<EffectBase*>&	GetEffectList()		{ return this->pEffectList; }		// �G�t�F�N�g�擾
		std::vector<BulletBase*>&	GetBulletList()		{ return this->pBulletList; }		// �e�擾
		std::vector<PlatformBase*>&	GetPlatformList()	{ return this->pPlatformList; }		// �v���b�g�t�H�[���擾
		
		/* �f�[�^�ݒ� */
		// �P��
		void	SetCharacterPlayer(CharacterBase* pCharacter)	{ this->pCharacterPlayer = pCharacter; }	// �v���C���[�ݒ�

		// ���X�g
		void	SetEnemy(EnemyBase* pEnemy)				{ pEnemyList.emplace_back(pEnemy); };			// �G�l�~�[�ǉ�
		void	SetEffect(EffectBase* pEffect)			{ pEffectList.emplace_back(pEffect); };			// �G�t�F�N�g�ǉ�
		void	SetBullet(BulletBase* pBullet)			{ pBulletList.emplace_back(pBullet); };			// �e�ǉ�
		void	SetPlatform(PlatformBase* pPlatform)	{ pPlatformList.emplace_back(pPlatform); };		// �v���b�g�t�H�[���ǉ�

	private:
		/* �Ǘ�����f�[�^ */
		// �P��
		CharacterBase*					pCharacterPlayer;	// �v���C���[

		// ���X�g
		std::vector<EnemyBase*>			pEnemyList;			// �G�l�~�[
		std::vector<EffectBase*>		pEffectList;		// �G�t�F�N�g
		std::vector<BulletBase*>		pBulletList;		// �e
		std::vector<PlatformBase*>		pPlatformList;		// �v���b�g�t�H�[��

	protected:
};
