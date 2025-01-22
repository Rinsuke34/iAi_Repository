/* 2024.12.21 ��򕗏� �t�@�C���쐬 */

#include "DataList_Input.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �v���C���[���͊Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_Input::DataList_Input() : DataListBase("DataList_Input")
{
	/* ���O��Ԃ̏ȗ� */
	using namespace Struct_Json_Input;	// ���͊Ǘ��p�̒萔�A�\����

	/* ������ */
	/* �e�L�[�R���t�B�O�Ƀf�t�H���g�̐ݒ���� */
	ConfigReset();

	/* Json�t�@�C�������[�h */
	JsonDataLoad();
}

// �f�X�g���N�^
DataList_Input::~DataList_Input()
{
	/* ���ׂẴL�[�R���t�B�O�����폜���� */
	ConfigDelete();
}

// �L�[�R���t�B�O���폜
void DataList_Input::ConfigDelete()
{
	/* ���ׂẴL�[�R���t�B�O�����폜���� */
	/* �W���C�p�b�h */
	for (auto& Data : this->stConfigJoypad)
	{
		delete Data;	// ���������J������
	}
	this->stConfigJoypad.clear();

	/* �L�[�{�[�h���}�E�X */
	for (auto& Data : this->stConfigKeyboardMouse)
	{
		delete Data;	// ���������J������
	}
	this->stConfigKeyboardMouse.clear();	// ���X�g���N���A
}

// Json����f�[�^�����[�h
void DataList_Input::JsonDataLoad()
{
	/* ���O��Ԃ̏ȗ� */
	using namespace Struct_Json_Input;	// ���͊Ǘ��p�̒萔�A�\����

	/* Json�t�@�C���̓ǂݍ��� */
	// �L�[�R���t�B�O�̐ݒ肳�ꂽJson�t�@�C�����J��(�����Ȃ�f�t�H���g�ݒ�ō쐬����)

	/* �p�X�ƃt�@�C�����̐ݒ� */
	std::string FilePath		= "resource/SetupData/";	// �ۑ��ꏊ
	std::string jsonFileName	= "InputData.json";			// �t�@�C����

	/* �t�@�C���W�J */
	std::ifstream inputFile(FilePath + jsonFileName);

	/* �t�@�C���̓W�J�������������m�F */
	if (inputFile.is_open())
	{
		// �t�@�C�������݂���ꍇ
		/* �L�[�R���t�B�O�̃f�[�^��ǂݍ��� */
		nlohmann::json	json;
		inputFile >> json;

		/* �L�[�R���t�B�O�擾 */
		// ���R���g���[���[�ƃL�[�{�[�h���}�E�X�̃L�[�R���t�B�O������̂�2��擾����
		std::string ObjeName[2] = { "Joypad", "Keyboard_Mouse" };

		for (int i = 0; i < 2; i++)
		{
			/* �t�@�C���̓ǂݍ��� */
			nlohmann::json GetConfig = json.at(ObjeName[i]);

			/* �L�[�R���t�B�O��ǂݍ��񂾃f�[�^�ōX�V���� */
			// ���C���f�b�N�X(i)�u0�F�W���C�p�b�h�A1�F�L�[�{�[�h���}�E�X�v
			std::vector<Struct_Json_Input::CONFIG_INFO*>& configList =
				(i == 0) ? this->stConfigJoypad : this->stConfigKeyboardMouse;

			for (auto& config : configList)
			{
				/* Json�ł̃Q�[������̎�ނ̖��̎擾 */
				std::string SearchName = GetControlName(config->iGameControl);

				/* �߂�l�m�F */
				if (SearchName == "Error")
				{
					/* �߂�l��"Error"�̏ꍇ�̓t�@�C���j���̉\��������̂ŏI���t���O��L���ɂ���(��) */
					gbEndFlg = true;
					return;
				}

				/* ���̖��̂ɐݒ肳��Ă�����̓R�[�h���擾���f�[�^�X�V */
				// ���L�[�R���t�B�O�̕ۑ��`���͉��L�̂悤�ɂȂ��Ă���
				// �Q�[������̎�� : [ ���͋@����, ���̓R�[�h ]
				GetConfig.at(SearchName).at(0).get_to(config->iEquipmentType);
				GetConfig.at(SearchName).at(1).get_to(config->iInput);
			}
		}
	}
	else
	{
		/* �e�L�[�R���t�B�O�Ƀf�t�H���g�̐ݒ���� */
		ConfigReset();
	}

	/* �t�@�C������� */
	inputFile.close();
}

