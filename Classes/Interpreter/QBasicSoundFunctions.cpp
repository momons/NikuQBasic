//
//  QBasicSoundFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#include "QBasicSoundFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"
#include "QBSoundBGMManager.h"
#include "QBSoundEffectManager.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicSoundFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
//	entity = QBasicStatementEntity("loadbgm", 1, false, loadbgm_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("playbgm", 1, true, playbgm_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("stopbgm", 0, false, stopbgm_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("loadse", 2, false, loadse_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("playse", 2, true, playse_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("stopse", 1, false, stopse_qb);
//	statementList[entity.name] = entity;
	
	return statementList;
}

/// BGM読み込み
QBasicVariableEntity *QBasicSoundFunctions::loadbgm_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	auto manager = QBSoundBGMManager::sharedInstance();
//	manager->preload(arg[0].c_str());
	return nullptr;
}
/// BGM再生
QBasicVariableEntity *QBasicSoundFunctions::playbgm_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	auto manager = QBSoundBGMManager::sharedInstance();
//	auto ret = manager->play(arg[0].compare("1")==0);
//	return ret?"1":"0";
	return nullptr;
}
/// BGM停止
QBasicVariableEntity *QBasicSoundFunctions::stopbgm_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	auto manager = QBSoundBGMManager::sharedInstance();
//	manager->stop();
	return nullptr;
}
/// 効果音読み込み
QBasicVariableEntity *QBasicSoundFunctions::loadse_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	auto manager = QBSoundEffectManager::sharedInstance();
//	manager->preload(stoi(arg[0]), arg[1].c_str());
	return nullptr;
}
/// 効果音再生
QBasicVariableEntity *QBasicSoundFunctions::playse_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	auto manager = QBSoundEffectManager::sharedInstance();
//	auto ret = manager->play(stoi(arg[0]), arg[1].compare("1")==0);
//	return ret?"1":"0";
	return nullptr;
}
/// 効果音停止
QBasicVariableEntity *QBasicSoundFunctions::stopse_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	auto manager = QBSoundEffectManager::sharedInstance();
//	manager->stop(stoi(arg[0]));
	return nullptr;
}
