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
string QBasicMathFunctions::abs_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(fabs(stod(arg[0])));
}
/// 最大値
string QBasicMathFunctions::max_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(fmax(stod(arg[0]),stod(arg[1])));
}
/// 最小値
string QBasicMathFunctions::min_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(fmin(stod(arg[0]),stod(arg[1])));
}
/// サイン
string QBasicMathFunctions::sin_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(sin(stod(arg[0])));
}
/// コサイン
string QBasicMathFunctions::cos_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(cos(stod(arg[0])));
}
/// タンジェント
string QBasicMathFunctions::tan_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(tan(stod(arg[0])));
}
/// アークサイン
string QBasicMathFunctions::asin_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(asin(stod(arg[0])));
}
/// アークコサイン
string QBasicMathFunctions::acos_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(acos(stod(arg[0])));
}
/// アークタンジェント
string QBasicMathFunctions::atan_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(atan(stod(arg[0])));
}
/// アークタンジェント2
string QBasicMathFunctions::atan2_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(atan2(stod(arg[0]), stod(arg[1])));
}
/// 平方根
string QBasicMathFunctions::cbrt_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(cbrt(stod(arg[0])));
}
/// へき乗
string QBasicMathFunctions::pow_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(pow(stod(arg[0]), stod(arg[1])));
}
/// ルート
string QBasicMathFunctions::sqrt_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(sqrt(stod(arg[0])));
}
/// デグリーからラジアン
string QBasicMathFunctions::deg2red_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(stod(arg[0]) * 3.14159265 / 180.0);
}
/// 乱数
string QBasicMathFunctions::rand_qb(QBasic *interpreter, const vector<string> arg) {
	int random = rand() % stoi(arg[0]);
	return StringUtil::toString(random);
}
