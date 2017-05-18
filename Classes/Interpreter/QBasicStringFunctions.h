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
	static inline vector<QBasicVariableEntity> len_params();
	static inline QBasicVariableEntity len_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 真ん中切り取り
	static inline vector<QBasicVariableEntity> mid_params();
	static inline QBasicVariableEntity mid_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 左切り取り
	static inline vector<QBasicVariableEntity> left_params();
	static inline QBasicVariableEntity left_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 右切り取り
	static inline vector<QBasicVariableEntity> right_params();
	static inline QBasicVariableEntity right_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 分割
	static inline vector<QBasicVariableEntity> split_params();
	static inline QBasicVariableEntity split_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// Empty
	static inline vector<QBasicVariableEntity> empty_params();
	static inline QBasicVariableEntity empty_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// Not Empty
	static inline vector<QBasicVariableEntity> notEmpty_params();
	static inline QBasicVariableEntity notEmpty_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 置換
	static inline vector<QBasicVariableEntity> replase_params();
	static inline QBasicVariableEntity replase_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 前方一致
	static inline vector<QBasicVariableEntity> prefix_params();
	static inline QBasicVariableEntity prefix_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 後方一致
	static inline vector<QBasicVariableEntity> suffix_params();
	static inline QBasicVariableEntity suffix_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);

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
