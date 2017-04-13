//
//  QBasicValidation.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/25.
//
//

#include "QBasicValidation.h"

#include "QBasicStatements.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"
#include "QBasicMessages.h"

/// エラーメッセージ
string QBasicValidation::errorMessage;

/// 基本ステートメント名
const vector<string> QBasicValidation::basicStatementNames = {
	"var",
	"if",
	"then",
	"endif",
	"elseif",
	"else",
	"label",
	"goto",
	"gosub",
	"return",
	"for",
	"to",
	"step",
	"next",
	"rem",
	"exit",
	"and",
	"or",
	"xor",
	"func",
	"end",
	"void",
	"int",
	"float",
	"str",
	"bool",
	"list",
	"dict",
};

/**
 *  変数名チェック
 *  @param variableName 変数名
 *  @return 変数名として使用可能か
 */
bool QBasicValidation::isValidVariableName(const string &variableName) {

	// 他の命令と被っていないか
	if (find(basicStatementNames.begin(), basicStatementNames.end(), variableName) != basicStatementNames.end()) {
		// [ERROR]変数名が予約語と被っています。
		errorMessage = QBasicMessages::sharedInstance()->getMessage("BadVariableName1", variableName.c_str());
		return false;
	}
	auto statements = QBasicStatements::sharedInstance();
	if (statements->getStatement(variableName) != nullptr) {
		// [ERROR]変数名が予約語と被っています。
		errorMessage = QBasicMessages::sharedInstance()->getMessage("BadVariableName1", variableName.c_str());
		return false;
	}
	
	int i = 0;
	for (i = 0;i < variableName.length();i++) {
		char c = variableName.c_str()[i];
		// アルファベットOK
		if (isalpha(c)) {
			continue;
		}
		// 最初の文字に数字はダメ
		if (isdigit(c)) {
			if (i == 0) {
				// [ERROR]変数名の頭に数字を使用しています。
				errorMessage = QBasicMessages::sharedInstance()->getMessage("BadVariableName2", variableName.c_str());
				return false;
			}
			continue;
		}
		// [ERROR]変数名に英数字以外を使用しています
		errorMessage = QBasicMessages::sharedInstance()->getMessage("BadVariableName3", variableName.c_str());
		return false;
	}
	return true;
}

/**
 *  関数名チェック
 *  @param functionName 関数名
 *  @return 変数名として使用可能か
 */
bool QBasicValidation::isValidFunctionName(const string &functionName) {

	// 他の命令と被っていないか
	if (find(basicStatementNames.begin(), basicStatementNames.end(), functionName) != basicStatementNames.end()) {
		// [ERROR]関数名が予約語と被っています。
		errorMessage = QBasicMessages::sharedInstance()->getMessage("BadFunctionName1", functionName.c_str());
		return false;
	}
	auto statements = QBasicStatements::sharedInstance();
	if (statements->getStatement(functionName) != nullptr) {
		// [ERROR]関数名が予約語と被っています。
		errorMessage = QBasicMessages::sharedInstance()->getMessage("BadFunctionName1", functionName.c_str());
		return false;
	}
	
	int i = 0;
	for (i = 0;i < functionName.length();i++) {
		char c = functionName.c_str()[i];
		// アルファベットOK
		if (isalpha(c)) {
			continue;
		}
		// 最初の文字に数字はダメ
		if (isdigit(c)) {
			if (i == 0) {
				// [ERROR]関数名の頭に数字を使用しています。
				errorMessage = QBasicMessages::sharedInstance()->getMessage("BadFunctionName2", functionName.c_str());
				return false;
			}
			continue;
		}
		// [ERROR]変数名に英数字以外を使用しています
		errorMessage = QBasicMessages::sharedInstance()->getMessage("BadFunctionName3", functionName.c_str());
		return false;
	}
	return true;
}

/**
 *  整数チェック
 *  @param num 文字
 *  @return 整数可否
 */
bool QBasicValidation::isInt(const string &num) {

	if (num.length() <= 0) {
		return false;
	}

	const char *cstr = num.c_str();
	if (cstr[0] == '-' || isdigit(cstr[0])) {
		for(int i = 1; i < num.length(); i++) {
			if (!isdigit(cstr[i])) {
				return false;
			}
		}
		return true;
	}
	
	return false;
}

/**
 *  数値チェック
 *  @param num 文字
 *  @return 数値か否か
 */
bool QBasicValidation::isFloat(const string &num) {
	
	if (num.length() <= 0) {
		return false;
	}
	
	const char *cstr = num.c_str();
	if (cstr[0] == '-' || cstr[0] == '.' || isdigit(cstr[0])) {
		bool hasPeriod = cstr[0] == '.';
		for(int i = 1; i < num.length(); i++) {
			if (cstr[i] == '.') {
				if (hasPeriod) {
					return false;
				}
				hasPeriod = true;
			} else if (!isdigit(cstr[i])) {
				return false;
			}
		}
		return true;
	}
	
	return false;
}

/**
 *  文字チェック
 *  @param str 文字
 *  @return 文字可否
 */
bool QBasicValidation::isStr(const string &str) {
	
	if (str.length() < 2) {
		return false;
	}
	const string quot = "\"";
	auto res = mismatch(quot.begin(), quot.end(), str.begin());
	if (res.first != quot.end()) {
		return false;
	}

	return str.compare(str.length() - quot.length(), quot.length(), quot) == 0;
}

/**
 *  ブール値チェック
 *  @param str 文字
 *  @return ブール値可否
 */
bool QBasicValidation::isBool(const string &str) {
	return str.compare("true") == 0 || str.compare("false") == 0;
}


/**
 *  変数タイプのチェック
 *  @param str 文字
 *  @return 変数タイプ
 */
VariableType QBasicValidation::checkVariableType(const string &str) {
	if (str.compare("void") == 0) {
		return VariableType::Void;
	}
	if (str.compare("int") == 0) {
		return VariableType::Int;
	}
	if (str.compare("float") == 0) {
		return VariableType::Float;
	}
	if (str.compare("str") == 0) {
		return VariableType::Str;
	}
	if (str.compare("bool") == 0) {
		return VariableType::Bool;
	}
//	if (str.compare("list") == 0) {
//		return VariableType::List;
//	}
//	if (str.compare("dict") == 0) {
//		return VariableType::Dict;
//	}
	return VariableType::Unknown;
}