// �C���^�[�t�F�C�X���͎擾
bool DataList_Input::bGetInterfaceInput(int iInputType, int iGetInputUI)
{
	// ����
	// iInputType	: �m�F���������̓^�C�v
	// iGetInputUI	: �m�F���������͓��e(UI����n)
	// �߂�l
	// bool			: �m�F�Ώۂ̓��͂��s���Ă��邩(true:�s���Ă���Afalse:�s���Ă��Ȃ�)

	/* �W���C�p�b�h���͒�`�e�[�u�� */
	int iPadInput[]			= { XINPUT_BUTTON_DPAD_UP, XINPUT_BUTTON_DPAD_DOWN, XINPUT_BUTTON_DPAD_LEFT, XINPUT_BUTTON_DPAD_RIGHT, XINPUT_BUTTON_A, XINPUT_BUTTON_B };

	/* �L�[�{�[�h���͒�`�e�[�u�� */
	int iKeyboardInput[]	= { KEY_INPUT_UP, KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_Z, KEY_INPUT_X };

	/* �Ώۂ̓��͂��s���Ă��邩�m�F */
	{
		/* �W���C�p�b�h */
		if (gstJoypadInputData.cgInput[iInputType][iPadInput[iGetInputUI]] == TRUE)
		{
			// ���͂���Ă���ꍇ
			return true;
		}
		
		/* �L�[�{�[�h���}�E�X */
		if (gstKeyboardInputData.cgInput[iInputType][iKeyboardInput[iGetInputUI]] == TRUE)
		{
			// ���͂���Ă���ꍇ
			return true;
		}
	}

	/* ���͂���Ă��Ȃ��Ɣ��� */
	return false;
}

