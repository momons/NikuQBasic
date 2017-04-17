//
//  QBasicTextFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#ifndef QBasicTextFunctions_h
#define QBasicTextFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト テキスト描画サブ関数群
class QBasicTextFunctions final {
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
	/// フォント指定
	static QBasicVariableEntity *font_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// テキスト描画
	static QBasicVariableEntity *text_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);

};

#endif /* QBasicTextFunctions_h */
