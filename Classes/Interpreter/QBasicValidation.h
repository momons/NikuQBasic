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
class QBasicVariableEntity;

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
	
	/**
	 *  論理演算可能かチェック
	 *  @param srcEntity 比較元
	 *  @param dstEntity 比較先
	 *  @return 論理演算可否
	 */
	static bool isValidExpression(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity);

	/**
	 *  not可能かチェック
	 *  @param entity 対象
	 *  @return not可否
	 */
	static bool isValidNot(const QBasicVariableEntity &entity);

	/**
	 *  足し算可能かチェック
	 *  @param srcEntity 比較元
	 *  @param dstEntity 比較先
	 *  @return 足し算可否
	 */
	static bool isValidAdd(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity);

	/**
	 *  引き算可能かチェック
	 *  @param entity 対象
	 *  @return 引き算可否
	 */
	static bool isValidSub(const QBasicVariableEntity &entity);
	
	/**
	 *  引き算可能かチェック
	 *  @param srcEntity 比較元
	 *  @param dstEntity 比較先
	 *  @return 引き算可否
	 */
	static bool isValidSub(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity);

	/**
	 *  掛け算可能かチェック
	 *  @param srcEntity 比較元
	 *  @param dstEntity 比較先
	 *  @return 引き算可否
	 */
	static bool isValidMul(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity);

	/**
	 *  掛け算可能かチェック
	 *  @param srcEntity 比較元
	 *  @param dstEntity 比較先
	 *  @return 引き算可否
	 */
	static bool isValidDiv(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity);

	/**
	 *  掛け算可能かチェック
	 *  @param srcEntity 比較元
	 *  @param dstEntity 比較先
	 *  @return 引き算可否
	 */
	static bool isValidMod(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity);

	/**
	 *  for可能かチェック
	 *  @param entity 対象
	 *  @return for可能可否
	 */
	static bool isValidFor(const QBasicVariableEntity &entity);

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
