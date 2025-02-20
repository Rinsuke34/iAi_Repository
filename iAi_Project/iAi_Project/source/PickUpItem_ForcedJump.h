/* 2024.02.10 �ΐ�q�� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* �I�u�W�F�N�g */
#include "Gimmick_ForcedJump_Spawn.h"
#include "CharacterPlayer.h"

/* �z�Q�Ƒ΍�(��قǑ΍�͎��{) */
class DataList_Object;
class Gimmick_ForcedJump_Spawn;
class CharacterPlayer;

/* �����W�����v�A�C�e��(�M�~�b�N)�N���X�̐錾 */

// �����W�����v�A�C�e��(�M�~�b�N)�N���X
class PickUpItem_ForcedJump : public PickUpItemBase
{
	public:
		PickUpItem_ForcedJump();			// �R���X�g���N�^
		virtual ~PickUpItem_ForcedJump();	// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		virtual void	BloomDraw()			override {};	// �����`��

		/* �f�[�^�ݒ� */
		void SetGimmick_ForcedJump_Spawn(Gimmick_ForcedJump_Spawn* pGimmick_ForcedJump_Spawn) { this->pGimmick_ForcedJump_Spawn = pGimmick_ForcedJump_Spawn; };		// �����W�����v�M�~�b�N�X�|�i�[(���g�̐�����)��ݒ�

	private:
		/* �f�[�^���X�g */
		DataList_Object* ObjectList;				// �I�u�W�F�N�g�Ǘ�
		DataList_PlayerStatus* PlayerStatusList;	// �v���C���[���

		/* �ϐ� */
		CharacterPlayer*			pPlayer;					// �v���C���[
		Gimmick_ForcedJump_Spawn*	pGimmick_ForcedJump_Spawn;	// �����W�����v�M�~�b�N�X�|�i�[(���g�̐�����)

	//�G�t�F�N�g
	EffectManualDelete* pEffectExplosion;	// �����G�t�F�N�g

};

