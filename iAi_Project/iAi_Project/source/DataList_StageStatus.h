/* 2025.01.22 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include "StageStatusDefine.h"

/* ��ʃG�t�F�N�g */
#include "ScreenEffect_Base.h"

/* �X�e�[�W��ԊǗ��N���X�̐錾 */

// �X�e�[�W��ԊǗ��N���X
class DataList_StageStatus : public DataListBase
{
	public:
		DataList_StageStatus();				// �R���X�g���N�^
		virtual ~DataList_StageStatus();	// �f�X�g���N�^

		/* �f�[�^�擾 */
		// ���X�g
		std::vector<ScreenEffect_Base*>&	GetScreenEffectList()		{ return this->pScreenEffectList; }			// ��ʃG�t�F�N�g���X�g�擾
		// �P��
		// �X�e�[�W���
		int		iGetGameStatus()	{ return this->iGameStatus; };	// �Q�[����Ԃ��擾
		int		iGetNowStageNo()	{ return this->iNowStageNo; };	// ���݂̃X�e�[�W�ԍ����擾
		int		iGetEndStageNo()	{ return this->iEndStageNo; };	// �ŏI�X�e�[�W�ԍ����擾
		bool	bGetGameSlowFlg()	{ return this->bGameSlowFlg; };	// �X���[���[�V�����t���O���擾		/*2025.02.05 �e�r�듹 �X���[���[�V�����Ɋւ���֐��ǉ� */
		int		iGetSlowCount()		{ return this->iSlowCount; };	// �X���[���[�V�����̃J�E���g
		bool	bGetAddUiFlg()		{ return this->bAddUiFlg; };	// UI�ǉ��t���O���擾
		int		iGetStartTime()		{ return this->iStartTime; };	// �J�n���̎��Ԃ��擾
		int		iGetClearTime()		{ return this->iClearTime; };	// �N���A���̎��Ԃ��擾
		int		iGetJumpStageNo()	{ return this->iJumpStageNo; };	// �W�����v��̃X�e�[�W�ԍ�(�f�o�b�O�p)���擾
		bool	bGetFastEditFlg()	{ return this->bFastEditFlg; };	// �ŏ��ɃG�f�B�b�g��ʂ�\�����邩�̃t���O
		// �J�����֘A
		int		iGetCameraMode()						{ return this->iCameraMode; }							// �J�������[�h�擾
		int		iGetCameraMode_Old()					{ return this->iCameraMode_Old; }						// �J�������[�h�擾(�ύX�O)
		VECTOR	vecGetCameraUp()						{ return this->vecCameraUp; }							// �J�����̏�����擾
		VECTOR	vecGetCameraPosition()					{ return this->vecCameraPosition; }						// �J�����̍��W�擾(���ݒn�_)
		VECTOR	vecGetCameraPosition_Start()			{ return this->vecCameraPosition_Start; }				// �J�����̍��W�擾(�ړ��O�n�_)
		VECTOR	vecGetCameraPosition_Target()			{ return this->vecCameraPosition_Target; }				// �J�����̍��W�擾(�ړ���n�_)
		int		iGetCameraPositionLeapCount()			{ return this->iCameraPositionLeapCount; }				// �J�������W�̐��`�ۊǗp�J�E���g�擾
		VECTOR	vecGetCameraTarget()					{ return this->vecCameraTarget; }						// �J�����̒����_�擾(���݈ʒu)
		VECTOR	vecGetCameraTarget_Start()				{ return this->vecCameraTarget_Start; }					// �J�����̒����_�擾(�ړ��O�ʒu)
		VECTOR	vecGetCameraTarget_Target()				{ return this->vecCameraTarget_Target; }				// �J�����̒����_�擾(�ړ���ʒu)
		int		iGetCameraTargetLeapCount()				{ return this->iCameraTargetLeapCount; }				// �J���������_�̐��`��ԗp�J�E���g�擾
		float	fGetCameraRadius()						{ return this->fCameraRadius; }							// �J�����̒��S�_����̋����擾
		float	fGetCameraAngleX()						{ return this->fCameraAngleX; }							// �J������X����]��(���W�A��)�擾
		float	fGetCameraAngleY()						{ return this->fCameraAngleY; }							// �J������Y����]��(���W�A��)�擾
		float	fGetCameraRotationalSpeed_Controller()	{ return this->fCameraRotationalSpeed_Controller; }		// �J�����̉�]���x(�R���g���[���[)�擾
		float	fGetCameraRotationalSpeed_Mouse()		{ return this->fCameraRotationalSpeed_Mouse; }			// �J�����̉�]���x(�}�E�X)�擾
		float	fGetCameraAngleLimitUp()				{ return this->fCameraAngleLimitUp; }					// �J�����̉�]�p�x�����擾(��)
		float	fGetCameraAngleLimitDown()				{ return this->fCameraAngleLimitDown; }					// �J�����̉�]�p�x�����擾(��)
		int		iGetCloseUpCount()						{ return this->iCloseUpCount; };						// �N���[�Y�A�b�v�J�E���g

