//
//  QBasicMathFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/20.
//
//

#include "QBasicMathFunctions.h"

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
unordered_map<string, QBasicStatementEntity> QBasicMathFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("abs", {VariableType::Float}, VariableType::Float, abs_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("max", {VariableType::Float,VariableType::Float}, VariableType::Float, max_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("min", {VariableType::Float,VariableType::Float}, VariableType::Float, min_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("sin", {VariableType::Float}, VariableType::Float, sin_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("cos", {VariableType::Float}, VariableType::Float, cos_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("tan", {VariableType::Float}, VariableType::Float, tan_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("asin", {VariableType::Float}, VariableType::Float, asin_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("acos", {VariableType::Float}, VariableType::Float, acos_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("atan", {VariableType::Float}, VariableType::Float, atan_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("atan2", {VariableType::Float,VariableType::Float}, VariableType::Float, atan2_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("cbrt", {VariableType::Float}, VariableType::Float, cbrt_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("pow", {VariableType::Float,VariableType::Float}, VariableType::Float, pow_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("sqrt", {VariableType::Float}, VariableType::Float, sqrt_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("deg2red", {VariableType::Float}, VariableType::Float, deg2red_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("rand", {VariableType::Int}, VariableType::Int, rand_qb);
	statementList[entity.name] = entity;

	return statementList;
}

/// 絶対値
QBasicVariableEntity QBasicMathFunctions::abs_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = fabs(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 最大値
QBasicVariableEntity QBasicMathFunctions::max_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = fmax(arg[0].floatValue, arg[1].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 最小値
QBasicVariableEntity QBasicMathFunctions::min_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = fmin(arg[0].floatValue, arg[1].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// サイン
QBasicVariableEntity QBasicMathFunctions::sin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = sin(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// コサイン
QBasicVariableEntity QBasicMathFunctions::cos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = cos(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// タンジェント
QBasicVariableEntity QBasicMathFunctions::tan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = tan(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// アークサイン
QBasicVariableEntity QBasicMathFunctions::asin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = asin(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// アークコサイン
QBasicVariableEntity QBasicMathFunctions::acos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = acos(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// アークタンジェント
QBasicVariableEntity QBasicMathFunctions::atan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = atan(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// アークタンジェント2
QBasicVariableEntity QBasicMathFunctions::atan2_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = atan2(arg[0].floatValue, arg[1].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 平方根
QBasicVariableEntity QBasicMathFunctions::cbrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = cbrt(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// へき乗
QBasicVariableEntity QBasicMathFunctions::pow_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = pow(arg[0].floatValue, arg[1].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// ルート
QBasicVariableEntity QBasicMathFunctions::sqrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = sqrt(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// デグリーからラジアン
QBasicVariableEntity QBasicMathFunctions::deg2red_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].floatValue * 3.14159265 / 180.0;
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 乱数
QBasicVariableEntity QBasicMathFunctions::rand_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = rand() % arg[0].intValue;
	return QBasicVariableEntity("", VariableType::Int, &answer);
}