// �Q�[���v���C�p���͎擾(�W�����v���̃A�N�V����)
bool DataList_Input::bGetGameInputAction(int iInputType, int iGetInputGame)
{
	// ����
	// iInputType		: �m�F���������̓^�C�v
	// iGetInputGame	: �m�F���������͓��e(����̎��)
	// �߂�l
	// bool				: �m�F�Ώۂ̓��͂��s���Ă��邩(true:�s���Ă���Afalse:�s���Ă��Ȃ�)

	/* ���O��Ԃ̏ȗ� */
	using namespace Struct_Json_Input;	// ���͊Ǘ��p�̒萔�A�\����

	/* �Ώۑ���̎�ނɓo�^����Ă�����̓R�[�h���擾���� */

	/* �K�v���̒�` */

	// �ǂ���ł��邩����p
	static const int JOYPAD			= 0;	// �W���C�p�b�h
	static const int KEYBOARD_MOUSE	= 1;	// �L�[�{�[�h���}�E�X

	// �擾�������̓R�[�h�Ɠ��͋@��̎�ނ��i�[����\����
	struct INPUT_CHECK
	{
		int iInput;			// ���̓R�[�h
		int iEquipmentType;	// ���͋@��̎��
		bool bSkipFlg;		// �X�L�b�v�t���O
	};

	INPUT_CHECK stInputCheck[2];	// �W���C�p�b�h�A�L�[�{�[�h���}�E�X�̓��̓R�[�h���i�[����\����

	/* �W���C�p�b�h�̊m�F */
	/* �m�F���������͓��e�̓��̓R�[�h�Ɠ��͋@��̎�ނ��擾 */
	if (bGetInputCode(this->stConfigJoypad, stInputCheck[JOYPAD].iInput, stInputCheck[JOYPAD].iEquipmentType, iGetInputGame) == false)
	{
		// �擾�ł��Ȃ������ꍇ
		stInputCheck[JOYPAD].bSkipFlg = true;
	}

	/* �L�[�{�[�h���}�E�X�̊m�F */
	if (bGetInputCode(this->stConfigKeyboardMouse, stInputCheck[KEYBOARD_MOUSE].iInput, stInputCheck[KEYBOARD_MOUSE].iEquipmentType, iGetInputGame) == false)
	{
		// �擾�ł��Ȃ������ꍇ
		stInputCheck[KEYBOARD_MOUSE].bSkipFlg = true;
	}

	/* �Ώۂ̓��͂��s���Ă��邩�m�F */
	/* �W���C�p�b�h */
	if (stInputCheck[JOYPAD].bSkipFlg != true)
	{
		switch (stInputCheck[JOYPAD].iEquipmentType)
		{
			/* �W���C�p�b�h(�{�^��) */
			case INPUT_EQUIPMENT_JOYPAD:
				if (gstJoypadInputData.cgInput[iInputType][stInputCheck[JOYPAD].iInput] == TRUE)
				{
					// ���͂���Ă���ꍇ
					return true;
				}
				break;

			/* �W���C�p�b�h(�g���K�[) */
			case INPUT_EQUIPMENT_JOYPAD_TRIGGER:
				switch (stInputCheck[JOYPAD].iInput)
				{
					/* ���g���K�[�̏ꍇ */
					case XINPUT_TRIGGER_LEFT:
						if(gstJoypadInputData.bgTrigger[iInputType][INPUT_LEFT] == true)
						{
							// ���͂���Ă���ꍇ
							return true;
						}
						break;

					/* �E�g���K�[�̏ꍇ */
					case XINPUT_TRIGGER_RIGHT:
						if (gstJoypadInputData.bgTrigger[iInputType][INPUT_RIGHT] == true)
						{
							// ���͂���Ă���ꍇ
							return true;
						}
						break;
				}
			break;
		}
	}

	/* �L�[�{�[�h���}�E�X */
	if (stInputCheck[KEYBOARD_MOUSE].bSkipFlg != true)
	{
		switch (stInputCheck[KEYBOARD_MOUSE].iEquipmentType)
		{
			/* �L�[�{�[�h */
			case INPUT_EQUIPMENT_KEYBOARD:
				if (gstKeyboardInputData.cgInput[iInputType][stInputCheck[KEYBOARD_MOUSE].iInput])
				{
					// ���͂���Ă���ꍇ
					return true;
				}
				break;

			/* �}�E�X */
			case INPUT_EQUIPMENT_MOUSE:
				if (gstKeyboardInputData.igInput[iInputType] & stInputCheck[KEYBOARD_MOUSE].iInput)
				{
					// ���͂���Ă���ꍇ
					return true;
				}
				break;
		}
	}
	
	/* ���͂���Ă��Ȃ��Ɣ��� */
	return false;
}

