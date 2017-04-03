//
//  QBInterpreterStatements.h
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/04/20.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#ifndef __ToolQTheWorld__QBInterpreterStatements__
#define __ToolQTheWorld__QBInterpreterStatements__

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/**
 * イベントスクリプトインタプリタクラス定数
 */
class QBInterpreterStatements final {
	
public:
	
	/**
	 * インスタンスシェア
	 * @return インスタンス
	 */
	static QBInterpreterStatements *sharedInstance();
	
	/**
	 * ステートメント一覧作成
	 * @param name ステートメント名
	 * @return ステートメント情報
	 */
	QBInterpreterStatementEntity *getStatement(const string name);
	
	/**
	 * デストラクタ
	 */
	~QBInterpreterStatements();
	
private:
	
	/** ステートメント一覧 ステートメント名,引数,戻り値 */
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	
	/** インスタンス */
	static QBInterpreterStatements *interpreterConstansInstance;
	
	/**
	 * コンストラクタ
	 */
	QBInterpreterStatements();
	
	/**
	 * 初期化
	 */
	static void initialize();
	
	/**
	 * ステートメント一覧作成
	 */
	void buildStatementList();
};

#endif /* defined(__ToolQTheWorld__QBInterpreterStatements__) */
