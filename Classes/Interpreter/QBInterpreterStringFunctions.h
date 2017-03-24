//
//  QBInterpreterStringFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#ifndef QBInterpreterStringFunctions_h
#define QBInterpreterStringFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト 文字操作サブ関数群
class QBInterpreterStringFunctions final {
public:
	
	/**
	 *  ステートメントを作成
	 *
	 *  @return 文字操作ステートメント
	 */
	static unordered_map<string, QBInterpreterStatementEntity> buildStatements();
	
	/**
	 *  スクリプト用ステートメント
	 *  @param interpreter 親クラス
	 *  @param arg         引数
	 *  @return 戻り値
	 */
	/// 文字列長取得
	static string length_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 真ん中切り取り
	static string mid_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 左切り取り
	static string left_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 右切り取り
	static string right_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 分割
	static string split_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 分割結果取得
	static string splitget_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 置換
	static string replase_qb(QBInterpreter *interpreter, const vector<string> arg);
	
	/**
	 *  文字列を分割する
	 *  @param inStr 文字列
	 *  @param split 分割文字列
	 *  @return カウント
	 */
	int splitString(const string str, const string split);
	
	/**
	 *  分割した文字取得
	 *  @param index インデックス
	 *  @return 文字列
	 */
	string splitStringGet(const int index);

	/**
	 *  コンストラクタ
	 */
	QBInterpreterStringFunctions();
	
	/**
	 * デストラクタ
	 */
	~QBInterpreterStringFunctions() { }
	
private:
	
	/// 分割文字列
	vector<string> splitList;
};

#endif /* QBInterpreterStringFunctions_h */
