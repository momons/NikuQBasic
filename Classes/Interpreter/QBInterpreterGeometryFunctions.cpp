//
//  QBInterpreterGeometryFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#include "QBInterpreterGeometryFunctions.h"

#include "QBInterpreter.h"
#include "QBInterpreterStatementEntity.h"
#include "QBInterpreterSubFunction.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterGeometryFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("line", 5, false, line_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("rect", 6, false, rect_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("circle", 6, false, circle_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("triangle", 8, false, triangle_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// 線描画
string QBInterpreterGeometryFunctions::line_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->drawLine(
								   stoi(arg[0]),
								   stod(arg[1]),
								   stod(arg[2]),
								   stod(arg[3]),
								   stod(arg[4])
								   );
	return "";
}
/// 四角描画
string QBInterpreterGeometryFunctions::rect_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->drawRect(
								   stoi(arg[0]),
								   stod(arg[1]),
								   stod(arg[2]),
								   stod(arg[3]),
								   stod(arg[4]),
								   arg[5].compare("1")==0
								   );
	return "";
}
/// 円描画
string QBInterpreterGeometryFunctions::circle_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->drawCircle(
									 stoi(arg[0]),
									 stod(arg[1]),
									 stod(arg[2]),
									 stod(arg[3]) / 2,
									 stod(arg[4]) / 2,
									 arg[5].compare("1")==0
									 );
	return "";
}
/// 三角描画
string QBInterpreterGeometryFunctions::triangle_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->drawTriangle(
									   stoi(arg[0]),
									   stod(arg[1]),
									   stod(arg[2]),
									   stod(arg[3]),
									   stod(arg[4]),
									   stod(arg[5]),
									   stod(arg[6]),
									   arg[7].compare("1")==0
									   );
	return "";
}
