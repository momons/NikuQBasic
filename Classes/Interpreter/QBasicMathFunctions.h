//
//  QBasicMathFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/20.
//
//

#ifndef QBasicMathFunctions_h
#define QBasicMathFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;

/// スクリプト Mathサブ関数群
class QBasicMathFunctions final {
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
	/// 絶対値
	static string abs_qb(QBasic *interpreter, const vector<string> arg);
	/// 最大値
	static string max_qb(QBasic *interpreter, const vector<string> arg);
	/// 最小値
	static string min_qb(QBasic *interpreter, const vector<string> arg);
	/// サイン
	static string sin_qb(QBasic *interpreter, const vector<string> arg);
	/// コサイン
	static string cos_qb(QBasic *interpreter, const vector<string> arg);
	/// タンジェント
	static string tan_qb(QBasic *interpreter, const vector<string> arg);
	/// アークサイン
	static string asin_qb(QBasic *interpreter, const vector<string> arg);
	/// アークコサイン
	static string acos_qb(QBasic *interpreter, const vector<string> arg);
	/// アークタンジェント
	static string atan_qb(QBasic *interpreter, const vector<string> arg);
	/// アークタンジェント2
	static string atan2_qb(QBasic *interpreter, const vector<string> arg);
	/// 平方根
	static string cbrt_qb(QBasic *interpreter, const vector<string> arg);
	/// へき乗
	static string pow_qb(QBasic *interpreter, const vector<string> arg);
	/// ルート
	static string sqrt_qb(QBasic *interpreter, const vector<string> arg);
	/// デグリーからラジアン
	static string deg2red_qb(QBasic *interpreter, const vector<string> arg);
	/// 乱数
	static string rand_qb(QBasic *interpreter, const vector<string> arg);

};

#endif /* QBasicMathFunctions_h */
