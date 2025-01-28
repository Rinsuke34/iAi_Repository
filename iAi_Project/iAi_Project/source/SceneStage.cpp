/* 2025.01.16 �t�@�C���쐬 ��򕗏� */

#include "SceneStage.h"

/* �X�e�[�W�N���X�̒�` */

// �R���X�g���N�^
SceneStage::SceneStage(): SceneBase("Stage", 1, true)
{
	/* �f�[�^���X�g�쐬 */
	{
		/* �f�[�^���X�g�T�[�o�[��"�v���C���[���"��ǉ� */
		gpDataListServer->AddDataList(new DataList_PlayerStatus());

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

		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList	= dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* UI�ǉ� */
	{
		/* �N���X�w�A */
		gpSceneServer->AddSceneReservation(new SceneUi_Crosshairs());

		/* HP */
		gpSceneServer->AddSceneReservation(new SceneUi_Hp());

		/* �N�i�C */
		gpSceneServer->AddSceneReservation(new SceneUi_Kunai());

		/* �R���{ */
		gpSceneServer->AddSceneReservation(new SceneUi_Combo());
	}

	/* �}�b�v�n���h���쐬 */
	this->iShadowMapScreenHandle			= MakeShadowMap(SHADOWMAP_SIZE, SHADOWMAP_SIZE);
	this->iLightMapScreenHandle				= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	this->iLightMapScreenHandle_DownScale	= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);
	this->iLightMapScreenHandle_Gauss		= MakeScreen(SCREEN_SIZE_WIDE / 8, SCREEN_SIZE_HEIGHT / 8);

	/* ������ */
	Initialization();
}

// �f�X�g���N�^
SceneStage::~SceneStage()
{
	/* �f�[�^���X�g�폜 */
	gpDataListServer->DeleteDataList("DataList_PlayerStatus");	// �v���C���[���
	gpDataListServer->DeleteDataList("DataList_Object");		// �I�u�W�F�N�g�Ǘ�

	/* �}�b�v�n���h���폜 */
	DeleteShadowMap(iShadowMapScreenHandle);	// �V���h�E�}�b�v
	DeleteGraph(iLightMapScreenHandle);			// ���C�g�}�b�v
}

// ������
void SceneStage::Initialization()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ɕύX */
	this->GameStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
}

// �v�Z
void SceneStage::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (iGameStatus)
	{
		/* "�Q�[�����s"��� */
		case GAMESTATUS_PLAY_GAME:
			/* ���ׂẴI�u�W�F�N�g�̍X�V */
			ObjectList->UpdateAll();

			/* �폜�t���O���L���ȃI�u�W�F�N�g�̍폜 */
			ObjectList->DeleteAll();
			break;

		/* "�G�f�B�b�g"��� */
		case GAMESTATUS_EDIT:
			/* �G�f�B�b�g��ʍ쐬���� */
			{
				/* �J�������[�h��"�Œ�"�ɕύX */
				this->PlayerStatusList->SetCameraMode(CAMERA_MODE_LOCK);

				/* �V�[��"�G�f�B�b�g���"���쐬 */
				SceneBase* pAddScene = new SceneEdit();

				/* �V�[��"�G�f�B�b�g���"���V�[���T�[�o�[�ɒǉ� */
				gpSceneServer->AddSceneReservation(pAddScene);
			}
			break;

		/* "���̃X�e�[�W�֑J��"��� */
		case GAMESTATUS_NEXTSTAGE:
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;

			/* �Q�[����Ԃ�"�Q�[�����s"�ɕύX���� */
			this->GameStatusList->SetGameStatus(GAMESTATUS_PLAY_GAME);
			break;
	}
}

