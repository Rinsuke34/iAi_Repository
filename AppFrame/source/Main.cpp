/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#include "Main.h"
#include "AppVariableDefine.h"
#include "AppConstantDefine.h"
#include "AppFunctionDefine.h"

/* �v���O�����̃��C�����[�v */

// ���C���v���O����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/* ���O��Ԃ̏ȗ� */
	using namespace Main;	// WinMain�֐��Ŏg�p����֐��A�ϐ��錾

	/* DX���C�u�������������� */
	Main::DxLibInit();

	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return -1;
	}

	/* ���C���v���O�������������� */
	Main::MainInit();

	/* ���C�����[�v */
	while (ProcessMessage() == 0)
	{
		/* �v���O�����I���t���O���m�F*/
		if (gbEndFlg == true)
		{
			/* �L���ł���Ȃ烁�C�����[�v�𔲂���(�v���O�����I��) */
			break;
		}

		/* �v���C���[�̓��͂��擾 */
		gpPlayerInput->Input();

		/* �V�[������ */
		/* �v�Z */
		gpSceneServer->SceneProcess();

		/* �`�� */
		ClearDrawScreen();
		{
			/* �`��(�ʏ�) */
			gpSceneServer->SceneDraw();

			/* �f�o�b�O�p�`�� */
			Main::DebugDraw();
		}
		ScreenFlip();

		/* �t���[�����[�g���� */
		gpFps->FpsUpdate();
		gpFps->FpsWait();
	}

	/* �I������ */
	Main::MainEnd();

	return 0;
}

// DX���C�u����������
void Main::DxLibInit()
{
	/* DXLib�̏d�����\�ɂ���(�ʐM�e�X�g�p) */
	SetDoubleStartValidFlag(TRUE);

	/* ��ʂ̉𑜓x����1920�~�c1080�A1�h�b�g������32�r�b�g�Ɏw�肷�� */
	SetGraphMode(SCREEN_SIZE::WIDE, SCREEN_SIZE::HEIGHT, 32);

	// �E�B���h�E���[�h�Ɏw�肷��
	ChangeWindowMode(true);

	// �E�B���h�E����A�N�e�B�u�ł��v���O���������s������
	SetAlwaysRunFlag(true);

	/* �}�E�X���W����ʒ����ɐݒ� */
	SetMousePoint(SCREEN_SIZE::WIDE / 2, SCREEN_SIZE::HEIGHT / 2);

	// �}�E�X�J�[�\�����\���ɂ���
	SetMouseDispFlag(FALSE);

	/* �W���C�p�b�h�̃f�b�h�]�[����ݒ� */
	//SetJoypadDeadZone(PAD_INPUT_1, double Zone);
}

// ���C���v���O����������
void Main::MainInit()
{
	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// FPS���Œ肷��N���X��ǉ�
	gpFps = new Fps();

	// �v���C���[���͂��擾����N���X��ǉ�
	gpPlayerInput = new PlayerInput();

	// �V�[���T�[�o�[���쐬
	gpSceneServer = new SceneServer();

	// �f�[�^���X�g�T�[�o�[���쐬
	gpDataListServer = new DataListServer();

	// �V�[����������Ԃɐݒ�
	// �����ʂ�AppFlame���g�p���邽�ߊe�v���O�����ɉ������V�[���ɐݒ肷��
	SCENE_SET::SetFastScene();

	// �v���W�F�N�g����������
	PROJECT_INIT::Init();
}

// �I������
void Main::MainEnd()
{
	// �v���C���[���͂��擾����N���X���폜����
	delete gpPlayerInput;

	// FPS���Œ肷��N���X���폜����
	delete gpFps;

	// �V�[���T�[�o�[���폜����
	delete gpSceneServer;

	// �f�[�^���X�g�T�[�o�[���폜����
	delete gpDataListServer;

	// DX���C�u�����̎g�p���I������
	DxLib_End();
}

// �f�o�b�O�`��
void Main::DebugDraw()
{
	/* �Ή������f�o�b�O�p�t���O���L���ł���Ȃ�΃f�o�b�O�p�`�ʂ��s�� */
	/* �V�[�����X�g�`�� */
	if (gbDrawSceneListFlg == true)
	{
		gpSceneServer->DrawSceneList();
	}

	/* �f�[�^���X�g�`�� */
	if (gbDrawDatalistFlg == true)
	{
		gpDataListServer->DrawDataList();
	}
}
