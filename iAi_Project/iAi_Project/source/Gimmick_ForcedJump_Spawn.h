/* 2025.02.12 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"
#include "GimmickDefine.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "PickUpItem_ForcedJump.h"

/* �z�Q�Ƒ΍�(��قǑ΍�͎��{) */
class PickUpItem_ForcedJump;

/* �����W�����v�M�~�b�N�X�|�i�[�N���X�̐錾 */

// �����W�����v�M�~�b�N�X�|�i�[�N���X
class Gimmick_ForcedJump_Spawn : public PlatformBase
{
	public:
		Gimmick_ForcedJump_Spawn();				// �R���X�g���N�^
		virtual ~Gimmick_ForcedJump_Spawn();	// �f�X�g���N�^

		virtual void	Initialization()	override {};	// ������
		virtual void	Update()			override;		// �X�V
		virtual void	Draw()				override {};	// �`��
		virtual void	BloomDraw()			override {};	// �����`��
		virtual void	CollisionDraw()		override {};	// �����蔻��`��

		/* �f�[�^�ݒ� */
		void SetSpawnObjectFlg(bool bSpawnObjectFlg) { this->bSpawnObjectFlg = bSpawnObjectFlg; };	// �I�u�W�F�N�g�̃X�|�[���t���O��ݒ�

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Object* ObjectList;	// �I�u�W�F�N�g�Ǘ�

		/* �ϐ� */
		bool	bSpawnObjectFlg;		// �I�u�W�F�N�g�̃X�|�[���t���O(�L���Ȃ琶��)
		int		iSpawnCoolTime;			// �X�|�[���̃N�[���^�C��	
};