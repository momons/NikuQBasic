//
//  QBInterpreterMathFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/20.
//
//

#include "QBInterpreterMathFunctions.h"

#include "QBInterpreter.h"
#include "StringUtil.h"
#include "QBInterpreterStatementEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterMathFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("abs", 1, true, abs_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("max", 2, true, max_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("min", 2, true, min_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("sin", 1, true, sin_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("cos", 1, true, cos_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("tan", 1, true, tan_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("asin", 1, true, asin_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("acos", 1, true, acos_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("atan", 1, true, atan_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("atan2", 2, true, atan2_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("cbrt", 1, true, cbrt_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("pow", 2, true, pow_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("sqrt", 1, true, sqrt_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("deg2red", 1, true, deg2red_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("rand", 1, true, rand_qb);
	statementList[entity.name] = entity;

	return statementList;
}

/// 絶対値
string QBInterpreterMathFunctions::abs_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(fabs(stod(arg[0])));
}
/// 最大値
string QBInterpreterMathFunctions::max_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(fmax(stod(arg[0]),stod(arg[1])));
}
/// 最小値
string QBInterpreterMathFunctions::min_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(fmin(stod(arg[0]),stod(arg[1])));
}
/// サイン
string QBInterpreterMathFunctions::sin_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(sin(stod(arg[0])));
}
/// コサイン
string QBInterpreterMathFunctions::cos_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(cos(stod(arg[0])));
}
/// タンジェント
string QBInterpreterMathFunctions::tan_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(tan(stod(arg[0])));
}
/// アークサイン
string QBInterpreterMathFunctions::asin_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(asin(stod(arg[0])));
}
/// アークコサイン
string QBInterpreterMathFunctions::acos_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(acos(stod(arg[0])));
}
/// アークタンジェント
string QBInterpreterMathFunctions::atan_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(atan(stod(arg[0])));
}
/// アークタンジェント2
string QBInterpreterMathFunctions::atan2_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(atan2(stod(arg[0]), stod(arg[1])));
}
/// 平方根
string QBInterpreterMathFunctions::cbrt_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(cbrt(stod(arg[0])));
}
/// へき乗
string QBInterpreterMathFunctions::pow_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(pow(stod(arg[0]), stod(arg[1])));
}
/// ルート
string QBInterpreterMathFunctions::sqrt_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(sqrt(stod(arg[0])));
}
/// デグリーからラジアン
string QBInterpreterMathFunctions::deg2red_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(stod(arg[0]) * 3.14159265 / 180.0);
}
/// 乱数
string QBInterpreterMathFunctions::rand_qb(QBInterpreter *interpreter, const vector<string> arg) {
	int random = rand() % stoi(arg[0]);
	return StringUtil::toString(random);
}
