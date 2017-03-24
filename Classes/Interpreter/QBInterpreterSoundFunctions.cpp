//
//  QBInterpreterSoundFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#include "QBInterpreterSoundFunctions.h"

#include "QBInterpreter.h"
#include "QBInterpreterStatementEntity.h"
#include "QBSoundBGMManager.h"
#include "QBSoundEffectManager.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterSoundFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("loadbgm", 1, false, loadbgm_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("playbgm", 1, true, playbgm_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("stopbgm", 0, false, stopbgm_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("loadse", 2, false, loadse_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("playse", 2, true, playse_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("stopse", 1, false, stopse_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// BGM読み込み
string QBInterpreterSoundFunctions::loadbgm_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto manager = QBSoundBGMManager::sharedInstance();
	manager->preload(arg[0].c_str());
	return "";
}
/// BGM再生
string QBInterpreterSoundFunctions::playbgm_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto manager = QBSoundBGMManager::sharedInstance();
	auto ret = manager->play(arg[0].compare("1")==0);
	return ret?"1":"0";
}
/// BGM停止
string QBInterpreterSoundFunctions::stopbgm_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto manager = QBSoundBGMManager::sharedInstance();
	manager->stop();
	return "";
}
/// 効果音読み込み
string QBInterpreterSoundFunctions::loadse_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto manager = QBSoundEffectManager::sharedInstance();
	manager->preload(stoi(arg[0]), arg[1].c_str());
	return "";
}
/// 効果音再生
string QBInterpreterSoundFunctions::playse_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto manager = QBSoundEffectManager::sharedInstance();
	auto ret = manager->play(stoi(arg[0]), arg[1].compare("1")==0);
	return ret?"1":"0";
}
/// 効果音停止
string QBInterpreterSoundFunctions::stopse_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto manager = QBSoundEffectManager::sharedInstance();
	manager->stop(stoi(arg[0]));
	return "";
}
