/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <vector>
#include <thread>
#include <future>
#include "AppStructDefine.h"
#include "Fps.h"
#include "PlayerInput.h"
#include "SceneServer.h"
#include "DataListServer.h"

/* �L��ϐ��̐錾 */

/* �v���O������� */
extern bool gbEndFlg;	// �v���O�����I���t���O

/* �t�H���g�֘A */
extern int giFontHandle;	// �t�H���g�n���h��

/* �v���C���[�̓��͏�� */
extern Struct_Input::PLAYER_INPUT_JOYPAD			gstJoypadInputData;			// �W���C�p�b�h
extern Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE	gstKeyboardInputData;		// �L�[�{�[�h���}�E�X
extern bool											gbUseMouseFlg;				// �}�E�X�g�p�t���O(�L���ł���Ȃ�΃J�[�\����`�ʁ����S�Œ����)
extern unsigned char								gucTriggerThreshold;		// �g���K�[���͂�臒l

/* ���s���N���X */
extern Fps* gpFps;								// fps�Œ�p�N���X
extern PlayerInput* gpPlayerInput;				// �v���C���[���͎擾�N���X
extern SceneServer* gpSceneServer;				// �V�[���T�[�o�[�N���X
extern DataListServer* gpDataListServer;		// �f�[�^���X�g�T�[�o�[�N���X

/* �t���[�����[�g�֘A */
extern int giNowFps;							// ���݂̃t���[�����[�g

/* �f�o�b�O�p�`�ʊǗ��t���O */
extern bool gbDrawSceneListFlg;					// �V�[�����X�g�̕`��
extern bool	gbDrawDatalistFlg;					// �v���C���[�X�e�[�^�X�̕`��

/* ���[�f�B���O�֘A */
extern std::vector<std::future<void>>	gstLoadingFutures;		// ���[�f�B���O�����̃X���b�h�ǐ՗pfuture
extern bool								gbNowLoadingFlg;		// ���[�f�B���O�t���O
