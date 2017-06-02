//
//  QBasicStringFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#include "QBasicStringFunctions.h"

#include "QBasic.h"
#include "StringUtil.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicStringFunctions::buildStatements() {

	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;

	entity = QBasicStatementEntity("len", len_params(), VariableType::Int, len_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("mid", mid_params(), VariableType::Str, mid_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("left", left_params(), VariableType::Str, left_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("right", right_params(), VariableType::Str, right_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("split", split_params(), VariableType::List, {VariableType::Str}, split_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("empty", empty_params(), VariableType::Bool, empty_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("notEmpty", notEmpty_params(), VariableType::Bool, notEmpty_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("replase", replase_params(), VariableType::Str, replase_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("prefix", prefix_params(), VariableType::Bool, prefix_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("suffix", suffix_params(), VariableType::Bool, suffix_qb);
	statementList[entity.alias] = entity;

	return statementList;
}

/// 文字列長取得
vector<QBasicVariableEntity> QBasicStringFunctions::len_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("s", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStringFunctions::len_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	int answer = (int)arg[0].strValue.length();
	return QBasicVariableEntity("", VariableType::Int, &answer);
}
/// 真ん中切り取り
vector<QBasicVariableEntity> QBasicStringFunctions::mid_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("s", VariableType::Str, nullptr));
	argNames.push_back(QBasicVariableEntity("index", VariableType::Int, nullptr));
	argNames.push_back(QBasicVariableEntity("length", VariableType::Int, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStringFunctions::mid_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].strValue.substr(arg[1].intValue, arg[2].intValue);
	return QBasicVariableEntity("", VariableType::Str, &answer);
}
/// 左切り取り
vector<QBasicVariableEntity> QBasicStringFunctions::left_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("s", VariableType::Str, nullptr));
	argNames.push_back(QBasicVariableEntity("length", VariableType::Int, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStringFunctions::left_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].strValue.substr(0, arg[1].intValue);
	return QBasicVariableEntity("", VariableType::Str, &answer);
}
/// 右切り取り
vector<QBasicVariableEntity> QBasicStringFunctions::right_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("s", VariableType::Str, nullptr));
	argNames.push_back(QBasicVariableEntity("length", VariableType::Int, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStringFunctions::right_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].strValue.substr(arg[0].strValue.length() - arg[1].intValue, arg[1].intValue);
	return QBasicVariableEntity("", VariableType::Str, &answer);
}
/// 分割
vector<QBasicVariableEntity> QBasicStringFunctions::split_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("s", VariableType::Str, nullptr));
	argNames.push_back(QBasicVariableEntity("delimiter", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStringFunctions::split_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	vector<string> answer;
	StringUtil::split(answer, arg[0].strValue, arg[1].strValue);
	vector<QBasicVariableEntity> values;
	for (auto it = answer.begin();it != answer.end();it++) {
		string str = *it;
		values.push_back(QBasicVariableEntity("", VariableType::Str, &str));
	}
	return QBasicVariableEntity("", {VariableType::Str}, values);
}
// Empty
vector<QBasicVariableEntity> QBasicStringFunctions::empty_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("s", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStringFunctions::empty_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].strValue.empty() || arg[0].isNil;
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
// NotEmpty
vector<QBasicVariableEntity> QBasicStringFunctions::notEmpty_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("s", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStringFunctions::notEmpty_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = !arg[0].strValue.empty() && !arg[0].isNil;
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
/// 置換
vector<QBasicVariableEntity> QBasicStringFunctions::replase_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("s", VariableType::Str, nullptr));
	argNames.push_back(QBasicVariableEntity("search", VariableType::Str, nullptr));
	argNames.push_back(QBasicVariableEntity("rep", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStringFunctions::replase_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	string::size_type pos(arg[0].strValue.find(arg[1].strValue));
	string retStr = arg[0].strValue;
	while (pos != string::npos) {
		retStr.replace(pos, arg[1].strValue.length(), arg[2].strValue);
		pos = retStr.find(arg[1].strValue, pos + arg[2].strValue.length());
	}
	return QBasicVariableEntity("", VariableType::Str, &retStr);
}
/// 前方一致
vector<QBasicVariableEntity> QBasicStringFunctions::prefix_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("s", VariableType::Str, nullptr));
	argNames.push_back(QBasicVariableEntity("search", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStringFunctions::prefix_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = mismatch(arg[1].strValue.begin(), arg[1].strValue.end(), arg[0].strValue.begin()).first == arg[1].strValue.end();
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
/// 後方一致
vector<QBasicVariableEntity> QBasicStringFunctions::suffix_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("s", VariableType::Str, nullptr));
	argNames.push_back(QBasicVariableEntity("search", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStringFunctions::suffix_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = false;
	if (arg[0].strValue.length() >= arg[1].strValue.length()) {
		answer = arg[0].strValue.compare(arg[0].strValue.length() - arg[1].strValue.length(), arg[1].strValue.length(), arg[1].strValue) == 0;
	}
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
