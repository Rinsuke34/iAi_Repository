/* 2025.01.30 駒沢風助 ファイル作成 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "SoundDefine.h"

/* 循環参照対策先行定義 */
class DataList_Option;

/* サウンド管理データリストの宣言 */

// サウンド管理データリスト
class DataList_Sound : public DataListBase
{
	public:
		DataList_Sound();				// コンストラクタ
		virtual ~DataList_Sound();		// デストラクタ

		/* BGM関係 */
		void BGM_SetHandle(int iBgmNo);			// BGMを設定
		void BGM_DeleteHandle();				// BGMを削除
		void BGM_PlaySound();					// BGMを再生
		void BGM_VolumeChange();				// BGMを音量変更
		void BGM_StopSound();					// BGMを停止

		/* SE関係 */
		void SE_AllSetHandle();					// 全てのサウンドハンドルを取得
		void SE_PlaySound(int iSeNo);			// サウンドを再生

		/* ボイス関係 */
		//void VOICE_AllSetHandle();				// 全てのボイスハンドルを取得
		//void VOICE_PlaySound(int iVoiceNo);		// ボイスを再生

	private:
		/* データリスト */
		DataList_Option* OptionList;				// オプション設定管理

		/* BGM関係 */
		// ※BGMは再生するタイミングで読み込みを行う
		int iBgmHandle;								// BGMのハンドル

		/* SE関係 */
		std::map<std::string, int>	pSeHandleList;	// サウンドハンドルリスト

		/* ボイス関係 */
};
