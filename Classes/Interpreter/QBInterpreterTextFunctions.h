//
//  QBInterpreterTextFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#ifndef QBInterpreterTextFunctions_h
#define QBInterpreterTextFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト テキスト描画サブ関数群
class QBInterpreterTextFunctions final {
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
	/// フォント指定
	static string font_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// テキスト描画
	static string text_qb(QBInterpreter *interpreter, const vector<string> arg);

};

#endif /* QBInterpreterTextFunctions_h */
