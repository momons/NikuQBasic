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
	/// タッチ開始
	static inline QBasicVariableEntity touchBegin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タッチ移動
	static inline QBasicVariableEntity touchMove_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タッチ終了 カウント
	static inline QBasicVariableEntity touchEnd_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
};

#endif /* QBasicTouchFunctions_h */
