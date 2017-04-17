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
	
	entity = QBasicStatementEntity("abs", 1, true, abs_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("max", 2, true, max_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("min", 2, true, min_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("sin", 1, true, sin_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("cos", 1, true, cos_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("tan", 1, true, tan_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("asin", 1, true, asin_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("acos", 1, true, acos_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("atan", 1, true, atan_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("atan2", 2, true, atan2_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("cbrt", 1, true, cbrt_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("pow", 2, true, pow_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("sqrt", 1, true, sqrt_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("deg2red", 1, true, deg2red_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("rand", 1, true, rand_qb);
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
