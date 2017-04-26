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
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("max", {VariableType::Float,VariableType::Float}, VariableType::Float, max_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("min", {VariableType::Float,VariableType::Float}, VariableType::Float, min_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("sin", {VariableType::Float}, VariableType::Float, sin_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("cos", {VariableType::Float}, VariableType::Float, cos_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("tan", {VariableType::Float}, VariableType::Float, tan_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("asin", {VariableType::Float}, VariableType::Float, asin_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("acos", {VariableType::Float}, VariableType::Float, acos_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("atan", {VariableType::Float}, VariableType::Float, atan_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("atan2", {VariableType::Float,VariableType::Float}, VariableType::Float, atan2_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("sinh", {VariableType::Float}, VariableType::Float, sinh_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("cosh", {VariableType::Float}, VariableType::Float, cosh_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("tanh", {VariableType::Float}, VariableType::Float, tanh_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("cbrt", {VariableType::Float}, VariableType::Float, cbrt_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("pow", {VariableType::Float,VariableType::Float}, VariableType::Float, pow_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("sqrt", {VariableType::Float}, VariableType::Float, sqrt_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("exp", {VariableType::Float}, VariableType::Float, exp_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("log", {VariableType::Float}, VariableType::Float, log_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("log10", {VariableType::Float}, VariableType::Float, log10_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("deg2rad", {VariableType::Float}, VariableType::Float, deg2rad_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("rad2deg", {VariableType::Float}, VariableType::Float, rad2deg_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("rand", {VariableType::Int}, VariableType::Int, rand_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("round", {VariableType::Float}, VariableType::Float, round_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("floor", {VariableType::Float}, VariableType::Float, floor_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("ceil", {VariableType::Float}, VariableType::Float, ceil_qb);
	statementList[entity.alias] = entity;

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
/// ハイパボリックサイン
QBasicVariableEntity QBasicMathFunctions::sinh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = sinh(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// ハイパボリックコサイン
QBasicVariableEntity QBasicMathFunctions::cosh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = cosh(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// ハイパボリックタンジェント
QBasicVariableEntity QBasicMathFunctions::tanh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = tanh(arg[0].floatValue);
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
/// 乗を求める
QBasicVariableEntity QBasicMathFunctions::exp_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = exp(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 自然対数
QBasicVariableEntity QBasicMathFunctions::log_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = log(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 常用対数
QBasicVariableEntity QBasicMathFunctions::log10_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = log10(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// デグリーからラジアン
QBasicVariableEntity QBasicMathFunctions::deg2rad_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].floatValue * 3.14159265 / 180.0;
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// ラジアンからデグリー
QBasicVariableEntity QBasicMathFunctions::rad2deg_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].floatValue * 180.0 / 3.14159265;
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 乱数
QBasicVariableEntity QBasicMathFunctions::rand_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = rand() % arg[0].intValue;
	return QBasicVariableEntity("", VariableType::Int, &answer);
}
/// 四捨五入
QBasicVariableEntity QBasicMathFunctions::round_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = round(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 四捨五入
QBasicVariableEntity QBasicMathFunctions::floor_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = floor(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 切り捨て
QBasicVariableEntity QBasicMathFunctions::ceil_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = ceil(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
