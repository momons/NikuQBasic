//
//  QBInterpreterAlertFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#ifndef QBInterpreterAlertFunctions_h
#define QBInterpreterAlertFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト アラートサブ関数群
class QBInterpreterAlertFunctions final {
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
	/// アラート
	static string alert_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 確認アラート
	static string confirm_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 入力アラート
	static string input_qb(QBInterpreter *interpreter, const vector<string> arg);
	
};

#endif /* QBInterpreterAlertFunctions_h */
