//
//  QBInterpreterStorageFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#ifndef QBInterpreterStorageFunctions_h
#define QBInterpreterStorageFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト ストレージサブ関数群
class QBInterpreterStorageFunctions final {
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
	/// 読み込み
	static string load_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// セーブ
	static string save_qb(QBInterpreter *interpreter, const vector<string> arg);

};

#endif /* QBInterpreterStorageFunctions_h */
