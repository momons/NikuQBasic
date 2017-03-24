//
//  QBInterpreterValidation.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/25.
//
//

#ifndef QBInterpreterValidation_h
#define QBInterpreterValidation_h

#include <stdio.h>

using namespace std;

/// インタプリタ バリデーション関連クラス
class QBInterpreterValidation final {
public:
	
	/**
	 *  変数名チェック
	 *  @param variableName 変数名
	 *  @return 変数名として使用可能か
	 */
	static bool isValidVariableName(const string variableName);

private:
	
	/// 基本ステートメント名
	static const vector<string> basicStatementNames;

	/**
	 *  コンストラクタ
	 */
	QBInterpreterValidation() {}
	
	/**
	 *  デストラクタ
	 */
	~QBInterpreterValidation() {}
	
};

#endif /* QBInterpreterValidation_h */
