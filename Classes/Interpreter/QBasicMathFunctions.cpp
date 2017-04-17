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
	entity = QBasicStatementEntity("rand", {VariableType::Float}, VariableType::Float, rand_qb);
	statementList[entity.name] = entity;

	return statementList;
}

/// 絶対値
QBasicVariableEntity *QBasicMathFunctions::abs_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(fabs(stod(arg[0])));
	return nullptr;
}
/// 最大値
QBasicVariableEntity *QBasicMathFunctions::max_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(fmax(stod(arg[0]),stod(arg[1])));
	return nullptr;
}
/// 最小値
QBasicVariableEntity *QBasicMathFunctions::min_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(fmin(stod(arg[0]),stod(arg[1])));
	return nullptr;
}
/// サイン
QBasicVariableEntity *QBasicMathFunctions::sin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(sin(stod(arg[0])));
	return nullptr;
}
/// コサイン
QBasicVariableEntity *QBasicMathFunctions::cos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(cos(stod(arg[0])));
	return nullptr;
}
/// タンジェント
QBasicVariableEntity *QBasicMathFunctions::tan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(tan(stod(arg[0])));
	return nullptr;
}
/// アークサイン
QBasicVariableEntity *QBasicMathFunctions::asin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(asin(stod(arg[0])));
	return nullptr;
}
/// アークコサイン
QBasicVariableEntity *QBasicMathFunctions::acos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(acos(stod(arg[0])));
	return nullptr;
}
/// アークタンジェント
QBasicVariableEntity *QBasicMathFunctions::atan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(atan(stod(arg[0])));
	return nullptr;
}
/// アークタンジェント2
QBasicVariableEntity *QBasicMathFunctions::atan2_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(atan2(stod(arg[0]), stod(arg[1])));
	return nullptr;
}
/// 平方根
QBasicVariableEntity *QBasicMathFunctions::cbrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(cbrt(stod(arg[0])));
	return nullptr;
}
/// へき乗
QBasicVariableEntity *QBasicMathFunctions::pow_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(pow(stod(arg[0]), stod(arg[1])));
	return nullptr;
}
/// ルート
QBasicVariableEntity *QBasicMathFunctions::sqrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(sqrt(stod(arg[0])));
	return nullptr;
}
/// デグリーからラジアン
QBasicVariableEntity *QBasicMathFunctions::deg2red_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(stod(arg[0]) * 3.14159265 / 180.0);
	return nullptr;
}
/// 乱数
QBasicVariableEntity *QBasicMathFunctions::rand_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	int random = rand() % stoi(arg[0]);
//	return StringUtil::toString(random);
	return nullptr;
}
