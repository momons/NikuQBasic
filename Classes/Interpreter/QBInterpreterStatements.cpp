//
//  QBInterpreterStatements.cpp
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/04/20.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#include "QBInterpreterStatements.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <mutex>
#include <string>
#include "QBInterpreter.h"
#include "QBInterpreterSubFunction.h"
#include "QBInterpreterMathFunctions.h"
#include "QBInterpreterStringFunctions.h"
#include "QBInterpreterDrawFunctions.h"
#include "QBInterpreterGeometryFunctions.h"
#include "QBInterpreterTextFunctions.h"
#include "QBInterpreterImageFunctions.h"
#include "QBInterpreterParticleFunctions.h"
#include "QBInterpreterSoundFunctions.h"
#include "QBInterpreterTouchFunctions.h"
#include "QBInterpreterStorageFunctions.h"
#include "QBInterpreterNetFunctions.h"
#include "QBInterpreterAlertFunctions.h"
#include "QBInterpreterDebugFunctions.h"
#include "QBInterpreterScene.h"
#include "QBUserDefaultsManager.h"
#include "QBSoundBGMManager.h"
#include "QBSoundEffectManager.h"
//#include "QBAlertViewLauncher.h"
#include "QBInterpreterStatementEntity.h"

/** インスタンス */
QBInterpreterStatements *QBInterpreterStatements::interpreterConstansInstance;

/**
 * インスタンスシェア
 * @return インスタンス
 */
QBInterpreterStatements *QBInterpreterStatements::sharedInstance()
{
	static once_flag flag;
	
	// 一度だけコール
	call_once(flag,initialize);
	
	return QBInterpreterStatements::interpreterConstansInstance;
}

/**
 * 初期化
 */
void QBInterpreterStatements::initialize() {
	QBInterpreterStatements::interpreterConstansInstance = new QBInterpreterStatements();
}

/**
 * コンストラクタ
 */
QBInterpreterStatements::QBInterpreterStatements() {
	
	// ステートメント一覧作成
	buildStatementList();
	
}

/**
 * デストラクタ
 */
QBInterpreterStatements::~QBInterpreterStatements() {
	delete QBInterpreterStatements::interpreterConstansInstance;
}

/**
 * ステートメント一覧作成
 */
void QBInterpreterStatements::buildStatementList() {
	
	/** ステートメント一覧 ステートメント名,引数,戻り値 */
	statementList = unordered_map<string,QBInterpreterStatementEntity>();
	
	QBInterpreterStatementEntity entity;
	unordered_map<string, QBInterpreterStatementEntity> statements;

	//===== 最大値、最小値、絶対値
	statements.clear();
	statements = QBInterpreterMathFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}
	
	//===== 文字列操作
	statements.clear();
	statements = QBInterpreterStringFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}

	//===== 描画
	statements.clear();
	statements = QBInterpreterDrawFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}
	
	//===== 図形
	statements.clear();
	statements = QBInterpreterGeometryFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}
	
	//===== 文字
	statements.clear();
	statements = QBInterpreterTextFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}

	//===== 画像
	statements.clear();
	statements = QBInterpreterImageFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}

	//===== パーティクル
	statements.clear();
	statements = QBInterpreterParticleFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}
	
	//===== サウンド
	statements.clear();
	auto soundStatements = QBInterpreterSoundFunctions::buildStatements();
	for (auto it = soundStatements.begin();it != soundStatements.end();it++) {
		statementList[it->first] = it->second;
	}
	
	//===== タッチイベント
	statements.clear();
	auto touchStatements = QBInterpreterTouchFunctions::buildStatements();
	for (auto it = touchStatements.begin();it != touchStatements.end();it++) {
		statementList[it->first] = it->second;
	}
	
	//===== データ操作
	statements.clear();
	statements = QBInterpreterStorageFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}

	//===== ネット通信
	statements.clear();
	statements = QBInterpreterNetFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}

	//===== アラート
	statements.clear();
	statements = QBInterpreterAlertFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}
	
	//===== デバッグ
	statements.clear();
	statements = QBInterpreterDebugFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statementList[it->first] = it->second;
	}

	// 乱数初期化
	srand((unsigned)time(NULL));
}

/**
 * ステートメント一覧作成
 * @param name ステートメント名
 * @return ステートメント情報
 */
QBInterpreterStatementEntity *QBInterpreterStatements::getStatement(const string name) {
	// ステートメントがあるか？
	unordered_map<string,QBInterpreterStatementEntity>::iterator it = statementList.find(name);
	if (it == statementList.end()) {
		return nullptr;
	}
	return &statementList[name];
}

