//
//  QBasicGeometryFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#include "QBasicGeometryFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"
#include "QBasicSubFunction.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicGeometryFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
//	entity = QBasicStatementEntity("line", 5, false, line_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("rect", 6, false, rect_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("circle", 6, false, circle_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("triangle", 8, false, triangle_qb);
//	statementList[entity.name] = entity;
	
	return statementList;
}

/// 線描画
QBasicVariableEntity *QBasicGeometryFunctions::line_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	interpreter->subFunc->drawLine(
//								   stoi(arg[0]),
//								   stod(arg[1]),
//								   stod(arg[2]),
//								   stod(arg[3]),
//								   stod(arg[4])
//								   );
	return nullptr;
}
/// 四角描画
QBasicVariableEntity *QBasicGeometryFunctions::rect_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	interpreter->subFunc->drawRect(
//								   stoi(arg[0]),
//								   stod(arg[1]),
//								   stod(arg[2]),
//								   stod(arg[3]),
//								   stod(arg[4]),
//								   arg[5].compare("1")==0
//								   );
	return nullptr;
}
/// 円描画
QBasicVariableEntity *QBasicGeometryFunctions::circle_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	interpreter->subFunc->drawCircle(
//									 stoi(arg[0]),
//									 stod(arg[1]),
//									 stod(arg[2]),
//									 stod(arg[3]) / 2,
//									 stod(arg[4]) / 2,
//									 arg[5].compare("1")==0
//									 );
	return nullptr;
}
/// 三角描画
QBasicVariableEntity *QBasicGeometryFunctions::triangle_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	interpreter->subFunc->drawTriangle(
//									   stoi(arg[0]),
//									   stod(arg[1]),
//									   stod(arg[2]),
//									   stod(arg[3]),
//									   stod(arg[4]),
//									   stod(arg[5]),
//									   stod(arg[6]),
//									   arg[7].compare("1")==0
//									   );
	return nullptr;
}
