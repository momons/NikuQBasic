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
class QBasicVariableEntity;

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
	static QBasicVariableEntity *touchbegincnt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タッチ開始 X座標取得
	static QBasicVariableEntity *touchbeginx_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タッチ開始 Y座標取得
	static QBasicVariableEntity *touchbeginy_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タッチ移動 カウント
	static QBasicVariableEntity *touchmovecnt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タッチ移動 X座標取得
	static QBasicVariableEntity *touchmovex_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タッチ移動 Y座標取得
	static QBasicVariableEntity *touchmovey_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タッチ終了 カウント
	static QBasicVariableEntity *touchendcnt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タッチ終了 X座標取得
	static QBasicVariableEntity *touchendx_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タッチ終了 Y座標取得
	static QBasicVariableEntity *touchendy_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
};

#endif /* QBasicTouchFunctions_h */
