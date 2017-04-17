//
//  QBasicStatements.h
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/04/20.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#ifndef __ToolQTheWorld__QBasicStatements__
#define __ToolQTheWorld__QBasicStatements__

using namespace std;

class QBasic;
class QBasicStatementEntity;

/**
 * イベントスクリプトインタプリタクラス定数
 */
class QBasicStatements final {
	
public:
	
	/**
	 * インスタンスシェア
	 * @return インスタンス
	 */
	static QBasicStatements *sharedInstance();
	
	/**
	 * ステートメント一覧作成
	 * @param name ステートメント名
	 * @return ステートメント情報
	 */
	QBasicStatementEntity *getStatement(const string &name);
	
	/**
	 * デストラクタ
	 */
	~QBasicStatements();
	
private:
	
	/** ステートメント一覧 ステートメント名,引数,戻り値 */
	unordered_map<string, QBasicStatementEntity> statementList;
	
	/** インスタンス */
	static QBasicStatements *interpreterConstansInstance;
	
	/**
	 * コンストラクタ
	 */
	QBasicStatements();
	
	/**
	 * 初期化
	 */
	static void initialize();
	
	/**
	 * ステートメント一覧作成
	 */
	void buildStatementList();
};

#endif /* defined(__ToolQTheWorld__QBasicStatements__) */
