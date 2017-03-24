//
//  QBInterpreterTextFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#include "QBInterpreterTextFunctions.h"

#include "QBInterpreter.h"
#include "QBInterpreterStatementEntity.h"
#include "QBInterpreterSubFunction.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterTextFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("font", 2, false, font_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("text", 4, false, text_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

string QBInterpreterTextFunctions::font_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->setFont(arg[0], stod(arg[1]));
	return "";
}
string QBInterpreterTextFunctions::text_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->drawText(
								   stoi(arg[0]),
								   arg[1],
								   stod(arg[2]),
								   stod(arg[3])
								   );
	return "";
}

