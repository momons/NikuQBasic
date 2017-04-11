//
//  QBasicImageFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#include "QBasicImageFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicImageFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("loadimg", 2, false, loadimg_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("drawimg", 3, false, drawimg_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("imgscale", 2, false, imgscale_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("imgalpha", 2, false, imgalpha_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

string QBasicImageFunctions::loadimg_qb(QBasic *interpreter, const vector<string> arg) {
	return "";
}
string QBasicImageFunctions::drawimg_qb(QBasic *interpreter, const vector<string> arg) {
	return "";
}
string QBasicImageFunctions::imgscale_qb(QBasic *interpreter, const vector<string> arg) {
	return "";
}
string QBasicImageFunctions::imgalpha_qb(QBasic *interpreter, const vector<string> arg) {
	return "";
}

