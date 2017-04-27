//
//  QBasicStatements.cpp
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/04/20.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#include "QBasicStatements.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <mutex>
#include <string>
#include "QBasic.h"
#include "QBasicSubFunction.h"
#include "QBasicVariableEntity.h"
#include "QBasicMathFunctions.h"
#include "QBasicStringFunctions.h"
#include "QBasicDrawFunctions.h"
#include "QBasicGeometryFunctions.h"
#include "QBasicTextFunctions.h"
#include "QBasicImageFunctions.h"
#include "QBasicParticleFunctions.h"
#include "QBasicSoundFunctions.h"
#include "QBasicTouchFunctions.h"
#include "QBasicStorageFunctions.h"
#include "QBasicNetFunctions.h"
#include "QBasicAlertFunctions.h"
#include "QBasicDebugFunctions.h"
#include "QBasicScene.h"
#include "QBUserDefaultsManager.h"
#include "QBSoundBGMManager.h"
#include "QBSoundEffectManager.h"
//#include "QBAlertViewLauncher.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"

/** インスタンス */
QBasicStatements *QBasicStatements::interpreterConstansInstance;

/**
 * インスタンスシェア
 * @return インスタンス
 */
QBasicStatements *QBasicStatements::sharedInstance()
{
	static once_flag flag;
	
	// 一度だけコール
	call_once(flag,initialize);
	
	return QBasicStatements::interpreterConstansInstance;
}

/**
 * 初期化
 */
void QBasicStatements::initialize() {
	QBasicStatements::interpreterConstansInstance = new QBasicStatements();
}

/**
 * コンストラクタ
 */
QBasicStatements::QBasicStatements() {
	
	// ステートメント一覧作成
	buildStatements();
	
	// 名前サマリ一覧作成
	buildSummaryNames();
}

/**
 * デストラクタ
 */
QBasicStatements::~QBasicStatements() {
	delete QBasicStatements::interpreterConstansInstance;
}

/**
 * ステートメント一覧作成
 */
void QBasicStatements::buildStatements() {
	
	/** ステートメント一覧 ステートメント名,引数,戻り値 */
	statements = unordered_map<string,QBasicStatementEntity>();
	
	QBasicStatementEntity entity;
	unordered_map<string, QBasicStatementEntity> statements;

	//===== 最大値、最小値、絶対値
	statements.clear();
	statements = QBasicMathFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}
	
	//===== 文字列操作
	statements.clear();
	statements = QBasicStringFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}

	//===== 描画
	statements.clear();
	statements = QBasicDrawFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}
	
	//===== 図形
	statements.clear();
	statements = QBasicGeometryFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}
	
	//===== 文字
	statements.clear();
	statements = QBasicTextFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}

	//===== 画像
	statements.clear();
	statements = QBasicImageFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}

	//===== パーティクル
	statements.clear();
	statements = QBasicParticleFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}
	
	//===== サウンド
	statements.clear();
	auto soundStatements = QBasicSoundFunctions::buildStatements();
	for (auto it = soundStatements.begin();it != soundStatements.end();it++) {
		statements[it->first] = it->second;
	}
	
	//===== タッチイベント
	statements.clear();
	auto touchStatements = QBasicTouchFunctions::buildStatements();
	for (auto it = touchStatements.begin();it != touchStatements.end();it++) {
		statements[it->first] = it->second;
	}
	
	//===== データ操作
	statements.clear();
	statements = QBasicStorageFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}

	//===== ネット通信
	statements.clear();
	statements = QBasicNetFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}

	//===== アラート
	statements.clear();
	statements = QBasicAlertFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}
	
	//===== デバッグ
	statements.clear();
	statements = QBasicDebugFunctions::buildStatements();
	for (auto it = statements.begin();it != statements.end();it++) {
		statements[it->first] = it->second;
	}

	// 乱数初期化
	srand((unsigned)time(NULL));
}

/**
 * 名前で存在判定
 * @param name ステートメント名
 * @return ステートメント情報
 */
bool QBasicStatements::hasName(const string &name) {
	return find(summaryNames.begin(), summaryNames.end(), name) != summaryNames.end();
}

/**
 * ステートメント一覧作成
 * @param name          ステートメント名
 * @param variableTypes 引数タイプ
 * @return ステートメント情報
 */
QBasicStatementEntity *QBasicStatements::getStatement(const string &name, const vector<QBasicVariableEntity> &variableTypes) {
	// ステートメントがあるか？
	auto it = statements.find(name);
	if (it == statements.end()) {
		return nullptr;
	}
	return &statements[name];
}

/**
 * 名前でさまった一覧作成
 */
void QBasicStatements::buildSummaryNames() {
	summaryNames.clear();
	for (auto it = statements.begin();it != statements.end();it++) {
		summaryNames.push_back(it->second.name);
	}
}
