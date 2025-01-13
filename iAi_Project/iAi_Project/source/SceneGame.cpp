/* 2024.12.XX YYYY ZZZZ */

#include "SceneGame.h"

/* �V�[���u�Q�[���v�̒�` */

// �R���X�g���N�^
SceneGame::SceneGame() : SceneBase("Game", 0, false)
{
	/* �񓯊��ǂݍ��݂�L�������� */
	SetUseASyncLoadFlag(true);

	/* �e�X�g�p���� �J�n */

	/* �f�[�^���X�g�쐬 */
	{
		/* �f�[�^���X�g�T�[�o�[��"�I�u�W�F�N�g�Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_Object());

		/* �f�[�^���X�g�T�[�o�[��"�v���C���[���"��ǉ� */
		gpDataListServer->AddDataList(new DataList_PlayerStatus());

		/* �f�[�^���X�g�T�[�o�[��"3D���f���Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_Model());
	}
	
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "3D���f���Ǘ�"���擾 */
		this->ModelList = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
	}

	/* �}�b�v�f�[�^�ǂݍ��� */
	LoadMapData();

	/* �e�X�g�p���� �I�� */

	/* �񓯊��ǂݍ��݂𖳌������� */
	SetUseASyncLoadFlag(false);

	/* �}�b�v�n���h���쐬 */
	this->iShadowMapScreenHandle	= MakeShadowMap(SCREEN_SIZE_WIDE * 2, SCREEN_SIZE_HEIGHT * 2);	// �V���h�E�}�b�v(��ʂ�2�{�̃T�C�Y�ō쐬)
	this->iLightMapScreenHandle		= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
}

// �f�X�g���N�^
SceneGame::~SceneGame()
{
	/* �f�[�^���X�g�폜 */
	gpDataListServer->DeleteDataList("DataList_Object");		// �I�u�W�F�N�g�Ǘ�
	gpDataListServer->DeleteDataList("DataList_PlayerStatus");	// �v���C���[���
	gpDataListServer->DeleteDataList("DataList_Model");			// 3D���f���Ǘ�

	/* �}�b�v�n���h���폜 */
	DeleteShadowMap(iShadowMapScreenHandle);	// �V���h�E�}�b�v
	DeleteGraph(iLightMapScreenHandle);			// ���C�g�}�b�v
}

// �v�Z
void SceneGame::Process()
{
	/* ���ׂẴI�u�W�F�N�g�̍X�V */
	ObjectList->UpdateAll();
}

// �`��
void SceneGame::Draw()
{
	/* ���ׂẴI�u�W�F�N�g�̕`�� */
	ObjectList->DrawAll();

	/* �J�����̐ݒ� */
	SetCamera();
}

// �J�����ݒ�
void SceneGame::SetCamera()
{
	/* �J�������[�h�ɉ����ď�����ύX */
	switch (this->PlayerStatusList->iGetCameraMode())
	{
		/* �t���[���[�h */
		case CAMERA_MODE_FREE:
			SetCamera_Free();
			break;
	}
}

// �J�����ݒ�(�t���[���[�h)
void SceneGame::SetCamera_Free()
{
	/* �v���C���[���W�擾 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* �J���������_�ݒ� */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, 100, 0));
	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	/* ���_�ύX�ɕK�v�ȃf�[�^�擾 */
	float fCameraAngleX						= this->PlayerStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY						= this->PlayerStatusList->fGetCameraAngleY();						// Y����]��
	float fCameraRotationalSpeed_Controller	= this->PlayerStatusList->fGetCameraRotationalSpeed_Controller();	// ��]���x(�R���g���[���[)
	float fCameraRotationalSpeed_Mouse		= this->PlayerStatusList->fGetCameraRotationalSpeed_Mouse();		// ��]���x(�}�E�X)

	/* ���͂���J������]�ʂ��擾 */
	/* �}�E�X */
	{
		fCameraAngleX -= gstKeyboardInputData.iMouseMoveX * fCameraRotationalSpeed_Mouse;
		fCameraAngleY -= gstKeyboardInputData.iMouseMoveY * fCameraRotationalSpeed_Mouse;
	}

	/* �R���g���[���[ */
	{
		fCameraAngleX += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]);
		fCameraAngleY += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]);
	}

	/* Y���̉�]�p�x���� */
	{
		float fAngleLimitUp		= this->PlayerStatusList->fGetCameraAngleLimitUp();		// ������̐����p�x
		float fAngleLimitDown	= this->PlayerStatusList->fGetCameraAngleLimitDown();	// �������̐����p�x

		if (fCameraAngleY > fAngleLimitUp)		{ fCameraAngleY = fAngleLimitUp; }		// ������̐����p�x�𒴂����琧���p�x�ɐݒ�
		if (fCameraAngleY < fAngleLimitDown)	{ fCameraAngleY = fAngleLimitDown; }	// �������̐����p�x�𒴂����琧���p�x�ɐݒ�
	}

	/* ��]�ʂ��X�V */
	{
		this->PlayerStatusList->SetCameraAngleX(fCameraAngleX);
		this->PlayerStatusList->SetCameraAngleY(fCameraAngleY);
	}

	/* �J�������W�ݒ� */
	{
		float fRadius	= this->PlayerStatusList->fGetCameraRadius();			// �����_����̋���
		float fCameraX	= fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X���W
		float fCameraY	= fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y���W
		float fCameraZ	= fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z���W

		this->PlayerStatusList->SetCameraPosition(VGet(fCameraX, fCameraY, fCameraZ));
	}

	/* �J�����ݒ� */
	{
		SetCameraPositionAndTargetAndUpVec(this->PlayerStatusList->vecGetCameraPosition(), this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraUp());
	}
}

// �f�o�b�O�`��
void SceneGame::DrawDebug()
{
	/* �V���h�E�}�b�v�`�� */
	if (gbDrawShadowMapFlg == true)
	{
		TestDrawShadowMap(iShadowMapScreenHandle, SCREEN_SIZE_WIDE - 516, 0, SCREEN_SIZE_WIDE, 516);
	}

	/* ���C�g�}�b�v�`�� */
	if (gbDrawLightMapFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - 516, 0, SCREEN_SIZE_WIDE, 516, this->iLightMapScreenHandle, FALSE);
	}
}
