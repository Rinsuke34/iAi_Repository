/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once

/* AppFrameで使用する定数の宣言 */

/* 画面関連 */
static const int SCREEN_SIZE_WIDE			= 1920;		// 画面サイズ(横)
static const int SCREEN_SIZE_HEIGHT			= 1080;		// 画面サイズ(縦)
static const int SCREEN_Z_BUFFER_BIT_DEPTH	= 32;		// Zバッファのビット深度

static const int SCREEN_TYPE_NORMAL		= 0;	// 通常画面
static const int SCREEN_TYPE_SHADOWMAP	= 1;	// シャドウマップ
static const int SCREEN_TYPE_LIGHTMAP	= 2;	// ライトマップ

static const int SCREEN_TYPE_MAX		= 3;	// 画面タイプの最大数

/* フレームレート関連 */
static const int FPS_RATE			= 60;	// フレームレート設定値

/* 入力関連 */
// 入力タイプ
static const int INPUT_HOLD	= 0;	// ホールド入力
static const int INPUT_TRG	= 1;	// トリガ入力
static const int INPUT_REL	= 2;	// リリース入力
static const int INPUT_MAX	= 3;	// 入力タイプの最大数

// スティック、トリガー用左右判別
static const int INPUT_LEFT			= 0;	// 左(スティック、トリガー)
static const int INPUT_RIGHT		= 1;	// 右(スティック、トリガー)
static const int INPUT_DIRECTION	= 2;	// 左右の総数(※マジックナンバー対策で作成)

// 初期閾値
static const unsigned char	INIT_TRIGGER_THRESHOLD	= 10;	// トリガー入力の初期閾値

/* オブジェクトのタイプ */
// ※接触判定を行う際に使用
static const int OBJECT_TYPE_PLAYER			= 0;	// プレイヤー
static const int OBJECT_TYPE_ENEMY			= 1;	// エネミー
static const int OBJECT_TYPE_MELEE_PLAYER	= 2;	// 近接攻撃(プレイヤー)
static const int OBJECT_TYPE_BULLET_PLAYER	= 3;	// 弾丸(プレイヤー)
static const int OBJECT_TYPE_BULLET_ENEMY	= 4;	// 弾丸(エネミー)

/* Effekseer関連 */
static const int EFFECT_MAX_PARTICLE		= 8000;		// エフェクトの最大パーティクル数
