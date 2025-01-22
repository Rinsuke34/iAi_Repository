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

		/* �C���^�[�t�F�C�X�p���͎擾 */
		bool	bGetInterfaceInput(int iInputType, int iGetInputUI);		// �C���^�[�t�F�C�X���͎擾

		/* �Q�[���v���C�p���͎擾 */
		bool	bGetGameInputAction(int iInputType, int iGetInputGame);		// �Q�[���v���C�p���͎擾(�A�N�V����)
		float	fGetGameInputMove();										// �Q�[���v���C�p���͎擾(�ړ���)
		VECTOR	vecGetGameInputMoveDirection();								// �Q�[���v���C�p���͎擾(�ړ�����)

	private:
		/* �֐� */
		void JsonDataLoad();		// Json����f�[�^�����[�h

		/* �L�[�R���t�B�O��� */
		std::vector<Struct_Json_Input::CONFIG_INFO*>	stConfigJoypad;			// �W���C�p�b�h
		std::vector<Struct_Json_Input::CONFIG_INFO*>	stConfigKeyboardMouse;	// �L�[�{�[�h���}�E�X

		/* �L�[�R���t�B�O�p�֐� */
		std::string	GetControlName(int iGameControl);		// �Q�[������̎�ނ�����̖͂��̂��擾

		/* �֐� */
		void	ConfigReset();																																// �L�[�R���t�B�O�����Z�b�g
		void	ConfigDelete();																																// �L�[�R���t�B�O���폜
		bool	bGetInputCode(const std::vector<Struct_Json_Input::CONFIG_INFO*>& stConfig, int& iInputCode, int& iIquipmentType, int iTargetInputGame);	// �L�[�R���t�B�O������̓R�[�h�擾

	protected:
};