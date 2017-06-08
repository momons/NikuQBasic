//
//  QBasic.h
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/13.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#ifndef __ToolQTheWorld__QBasic__
#define __ToolQTheWorld__QBasic__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class QBasicStatements;
class QBasicFunctions;
class QBasicFors;
class QBasicIfs;
class QBasicSymbols;
class QBasicErrors;
class QBasicSubFunction;
class QBasicNetFunctions;
class QBasicScene;
class QBasicVariableEntity;
class QBasicBase;
class QBasicCompile;
class QBasicExec;

/**
 * イベントスクリプトインタプリタクラス
 */
class QBasic final {
public:
	
	/// 通信用サブファンクション
	QBasicNetFunctions *netFunc;
	/// サブファンクション
	QBasicSubFunction *subFunc;
	
	/// グローバル変数
	unordered_map<string, QBasicVariableEntity> variables;
	/// ローカル変数
	unordered_map<string, QBasicVariableEntity> localVariables;

	/// シンボル制御
	QBasicSymbols *symbols = nullptr;
	/// エラー群
	QBasicErrors *errors = nullptr;

	/// ステートメント群
	QBasicStatements *statements;
	/// ファンクション群
	QBasicFunctions *functions = nullptr;

	/// コンパイル
	QBasicCompile *basiCompile = nullptr;
	/// 実行
	QBasicExec *basicExec = nullptr;

	/// for群
	QBasicFors *fors = nullptr;
	/// if群
	QBasicIfs *ifs = nullptr;

	/**
	 *  コンストラクタ
	 *  @param scene     シーン
	 *  @param source    ソース
	 *  @param projectId プロジェクトId
	 */
	QBasic(QBasicScene *scene, const string &source, const string &projectId);
		
    /**
     *  デストラクタ
     */
    ~QBasic();
	
	/**
	 *  実行
	 *  @exception コンパイルエラー
	 */
	void run();
	
	/**
	 *  バックグランド実行
	 *  @return スレッド
	 *  @exception コンパイルエラー
	 */
	thread backgroundRun();

	/**
	 *  コンパイル
	 *  @exception コンパイルエラー
	 */
	void compile();

private:
    
    /// 実行プログラムソース
    string source;

	/**
	 *  実行 or コンパイル
	 *  @param run   true:実行 false:コンパイル
	 *  @param basic コンパイル/実行
	 *  @exception コンパイルエラー
	 */
	void initAndRun(const bool run, QBasicBase *basic);
};

#endif /* defined(__ToolQTheWorld__QBasic__) */
