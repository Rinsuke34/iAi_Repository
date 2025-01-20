/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#include <cstring>
#include "SceneBase.h"
#include "AppVariableDefine.h"

/* �V�[���̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
SceneBase::SceneBase(const std::string& cName, const int iLayer, const bool bLowerLayerStopFlg)
{
	// ����
	// iLayer					<- �V�[���̃��C���[
	// cName					<- �V�[���̖��O
	// bLowerLayerProcessFlg	<- ���w���C���[�̌v�Z��~�t���O(�L���ł��`�ʂ͂���܂�)

	/* ���������� */
	// SceneServer�ł̊Ǘ��p�f�[�^
	this->stSceneName			= cName;					// �V�[������ݒ�
	this->iLayerOrder			= iLayer;					// ���C���[������ݒ�
	this->bDeleteFlg			= false;					// �폜�t���O�𖳌���
	this->bLowerLayerStopFlg	= bLowerLayerStopFlg;		// ���ʃ��C���[�̌v�Z��~�t���O��ݒ�
}

// ������
void SceneBase::Initialization()
{
	/* ���L���\�[�X�̃��b�N���擾 */
	std::lock_guard<std::mutex> lock(mtx);
}
