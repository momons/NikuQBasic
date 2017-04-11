//
//  QBasicValidation.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/25.
//
//

#ifndef QBasicValidation_h
#define QBasicValidation_h

#include <stdio.h>

using namespace std;

/// インタプリタ バリデーション関連クラス
class QBasicValidation final {
public:
	
	/// エラーメッセージ
	static string errorMessage;
	
	/**
	 *  変数名チェック
	 *  @param variableName 変数名
	 *  @return 変数名として使用可能か
	 */
	static bool isValidVariableName(const string variableName);

	/**
	 *  関数名チェック
	 *  @param functionName 関数名
	 *  @return 変数名として使用可能か
	 */
	static bool isValidFunctionName(const string functionName);
	
	/**
	 *  数値チェック
	 *  @param num 文字
	 *  @return 数値か否か
	 */
	static bool isNumeric(const string num);

private:
	
	/// 基本ステートメント名
	static const vector<string> basicStatementNames;

	/**
	 *  コンストラクタ
	 */
	QBasicValidation() {}
	
	/**
	 *  デストラクタ
	 */
	~QBasicValidation() {}
	
};

#endif /* QBasicValidation_h */
