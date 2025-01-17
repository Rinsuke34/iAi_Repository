/* 2025.01.16 �t�@�C���쐬 ��򕗏� */

#include "StageBase.h"

/* �X�e�[�W�̃x�[�X�N���X�̒�` */

// �R���X�g���N�^
StageBase::StageBase()
{
	/* �񓯊��ǂݍ��݂�L�������� */
	SetUseASyncLoadFlag(true);

	/* �f�[�^���X�g�쐬 */
	{
		/* �f�[�^���X�g�T�[�o�[��"�I�u�W�F�N�g�Ǘ�"��ǉ� */
		gpDataListServer->AddDataList(new DataList_Object());
	}

	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�v���C���[���"���擾 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "3D���f���Ǘ�"���擾 */
		this->ModelList			= dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
	}

	/* �e�X�g�p���� �I�� */

	/* �񓯊��ǂݍ��݂𖳌������� */
	SetUseASyncLoadFlag(false);

	/* �}�b�v�n���h���쐬 */
	this->iShadowMapScreenHandle			= MakeShadowMap(SHADOWMAP_SIZE, SHADOWMAP_SIZE);
	this->iLightMapScreenHandle				= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle_DownScale	= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iLightMapScreenHandle_Gauss		= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
}

// �f�X�g���N�^
StageBase::~StageBase()
{
	/* �f�[�^���X�g�폜 */
	gpDataListServer->DeleteDataList("DataList_Object");		// �I�u�W�F�N�g�Ǘ�

	/* �}�b�v�n���h���폜 */
	DeleteShadowMap(iShadowMapScreenHandle);	// �V���h�E�}�b�v
	DeleteGraph(iLightMapScreenHandle);			// ���C�g�}�b�v
}

// �v�Z
void StageBase::Process()
{
	/* ���ׂẴI�u�W�F�N�g�̍X�V */
	ObjectList->UpdateAll();

	/* �폜�t���O���L���ȃI�u�W�F�N�g�̍폜 */
	ObjectList->DeleteAll();
}

// �`��
void StageBase::Draw()
{
	/* �����x�Ɋ֌W�Ȃ��`�ʂ���悤�ݒ�@*/
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);

	/* �V���h�E�}�b�v�쐬 */
	SetupShadowMap();

	/* ���C�g�}�b�v�쐬 */
	SetupLightMap();

	/* �J�����̐ݒ� */
	SetCamera();

	/* �`�ʂɎg�p����V���h�E�}�b�v�̐ݒ� */
	SetUseShadowMap(0, this->iShadowMapScreenHandle);

	/* ������������`�ʂ��Ȃ��悤�ݒ� */
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);

	/* �����������̂Ȃ����ׂẴI�u�W�F�N�g��`�� */
	ObjectList->DrawAll();

	/* �`�ʂɎg�p����V���h�E�}�b�v�̐ݒ������ */
	SetUseShadowMap(this->iShadowMapScreenHandle, -1);

	/* �����������̂ݕ`�ʂ���悤�ɐݒ� */
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_SEMITRANS_ONLY);

	/* �����������̂��ׂẴI�u�W�F�N�g��`�� */
	ObjectList->DrawAll();

	/* �G�t�F�N�g�`�� */
	{
		/* �G�t�F�N�g�X�V */
		UpdateEffekseer3D();

		/* �G�t�F�N�g�p�J�����ʒu���� */
		Effekseer_Sync3DSetting();

		/* �G�t�F�N�g�`�� */
		DrawEffekseer3D();
	}

	/* ���C�g�}�b�v�`�� */
	{
		/* �`�惂�[�h���o�C���j�A�t�B���^�����O�ɕύX�@*/
		// ���g�厞�Ƀh�b�g���ڂ₯������
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		/* �`��u�����h���[�h�����Z�ɂ��� */
		// �����C�g�}�b�v�̍��F�����͕`�ʂ���Ȃ��悤�ɂ���
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

		/* ���C�g�}�b�v(�ڂ���)��`�� */
		DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iLightMapScreenHandle_Gauss, FALSE);

		/* �`��u�����h���[�h���u�����h�����ɖ߂� */
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		/* �`�惂�[�h���A���X�g�ɖ߂� */
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

	/* �f�o�b�O�`�� */
	DrawDebug();
}

// �V���h�E�}�b�v�̐ݒ�
void StageBase::SetupShadowMap()
{
	/* ���C�g�����ݒ� */
	SetShadowMapLightDirection(this->iShadowMapScreenHandle, VGet(0.8f, -1.f, 0.8f));

	/* �V���h�E�}�b�v�̕`�ʔ͈͐ݒ� */
	{
		/* �J�����̃^�[�Q�b�g���W���擾 */
		VECTOR vecTargetPos = this->PlayerStatusList->vecGetCameraTarget();

		/* �V���h�E�}�b�v�͈͐ݒ� */
		// ���J�����̃^�[�Q�b�g���W�𒆐S�ɕ`��
		SetShadowMapDrawArea(this->iShadowMapScreenHandle, VAdd(vecTargetPos, VGet(-SHADOWMAP_RANGE, -SHADOWMAP_RANGE, -SHADOWMAP_RANGE)), VAdd(vecTargetPos, VGet(SHADOWMAP_RANGE, SHADOWMAP_RANGE, SHADOWMAP_RANGE)));
	}

	/* �V���h�E�}�b�v�ւ̕`�ʂ��J�n */
	ShadowMap_DrawSetup(this->iShadowMapScreenHandle);

	/* ���ׂẴI�u�W�F�N�g�̕`�� */
	ObjectList->DrawAll();

	/* �V���h�E�}�b�v�ւ̕`�ʂ��I�� */
	ShadowMap_DrawEnd();
}

