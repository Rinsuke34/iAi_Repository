/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ObjectBase.h"

/* ���ׂẴA�N�^�̃x�[�X�ƂȂ�N���X�̐錾 */

// �A�N�^�x�[�X�N���X
class ActorBase : public ObjectBase
{
	public:
		ActorBase();			// �R���X�g���N�^
		virtual ~ActorBase();	// �f�X�g���N�^

		virtual void	Initialization()	override	{};	// ������
		virtual void	Update()			override	{};	// �X�V
		virtual void	Draw()							{};	// �`��
		virtual void	BloomDraw()						{};	// �����`��

		int		iGetModelHandle()	{ return this->iModelHandle; };		// ���f���n���h�����擾
		int		iGetLightFrameNo()	{ return this->iLightFrameNo; };	// ���������̐ݒ肳�ꂽ���f���̃t���[���ԍ����擾

		void	SetModelHandle(int iModelHandle)	{ this->iModelHandle	= iModelHandle; };	// ���f���n���h����ݒ�
		void	SetLightFrameNo(int iLightFrameNo)	{ this->iLightFrameNo	= iLightFrameNo; };	// ���������̐ݒ肳�ꂽ���f���̃t���[���ԍ����擾

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		int		iModelHandle;	// ���f���n���h��
		int		iLightFrameNo;	// ���������̐ݒ肳�ꂽ���f���̃t���[���ԍ�
};
