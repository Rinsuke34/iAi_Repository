/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include <vector>
#include "PublicInclude.h"

/* �I�u�W�F�N�g */
#include "EnemyBasic.h"

/* �O���Q�� */
// ��AppFrame�Œ�`����Ă��Ȃ��N���X���g�p����ꍇ�A�z�Q�Ƒ΍�Ɏ��{����B
class EnemyBasic;

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
		void	DrawAll();				// �S�I�u�W�F�N�g�`��(�G�t�F�N�g������)
		void	DrawPlayer();			// �v���C���[�`��
		void	DrawEnemy();			// �G�l�~�[�`��
		void	DrawBullet();			// �e�`��
		void	DrawPlatform();			// �v���b�g�t�H�[���`��
		void	DrawEffect();			// �G�t�F�N�g�`��

		/* ���X�g���I�u�W�F�N�g�R���W�����`�� */
		void	DrawAll_Collision();		// �S�I�u�W�F�N�g�R���W�����`��
		void	DrawPlayer_Collision();		// �v���C���[�R���W�����`��
		void	DrawEnemy_Collision();		// �G�l�~�[�R���W�����`��
		void	DrawBullet_Collision();		// �e�R���W�����`��
		void	DrawPlatform_Collision();	// �v���b�g�t�H�[���R���W�����`��

		/* ���X�g���I�u�W�F�N�g�����`�� */
		void	DrawAll_Bloom();		// �S�I�u�W�F�N�g�����`��
		void	DrawPlayer_Bloom();		// �v���C���[�����`��
		void	DrawEnemy_Bloom();		// �G�l�~�[�����`��
		void	DrawBullet_Bloom();		// �e�����`��
		void	DrawPlatform_Bloom();	// �v���b�g�t�H�[�������`��

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
		std::vector<EnemyBasic*>&		GetEnemyList()		{ return this->pEnemyList; }		// �G�l�~�[�擾
		std::vector<EffectBase*>&		GetEffectList()		{ return this->pEffectList; }		// �G�t�F�N�g�擾
		std::vector<BulletBase*>&		GetBulletList()		{ return this->pBulletList; }		// �e�擾
		std::vector<CollisionBase*>&	GetCollisionList()	{ return this->pCollisionList; }	// �v���b�g�t�H�[��(�R���W����)
		std::vector<BackGroundBase*>&	GetBackGroundList() { return this->pBackGroundList; }	// �v���b�g�t�H�[��(�`�ʃ��f��)
		
		/* �f�[�^�ݒ� */
		// �P��
		void	SetCharacterPlayer(CharacterBase* pCharacter)	{ this->pCharacterPlayer = pCharacter; }	// �v���C���[�ݒ�

		// ���X�g
		void	SetEnemy(EnemyBasic* pEnemy)				{ pEnemyList.emplace_back(pEnemy); };			// �G�l�~�[�ǉ�
		void	SetEffect(EffectBase* pEffect)				{ pEffectList.emplace_back(pEffect); };			// �G�t�F�N�g�ǉ�
		void	SetBullet(BulletBase* pBullet)				{ pBulletList.emplace_back(pBullet); };			// �e�ǉ�
		void	SetCollision(CollisionBase* pCollision)		{ pCollisionList.emplace_back(pCollision); };	// �v���b�g�t�H�[��(�R���W����)�ǉ�
		void	SetBackGround(BackGroundBase* pBackGround)	{ pBackGroundList.emplace_back(pBackGround); };	// �v���b�g�t�H�[��(�`�ʃ��f��)�ǉ�

	private:
		/* �Ǘ�����f�[�^ */
		// �P��
		CharacterBase*					pCharacterPlayer;	// �v���C���[

		// ���X�g
		std::vector<EnemyBasic*>		pEnemyList;			// �G�l�~�[
		std::vector<EffectBase*>		pEffectList;		// �G�t�F�N�g
		std::vector<BulletBase*>		pBulletList;		// �e
		std::vector<CollisionBase*>		pCollisionList;		// �v���b�g�t�H�[��(�R���W����)
		std::vector<BackGroundBase*>	pBackGroundList;	// �v���b�g�t�H�[��(�`�ʃ��f��)

	protected:
};
