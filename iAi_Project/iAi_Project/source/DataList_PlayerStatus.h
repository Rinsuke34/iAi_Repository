/* 2024.12.26 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "PublicInclude.h"
#include "PlayerStatusDefine.h"

/* �v���C���[��ԊǗ��N���X�̐錾 */

// �v���C���[��ԊǗ��N���X
class DataList_PlayerStatus : public DataListBase
{
	public:
		DataList_PlayerStatus();			// �R���X�g���N�^
		virtual ~DataList_PlayerStatus();	// �f�X�g���N�^

		/* �f�[�^�擾 */
		// ��{�X�e�[�^�X�֘A
		
		// �J�����֘A
		VECTOR	vecGetCameraUp()				{ return this->vecCameraUp; };				// �J�����̏�����擾
		VECTOR	vecGetCameraPosition()			{ return this->vecCameraPosition; };		// �J�����̍��W�擾
		VECTOR	vecGetCameraTarget()			{ return this->vecCameraTarget; };			// �J�����̒����_�擾
		float	fGetCameraRadius()				{ return this->fCameraRadius; };			// �J�����̒��S�_����̋����擾
		float	fGetCameraAngleX()				{ return this->fCameraAngleX; };			// �J������X����]�ʎ擾
		float	fGetCameraAngleY()				{ return this->fCameraAngleY; };			// �J������Y����]�ʎ擾
		float	fGetCameraRotationalSpeed()		{ return this->fCameraRotationalSpeed; };	// �J�����̉�]���x�擾
		float	fGetCameraAngleLimitUp()		{ return this->fCameraAngleLimitUp; };		// �J�����̉�]�p�x�����擾(��)
		float	fGetCameraAngleLimitDown()		{ return this->fCameraAngleLimitDown; };	// �J�����̉�]�p�x�����擾(��)

		/* �f�[�^�ݒ� */
		// ��{�X�e�[�^�X�֘A

		// �J�����֘A
		void	SetCameraUp(VECTOR vecCameraUp)								{ this->vecCameraUp				= vecCameraUp; };				// �J�����̏�����ݒ�
		void	SetCameraPosition(VECTOR vecCameraPosition)					{ this->vecCameraPosition		= vecCameraPosition; };			// �J�����̍��W�ݒ�
		void	SetCameraTarget(VECTOR vecCameraTarget)						{ this->vecCameraTarget			= vecCameraTarget; };			// �J�����̒����_�ݒ�
		void	SetCameraRadius(float fCameraRadius)						{ this->fCameraRadius			= fCameraRadius; };				// �J�����̒��S�_����̋����ݒ�
		void	SetCameraAngleX(float fCameraAngleX)						{ this->fCameraAngleX			= fCameraAngleX; };				// �J������X����]�ʐݒ�
		void	SetCameraAngleY(float fCameraAngleY)						{ this->fCameraAngleY			= fCameraAngleY; };				// �J������Y����]�ʐݒ�
		void	SetCameraRotationalSpeed(float fCameraRotationalSpeed)		{ this->fCameraRotationalSpeed	= fCameraRotationalSpeed; };	// �J�����̉�]���x�ݒ�
		void	SetCameraAngleLimitUp(float fCameraAngleupsideLimitUp)		{ this->fCameraAngleLimitUp		= fCameraAngleLimitUp; };		// �J�����̉�]�p�x�����ݒ�(��)
		void	SetCameraAngleLimitDown(float fCameraAngleupsideLimitDown)	{ this->fCameraAngleLimitDown	= fCameraAngleLimitDown; };		// �J�����̉�]�p�x�����ݒ�(��)

	private:
		/* ��{�X�e�[�^�X�֘A */

		/* �J�����֘A */
		VECTOR	vecCameraUp;				// �J�����̏����
		VECTOR	vecCameraPosition;			// �J�����̍��W
		VECTOR	vecCameraTarget;			// �J�����̒����_
		float	fCameraRadius;				// �J�����̒��S�_����̋���(�Y�[����)
		float	fCameraAngleX;				// �J������X����]��
		float	fCameraAngleY;				// �J������Y����]��
		float	fCameraRotationalSpeed;		// �J�����̉�]���x
		float	fCameraAngleLimitUp;		// �J�����̉�]�p�x����(��)
		float	fCameraAngleLimitDown;		// �J�����̉�]�p�x����(��)

	protected:
};
