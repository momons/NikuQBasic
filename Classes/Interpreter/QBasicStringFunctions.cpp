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

	entity = QBasicStatementEntity("len", {VariableType::Str}, VariableType::Int, len_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("mid", {VariableType::Str, VariableType::Int, VariableType::Int}, VariableType::Str, mid_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("left", {VariableType::Str, VariableType::Int}, VariableType::Str, left_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("right", {VariableType::Str, VariableType::Int}, VariableType::Str, right_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("split", {VariableType::Str, VariableType::Str}, VariableType::List, {VariableType::Str}, split_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("empty", {VariableType::Str}, VariableType::Bool, empty_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("not_empty", {VariableType::Str}, VariableType::Bool, not_empty_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("replase", {VariableType::Str, VariableType::Str, VariableType::Str}, VariableType::Str, replase_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("prefix", {VariableType::Str, VariableType::Str}, VariableType::Bool, prefix_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("suffix", {VariableType::Str, VariableType::Str}, VariableType::Bool, suffix_qb);
	statementList[entity.name] = entity;

	return statementList;
}

/// 文字列長取得
QBasicVariableEntity QBasicStringFunctions::len_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	int answer = (int)arg[0].strValue.length();
	return QBasicVariableEntity("", VariableType::Int, &answer);
}
/// 真ん中切り取り
QBasicVariableEntity QBasicStringFunctions::mid_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].strValue.substr(arg[1].intValue, arg[2].intValue);
	return QBasicVariableEntity("", VariableType::Str, (void *)answer.c_str());
}
/// 左切り取り
QBasicVariableEntity QBasicStringFunctions::left_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].strValue.substr(0, arg[1].intValue);
	return QBasicVariableEntity("", VariableType::Str, (void *)answer.c_str());
}
/// 右切り取り
QBasicVariableEntity QBasicStringFunctions::right_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].strValue.substr(arg[0].strValue.length() - arg[1].intValue, arg[1].intValue);
	return QBasicVariableEntity("", VariableType::Str, (void *)answer.c_str());
}
/// 分割
QBasicVariableEntity QBasicStringFunctions::split_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	vector<string> answer;
	StringUtil::split(answer, arg[0].strValue, arg[1].strValue);
	vector<QBasicVariableEntity> values;
	for (auto it = answer.begin();it != answer.end();it++) {
		values.push_back(QBasicVariableEntity("", VariableType::Str, &it));
	}
	return QBasicVariableEntity("", {VariableType::Str}, values);
}
// Empty
QBasicVariableEntity QBasicStringFunctions::empty_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].strValue.empty();
	return QBasicVariableEntity("", VariableType::Str, &answer);
}
// NotEmpty
QBasicVariableEntity QBasicStringFunctions::not_empty_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = !arg[0].strValue.empty();
	return QBasicVariableEntity("", VariableType::Str, &answer);
}
/// 置換
QBasicVariableEntity QBasicStringFunctions::replase_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	string::size_type pos(arg[0].strValue.find(arg[1].strValue));
	string retStr = arg[0].strValue;
	while (pos != string::npos) {
		retStr.replace(pos, arg[1].strValue.length(), arg[2].strValue);
		pos = retStr.find(arg[1].strValue, pos + arg[2].strValue.length());
	}
	return QBasicVariableEntity("", VariableType::Str, (void *)retStr.c_str());
}
/// 前方一致
QBasicVariableEntity QBasicStringFunctions::prefix_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = mismatch(arg[0].strValue.begin(), arg[0].strValue.end(), arg[1].strValue.begin()).first == arg[1].strValue.begin();
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
/// 後方一致
QBasicVariableEntity QBasicStringFunctions::suffix_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = mismatch(arg[0].strValue.begin(), arg[0].strValue.end(), arg[1].strValue.begin()).first == arg[1].strValue.begin();
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
