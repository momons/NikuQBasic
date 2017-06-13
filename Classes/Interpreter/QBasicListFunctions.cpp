	//
//  QBasicListFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/10.
//
//

#include "QBasicListFunctions.h"

#include "QBasic.h"
#include "StringUtil.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"
#include "QBasicErrors.h"
#include "QBasicErrorEntity.h"
#include "QBasicValidation.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicListFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("count", count_params(), { VariableType::Int }, count_qb, count_compile);
	statementList[entity.alias] = entity;
//	entity = QBasicStatementEntity("append", append_params(), { VariableType::List }, append_qb, append_compile);
//	statementList[entity.alias] = entity;
//	entity = QBasicStatementEntity("extend", extend_params(), VariableType::List, count_qb, extend_compile);
//	statementList[entity.alias] = entity;
	
	return statementList;
}

/// 要素数カウント
vector<QBasicVariableEntity> QBasicListFunctions::count_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Unknown }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicListFunctions::count_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	int count = 0;
	switch (arg[0].types[0]) {
		case VariableType::List:
			count = arg[0].isNil ? 0 : (int)arg[0].listValue.size();
			break;
		case VariableType::Dict:
			count = arg[0].isNil ? 0 : (int)arg[0].dictValue.size();
			break;
		default:
			break;
	}
	return QBasicVariableEntity("", { VariableType::Int }, &count);
}
void QBasicListFunctions::count_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset) {
	vector<VariableType> variableTypes = {
		VariableType::List,
		VariableType::Dict,
	};
	if (find(variableTypes.begin(), variableTypes.end(), arg[0].types[0]) == variableTypes.end()){
		interpreter->errors->addError(symbolOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(variableTypes, arg[0]));
	}
}
// 要素追加
vector<QBasicVariableEntity> QBasicListFunctions::append_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", { VariableType::List }, nullptr));
	argNames.push_back(QBasicVariableEntity("append", { VariableType::Unknown }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicListFunctions::append_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0];
	answer.listValue.push_back(arg[1]);
	return QBasicVariableEntity("", answer.types, &answer);
}
void QBasicListFunctions::append_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset) {
	if (!QBasicValidation::isValidVariableTypeList(arg[0], arg[1].types, 0)) {
		interpreter->errors->addError(symbolOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(arg[0].types, arg[1].types));
	}
}

