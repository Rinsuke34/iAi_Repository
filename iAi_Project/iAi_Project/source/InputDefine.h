/* 2024.12.22 駒沢風助 ファイル作成 */
/* 2025.01.21 菊池雅道 定数仮追加 */

#pragma once
#include <string>

/* 入力管理用の構造体や定数の宣言を行う */

/* 入力管理用の定数 */
/* 入力機器 */
static const int INPUT_EQUIPMENT_JOYPAD			= 0;	// ジョイパッド
static const int INPUT_EQUIPMENT_JOYPAD_TRIGGER	= 1;	// ジョイパッド(トリガー)
static const int INPUT_EQUIPMENT_KEYBOARD		= 2;	// キーボード
static const int INPUT_EQUIPMENT_MOUSE			= 3;	// マウス

/* 入力内容 */
// UI操作
static const int UI_UP		= 0;	// 上
static const int UI_DOWN	= 1;	// 下
static const int UI_LEFT	= 2;	// 左
static const int UI_RIGHT	= 3;	// 右
static const int UI_DECID	= 4;	// 決定
static const int UI_CANCEL	= 5;	// キャンセル
static const int UI_PAUSE	= 6;	// ポーズ
static const int UI_ANY		= 7;	// 任意のボタン

// ゲーム操作
static const int GAME_JUMP		= 0;	// ジャンプ
static const int GAME_ATTACK	= 1;	// 攻撃
static const int GAME_AIM		= 2;	// エイム(構え)
static const int GAME_RESET		= 3;	// カメラリセット
static const int GAME_DODGE		= 4;	// 回避
static const int GAME_FORWARD	= 5;	// 前進(キーボード＆マウス専用)
static const int GAME_BACK		= 6;	// 後退(キーボード＆マウス専用)
static const int GAME_LEFT		= 7;	// 左移動(キーボード＆マウス専用)
static const int GAME_RIGHT		= 8;	// 右移動(キーボード＆マウス専用)

/* 入力コード(オリジナル処理用) */
// ジョイパッド(XInput用)
static const int XINPUT_TRIGGER_LEFT	= 0;	// 左トリガー
static const int XINPUT_TRIGGER_RIGHT	= 1;	// 右トリガー

/* 仮追加 */
const float STICK_DEAD_ZONE = 0.01f; //スティック入力のデッドゾーン（範囲：範囲：0 ～ 32767）/*2025.01.09 菊池雅道 仮追加 */

/* 入力管理用の構造体 */

namespace Struct_Json_Input
{
	/* 入力情報 */
	struct INPUT_INFO
	{
		int			iInput;			// 入力コード
		int			iEquipmentType;	// 入力機器の種類		
		std::string pcName;			// 入力の名称
	};

	/* キーコンフィグ情報 */
	struct CONFIG_INFO
	{
		int			iGameControl;	// ゲーム操作の種類
		int			iInput;			// 入力コード
		int			iEquipmentType;	// 入力機器の種類
	};

	/* Jsonファイル読み込み用情報 */
	struct CONFIG_JSON
	{
		int			iGameControl;		// ゲーム操作の種類
		std::string	pcControlName;		// 入力の名称
		bool		bKeyboardMouseOnly;	// キーボード＆マウス専用
	};
}
