#pragma once
#include "Appframe.h"
class Bullet : public BulletBase
{
public:
	
	virtual ~Bullet() {}
	Bullet();				// �R���X�g���N�^
		virtual ~Bullet();		// �f�X�g���N�^
	//Bullet();				// �R���X�g���N�^
	//	virtual ~Bullet();		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		virtual void	Draw()				override;		// �`��
		virtual void	BloomDraw()			override {};	// �����`��


		int		IGetlife() { return this->_life; };		// �e�̐������Ԃ�擾
protected:

	void	Prosses();	// ����


	VECTOR _vPos;		// �ʒu
	VECTOR _vPos2;		// �ʒu
	VECTOR _vOldPos;	// �O�t���[���̈ʒu
	VECTOR _vDir;		// ����
	float	_speed;		// ���x
	int		_life;		// �����J�E���^

	int _effectHandle; // �ǉ�: �G�t�F�N�g�n���h��
	int _effectHandle2;// = LoadEffekseerEffect("res/FX_e_die03.efkefc");; // �ǉ�: �G�t�F�N�g�n���h��

	void Update() {

		VECTOR _vPos;		// �ʒu
		VECTOR _vPos2;		// �ʒu
		VECTOR _vOldPos;	// �O�t���[���̈ʒu
		VECTOR _vDir;		// ����
		float	_speed;		// ���x
		int		_life;		// �����J�E���^
		//void	Prosses();	// ����
		int _effectHandle; // �ǉ�: �G�t�F�N�g�n���h��
		void Prosses()
		{
			_vPos = VAdd(_vPos, VScale(_vDir, _speed));
			SetPosPlayingEffekseer3DEffect(_effectHandle, _vPos.x, _vPos.y, _vPos.z);
			//SetPosPlayingEffekseer3DEffect(_effectHandle2, _vPos.x, _vPos.y, _vPos.z);
			_life--;
		}
protected:



	
	int _effectHandle2;// = LoadEffekseerEffect("res/FX_e_die03.efkefc");; // �ǉ�: �G�t�F�N�g�n���h��

	/*void Update() {
		_vPos = VAdd(_vPos, VScale(_vDir, _speed));
		SetPosPlayingEffekseer3DEffect(_effectHandle, _vPos.x, _vPos.y, _vPos.z);
		SetPosPlayingEffekseer3DEffect(_effectHandle2, _vPos.x, _vPos.y, _vPos.z);
		_life--;
	}
	// ��ѓ���p
	int	_cgBall;
	std::vector<Bullet*> _vBullet;
	}*/
	// ��ѓ���p
	int	_cgBall;
	/*std::vector<Bullet*> _vBullet;*/




};

class Bullet2 : public BulletBase {
public:
	virtual ~Bullet2() {}
	Bullet2();				// �R���X�g���N�^
	virtual ~Bullet2();		// �f�X�g���N�^

	virtual void	Initialization()	override;		// ������
	virtual void	Update()			override;		// �X�V
	virtual void	Draw()				override;		// �`��
	virtual void	BloomDraw()			override {};	// �����`��
	VECTOR _vPos;
	VECTOR _vDir;
	float _speed;
	int _life;
	float _homingTime; // �z�[�~���O���鎞�Ԃ�Ǘ�����ϐ�
	int _Irradiation;


	Bullet2() : _homingTime(2.0f) {
		StopEffekseer3DEffect(_effectHandle);
	} // ��: 5�b�ԃz�[�~���O����


	int _effectHandle; // �ǉ�: �G�t�F�N�g�n���h��

	void Update() {
		_vPos = VAdd(_vPos, VScale(_vDir, _speed));
		SetPosPlayingEffekseer3DEffect(_effectHandle, _vPos.x, _vPos.y, _vPos.z);
		_life--;
	}
	// ��ѓ���p

	int	_cgBall2;
	std::vector<Bullet2*> _vBullet2;
};
//class Bullet2 : public BulletBase {
//public:
//	virtual ~Bullet2() {}
//	Bullet2();				// �R���X�g���N�^
//	virtual ~Bullet2();		// �f�X�g���N�^
//
//	virtual void	Initialization()	override;		// ������
//	virtual void	Update()			override;		// �X�V
//	virtual void	Draw()				override;		// �`��
//	virtual void	BloomDraw()			override {};	// �����`��
//	VECTOR _vPos;
//	VECTOR _vDir;
//	float _speed;
//	int _life;
//	float _homingTime; // �z�[�~���O���鎞�Ԃ�Ǘ�����ϐ�
//	int _Irradiation;
//
//
//	//Bullet2() : _homingTime(2.0f) {
//	//	StopEffekseer3DEffect(_effectHandle);
//	//} // ��: 5�b�ԃz�[�~���O����
//
//
//	int _effectHandle; // �ǉ�: �G�t�F�N�g�n���h��
//
//	/*void Update() {
//		_vPos = VAdd(_vPos, VScale(_vDir, _speed));
//		SetPosPlayingEffekseer3DEffect(_effectHandle, _vPos.x, _vPos.y, _vPos.z);
//		_life--;
//	}*/
//	// ��ѓ���p
//
//	int	_cgBall2;
//	std::vector<Bullet2*> _vBullet2;
//};
