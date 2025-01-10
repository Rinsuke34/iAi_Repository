/* 2024.12.21 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "InputDefine.h"

/* �v���C���[���͊Ǘ��N���X�̐錾 */

// �v���C���[���͊Ǘ��N���X
class DataList_Input : public DataListBase
{
	public:
		DataList_Input();				// �R���X�g���N�^
		virtual ~DataList_Input();		// �f�X�g���N�^

		void	JsonDataLoad();			// Json����f�[�^�����[�h

		/* �C���^�[�t�F�C�X�p���͎擾 */
		bool	bGetInterfaceInput(int iInputType, int iGetInputUI);		// �C���^�[�t�F�C�X���͎擾

		/* �Q�[���v���C�p���͎擾 */
		bool	bGetGameInputAction(int iInputType, int iGetInputGame);		// �Q�[���v���C�p���͎擾(�A�N�V����)
		VECTOR	vecGetGameInputMove();										// �Q�[���v���C�p���͎擾(�ړ���)
		VECTOR	vecGetGameInputAim();										// �Q�[���v���C�p���͎擾(�Ə�)

	private:
		/* �L�[�R���t�B�O��� */
		std::vector<Struct_Json_Input::CONFIG_INFO*>	stConfigJoypad;			// �W���C�p�b�h
		std::vector<Struct_Json_Input::CONFIG_INFO*>	stConfigKeyboardMouse;	// �L�[�{�[�h���}�E�X

		/* �L�[�R���t�B�O�p�֐� */
		std::string	GetControlName(int iGameControl);		// �Q�[������̎�ނ�����̖͂��̂��擾

		/* �֐� */
		void	ConfigReset();																																// �L�[�R���t�B�O�����Z�b�g
		void	ConfigDelete();																																// �L�[�R���t�B�O���폜
		bool	bGetInputCode(const std::vector<Struct_Json_Input::CONFIG_INFO*>& stConfig, int& iInputCode, int& iIquipmentType, int iTargetInputGame);	// �L�[�R���t�B�O������̓R�[�h�擾

