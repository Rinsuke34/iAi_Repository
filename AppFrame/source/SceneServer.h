/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "SceneBase.h"
#include <list>

/* ���s���̃V�[���̊Ǘ����s���N���X�̐錾 */
// ��vector���g�p����ƃG���[��������������list�ŃN���X���Ǘ�����

// �V�[���T�[�o�[�N���X
class SceneServer
{
	public:
		SceneServer();				// �R���X�g���N�^
		virtual ~SceneServer();		// �f�X�g���N�^

		void	SceneProcess();		// �V�[���v�Z����
		void	SceneDraw();		// �V�[���`�揈��
		void	DrawSceneList();	// �f�[�^���X�g�`��(�f�o�b�O�p)

		
		void		AddSceneReservation(SceneBase* NewScene);	// �V�[���ǉ��\��
		SceneBase*	GetScene(const std::string& cName);			// �V�[���擾

		void	SetDeleteCurrentSceneFlg(bool bDeleteCurrentSceneFlg)	{ this->bDeleteCurrentSceneFlg	= bDeleteCurrentSceneFlg; };	// �V�[���ǉ����A���s�V�[�����폜����
		void	SetAddLoadSceneFlg(bool bAddLoadSceneFlg)				{ this->bAddLoadSceneFlg		= bAddLoadSceneFlg; };			// �V�[���ǉ����A���[�h�V�[����ǉ�����
		

	private:
		// �V�[�����X�g
		std::list<SceneBase*> pstSceneList;

		// �ǉ��\��̃V�[�����X�g
		std::list<SceneBase*> pstAddSceneList;

		/* �֐� */
		void	AddScene();						// �V�[�����X�g�ւ̃V�[���ǉ�
		void	SceneSortLayerOrder();			// �V�[�����X�g�̕��ёւ�(���C���[�����̑傫����)
		void	DeleteUnnecessaryScene();		// �V�[���폜(�폜�t���O���L���ȃV�[���ɑ΂���)
		void	DeleteAllScene();				// �V�[���폜(�V�[�����X�g���̂��ׂẴV�[���ɑ΂���)
		void	DeleteAllAddScene();			// �V�[���폜(�ǉ��\��̃V�[�����X�g���̂��ׂẴV�[���ɑ΂���)

		/* �ϐ� */
		bool	bSceneDeleteFlg;			// �V�[���폜�t���O(�폜�\��̃V�[��������Ȃ�ΗL���ɂ���)
		bool	bSceneAddFlg;				// �V�[���ǉ��t���O(�ǉ��\��̃V�[��������Ȃ�ΗL���ɂ���)
		bool	bDeleteCurrentSceneFlg;		// ���s�V�[���폜�t���O(�V�[�����X�g���̂��ׂẴV�[�����폜���邩�̃t���O)
		bool	bAddLoadSceneFlg;			// ���[�h�V�[���ǉ��t���O(���[�h�V�[����ǉ����邩�̃t���O)

	protected:
};
