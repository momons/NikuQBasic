//
//  QBasicTouchFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#ifndef QBasicTouchFunctions_h
#define QBasicTouchFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;

/// スクリプト タッチサブ関数群
class QBasicTouchFunctions final {
public:
	
	/**
	 *  ステートメントを作成
	 *
	 *  @return 文字操作ステートメント
	 */
	static unordered_map<string, QBasicStatementEntity> buildStatements();
	
	/**
	 *  スクリプト用ステートメント
	 *  @param interpreter 親クラス
	 *  @param arg         引数
	 *  @return 戻り値
	 */
	/// タッチ開始 カウント
	static string touchbegincnt_qb(QBasic *interpreter, const vector<string> arg);
	/// タッチ開始 X座標取得
	static string touchbeginx_qb(QBasic *interpreter, const vector<string> arg);
	/// タッチ開始 Y座標取得
	static string touchbeginy_qb(QBasic *interpreter, const vector<string> arg);
	/// タッチ移動 カウント
	static string touchmovecnt_qb(QBasic *interpreter, const vector<string> arg);
	/// タッチ移動 X座標取得
	static string touchmovex_qb(QBasic *interpreter, const vector<string> arg);
	/// タッチ移動 Y座標取得
	static string touchmovey_qb(QBasic *interpreter, const vector<string> arg);
	/// タッチ終了 カウント
	static string touchendcnt_qb(QBasic *interpreter, const vector<string> arg);
	/// タッチ終了 X座標取得
	static string touchendx_qb(QBasic *interpreter, const vector<string> arg);
	/// タッチ終了 Y座標取得
	static string touchendy_qb(QBasic *interpreter, const vector<string> arg);
};

#endif /* QBasicTouchFunctions_h */
