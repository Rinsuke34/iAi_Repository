#pragma once
#include "Appframe.h"
class Bullet : public BulletBase
{
public:
	
	virtual ~Bullet() {}
	Bullet();				// コンストラクタ
		virtual ~Bullet();		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	Draw()				override;		// 描写
		virtual void	BloomDraw()			override {};	// 発光描写


		int		IGetlife() { return this->_life; };		// 弾の生存時間を取得
protected:

	void	Prosses();	// 処理


	VECTOR _vPos;		// 位置
	VECTOR _vPos2;		// 位置
	VECTOR _vOldPos;	// 前フレームの位置
	VECTOR _vDir;		// 向き
	float	_speed;		// 速度
	int		_life;		// 生存カウンタ

	int _effectHandle; // 追加: エフェクトハンドル
	int _effectHandle2;// = LoadEffekseerEffect("res/FX_e_die03.efkefc");; // 追加: エフェクトハンドル

	void Update() {
		_vPos = VAdd(_vPos, VScale(_vDir, _speed));
		SetPosPlayingEffekseer3DEffect(_effectHandle, _vPos.x, _vPos.y, _vPos.z);
		SetPosPlayingEffekseer3DEffect(_effectHandle2, _vPos.x, _vPos.y, _vPos.z);
		_life--;
	}
	// 飛び道具用
	int	_cgBall;
	std::vector<Bullet*> _vBullet;




};

class Bullet2 : public BulletBase {
public:
	virtual ~Bullet2() {}
	Bullet2();				// コンストラクタ
	virtual ~Bullet2();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新
	virtual void	Draw()				override;		// 描写
	virtual void	BloomDraw()			override {};	// 発光描写
	VECTOR _vPos;
	VECTOR _vDir;
	float _speed;
	int _life;
	float _homingTime; // ホーミングする時間を管理する変数
	int _Irradiation;


	Bullet2() : _homingTime(2.0f) {
		StopEffekseer3DEffect(_effectHandle);
	} // 例: 5秒間ホーミングする


	int _effectHandle; // 追加: エフェクトハンドル

	void Update() {
		_vPos = VAdd(_vPos, VScale(_vDir, _speed));
		SetPosPlayingEffekseer3DEffect(_effectHandle, _vPos.x, _vPos.y, _vPos.z);
		_life--;
	}
	// 飛び道具用

	int	_cgBall2;
	std::vector<Bullet2*> _vBullet2;
};