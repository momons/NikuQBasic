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
#include "QBasicVariableEntity.h"
#include "QBasicSubFunction.h"
#include "QBasicStorages.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicStorageFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
//	entity = QBasicStatementEntity("load", { VariableType::Str }, VariableType::Str, load_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("save", { VariableType::Str, VariableType::Str }, VariableType::Void, save_qb);
//	statementList[entity.name] = entity;
	
	return statementList;
}

/// 読み込み
QBasicVariableEntity *QBasicStorageFunctions::load_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return interpreter->subFunc->userDefaultsManager->read(arg[0]);
	return nullptr;
}
/// セーブ
QBasicVariableEntity *QBasicStorageFunctions::save_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	interpreter->subFunc->userDefaultsManager->write(arg[0], arg[1]);
	return nullptr;
}

#pragma mark - サブルーチン

