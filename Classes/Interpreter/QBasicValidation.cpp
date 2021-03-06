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
	"var", "let",
	"if", "endif", "elseif", "else",
	"return",
	"for", "to", "step", "next",
	"while", "do",
	"break", "continue",
	"pass",
	"switch", "case", "default",
	"exit",
	"func", "endfunc",
	"try", "catch", "throw",
	"void", "int", "long", "float", "double", "str", "bool", "true", "false", "list", "dict",
	"nil", "null",
	"class", "endclass",
	"struct", "endstruct",
	"private", "protected", "public",
	"final", "override",
	"import",
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
	if (statements->hasName(functionName)) {
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
 *  変数タイプチェック
 *  @param value1     変数Entity1
 *  @param value2     変数Entity2
 *  @return 変数可否
 */
bool QBasicValidation::isValidVariableType(
										   const QBasicVariableEntity &value1,
										   const QBasicVariableEntity &value2) {
	if (value1.isNil && value2.isNil) {
		return true;
	}
	if ((value1.isNil && value1.types[0] == VariableType::Unknown) ||
		(value2.isNil && value2.types[0] == VariableType::Unknown)) {
		return true;
	}
	if (value1.types[0] != value2.types[0]) {
		return false;
	}
	switch (value1.types[0]) {
		case VariableType::List:
			if (!QBasicValidation::isValidVariableTypeList(value1, value2.types, 1)) {
				return false;
			}
			break;
		case VariableType::Dict:
			if (!QBasicValidation::isValidVariableTypeDict(value1, value2.types, 1)) {
				return false;
			}
			break;
		default:
			break;
	}
	return true;
}

/**
 *  変数チェック
 *  @param variableEntity     変数Entity
 *  @param valueVariableTypes 変数タイプ群
 *  @return 配列変数可否
 */
bool QBasicValidation::isValidVariableType(
										   const QBasicVariableEntity &variableEntity,
										   const vector<VariableType> &variableTypes) {
	if (variableEntity.types[0] == VariableType::Unknown && variableEntity.isNil) {
		return true;
	}
	if (variableEntity.types[0] != variableTypes[0]) {
		return false;
	}
	switch (variableEntity.types[0]) {
		case VariableType::List:
			if (!QBasicValidation::isValidVariableTypeList(variableEntity, variableTypes, 1)) {
				return false;
			}
			break;
		case VariableType::Dict:
			if (!QBasicValidation::isValidVariableTypeDict(variableEntity, variableTypes, 1)) {
				return false;
			}
			break;
		default:
			break;
	}
	return true;
}

/**
 *  配列変数チェック
 *  @param variableEntity 変数Entity
 *  @param variableTypes  変数タイプ群
 *  @param level          階層
 *  @return 配列変数可否
 */
bool QBasicValidation::isValidVariableTypeList(
										   const QBasicVariableEntity &variableEntity,
										   const vector<VariableType> &variableTypes,
										   const int level) {
	for (auto it = variableEntity.listValue.begin();it != variableEntity.listValue.end();it++) {
		if (variableTypes[level] != it->types[0]) {
			return false;
		}
		if (it->types[0] == VariableType::List) {
			if (!isValidVariableTypeList(*it, variableTypes, level + 1)) {
				return false;
			}
		} else if (it->types[0] == VariableType::Dict ) {
			if (!isValidVariableTypeDict(*it, variableTypes, level + 1)) {
				return false;
			}
		}
	}
	return true;
}

/**
 *  連想配列変数チェック
 *  @param variableEntity 変数Entity
 *  @param variableTypes  変数タイプ群
 *  @param level          階層
 *  @return 配列変数可否
 */
bool QBasicValidation::isValidVariableTypeDict(
										   const QBasicVariableEntity &variableEntity,
										   const vector<VariableType> &variableTypes,
										   const int level) {
	for (auto it = variableEntity.dictValue.begin();it != variableEntity.dictValue.end();it++) {
		if (variableTypes[level] != it->second.types[0]) {
			return false;
		}
		if (it->second.types[0] == VariableType::List) {
			if (!isValidVariableTypeList(it->second, variableTypes, level + 1)) {
				return false;
			}
		} else if (it->second.types[0] == VariableType::Dict) {
			if (!isValidVariableTypeDict(it->second, variableTypes, level + 1)) {
				return false;
			}
		}
	}
	return true;
}

/**
 *  論理演算可能かチェック
 *  @param srcEntity 比較元
 *  @param dstEntity 比較先
 *  @return 論理演算可否
 */
bool QBasicValidation::isValidExpression(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity) {
	return (srcEntity.types[0] == VariableType::Bool && dstEntity.types[0] == VariableType::Bool);
}

/**
 *  not可能かチェック
 *  @param entity 対象
 *  @return not可否
 */
bool QBasicValidation::isValidNot(const QBasicVariableEntity &entity) {
	return entity.types[0] == VariableType::Bool;
}

/**
 *  足し算可能かチェック
 *  @param srcEntity 比較元
 *  @param dstEntity 比較先
 *  @return 足し算可否
 */
bool QBasicValidation::isValidAdd(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity) {
	if ((srcEntity.types[0] == VariableType::Unknown && srcEntity.isNil) ||
		(dstEntity.types[0] == VariableType::Unknown && dstEntity.isNil) ) {
		return true;
	}
	return (srcEntity.types[0] == VariableType::Int && dstEntity.types[0] == VariableType::Int) ||
	(srcEntity.types[0] == VariableType::Float && dstEntity.types[0] == VariableType::Float) ||
	(srcEntity.types[0] == VariableType::Str && dstEntity.types[0] == VariableType::Str);
}

/**
 *  引き算可能かチェック
 *  @param entity 対象
 *  @return 引き算可否
 */
bool QBasicValidation::isValidSub(const QBasicVariableEntity &entity) {
	return entity.types[0] == VariableType::Int || entity.types[0] == VariableType::Float;
}

/**
 *  引き算可能かチェック
 *  @param srcEntity 比較元
 *  @param dstEntity 比較先
 *  @return 引き算可否
 */
bool QBasicValidation::isValidSub(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity) {
	if ((srcEntity.types[0] == VariableType::Unknown && srcEntity.isNil) ||
		(dstEntity.types[0] == VariableType::Unknown && dstEntity.isNil) ) {
		return true;
	}
	return (srcEntity.types[0] == VariableType::Int && dstEntity.types[0] == VariableType::Int) ||
	(srcEntity.types[0] == VariableType::Float && dstEntity.types[0] == VariableType::Float);
}

/**
 *  掛け算可能かチェック
 *  @param srcEntity 比較元
 *  @param dstEntity 比較先
 *  @return 引き算可否
 */
bool QBasicValidation::isValidMul(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity) {
	if ((srcEntity.types[0] == VariableType::Unknown && srcEntity.isNil) ||
		(dstEntity.types[0] == VariableType::Unknown && dstEntity.isNil) ) {
		return true;
	}
	return (srcEntity.types[0] == VariableType::Int && dstEntity.types[0] == VariableType::Int) ||
	(srcEntity.types[0] == VariableType::Float && dstEntity.types[0] == VariableType::Float);
}

/**
 *  掛け算可能かチェック
 *  @param srcEntity 比較元
 *  @param dstEntity 比較先
 *  @return 引き算可否
 */
bool QBasicValidation::isValidDiv(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity) {
	if ((srcEntity.types[0] == VariableType::Unknown && srcEntity.isNil) ||
		(dstEntity.types[0] == VariableType::Unknown && dstEntity.isNil) ) {
		return true;
	}
	return (srcEntity.types[0] == VariableType::Int && dstEntity.types[0] == VariableType::Int) ||
	(srcEntity.types[0] == VariableType::Float && dstEntity.types[0] == VariableType::Float);
}

/**
 *  掛け算可能かチェック
 *  @param srcEntity 比較元
 *  @param dstEntity 比較先
 *  @return 引き算可否
 */
bool QBasicValidation::isValidMod(const QBasicVariableEntity &srcEntity, const QBasicVariableEntity &dstEntity) {
	if ((srcEntity.types[0] == VariableType::Unknown && srcEntity.isNil) ||
		(dstEntity.types[0] == VariableType::Unknown && dstEntity.isNil) ) {
		return true;
	}
	return (srcEntity.types[0] == VariableType::Int && dstEntity.types[0] == VariableType::Int);
}

/**
 *  for可能かチェック
 *  @param entity 対象
 *  @return for可能可否
 */
bool QBasicValidation::isValidFor(const QBasicVariableEntity &entity) {
	return entity.types[0] == VariableType::Int;
}

/**
 *  if可能かチェック
 *  @param entity 対象
 *  @return for可能可否
 */
bool QBasicValidation::isValidIf(const QBasicVariableEntity &entity) {
	return entity.types[0] == VariableType::Bool;
}