		/* �f�[�^�ݒ� */
		// ���X�g
		void	SetScreenEffect(ScreenEffect_Base* pScreenEffect)	{ pScreenEffectList.emplace_back(pScreenEffect); }					// ��ʃG�t�F�N�g���X�g�ݒ�
		// �P��
		// �X�e�[�W���
		void	SetGameStatus(int iGameStatus)		{ this->iGameStatus		= iGameStatus; };	// �Q�[����Ԃ�ݒ�
		void	SetNowStageNo(int iNowStageNo)		{ this->iNowStageNo		= iNowStageNo; };	// �Q�[����Ԃ�ݒ�
		void	SetEndStageNo(int iEndStageNo)		{ this->iEndStageNo		= iEndStageNo; };	// �ŏI�X�e�[�W�ԍ���ݒ�
		void	SetGameSlowFlg(bool bGameSlowFlg)	{ this->bGameSlowFlg	= bGameSlowFlg; };	// �X���[���[�V�����t���O��ݒ�		/*2025.02.05 �X���[���[�V�����Ɋւ���e�r�듹 �֐��ǉ� */
		void	SetSlowCount(int iSlowCount)		{ this->iSlowCount		= iSlowCount; };	// �X���[���[�V�����̃J�E���g
		void	SetAddUiFlg(bool bAddUiFlg)			{ this->bAddUiFlg		= bAddUiFlg; };		// UI�ǉ��t���O�ݒ�
		void	SetStartTime(int iStartTime)		{ this->iStartTime		= iStartTime; };	// �J�n�����Ԃ̐ݒ�
		void	SetClearTime(int iClearTime)		{ this->iClearTime		= iClearTime; };	// �N���A�����Ԃ̐ݒ�
		void	SetJumpStageNo(int iJumpStageNo)	{ this->iJumpStageNo	= iJumpStageNo; };	// �W�����v��̃X�e�[�W�ԍ�(�f�o�b�O�p)�ݒ�
		void	SetFastEditFlg(bool bFastEditFlg)	{ this->bFastEditFlg	= bFastEditFlg; };	// �ŏ��ɃG�f�B�b�g��ʂ�\�����邩�̃t���O
		// �J�����֘A
		void	SetCameraMode(int iCameraMode)										{ this->iCameraMode							= iCameraMode; }				// �J�������[�h�ݒ�
		void	SetCameraMode_Old(int iCameraMode_Old)								{ this->iCameraMode_Old						= iCameraMode_Old; }			// �J�������[�h(�ύX�O)�ݒ�
		void	SetCameraUp(VECTOR vecCameraUp)										{ this->vecCameraUp							= vecCameraUp; }				// �J�����̏�����ݒ�
		void	SetCameraPosition(VECTOR vecCameraPosition)							{ this->vecCameraPosition					= vecCameraPosition; }			// �J�����̍��W�ݒ�(���ݒn�_)
		void	SetCameraPosition_Start(VECTOR vecCameraPosition_Start)				{ this->vecCameraPosition_Start				= vecCameraPosition_Start; }	// �J�����̍��W�ݒ�(�ړ��O�n�_)
		void	SetCameraPosition_Target(VECTOR vecCameraPosition_Target)			{ this->vecCameraPosition_Target			= vecCameraPosition_Target; }	// �J�����̍��W�ݒ�(�ړ���n�_)
		void	SetCameraPositionLeapCount(int iCameraPositionLeapCount)			{ this->iCameraPositionLeapCount			= iCameraPositionLeapCount; }	// �J�������W�̐��`�ۊǗp�J�E���g�ݒ�
		void	SetCameraTarget(VECTOR vecCameraTarget)								{ this->vecCameraTarget						= vecCameraTarget; }			// �J�����̒����_�ݒ�(���ݒn�_)
		void	SetCameraTarget_Start(VECTOR vecCameraTarget_Start)					{ this->vecCameraTarget_Start				= vecCameraTarget_Start; }		// �J�����̒����_�ݒ�(�ړ��O�n�_)
		void	SetCameraTarget_Target(VECTOR vecCameraTarget_Target)				{ this->vecCameraTarget_Target				= vecCameraTarget_Target; }		// �J�����̒����_�ݒ�(�ړ���n�_)
		void	SetCameraTargetLeapCount(int iCameraTargetLeapCount)				{ this->iCameraTargetLeapCount				= iCameraTargetLeapCount; }		// �J���������_�̐��`��ԗp�J�E���g�ݒ�
		void	SetCameraRadius(float fCameraRadius)								{ this->fCameraRadius						= fCameraRadius; }				// �J�����̒��S�_����̋����ݒ�
		void	SetCameraAngleX(float fCameraAngleX)								{ this->fCameraAngleX						= fCameraAngleX; }				// �J������X����]��(���W�A��)�ݒ�
		void	SetCameraAngleY(float fCameraAngleY)								{ this->fCameraAngleY						= fCameraAngleY; }				// �J������Y����]��(���W�A��)�ݒ�
		void	SetCameraRotationalSpeed_Controller(float fCameraRotationalSpeed)	{ this->fCameraRotationalSpeed_Controller	= fCameraRotationalSpeed; }		// �J�����̉�]���x(�R���g���[���[)�ݒ�
		void	SetCameraRotationalSpeed_Mouse(float fCameraRotationalSpeed)		{ this->fCameraRotationalSpeed_Mouse		= fCameraRotationalSpeed; }		// �J�����̉�]���x(�}�E�X)�ݒ�
		void	SetCameraAngleLimitUp(float fCameraAngleupsideLimitUp)				{ this->fCameraAngleLimitUp					= fCameraAngleLimitUp; }		// �J�����̉�]�p�x�����ݒ�(��)
		void	SetCameraAngleLimitDown(float fCameraAngleupsideLimitDown)			{ this->fCameraAngleLimitDown				= fCameraAngleLimitDown; }		// �J�����̉�]�p�x�����ݒ�(��)
		void	SetCameraCloseUpCount(int iCloseUpCount)							{ this->iCloseUpCount						= iCloseUpCount; };				// �N���[�Y�A�b�v�J�E���g

