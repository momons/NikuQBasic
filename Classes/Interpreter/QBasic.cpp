//
//  QBasic.cpp
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/13.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#include "QBasic.h"

#include "QBasicExec.h"
#include "QBasicCompile.h"
#include "QBasicStatements.h"
#include "QBasicStatementEntity.h"
#include "QBasicFunctions.h"
#include "QBasicFunctionEntity.h"
#include "QBasicFors.h"
#include "QBasicForEntity.h"
#include "QBasicIfs.h"
#include "QBasicIfEntity.h"
#include "QBasicSymbols.h"
#include "QBasicSymbolEntity.h"
#include "QBasicErrors.h"
#include "QBasicErrorEntity.h"
#include "QBasicScene.h"
#include "QBasicVariableEntity.h"
#include "QBasicPushBackEntity.h"
#include "QBasicSetupNodeEntity.h"
#include "QBasicSubFunction.h"
#include "QBasicStringFunctions.h"
#include "QBasicNetFunctions.h"
#include "QBasicValidation.h"
#include "StringUtil.h"

/** 関数返却変数名 */
#define FUNCTION_RETURN_VARIABLE_NAME  "__return_variable__"

/**
 *  コンストラクタ
 *  @param scene     シーン
 *  @param source    ソース
 *  @param projectId プロジェクトId
 */
QBasic::QBasic(QBasicScene *scene, const string &source, const string &projectId) {

    // 必要なサブクラスを取得
	statements = QBasicStatements::sharedInstance();
	
    // 退避
    this->source = source;
	
	// サブファンクション作成
	netFunc = new QBasicNetFunctions();
	subFunc = new QBasicSubFunction(scene, projectId);
}

/**
 *  デストラクタ
 */
QBasic::~QBasic() {
	// 解放
	if (basiCompile != nullptr) {
		delete basiCompile;
	}
	if (basicExec != nullptr) {
		delete basicExec;
	}
	if (functions != nullptr) {
		delete functions;
	}
	delete netFunc;
	delete subFunc;
	if (fors != nullptr) {
		delete fors;
	}
	if (ifs != nullptr) {
		delete ifs;
	}
	if (errors != nullptr) {
		delete errors;
	}
	if (symbols != nullptr) {
		delete symbols;
	}
}

/**
 *  通常実行
 *  @exception コンパイルエラー
 */
void QBasic::run() {
	// コンパイル
	compile();
	// コンパイルエラーがあればここで終了
	if (errors->hasError()) {
		throw "Compile error!";
	}
	// 実行
	basicExec = new QBasicExec(this);
	initAndRun(true, basicExec);
}

/**
 *  バックグランド実行
 *  @return スレッド
 *  @exception コンパイルエラー
 */
thread QBasic::backgroundRun() {
	thread t1(&QBasic::run, this);
	return t1;
}

/**
 *  コンパイル
 *  @exception コンパイルエラー
 */
void QBasic::compile() {
	// 初期化
	functions = new QBasicFunctions();
	fors = new QBasicFors();
	ifs = new QBasicIfs();
	// シンボル解析
	symbols = new QBasicSymbols(source);
	// エラー確保
	errors = new QBasicErrors(symbols);
	// コンパイル
	basiCompile = new QBasicCompile(this);
	initAndRun(false, basiCompile);
}

/**
 *  実行 or コンパイル
 *  @param run   true:実行 false:コンパイル
 *  @param basic コンパイル/実行
 *  @exception コンパイルエラー
 */
void QBasic::initAndRun(const bool run, QBasicBase *basic) {
	
	// 初期化
	variables.clear();
	localVariables.clear();
	if (!run) {
		functions->clear();
		fors->clear();
		ifs->clear();
	}
	symbols->jumpOffset(0);
	errors->clear();
	
	// 実行
	while(true) {
		bool isExecute = basic->statement(run);
		if (!isExecute) {
			break;
		}
	}
}
