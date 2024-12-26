/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <DxLib.h>
#include <string>

/* ���ׂẴV�[���̃x�[�X�ƂȂ�N���X�̐錾 */

// �V�[���x�[�X�N���X
class SceneBase
{
	public:
		SceneBase(const std::string& cName, const int iLayer, const bool bLowerLayerStopFlg);		// �R���X�g���N�^
		virtual ~SceneBase() {};																	// �f�X�g���N�^

		virtual void	Process() {};	// �v�Z
		virtual void	Draw() {};		// �`��

		bool	bGetDeleteFlg()				{ return this->bDeleteFlg; };				// �폜�t���O���擾
		int		iGetSceneLayerOrder()		{ return this->iLayerOrder; };				// ���C���[�������擾
		bool	bGetLowerLayerProcessFlg()	{ return this->bLowerLayerStopFlg; }		// ���w���C���[�v�Z��~�t���O���擾
		std::string	stGetSceneName()		{ return this->stSceneName; }				// �V�[�����̂��擾

	private:
	protected:
		/* �֐� */

		/* �ϐ� */
		// SceneServer�ł̊Ǘ��p�f�[�^
		std::string		stSceneName;			// �V�[������
		int				iLayerOrder;			// ���C���[����(�l���傫���قǎ�O�ɕ`��)
		bool			bLowerLayerStopFlg;		// ���w���C���[�v�Z��~�t���O(�L���Ȃ牺�w���C���[�Ōv�Z���s��Ȃ�)
		bool			bDeleteFlg;				// �폜�t���O(�L���Ȃ�V�[�����폜)
};