// �Q�[���v���C�p���͎擾(�ړ���)
float DataList_Input::fGetGameInputMove()
{
	// �߂�l
	// float	: �ړ����͂̋���(0.f�`1.f)

	float	fReturn = 0;

	/* �L�[�{�[�h�ňړ����͂�����Ă��邩�m�F */
	if (bGetGameInputAction(INPUT_HOLD, GAME_FORWARD) ||
		bGetGameInputAction(INPUT_HOLD, GAME_BACK)	||
		bGetGameInputAction(INPUT_HOLD, GAME_RIGHT)	||
		bGetGameInputAction(INPUT_HOLD, GAME_LEFT)	)
	{
		// ���͂���Ă���ꍇ
		/* ���͂̋�����1(�ő�)�ŕԂ� */
		fReturn = 1.f;
		return fReturn;
	}

	/* �R���g���[���[�ňړ����͂�����Ă��邩�m�F */
	// ���}32767�͈̔͂ŏo�͂����̂Ł}1.0f�ɕϊ�����
	VECTOR vecReturn = VGet(0.0f, 0.0f, 0.0f);
	vecReturn.x += PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_LEFT]);
	vecReturn.z += PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_LEFT]);

	/* �ړ�����������ꍇ */
	if (vecReturn.x != -0 || vecReturn.z != -0)
	{
		/* �e�����̒l���}1�ȓ��Ɏ��߂�(�L�[�{�[�h�ƃR���g���[���̓������͑΍�) */
		vecReturn.x = PUBLIC_PROCESS::fClamp(vecReturn.x, 1.0f, -1.0f);
		vecReturn.z = PUBLIC_PROCESS::fClamp(vecReturn.z, 1.0f, -1.0f);
		
		/* ���͂̑傫�����擾 */
		fReturn = VSize(vecReturn);

		/* 2025.01.21 �e�r�듹 �����ǉ� �J�n */
		/* �f�b�h�]�[�� */
		if (PUBLIC_PROCESS::bCheckInputDeadzone(fReturn, STICK_DEAD_ZONE))
		{
			// �f�b�h�]�[���͈͓��ł���Ȃ��
			/* ���͂𖳌��� */
			fReturn = 0;
		}
		/* 2025.01.21 �e�r�듹 �����ǉ� �I�� */
	}

	/* �ړ�������Ԃ� */
	return fReturn;
}

// �Q�[���v���C�p���͎擾(�ړ�����)
VECTOR DataList_Input::vecGetGameInputMoveDirection()
{
	// �߂�l
	// VECTOR	: �ړ�����(�ڍׂ͉��L�Q��)

	// ���߂�l�̕����ɂ��Ă͉��L�̒ʂ�Ƃ���B
	//	�E��	: +Z
	//	�E�O	: -Z
	//	�E�E	: +X
	//	�E��	: -X
	//	��Y�͕K��0.0f�ƂȂ�
	// ��X,Y,Z�̒l��-1.0f�`1.0f�͈̔͂Ƃ���B
	// ���R���g���[���[�g�p���̓A�i���O�l����Z�o���邽�߁A1.f�ɓ͂��Ȃ��ꍇ������B
	// ���L�[�{�[�h�̏ꍇ�͏㉺���E�L�[�ŎZ�o���邽�ߏo�͂�8�����̂݁B
	// ���R���g���[���[�ƃL�[�{�[�h�̓������͂��������ꍇ�͑o���𑫂����킹���l��Ԃ��B
	// ���R���g���[���[�͍��X�e�B�b�N�̓��͂��g�p����B

	VECTOR vecReturn = VGet(0.0f, 0.0f, 0.0f);

	/* �R���g���[���[����ړ��������擾 */
	// ���}32767�͈̔͂ŏo�͂����̂Ł}1.0f�ɕϊ�����
	vecReturn.x += PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_LEFT]);
	vecReturn.z += PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_LEFT]);

	/* 2025.01.21 �e�r�듹 �����ǉ� �J�n */
	/* �f�b�h�]�[�� */
	// X�����̓���
	if (PUBLIC_PROCESS::bCheckInputDeadzone(vecReturn.x, STICK_DEAD_ZONE))
	{
		// �f�b�h�]�[���͈͓��ł���Ȃ��
		/* ���͂𖳌��� */
		vecReturn.x = 0.f;
	}
	// Z�����̓���
	if (PUBLIC_PROCESS::bCheckInputDeadzone(vecReturn.z, STICK_DEAD_ZONE))
	{
		// �f�b�h�]�[���͈͓��ł���Ȃ��
		/* ���͂𖳌��� */
		vecReturn.z = 0.f;
	}
	/* 2025.01.21 �e�r�듹 �����ǉ� �I�� */

	/* �L�[�{�[�h����ړ��������擾 */
	/* �O�i */
	if (bGetGameInputAction(INPUT_HOLD, GAME_FORWARD) == true)
	{
		vecReturn.z += 1.0f;
	}

	/* ��� */
	if (bGetGameInputAction(INPUT_HOLD, GAME_BACK) == true)
	{
		vecReturn.z -= 1.0f;
	}

	/* �E�ړ� */
	if (bGetGameInputAction(INPUT_HOLD, GAME_RIGHT) == true)
	{
		vecReturn.x += 1.0f;
	}

	/* ���ړ� */
	if (bGetGameInputAction(INPUT_HOLD, GAME_LEFT) == true)
	{
		vecReturn.x -= 1.0f;
	}

	/* �ړ�����������ꍇ */
	if (vecReturn.x != -0 || vecReturn.z != -0)
	{
		/* �ړ������𐳋K�� */
		vecReturn = VNorm(vecReturn);
	}

	/* �ړ�������Ԃ� */
	return vecReturn;
}

