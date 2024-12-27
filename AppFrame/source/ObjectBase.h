/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <DxLib.h>
#include "AppStructDefine.h"

/* ���ׂẴI�u�W�F�N�g�̃x�[�X�ƂȂ�N���X�̐錾 */

// �I�u�W�F�N�g�x�[�X�N���X
class ObjectBase
{
	public:
		ObjectBase();					// �R���X�g���N�^
		virtual ~ObjectBase() {};		// �f�X�g���N�^

		virtual void	Update() {};	// �X�V

		bool	bGetDeleteFlg()		{ return this->bDeleteFlg; };		// �폜�t���O���擾
		VECTOR	vecGetPosition()	{ return this->vecPosition; };		// ���W���擾

		void	SetDeleteFlg(bool bDeleteFlg)	{ this->bDeleteFlg	= bDeleteFlg; };	// �폜�t���O��ݒ�
		void	SetPosition(VECTOR vecPostion)	{ this->vecPosition	= vecPostion; };	// �I�u�W�F�N�g�̍��W��ݒ�

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		bool	bDeleteFlg;				// �폜�t���O(�L���Ȃ�I�u�W�F�N�g���폜)
		VECTOR	vecPosition;			// �I�u�W�F�N�g�̍��W
};