		/* �ȉ��A�g����������Ȃ��̂Ńo�b�N�A�b�v�Ƃ��Ď���Ă��� */
		///* ���̓R�[�h�ꗗ */
		//Struct_Json_Input::INPUT_INFO stInputInfo[73] =
		//{
		//	/*	���̓R�[�h,			���͋@��̎��,				���̖͂���	*/
		//	/* �W���C�p�b�h */
		//	{	PAD_INPUT_UP,		INPUT_EQUIPMENT_JOYPAD,		"��"			},	// ��{�^��
		//	{	PAD_INPUT_LEFT,		INPUT_EQUIPMENT_JOYPAD,		"��"			},	// ���{�^��
		//	{	PAD_INPUT_RIGHT,	INPUT_EQUIPMENT_JOYPAD,		"�E"			},	// �E�{�^��
		//	{	PAD_INPUT_DOWN,		INPUT_EQUIPMENT_JOYPAD,		"��"			},	// ���{�^��
		//	{	PAD_INPUT_A,		INPUT_EQUIPMENT_JOYPAD,		"A"				},	// A�{�^��
		//	{	PAD_INPUT_B,		INPUT_EQUIPMENT_JOYPAD,		"B"				},	// B�{�^��
		//	{	PAD_INPUT_C,		INPUT_EQUIPMENT_JOYPAD,		"C"				},	// C�{�^��
		//	{	PAD_INPUT_X,		INPUT_EQUIPMENT_JOYPAD,		"X"				},	// X�{�^��
		//	{	PAD_INPUT_Y,		INPUT_EQUIPMENT_JOYPAD,		"Y"				},	// Y�{�^��
		//	{	PAD_INPUT_Z,		INPUT_EQUIPMENT_JOYPAD,		"Z"				},	// Z�{�^��
		//	{	PAD_INPUT_L,		INPUT_EQUIPMENT_JOYPAD,		"L"				},	// L�{�^��
		//	{	PAD_INPUT_R,		INPUT_EQUIPMENT_JOYPAD,		"R"				},	// R�{�^��
		//	{	PAD_INPUT_START,	INPUT_EQUIPMENT_JOYPAD,		"START"			},	// �X�^�[�g�{�^��
		//	{	PAD_INPUT_M,		INPUT_EQUIPMENT_JOYPAD,		"M"				},	// M�{�^��
		//	/* �L�[�{�[�h */
		//	{	KEY_INPUT_BACK,		INPUT_EQUIPMENT_KEYBOARD,	"BACK"			},	// �o�b�N�X�y�[�X�L�[
		//	{	KEY_INPUT_TAB,		INPUT_EQUIPMENT_KEYBOARD,	"TAB"			},	// �^�u�L�[
		//	{	KEY_INPUT_RETURN,	INPUT_EQUIPMENT_KEYBOARD,	"ENTER"			},	// �G���^�[�L�[
		//	{	KEY_INPUT_LSHIFT,	INPUT_EQUIPMENT_KEYBOARD,	"L SHIFT"		},	// ���V�t�g�L�[
		//	{	KEY_INPUT_RSHIFT,	INPUT_EQUIPMENT_KEYBOARD,	"R SHIFT"		},	// �E�V�t�g�L�[
		//	{	KEY_INPUT_LCONTROL,	INPUT_EQUIPMENT_KEYBOARD,	"L CONTROL"		},	// ���R���g���[���L�[
		//	{	KEY_INPUT_RCONTROL,	INPUT_EQUIPMENT_KEYBOARD,	"R CONTROL"		},	// �E�R���g���[���L�[
		//	{	KEY_INPUT_ESCAPE,	INPUT_EQUIPMENT_KEYBOARD,	"ESCAPE"		},	// �G�X�P�[�v�L�[
		//	{	KEY_INPUT_SPACE,	INPUT_EQUIPMENT_KEYBOARD,	"SPACE"			},	// �X�y�[�X�L�[
		//	{	KEY_INPUT_PGUP,		INPUT_EQUIPMENT_KEYBOARD,	"PAGE UP"		},	// �o�������t�o�L�[
		//	{	KEY_INPUT_PGDN,		INPUT_EQUIPMENT_KEYBOARD,	"PAGE DOWN"		},	// �o�������c�������L�[
		//	{	KEY_INPUT_END,		INPUT_EQUIPMENT_KEYBOARD,	"END"			},	// �G���h�L�[
		//	{	KEY_INPUT_HOME,		INPUT_EQUIPMENT_KEYBOARD,	"HOME"			},	// �z�[���L�[
		//	{	KEY_INPUT_LEFT,		INPUT_EQUIPMENT_KEYBOARD,	"LEFT"			},	// ���L�[
		//	{	KEY_INPUT_UP,		INPUT_EQUIPMENT_KEYBOARD,	"UP"			},	// ��L�[
		//	{	KEY_INPUT_RIGHT,	INPUT_EQUIPMENT_KEYBOARD,	"RIGHT"			},	// �E�L�[
		//	{	KEY_INPUT_DOWN,		INPUT_EQUIPMENT_KEYBOARD,	"DOWN"			},	// ���L�[
		//	{	KEY_INPUT_INSERT,	INPUT_EQUIPMENT_KEYBOARD,	"INSERT"		},	// �C���T�[�g�L�[
		//	{	KEY_INPUT_DELETE,	INPUT_EQUIPMENT_KEYBOARD,	"DELETE"		},	// �f���[�g�L�[
		//	{	KEY_INPUT_A,		INPUT_EQUIPMENT_KEYBOARD,	"A"				},	// �`�L�[
		//	{	KEY_INPUT_B,		INPUT_EQUIPMENT_KEYBOARD,	"B"				},	// �a�L�[
		//	{	KEY_INPUT_C,		INPUT_EQUIPMENT_KEYBOARD,	"C"				},	// �b�L�[
		//	{	KEY_INPUT_D,		INPUT_EQUIPMENT_KEYBOARD,	"D"				},	// �c�L�[
		//	{	KEY_INPUT_E,		INPUT_EQUIPMENT_KEYBOARD,	"E"				},	// �d�L�[
		//	{	KEY_INPUT_F,		INPUT_EQUIPMENT_KEYBOARD,	"F"				},	// �e�L�[
		//	{	KEY_INPUT_G,		INPUT_EQUIPMENT_KEYBOARD,	"G"				},	// �f�L�[
		//	{	KEY_INPUT_H,		INPUT_EQUIPMENT_KEYBOARD,	"H"				},	// �g�L�[
		//	{	KEY_INPUT_I,		INPUT_EQUIPMENT_KEYBOARD,	"I"				},	// �h�L�[
		//	{	KEY_INPUT_J,		INPUT_EQUIPMENT_KEYBOARD,	"J"				},	// �i�L�[
		//	{	KEY_INPUT_K,		INPUT_EQUIPMENT_KEYBOARD,	"K"				},	// �j�L�[
		//	{	KEY_INPUT_L,		INPUT_EQUIPMENT_KEYBOARD,	"L"				},	// �k�L�[
		//	{	KEY_INPUT_M,		INPUT_EQUIPMENT_KEYBOARD,	"M"				},	// �l�L�[
		//	{	KEY_INPUT_N,		INPUT_EQUIPMENT_KEYBOARD,	"N"				},	// �m�L�[
		//	{	KEY_INPUT_O,		INPUT_EQUIPMENT_KEYBOARD,	"O"				},	// �n�L�[
		//	{	KEY_INPUT_P,		INPUT_EQUIPMENT_KEYBOARD,	"P"				},	// �o�L�[
		//	{	KEY_INPUT_Q,		INPUT_EQUIPMENT_KEYBOARD,	"Q"				},	// �p�L�[
		//	{	KEY_INPUT_R,		INPUT_EQUIPMENT_KEYBOARD,	"R"				},	// �q�L�[
		//	{	KEY_INPUT_S,		INPUT_EQUIPMENT_KEYBOARD,	"S"				},	// �r�L�[
		//	{	KEY_INPUT_T,		INPUT_EQUIPMENT_KEYBOARD,	"T"				},	// �s�L�[
		//	{	KEY_INPUT_U,		INPUT_EQUIPMENT_KEYBOARD,	"U"				},	// �t�L�[
		//	{	KEY_INPUT_V,		INPUT_EQUIPMENT_KEYBOARD,	"V"				},	// �u�L�[
		//	{	KEY_INPUT_W,		INPUT_EQUIPMENT_KEYBOARD,	"W"				},	// �v�L�[
		//	{	KEY_INPUT_X,		INPUT_EQUIPMENT_KEYBOARD,	"X"				},	// �w�L�[
		//	{	KEY_INPUT_Y,		INPUT_EQUIPMENT_KEYBOARD,	"Y"				},	// �x�L�[
		//	{	KEY_INPUT_Z,		INPUT_EQUIPMENT_KEYBOARD,	"Z"				},	// �y�L�[
		//	{	KEY_INPUT_0, 		INPUT_EQUIPMENT_KEYBOARD,	"0"				},	// �O�L�[
		//	{	KEY_INPUT_1,		INPUT_EQUIPMENT_KEYBOARD,	"1"				},	// �P�L�[
		//	{	KEY_INPUT_2,		INPUT_EQUIPMENT_KEYBOARD,	"2"				},	// �Q�L�[
		//	{	KEY_INPUT_3,		INPUT_EQUIPMENT_KEYBOARD,	"3"				},	// �R�L�[
		//	{	KEY_INPUT_4,		INPUT_EQUIPMENT_KEYBOARD,	"4"				},	// �S�L�[
		//	{	KEY_INPUT_5,		INPUT_EQUIPMENT_KEYBOARD,	"5"				},	// �T�L�[
		//	{	KEY_INPUT_6,		INPUT_EQUIPMENT_KEYBOARD,	"6"				},	// �U�L�[
		//	{	KEY_INPUT_7,		INPUT_EQUIPMENT_KEYBOARD,	"7"				},	// �V�L�[
		//	{	KEY_INPUT_8,		INPUT_EQUIPMENT_KEYBOARD,	"8"				},	// �W�L�[
		//	{	KEY_INPUT_9,		INPUT_EQUIPMENT_KEYBOARD,	"9"				},	// �X�L�[
		//	/* �}�E�X */
		//	{	MOUSE_INPUT_LEFT,	INPUT_EQUIPMENT_MOUSE,		"���N���b�N"	},	// ���N���b�N
		//	{	MOUSE_INPUT_RIGHT,	INPUT_EQUIPMENT_MOUSE,		"�E�N���b�N"	},	// �E�N���b�N
		//	{	MOUSE_INPUT_MIDDLE,	INPUT_EQUIPMENT_MOUSE,		"�����{�^��"	},	// �����{�^��
		//	{	-1,					NULL,						NULL			}
		//};

		

		
	protected:
};