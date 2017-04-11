//
//  QBasicStorageFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#include "QBasicStorageFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"
#include "QBasicSubFunction.h"
#include "QBUserDefaultsManager.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicStorageFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("load", 1, true, load_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("save", 2, false, save_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// 読み込み
string QBasicStorageFunctions::load_qb(QBasic *interpreter, const vector<string> arg) {
	return interpreter->subFunc->userDefaultsManager->read(arg[0]);
}
/// セーブ
string QBasicStorageFunctions::save_qb(QBasic *interpreter, const vector<string> arg) {
	interpreter->subFunc->userDefaultsManager->write(arg[0], arg[1]);
	return "";
}

#pragma mark - サブルーチン

