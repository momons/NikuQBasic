//
//  QBInterpreterStorageFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#include "QBInterpreterStorageFunctions.h"

#include "QBInterpreter.h"
#include "QBInterpreterStatementEntity.h"
#include "QBInterpreterSubFunction.h"
#include "QBUserDefaultsManager.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterStorageFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("load", 1, true, load_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("save", 2, false, save_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// 読み込み
string QBInterpreterStorageFunctions::load_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return interpreter->subFunc->userDefaultsManager->read(arg[0]);
}
/// セーブ
string QBInterpreterStorageFunctions::save_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->userDefaultsManager->write(arg[0], arg[1]);
	return "";
}

#pragma mark - サブルーチン

