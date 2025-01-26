/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ObjectBase.h"

/* ���O��ԏȗ� */
using namespace Struct_Collision;

/* ���ׂẴv���b�g�t�H�[���̃x�[�X�ƂȂ�N���X�̐錾 */

// �v���b�g�t�H�[���x�[�X�N���X
class PlatformBase : public ObjectBase
{
	public:
		PlatformBase();				// �R���X�g���N�^
		virtual ~PlatformBase();	// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������

		int		iGetModelHandle()		{ return this->iModelHandle; };			// ���f���n���h�����擾
		VECTOR	vecGetScale()			{ return this->vecScale; };				// �g�嗦���擾

		void	SetModelHandle(int iModelHandle)			{ this->iModelHandle		= iModelHandle; };			// ���f���n���h����ݒ�
		void	SetScale(VECTOR vecScale)					{ this->vecScale			= vecScale; };				// �g�嗦��ݒ�

	private:
	protected:
		/* �ϐ� */
		int						iModelHandle;			// ���f���n���h��
		VECTOR					vecScale;				// �g�嗦(x,y,z�������ꂼ��̊g��{��)
};