// �`��
void SceneStage::Draw()
{
	/* ���[�f�B���O���ł��邩�m�F */
	if (gbNowLoadingFlg == true)
	{
		// ���[�f�B���O���ł���ꍇ
		/* �`�ʂ��s��Ȃ� */
		return;
	}
	
	/* �����x�Ɋ֌W�Ȃ��`�ʂ���悤�ݒ�@*/
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);

	/* �V���h�E�}�b�v�쐬 */
	SetupShadowMap();

	/* ���C�g�}�b�v�쐬 */
	SetupLightMap();

	/* �I�u�W�F�N�g�`�� */
	{
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

		/* �R���W�����`�ʃt���O���L���ł��邩�m�F */
		if (gbDrawCollisionFlg == true)
		{
			/* �R���W�����`�� */
			/* ���������ǂ����֌W�Ȃ��`�悷��悤�ɐݒ� */
			MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);

			/* ���ׂẴI�u�W�F�N�g�̃R���W������`�� */
			ObjectList->DrawAll_Collision();
		}
	}

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
		// �����C�g�}�b�v�̍��F������`�ʂ���Ȃ��悤�ɂ���
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

		/* ���C�g�}�b�v��`�� */
		DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iLightMapScreenHandle, FALSE);

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
void SceneStage::SetupShadowMap()
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
void SceneStage::SetupLightMap()
{
	/* ���C�g�}�b�v�`�� */
	{
		/* ���C�g�}�b�v�ւ̕`�ʂ��J�n */
		SetDrawScreen(this->iLightMapScreenHandle);

		/* ���C�e�B���O�𖳌��� */
		SetUseLighting(FALSE);

		/* ��ʃN���A */
		ClearDrawScreen();

		/* �J�����̐ݒ� */
		SetCamera();

		/* ���ׂẴI�u�W�F�N�g�̔��������̕`�� */
		ObjectList->DrawAll_Bloom();

		/* ���C�g�}�b�v�ւ̕`�ʂ��I�� */
		SetDrawScreen(DX_SCREEN_BACK);

		/* ���C�e�B���O��L���� */
		SetUseLighting(TRUE);
	}

	/* ���C�g�}�b�v�̏k���ł��擾 */
	GraphFilterBlt(this->iLightMapScreenHandle, this->iLightMapScreenHandle_DownScale, DX_GRAPH_FILTER_DOWN_SCALE, LIGHTMAP_DOWNSCALE);

	/* ���C�g�}�b�v�̂ڂ₩�����ł��擾 */
	GraphFilterBlt(this->iLightMapScreenHandle_DownScale, this->iLightMapScreenHandle_Gauss, DX_GRAPH_FILTER_GAUSS, LIGHTMAP_GAUSS_WIDTH, LIGHTMAP_GAUSS_RATIO);
}

// �J�����ݒ�
void SceneStage::SetCamera()
{
	/* �J�������[�h�ɉ����ď�����ύX */
	switch (this->PlayerStatusList->iGetCameraMode())
	{
		/* �t���[ */
		case CAMERA_MODE_FREE:
			CameraRotateUpdata();
			SetCamera_Free();
			break;

		/* �Œ� */
		case CAMERA_MODE_LOCK:
			SetCamera_Lock();
			break;

		/* �\��(�Y�[��) */
		case CAMERA_MODE_AIM:
			CameraRotateUpdata();
			SetCamera_Aim();
			break;
	}
}

// ���͂ɂ��J������]�ʎ擾
void SceneStage::CameraRotateUpdata()
{
	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX						= this->PlayerStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY						= this->PlayerStatusList->fGetCameraAngleY();						// Y����]��
	float fCameraRotationalSpeed_Controller	= this->PlayerStatusList->fGetCameraRotationalSpeed_Controller();	// ��]���x(�R���g���[���[)
	float fCameraRotationalSpeed_Mouse		= this->PlayerStatusList->fGetCameraRotationalSpeed_Mouse();		// ��]���x(�}�E�X)

	/* ���͂���J������]�ʂ��擾 */
	/* �}�E�X */
	fCameraAngleX -= gstKeyboardInputData.iMouseMoveX * fCameraRotationalSpeed_Mouse;
	fCameraAngleY -= gstKeyboardInputData.iMouseMoveY * fCameraRotationalSpeed_Mouse;

	/* �R���g���[���[ */
	fCameraAngleX += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]);
	fCameraAngleY += fCameraRotationalSpeed_Controller * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]);

	/* Y���̉�]�p�x���� */
	float fAngleLimitUp		= this->PlayerStatusList->fGetCameraAngleLimitUp();		// ������̐����p�x
	float fAngleLimitDown	= this->PlayerStatusList->fGetCameraAngleLimitDown();	// �������̐����p�x

	if (fCameraAngleY > fAngleLimitUp)		{ fCameraAngleY = fAngleLimitUp; }		// ������̐����p�x�𒴂����琧���p�x�ɐݒ�
	if (fCameraAngleY < fAngleLimitDown)	{ fCameraAngleY = fAngleLimitDown; }	// �������̐����p�x�𒴂����琧���p�x�ɐݒ�

	/* ��]�ʂ��X�V */
	this->PlayerStatusList->SetCameraAngleX(fCameraAngleX);
	this->PlayerStatusList->SetCameraAngleY(fCameraAngleY);
}

