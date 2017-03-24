//
//  QBInterpreterDebugFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#ifndef QBInterpreterDebugFunctions_h
#define QBInterpreterDebugFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト デバッグサブ関数群
class QBInterpreterDebugFunctions final {
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
	static string wait_qb(QBInterpreter *interpreter, const vector<string> arg);
	static string log_qb(QBInterpreter *interpreter, const vector<string> arg);
	static string error_qb(QBInterpreter *interpreter, const vector<string> arg);

};

#endif /* QBInterpreterDebugFunctions_h */
