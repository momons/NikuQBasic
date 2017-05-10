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
	
	entity = QBasicStatementEntity("abs", abs_params(), VariableType::Float, abs_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("max", max_params(), VariableType::Float, max_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("min", min_params(), VariableType::Float, min_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("sin", sin_params(), VariableType::Float, sin_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("cos", cos_params(), VariableType::Float, cos_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("tan", tan_params(), VariableType::Float, tan_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("asin", asin_params(), VariableType::Float, asin_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("acos", acos_params(), VariableType::Float, acos_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("atan", atan_params(), VariableType::Float, atan_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("atan2", atan2_params(), VariableType::Float, atan2_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("sinh", sinh_params(), VariableType::Float, sinh_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("cosh", cosh_params(), VariableType::Float, cosh_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("tanh", tanh_params(), VariableType::Float, tanh_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("cbrt", cbrt_params(), VariableType::Float, cbrt_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("pow", pow_params(), VariableType::Float, pow_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("sqrt", sqrt_params(), VariableType::Float, sqrt_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("exp", exp_params(), VariableType::Float, exp_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("log", log_params(), VariableType::Float, log_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("log10", log10_params(), VariableType::Float, log10_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("deg2rad", deg2rad_params(), VariableType::Float, deg2rad_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("rad2deg", rad2deg_params(), VariableType::Float, rad2deg_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("rand", rand_params(), VariableType::Int, rand_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("round", round_params(), VariableType::Float, round_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("floor", floor_params(), VariableType::Float, floor_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("ceil", ceil_params(), VariableType::Float, ceil_qb);
	statementList[entity.alias] = entity;

	return statementList;
}

/// 絶対値
vector<QBasicVariableEntity> QBasicMathFunctions::abs_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::abs_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = fabs(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 最大値
vector<QBasicVariableEntity> QBasicMathFunctions::max_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v1", VariableType::Float, nullptr));
	argNames.push_back(QBasicVariableEntity("v2", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::max_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = fmax(arg[0].floatValue, arg[1].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 最小値
vector<QBasicVariableEntity> QBasicMathFunctions::min_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v1", VariableType::Float, nullptr));
	argNames.push_back(QBasicVariableEntity("v2", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::min_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = fmin(arg[0].floatValue, arg[1].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// サイン
vector<QBasicVariableEntity> QBasicMathFunctions::sin_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::sin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = sin(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// コサイン
vector<QBasicVariableEntity> QBasicMathFunctions::cos_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::cos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = cos(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// タンジェント
vector<QBasicVariableEntity> QBasicMathFunctions::tan_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::tan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = tan(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// アークサイン
vector<QBasicVariableEntity> QBasicMathFunctions::asin_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::asin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = asin(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// アークコサイン
vector<QBasicVariableEntity> QBasicMathFunctions::acos_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::acos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = acos(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// アークタンジェント
vector<QBasicVariableEntity> QBasicMathFunctions::atan_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::atan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = atan(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// アークタンジェント2
vector<QBasicVariableEntity> QBasicMathFunctions::atan2_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("y", VariableType::Float, nullptr));
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::atan2_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = atan2(arg[0].floatValue, arg[1].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// ハイパボリックサイン
vector<QBasicVariableEntity> QBasicMathFunctions::sinh_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::sinh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = sinh(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// ハイパボリックコサイン
vector<QBasicVariableEntity> QBasicMathFunctions::cosh_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::cosh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = cosh(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// ハイパボリックタンジェント
vector<QBasicVariableEntity> QBasicMathFunctions::tanh_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::tanh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = tanh(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 平方根
vector<QBasicVariableEntity> QBasicMathFunctions::cbrt_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::cbrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = cbrt(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// へき乗
vector<QBasicVariableEntity> QBasicMathFunctions::pow_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	argNames.push_back(QBasicVariableEntity("y", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::pow_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = pow(arg[0].floatValue, arg[1].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// ルート
vector<QBasicVariableEntity> QBasicMathFunctions::sqrt_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::sqrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = sqrt(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 乗を求める
vector<QBasicVariableEntity> QBasicMathFunctions::exp_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::exp_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = exp(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 自然対数
vector<QBasicVariableEntity> QBasicMathFunctions::log_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::log_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = log(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 常用対数
vector<QBasicVariableEntity> QBasicMathFunctions::log10_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::log10_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = log10(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// デグリーからラジアン
vector<QBasicVariableEntity> QBasicMathFunctions::deg2rad_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("deg", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::deg2rad_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].floatValue * 3.14159265 / 180.0;
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// ラジアンからデグリー
vector<QBasicVariableEntity> QBasicMathFunctions::rad2deg_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("rad", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::rad2deg_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = arg[0].floatValue * 180.0 / 3.14159265;
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 乱数
vector<QBasicVariableEntity> QBasicMathFunctions::rand_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Int, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::rand_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = rand() % arg[0].intValue;
	return QBasicVariableEntity("", VariableType::Int, &answer);
}
/// 四捨五入
vector<QBasicVariableEntity> QBasicMathFunctions::round_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::round_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = round(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 四捨五入
vector<QBasicVariableEntity> QBasicMathFunctions::floor_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::floor_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = floor(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// 切り捨て
vector<QBasicVariableEntity> QBasicMathFunctions::ceil_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("x", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicMathFunctions::ceil_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = ceil(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