// �J�����ݒ�(�t���[���[�h)
void SceneStage::SetCamera_Free()
{
	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX = this->PlayerStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY = this->PlayerStatusList->fGetCameraAngleY();						// Y����]��

	/* �v���C���[���W�擾 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* �J���������_�ݒ� */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT - 20.f, 0));
	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	/* �J�������W�ݒ� */
	float fRadius	= this->PlayerStatusList->fGetCameraRadius();				// �����_����̋���
	float fCameraX	= fRadius * -sinf(fCameraAngleX) + vecCameraTarget.x;	// X���W
	float fCameraY	= fRadius * -sinf(fCameraAngleY) + vecCameraTarget.y;	// Y���W
	float fCameraZ	= fRadius * +cosf(fCameraAngleX) + vecCameraTarget.z;	// Z���W

	this->PlayerStatusList->SetCameraPosition(VGet(fCameraX, fCameraY, fCameraZ));

	/* �J�����ݒ� */
	SetCameraPositionAndTargetAndUpVec(this->PlayerStatusList->vecGetCameraPosition(), this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraUp());
}

// �J�����ݒ�(�Œ胂�[�h)
void SceneStage::SetCamera_Lock()
{
	/* �J�����ݒ� */
	// ���X�V�͍s��Ȃ�
	{
		SetCameraPositionAndTargetAndUpVec(this->PlayerStatusList->vecGetCameraPosition(), this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraUp());
	}
}

// �J�����ݒ�(�\��(�Y�[��))
void  SceneStage::SetCamera_Aim()
{
	/* ���݂̉�]�ʓ����擾 */
	float fCameraAngleX = this->PlayerStatusList->fGetCameraAngleX();						// X����]��
	float fCameraAngleY = this->PlayerStatusList->fGetCameraAngleY();						// Y����]��

	/* �v���C���[���W�擾 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	/* �J���������_�ݒ� */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, PLAYER_HEIGHT - 20.f, 0));
	float fRadius		= 800.f;												// �����_����̋���
	vecCameraTarget.x	= fRadius * +sinf(fCameraAngleX) + vecCameraTarget.x;	// X���W
	vecCameraTarget.y	= fRadius * +sinf(fCameraAngleY) + vecCameraTarget.y;	// Y���W
	vecCameraTarget.z	= fRadius * -cosf(fCameraAngleX) + vecCameraTarget.z;	// Z���W

	/* �J�����̐�[�����b�N�I���͈͂̉��ɍ��킹�� */
	//vecCameraTarget = this->PlayerStatusList->stGetMeleeSearchCollision().vecCapsuleBottom;

	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	/* �J�������W�ݒ� */
	VECTOR vecCameraPosition	= VAdd(vecPlayerPos, VGet(0.f, PLAYER_HEIGHT - 20.f, 0.f));
	fRadius				= 200.f;												// �����_����̋���
	fCameraAngleX		= fCameraAngleX + DX_PI_F / 4.0f;						// �E���ɔz�u���邽�߂̊p�x����
	vecCameraPosition.x = fRadius * -sinf(fCameraAngleX) + vecCameraPosition.x; // X���W
	vecCameraPosition.y = fRadius * -sinf(fCameraAngleY) + vecCameraPosition.y; // Y���W
	vecCameraPosition.z = fRadius * +cosf(fCameraAngleX) + vecCameraPosition.z; // Z���W

	this->PlayerStatusList->SetCameraPosition(vecCameraPosition);

	/* �J�����ݒ� */
	SetCameraPositionAndTargetAndUpVec(this->PlayerStatusList->vecGetCameraPosition(), this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraUp());
}

// �f�o�b�O�`��
void SceneStage::DrawDebug()
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
	if (gbDrawLightMapGaussFlg == true)
	{
		DrawExtendGraph(SCREEN_SIZE_WIDE - DEBUG_MAP_WIDTH, DEBUG_MAP_HEIGHT * iDrawCount, SCREEN_SIZE_WIDE, DEBUG_MAP_HEIGHT * (iDrawCount + 1), this->iLightMapScreenHandle_Gauss, FALSE);
		iDrawCount++;
	}
}
