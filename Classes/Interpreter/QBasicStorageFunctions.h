//
//  QBasicStorageFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#ifndef QBasicStorageFunctions_h
#define QBasicStorageFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;

/// スクリプト ストレージサブ関数群
class QBasicStorageFunctions final {
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
	/// 読み込み
	static string load_qb(QBasic *interpreter, const vector<string> arg);
	/// セーブ
	static string save_qb(QBasic *interpreter, const vector<string> arg);

};

#endif /* QBasicStorageFunctions_h */