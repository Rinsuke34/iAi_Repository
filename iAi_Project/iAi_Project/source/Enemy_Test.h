/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"
#include "EffectTest.h"
#include "Bullet.h"

/* データリスト */
#include "DataList_Input.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Object.h"
/* テスト用敵クラス */

// エネミーベースクラス
class TestEnemy : public EnemyBase
{
public:
	TestEnemy();				// コンストラクタ
	virtual ~TestEnemy();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新
	virtual void	Draw()				override;		// 描写
	virtual void	BloomDraw()			override {};	// 発光描写

private:
protected:
	/* 関数 */
	void FireBallFromEnemy(); // 敵から玉を発射するメソッドを追加
	void FireBallFromEnemy2(); // 敵から玉を発射するメソッドを追加
	void MoveEnemy(); // 敵を移動させるメソッドを追加
	void EnemyBulletMove(); // 敵を移動させるメソッドを追加



	/* 変数 */

	VECTOR _vInitPos;	// 初期位置
	VECTOR _vDir;	// 向き
	float _colSubY;	// コリジョン判定時のY補正(腰位置）

	float _total_time;
	float _play_time;


	bool _isVisible = true; // 描画制御用のフラグ
	bool _isActive = true; // 追加: 処理を制御するフラグ


	int _handleEnemy; // 敵のモデルハンドル
	VECTOR _vEnemyPos; // 敵の位置
	VECTOR _vEnemyTargetPos; // _vEnemyTargetPosの定義を追加


	int _handleEnemy3; // 敵のモデルハンドル
	VECTOR _vEnemy3Pos; // 敵の位置
	VECTOR _vEnemy3TargetPos; // _vEnemyTargetPosの定義を追加


	int _handleEnemy2; // 敵のモデルハンドル
	VECTOR _vEnemy2Pos; // 敵の位置
	VECTOR _vEnemy2TargetPos; // _vEnemyTargetPosの定義を追加

	int _handleEnemy4; // 敵のモデルハンドル
	VECTOR _vEnemy4Pos; // 敵の位置
	VECTOR _vEnemy4TargetPos; // _vEnemyTargetPosの定義を追加

	int _handleEnemy5; // 敵のモデルハンドル
	VECTOR _vEnemy5Pos; // 敵の位置

	float _fireInterval; // 玉の発射間隔
	float _fireInterval2; // 玉の発射間隔
	float _timeSinceLastFire; // 最後に発射してからの経過時間
	float _timeSinceLastFire2; // 最後に発射してからの経過時間

	float _moveDuration; // 移動の持続時間
	float _moveElapsedTime; // 移動の経過時間

	int textureHandle; // テクスチャハンドルを追加

	// フラグを追加
	bool _isFiringBall;
	bool _isFiringBall2;

	int _lastTime; // 追加: _lastTime メンバー変数
	int _lastMoveTime; // 追加: _lastMoveTime メンバー変数
	float _moveInterval; // 追加: _moveInterval メンバー変数
	// 飛び道具用
	int	_cgBullet;
	int	_cgBullet2;


	std::vector<Bullet*> _vBullet;

	DataList_Object* ObjectList;			// オブジェクト管理
};
