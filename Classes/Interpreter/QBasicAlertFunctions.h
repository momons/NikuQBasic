//
//  QBasicAlertFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#ifndef QBasicAlertFunctions_h
#define QBasicAlertFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;

/// スクリプト アラートサブ関数群
class QBasicAlertFunctions final {
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
	/// アラート
	static string alert_qb(QBasic *interpreter, const vector<string> arg);
	/// 確認アラート
	static string confirm_qb(QBasic *interpreter, const vector<string> arg);
	/// 入力アラート
	static string input_qb(QBasic *interpreter, const vector<string> arg);
	
};

#endif /* QBasicAlertFunctions_h */
