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
class QBasicVariableEntity;

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
	 * 名前で存在判定
	 * @param name ステートメント名
	 * @return 存在可否
	 */
	bool hasName(const string &name);

	/**
	 * 名前と引数で取得
	 * @param name          ステートメント名
	 * @param variableTypes 引数タイプ
	 * @return ステートメント情報
	 */
	QBasicStatementEntity *getStatement(const string &name, const vector<QBasicVariableEntity> &variableTypes);

	/**
	 * 省略引数をマージする
	 * @param name      関数名
	 * @param arguments 引数
	 * @return 引数群
	 */
	vector<QBasicVariableEntity> mergeArguments(const string &name, const vector<QBasicVariableEntity> &arguments);

	/**
	 * デストラクタ
	 */
	~QBasicStatements();
	
private:
	
	/// ステートメント一覧 ステートメント名,引数,戻り値
	unordered_map<string, QBasicStatementEntity> statements;
	/// ステートメントを名前でさまった一覧
	vector<string> summaryNames;
	
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
	void inline buildStatements();

	/**
	 * 名前でさまった一覧作成
	 */
	void inline buildSummaryNames();
};

#endif /* defined(__ToolQTheWorld__QBasicStatements__) */
