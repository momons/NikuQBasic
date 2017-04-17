//
//  QBasicStringFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#ifndef QBasicStringFunctions_h
#define QBasicStringFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト 文字操作サブ関数群
class QBasicStringFunctions final {
public:
	
	/**
	 *  ステートメントを作成
	 *
	 *  @return 文字操作ステートメント
	 */
	static unordered_map<string, QBasicStatementEntity> buildStatements();
	
	/**
	 *  スクリプト用ステートメント
	 *  @param interpreter 親クラス
	 *  @param arg         引数
	 *  @return 戻り値
	 */
	/// 文字列長取得
	static QBasicVariableEntity *length_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 真ん中切り取り
	static QBasicVariableEntity *mid_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 左切り取り
	static QBasicVariableEntity *left_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 右切り取り
	static QBasicVariableEntity *right_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 分割
	static QBasicVariableEntity *split_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 分割結果取得
	static QBasicVariableEntity *splitget_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 置換
	static QBasicVariableEntity *replase_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	
	/**
	 *  文字列を分割する
	 *  @param inStr 文字列
	 *  @param split 分割文字列
	 *  @return カウント
	 */
	int splitString(const string &str, const string &split);
	
	/**
	 *  分割した文字取得
	 *  @param index インデックス
	 *  @return 文字列
	 */
	string splitStringGet(const int index);

	/**
	 *  コンストラクタ
	 */
	QBasicStringFunctions();
	
	/**
	 * デストラクタ
	 */
	~QBasicStringFunctions() { }
	
private:
	
	/// 分割文字列
	vector<string> splitList;
};

#endif /* QBasicStringFunctions_h */
