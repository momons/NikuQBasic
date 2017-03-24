//
//  QBInterpreterMathFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/20.
//
//

#ifndef QBInterpreterMathFunctions_h
#define QBInterpreterMathFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト Mathサブ関数群
class QBInterpreterMathFunctions final {
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
	/// 絶対値
	static string abs_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 最大値
	static string max_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 最小値
	static string min_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// サイン
	static string sin_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// コサイン
	static string cos_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// タンジェント
	static string tan_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// アークサイン
	static string asin_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// アークコサイン
	static string acos_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// アークタンジェント
	static string atan_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// アークタンジェント2
	static string atan2_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 平方根
	static string cbrt_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// へき乗
	static string pow_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// ルート
	static string sqrt_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// デグリーからラジアン
	static string deg2red_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 乱数
	static string rand_qb(QBInterpreter *interpreter, const vector<string> arg);

};

#endif /* QBInterpreterMathFunctions_h */