// �Q�[������̎�ނ�����̖͂��̂��擾
std::string DataList_Input::GetControlName(int iGameControl)
{
	// ����
	// iGameControl	: �Q�[������̎��(InputDefine�́u���͓��e-�Q�[������v�Q��)
	// �߂�l
	// std::string	: ���̑���̖���(������Ȃ��ꍇ��"Error"��Ԃ�)

	/* ���O��Ԃ̏ȗ� */
	using namespace Struct_Json_Input;	// ���͊Ǘ��p�̒萔�A�\����

	/* �����Json�t�@�C���ł̖��̂̑Ή��\ */
	Struct_Json_Input::CONFIG_JSON stConfig_Json_Operation[] =
	{
		/* ���� */
		{	GAME_JUMP,		"Jump",		false	},
		{	GAME_ATTACK,	"Attack",	false	},
		{	GAME_AIM,		"Aim",		false	},
		{	GAME_RESET,		"Reset",	false	},
		{	GAME_DODGE,		"Dodge",	false	},
		/* �L�[�{�[�h���}�E�X�̂� */
		{	GAME_FORWARD,	"Forward",	true	},
		{	GAME_BACK,		"Back",		true	},
		{	GAME_LEFT,		"Left",		true	},
		{	GAME_RIGHT,		"Right",	true	},
		{	-1,									}
	};

	/* ���̖͂��̂��擾 */
	for (int i = 0; stConfig_Json_Operation->iGameControl != -1; i++)
	{
		/* �w��̃Q�[�����삪���������� */
		if (stConfig_Json_Operation[i].iGameControl == iGameControl)
		{
			// ���O��Ԃ�
			return stConfig_Json_Operation[i].pcControlName;
		}
	}

	/* ������Ȃ������ꍇ */
	return "Error";
}