	private:
		/* �Ǘ�����f�[�^���X�g */
		std::vector<ScreenEffect_Base*>		pScreenEffectList;			// ��ʃG�t�F�N�g���X�g

		/* �Ǘ�����f�[�^ */
		int		iGameStatus;	// �Q�[�����
		int		iNowStageNo;	// ���݂̃X�e�[�W�ԍ�
		int		iEndStageNo;	// �ŏI�X�e�[�W�ԍ�
		bool	bGameSlowFlg;	// �X���[���[�V�����t���O		/*2025.02.05 �e�r�듹 �ϐ��ǉ� */
		int		iSlowCount;		// �X���[���[�V�����̃J�E���g
		bool	bAddUiFlg;		// UI�ǉ��t���O(��{�I�Ƀ^�C�g���ł͖����A�Q�[���ł͗L��)
		int		iStartTime;		// �J�n���̎���
		int		iClearTime;		// �N���A���̎���
		int		iJumpStageNo;	// �W�����v��̃X�e�[�W�ԍ�(�f�o�b�O�p)
		bool	bFastEditFlg;	// �ŏ��ɃG�f�B�b�g��ʂ�\�����邩�̃t���O

		/* �J�����֘A */
		int		iCameraMode;						// �J�������[�h
		int		iCameraMode_Old;					// �J�������[�h(�ύX�O)
		VECTOR	vecCameraUp;						// �J�����̏����
		VECTOR	vecCameraPosition;					// �J�����̍��W(���ݒn�_)
		VECTOR	vecCameraPosition_Start;			// �J�����̍��W(�ړ��O�n�_)
		VECTOR	vecCameraPosition_Target;			// �J�����̍��W(�ړ���n�_)
		int		iCameraPositionLeapCount;			// �J�������W�̐��`�ۊǗp�J�E���g
		VECTOR	vecCameraTarget;					// �J�����̒����_(���ݒn�_)
		VECTOR	vecCameraTarget_Start;				// �J�����̒����_(�ړ��O�n�_)
		VECTOR	vecCameraTarget_Target;				// �J�����̒����_(�ړ���n�_)
		int		iCameraTargetLeapCount;				// �J���������_�̐��`��ԗp�J�E���g
		float	fCameraRadius;						// �J�����̒��S�_����̋���(�Y�[����)
		float	fCameraAngleX;						// �J������X����]��(���W�A��)
		float	fCameraAngleY;						// �J������Y����]��(���W�A��)
		float	fCameraRotationalSpeed_Controller;	// �J�����̉�]���x(�R���g���[���[)
		float	fCameraRotationalSpeed_Mouse;		// �J�����̉�]���x(�}�E�X)
		float	fCameraAngleLimitUp;				// �J�����̉�]�p�x����(��)
		float	fCameraAngleLimitDown;				// �J�����̉�]�p�x����(��)
		int		iCloseUpCount;						// �N���[�Y�A�b�v�J�E���g
};
