//
//  QBasicDebugFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#ifndef QBasicDebugFunctions_h
#define QBasicDebugFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト デバッグサブ関数群
class QBasicDebugFunctions final {
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
	static QBasicVariableEntity *wait_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	static QBasicVariableEntity *log_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	static QBasicVariableEntity *error_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);

};

#endif /* QBasicDebugFunctions_h */
