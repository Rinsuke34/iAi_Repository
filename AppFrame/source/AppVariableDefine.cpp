/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#include "AppVariableDefine.h"

/* �L��ϐ��̏����� */

/* �v���O������� */
bool gbEndFlg	= false;	// �v���O�����I���t���O

/* �t�H���g�֘A */
int giFontHandle_Small					= 0;	// �t�H���g�n���h��(�}�L�i�X/�ʏ�T�C�Y)
int giFontHandle_Medium					= 0;	// �t�H���g�n���h��(�}�L�i�X/���T�C�Y)
int giFontHandle_Large					= 0;	// �t�H���g�n���h��(�}�L�i�X/��T�C�Y)
int giFontHandle_NotoSerifJP_Medium		= 0;	// �t�H���g�n���h��(�̂Ƃ����/�Z���t�e�L�X�g�p)
int giFontHandle_NotoSerifJP_SemiBold	= 0;	// �t�H���g�n���h��(�̂Ƃ����/�l�[���^�O�A�I�v�V�����p)

/* �v���C���[�̓��͏�� */
Struct_Input::PLAYER_INPUT_JOYPAD			gstJoypadInputData;					// �W���C�p�b�h
Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE	gstKeyboardInputData;				// �L�[�{�[�h���}�E�X
bool										gbUseMouseFlg			= false;	// �}�E�X�g�p�t���O(�L���ł���Ȃ�΃J�[�\����`�ʁ����S�Œ����)
unsigned char								gucTriggerThreshold		= 0;		// �g���K�[���͂�臒l

/* ���s���N���X */
Fps*			gpFps				= nullptr;	// fps�Œ�p�N���X
PlayerInput*	gpPlayerInput		= nullptr;	// �v���C���[���͎擾�N���X
SceneServer*	gpSceneServer		= nullptr;	// �V�[���T�[�o�[�N���X
DataListServer* gpDataListServer	= nullptr;	// �f�[�^���X�g�T�[�o�[�N���X

/* �t���[�����[�g�֘A */
int	giNowFps	= 0;						// ���݂̃t���[�����[�g

/* �f�o�b�O�p�`�ʊǗ��t���O */
bool gbDrawSceneListFlg		= true;		// �V�[�����X�g�̕`��
bool gbDrawDatalistFlg		= false;		// �f�[�^���X�g�̕`��
bool gbDrawFpsFlg			= false;		// �t���[�����[�g�̕`��

/* ���[�f�B���O�֘A */
bool gbNowLoadingFlg		= false;		// ���[�h���t���O