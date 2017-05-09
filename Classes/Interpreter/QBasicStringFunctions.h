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
	static vector<QBasicVariableEntity> len_params();
	static QBasicVariableEntity len_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 真ん中切り取り
	static vector<QBasicVariableEntity> mid_params();
	static QBasicVariableEntity mid_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 左切り取り
	static vector<QBasicVariableEntity> left_params();
	static QBasicVariableEntity left_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 右切り取り
	static vector<QBasicVariableEntity> right_params();
	static QBasicVariableEntity right_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 分割
	static vector<QBasicVariableEntity> split_params();
	static QBasicVariableEntity split_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// Empty
	static vector<QBasicVariableEntity> empty_params();
	static QBasicVariableEntity empty_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// Not Empty
	static vector<QBasicVariableEntity> notEmpty_params();
	static QBasicVariableEntity notEmpty_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 置換
	static vector<QBasicVariableEntity> replase_params();
	static QBasicVariableEntity replase_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 前方一致
	static vector<QBasicVariableEntity> prefix_params();
	static QBasicVariableEntity prefix_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 後方一致
	static vector<QBasicVariableEntity> suffix_params();
	static QBasicVariableEntity suffix_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);

	/**
	 * デストラクタ
	 */
	~QBasicStringFunctions() { }
	
private:
	
	/**
	 *  コンストラクタ
	 */
	QBasicStringFunctions();
	
};

#endif /* QBasicStringFunctions_h */