// �L�[�R���t�B�O�����Z�b�g
void DataList_Input::ConfigReset()
{
	/* ���ׂẴL�[�R���t�B�O���f�t�H���g�ݒ�ɖ߂� */

	/* ���O��Ԃ̏ȗ� */
	using namespace Struct_Json_Input;	// ���͊Ǘ��p�̒萔�A�\����

	/* �L�[�R���t�B�O�f�t�H���g(�W���C�p�b�h) */
	Struct_Json_Input::CONFIG_INFO stConfig_Default_Joypad[] =
	{
		{	GAME_JUMP,		XINPUT_BUTTON_A,				INPUT_EQUIPMENT_JOYPAD			},	// �W�����v
		{	GAME_ATTACK,	XINPUT_BUTTON_RIGHT_SHOULDER,	INPUT_EQUIPMENT_JOYPAD			},	// �U��
		{	GAME_AIM,		XINPUT_TRIGGER_LEFT,			INPUT_EQUIPMENT_JOYPAD_TRIGGER	},	// �G�C��(�\��)
		{	GAME_RESET,		XINPUT_BUTTON_LEFT_SHOULDER,	INPUT_EQUIPMENT_JOYPAD			},	// �J�������Z�b�g
		{	GAME_DODGE,		XINPUT_BUTTON_B,				INPUT_EQUIPMENT_JOYPAD			},	// ���
		{	-1,																				}
	};

	/* �L�[�R���t�B�O�f�t�H���g(�L�[�{�[�h���}�E�X) */
	Struct_Json_Input::CONFIG_INFO stConfig_Default_Keyboard_Mouse[] =
	{
		{	GAME_FORWARD,	KEY_INPUT_W,			INPUT_EQUIPMENT_KEYBOARD	},	// �O�i
		{	GAME_BACK,		KEY_INPUT_S,			INPUT_EQUIPMENT_KEYBOARD	},	// ���
		{	GAME_LEFT,		KEY_INPUT_A,			INPUT_EQUIPMENT_KEYBOARD	},	// ���ړ�
		{	GAME_RIGHT,		KEY_INPUT_D,			INPUT_EQUIPMENT_KEYBOARD	},	// �E�ړ�
		{	GAME_JUMP,		KEY_INPUT_SPACE,		INPUT_EQUIPMENT_KEYBOARD	},	// �W�����v
		{	GAME_ATTACK,	MOUSE_INPUT_LEFT,		INPUT_EQUIPMENT_MOUSE		},	// �U��
		{	GAME_AIM,		MOUSE_INPUT_RIGHT,		INPUT_EQUIPMENT_MOUSE		},	// �G�C��(�\��)
		{	GAME_RESET,		MOUSE_INPUT_MIDDLE,		INPUT_EQUIPMENT_MOUSE		},	// �J�������Z�b�g
		{	GAME_DODGE,		KEY_INPUT_LCONTROL,		INPUT_EQUIPMENT_KEYBOARD	},	// ���
		{	-1,																	}
	};

	/* ���ׂẴL�[�R���t�B�O�����폜���� */
	ConfigDelete();

	/* �e�L�[�R���t�B�O�Ƀf�t�H���g�̐ݒ���� */
	// �W���C�p�b�h
	for (int i = 0; stConfig_Default_Joypad[i].iGameControl != -1; ++i)
	{
		stConfigJoypad.push_back(new CONFIG_INFO(stConfig_Default_Joypad[i]));
	}

	// �L�[�{�[�h���}�E�X
	for (int i = 0; stConfig_Default_Keyboard_Mouse[i].iGameControl != -1; ++i)
	{
		stConfigKeyboardMouse.push_back(new CONFIG_INFO(stConfig_Default_Keyboard_Mouse[i]));
	}
}

// �L�[�R���t�B�O������̓R�[�h�擾
bool DataList_Input::bGetInputCode(const std::vector<Struct_Json_Input::CONFIG_INFO*>& stConfig, int& iInputCode, int& iIquipmentType, int iTargetInputGame)
{
	// ����
	// stConfig			: �m�F�������L�[�R���t�B�O(�A�h���X)
	// iInputCode		: �擾�R�[�h�ۑ��ꏊ(�A�h���X)
	// iIquipmentType	: �擾���͋@��ۑ��ꏊ(�A�h���X)
	// iTargetInputGame	: �m�F���������͓��e(����̎��)
	// �߂�l
	// bool				: �w��̓��͓��e������������(true:���������Afalse:������Ȃ�����)
	
	/* �Ώۂ̃L�[�R���t�B�O����w��̓��͓��e�̓��̓R�[�h�Ɠ��͋@����擾 */

	/* �R���t�B�O���X�g����w��̓��͓��e��T�� */
	for (const auto& config : stConfig)
	{
		/* �擾�������͓��e���m�F���������͓��e�ł��邩�m�F */
		if (config->iGameControl == iTargetInputGame)
		{
			// �m�F���������͓��e�ł���ꍇ
			/* ���̓R�[�h�Ɠ��͋@���Ԃ� */
			iInputCode		= config->iInput;
			iIquipmentType	= config->iEquipmentType;
			return true;
		}
	}

	/* ������Ȃ������ꍇ */
	return false;
}