// ���C�g�}�b�v�̐ݒ�
void StageBase::SetupLightMap()
{
	/* ���C�g�}�b�v�`�� */
	{
		/* ���C�g�}�b�v�ւ̕`�ʂ��J�n */
		SetDrawScreen(this->iLightMapScreenHandle);

		/* ��ʃN���A */
		ClearDrawScreen();

		/* �J�����̐ݒ� */
		SetCamera();

		/* ���ׂẴI�u�W�F�N�g�̔��������̕`�� */
		ObjectList->BloomDrawAll();

		/* ���C�g�}�b�v�ւ̕`�ʂ��I�� */
		SetDrawScreen(DX_SCREEN_BACK);
	}

	/* ���C�g�}�b�v�̏k���ł��擾 */
	GraphFilterBlt(this->iLightMapScreenHandle, this->iLightMapScreenHandle_DownScale, DX_GRAPH_FILTER_DOWN_SCALE, LIGHTMAP_DOWNSCALE);

	/* ���C�g�}�b�v�̂ڂ₩�����ł��擾 */
	GraphFilterBlt(this->iLightMapScreenHandle_DownScale, this->iLightMapScreenHandle_Gauss, DX_GRAPH_FILTER_GAUSS, LIGHTMAP_GAUSS_WIDTH, LIGHTMAP_GAUSS_RATIO);
}

// �J�����ݒ�
void StageBase::SetCamera()
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
void StageBase::SetCamera_Free()
{
	/* �v���C���[���W�擾 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* �J���������_�ݒ� */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, 100, 0));
	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	/* ���_�ύX�ɕK�v�ȃf�[�^�擾 */
	float fCameraAngleX = this->PlayerStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY = this->PlayerStatusList->fGetCameraAngleY();						// Y����]��
	float fCameraRotationalSpeed_Controller = this->PlayerStatusList->fGetCameraRotationalSpeed_Controller();	// ��]���x(�R���g���[���[)
	float fCameraRotationalSpeed_Mouse = this->PlayerStatusList->fGetCameraRotationalSpeed_Mouse();		// ��]���x(�}�E�X)

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
		float fAngleLimitUp = this->PlayerStatusList->fGetCameraAngleLimitUp();		// ������̐����p�x
		float fAngleLimitDown = this->PlayerStatusList->fGetCameraAngleLimitDown();	// �������̐����p�x

		if (fCameraAngleY > fAngleLimitUp) { fCameraAngleY = fAngleLimitUp; }		// ������̐����p�x�𒴂����琧���p�x�ɐݒ�
		if (fCameraAngleY < fAngleLimitDown) { fCameraAngleY = fAngleLimitDown; }	// �������̐����p�x�𒴂����琧���p�x�ɐݒ�
	}

	/* ��]�ʂ��X�V */
	{
		this->PlayerStatusList->SetCameraAngleX(fCameraAngleX);
		this->PlayerStatusList->SetCameraAngleY(fCameraAngleY);
	}

	/* �J�������W�ݒ� */
	{
		float fRadius = this->PlayerStatusList->fGetCameraRadius();			// �����_����̋���
		float fCameraX = fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X���W
		float fCameraY = fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y���W
		float fCameraZ = fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z���W

		this->PlayerStatusList->SetCameraPosition(VGet(fCameraX, fCameraY, fCameraZ));
	}

	/* �J�����ݒ� */
	{
		SetCameraPositionAndTargetAndUpVec(this->PlayerStatusList->vecGetCameraPosition(), this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraUp());
	}
}

// �f�o�b�O�`��
void StageBase::DrawDebug()
{
	int iDrawCount = 0;

	/* �V���h�E�}�b�v�`�� */
	if (gbDrawShadowMapFlg == true)
	{
		TestDrawShadowMap(iShadowMapScreenHandle, SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1));
		iDrawCount++;
	}

	/* ���C�g�}�b�v�`�� */
	if (gbDrawLightMapFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1), this->iLightMapScreenHandle, FALSE);
		iDrawCount++;
	}

	/* ���C�g�}�b�v(�k��)�`�� */
	if (gbDrawLightMapDownScaleFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1), this->iLightMapScreenHandle_DownScale, FALSE);
		iDrawCount++;
	}

	/* ���C�g�}�b�v(�ڂ���)�`�� */
	if (gpDrawLightMapGaussFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1), this->iLightMapScreenHandle_Gauss, FALSE);
		iDrawCount++;
	}
}
