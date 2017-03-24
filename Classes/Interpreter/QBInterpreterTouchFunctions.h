//
//  QBInterpreterTouchFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#ifndef QBInterpreterTouchFunctions_h
#define QBInterpreterTouchFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト タッチサブ関数群
class QBInterpreterTouchFunctions final {
public:
	
	/**
	 *  ステートメントを作成
	 *
	 *  @return 文字操作ステートメント
	 */
	static unordered_map<string, QBInterpreterStatementEntity> buildStatements();
	
	/**
	 *  スクリプト用ステートメント
	 *  @param interpreter 親クラス
	 *  @param arg         引数
	 *  @return 戻り値
	 */
	/// タッチ開始 カウント
	static string touchbegincnt_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// タッチ開始 X座標取得
	static string touchbeginx_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// タッチ開始 Y座標取得
	static string touchbeginy_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// タッチ移動 カウント
	static string touchmovecnt_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// タッチ移動 X座標取得
	static string touchmovex_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// タッチ移動 Y座標取得
	static string touchmovey_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// タッチ終了 カウント
	static string touchendcnt_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// タッチ終了 X座標取得
	static string touchendx_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// タッチ終了 Y座標取得
	static string touchendy_qb(QBInterpreter *interpreter, const vector<string> arg);
};

#endif /* QBInterpreterTouchFunctions_h */
