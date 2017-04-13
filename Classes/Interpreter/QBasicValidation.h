//
//  QBasicValidation.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/25.
//
//

#ifndef QBasicValidation_h
#define QBasicValidation_h

#include <string>
#include <vector>

using namespace std;

enum class VariableType;

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
	static bool isValidVariableName(const string &variableName);

	/**
	 *  関数名チェック
	 *  @param functionName 関数名
	 *  @return 変数名として使用可能か
	 */
	static bool isValidFunctionName(const string &functionName);
	
	/**
	 *  整数チェック
	 *  @param num 文字
	 *  @return 整数可否
	 */
	static bool isInt(const string &num);

	/**
	 *  数値チェック
	 *  @param num 文字
	 *  @return 数値か否か
	 */
	static bool isFloat(const string &num);
	
	/**
	 *  文字チェック
	 *  @param str 文字
	 *  @return 文字可否
	 */
	static bool isStr(const string &str);
	
	/**
	 *  ブール値チェック
	 *  @param str 文字
	 *  @return ブール値可否
	 */
	static bool isBool(const string &str);
	
	/**
	 *  変数タイプのチェック
	 *  @param str 文字
	 *  @return 変数タイプ
	 */
	static VariableType checkVariableType(const string &str);
	
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
