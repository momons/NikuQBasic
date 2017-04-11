//
//  QBasicTextFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#include "QBasicTextFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"
#include "QBasicSubFunction.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicTextFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("font", 2, false, font_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("text", 4, false, text_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

string QBasicTextFunctions::font_qb(QBasic *interpreter, const vector<string> arg) {
	interpreter->subFunc->setFont(arg[0], stod(arg[1]));
	return "";
}
string QBasicTextFunctions::text_qb(QBasic *interpreter, const vector<string> arg) {
	interpreter->subFunc->drawText(
								   stoi(arg[0]),
								   arg[1],
								   stod(arg[2]),
								   stod(arg[3])
								   );
	return "";
}

