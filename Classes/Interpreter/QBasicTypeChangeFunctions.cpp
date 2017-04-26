//
//  QBasicTypeChangeFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/27.
//
//

#include "QBasicTypeChangeFunctions.h"

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
unordered_map<string, QBasicStatementEntity> QBasicTypeChangeFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("abs", {VariableType::Float}, VariableType::Float, abs_qb);
	statementList[entity.alias] = entity;

	return statementList;
}

/// 絶対値
QBasicVariableEntity QBasicTypeChangeFunctions::abs_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto answer = fabs(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
