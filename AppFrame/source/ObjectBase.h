/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <DxLib.h>
#include <vector>
#include <algorithm>
#include "AppStructDefine.h"
#include "AppFunctionDefine.h"

/* ���ׂẴI�u�W�F�N�g�̃x�[�X�ƂȂ�N���X�̐錾 */

// �I�u�W�F�N�g�x�[�X�N���X
class ObjectBase
{
	public:
		ObjectBase();					// �R���X�g���N�^
		virtual ~ObjectBase() {};		// �f�X�g���N�^

		virtual void	Initialization()	{};	// ������
		virtual void	Update()			{};	// �X�V
		virtual void	Draw()				{};	// �`��
		virtual void	BloomDraw()			{};	// �����`��
		virtual void	CollisionDraw()		{};	// �����蔻��`��


		bool	bGetDeleteFlg()		{ return this->bDeleteFlg; };		// �폜�t���O���擾
		VECTOR	vecGetPosition()	{ return this->vecPosition; };		// ���W���擾
		VECTOR	vecGetRotation()	{ return this->vecRotation; };		// �I�u�W�F�N�g�̉�]�ʂ��擾
		VECTOR	vecGetScale()		{ return this->vecScale; };			// �I�u�W�F�N�g�g�嗦���擾

		void	SetDeleteFlg(bool bDeleteFlg)		{ this->bDeleteFlg	= bDeleteFlg; };	// �폜�t���O��ݒ�
		void	SetPosition(VECTOR vecPostion)		{ this->vecPosition	= vecPostion; };	// �I�u�W�F�N�g�̍��W��ݒ�
		void	SetRotation(VECTOR vecRotation)		{ this->vecRotation = vecRotation; };	// �I�u�W�F�N�g�̌�����ݒ�
		void	SetScale(VECTOR vecScale)			{ this->vecScale	= vecScale; };		// �I�u�W�F�N�g�̊g�嗦��ݒ�

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		bool	bDeleteFlg;				// �폜�t���O(�L���Ȃ�I�u�W�F�N�g���폜)
		VECTOR	vecPosition;			// �I�u�W�F�N�g�̍��W
		VECTOR	vecRotation;			// �I�u�W�F�N�g�̉�]��
		VECTOR	vecScale;				// �I�u�W�F�N�g�̊g�嗦(x,y,z�������ꂼ��̊g��{��)
};
