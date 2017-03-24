//
//  QBInterpreterImageFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#include "QBInterpreterImageFunctions.h"

#include "QBInterpreter.h"
#include "QBInterpreterStatementEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterImageFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("loadimg", 2, false, loadimg_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("drawimg", 3, false, drawimg_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("imgscale", 2, false, imgscale_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("imgalpha", 2, false, imgalpha_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

string QBInterpreterImageFunctions::loadimg_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return "";
}
string QBInterpreterImageFunctions::drawimg_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return "";
}
string QBInterpreterImageFunctions::imgscale_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return "";
}
string QBInterpreterImageFunctions::imgalpha_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return "";
}

