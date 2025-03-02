/* 2025.02.04 �t�@�C���쐬 ��򕗏� */

#include "SceneStage.h"

/* �X�e�[�W�N���X�̒�`(�`��) */

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

	/* ���C���̕`�ʏ��� */
	SetupMainScreen();

	/* ���C����ʂ�`�� */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iMainScreenHandle, FALSE);

	/* ��ʃG�t�F�N�g��`�� */
	SetupScreenEffects();

	/* �J�����ݒ� */
	SetCamera();

	/* �Q�[����Ԃ�"�X�e�[�W�N���A"�ł���ꍇ */
	// ���X�e�[�W�N���A�����p�̃J�E���g��1�ȏ�ł���Ȃ�"�X�e�[�W�N���A"����
	if (this->iStageClear_Count > 0)
	{
		// �X�e�[�W�N���A�ł���ꍇ
		/* �t�F�[�h�C������ */
		{
			/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iBlendAlpha_StageClear_Fadein);

			/* ��ʑS�̂𔒐F�ŕ`�� */
			DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(255, 255, 255), TRUE);

			/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			/* �V�[��"���U���g"���쐬�������m�F */
			if (this->iStageClear_Count >= STAGECLEAR_COUNT_START_RESULT)
			{
				// �쐬���Ă���ꍇ
				/* ���U���g�p�̃t���[����`�� */
				DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_ResultFrame, FALSE);
			}
		}
	}	
}

// �V���h�E�}�b�v�̐ݒ�
void SceneStage::SetupShadowMap()
{
	/* ���C�g�����ݒ� */
	SetShadowMapLightDirection(this->iShadowMapScreenHandle, VNorm(VGet(0.f, -1.f, 0.f)));

	/* �V���h�E�}�b�v�̕`�ʔ͈͐ݒ� */
	{
		/* �J�����̃^�[�Q�b�g���W���擾 */
		VECTOR vecTargetPos = this->StageStatusList->vecGetCameraTarget();

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

// ���C���̕`�ʏ���
void SceneStage::SetupMainScreen()
{
	/* ���C����ʂւ̕`�ʂ��J�n */
	SetDrawScreen(this->iMainScreenHandle);

	/* ��ʃN���A */
	ClearDrawScreen();

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

	/* �G�t�F�N�g�̕`�ʏ��� */
	SetupEffectScreen();

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

	/* ���C����ʂւ̕`�ʂ��I�� */
	SetDrawScreen(DX_SCREEN_BACK);
}

/* �G�t�F�N�g�̕`�ʏ��� */
void SceneStage::SetupEffectScreen()
{
	/* �G�t�F�N�g�X�V */
	UpdateEffekseer3D();

	/* �G�t�F�N�g�p�J�����ʒu���� */
	Effekseer_Sync3DSetting();

	/* �G�t�F�N�g�`�� */
	//ObjectList->DrawEffect();
	DrawEffekseer3D();
}

// ��ʃG�t�F�N�g
void SceneStage::SetupScreenEffects()
{
	/* ��ʃG�t�F�N�g�`�� */
	for (auto& pScreenEffectDraw : this->StageStatusList->GetScreenEffectList())
	{
		/* ��ʃG�t�F�N�g�X�V���� */
		pScreenEffectDraw->Update(this->iMainScreenHandle);
	}

	/* �폜�t���O���L���ȉ�ʃG�t�F�N�g���폜 */
	this->StageStatusList->GetScreenEffectList().erase(std::remove_if(this->StageStatusList->GetScreenEffectList().begin(), this->StageStatusList->GetScreenEffectList().end(), [](ScreenEffect_Base* pScreenEffect)
		{
			/* �폜�t���O���L���ł��邩�m�F�@*/
			if (pScreenEffect->bGetDeleteFlg() == true)
			{
				// �L���ł���ꍇ
				delete pScreenEffect;
				return true;
			}
			else
			{
				// �����ł���ꍇ
				return false;
			}
		}), this->StageStatusList->GetScreenEffectList().end());
}

