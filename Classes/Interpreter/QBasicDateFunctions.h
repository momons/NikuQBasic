//
//  QBasicDateFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/20.
//
//

#ifndef QBasicDateFunctions_h
#define QBasicDateFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;

/// スクリプト 日付操作サブ関数群
class QBasicDateFunctions final {
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
	/// 年取得
	static string year_qb(QBasic *interpreter, const vector<string> arg);
	/// 月取得
	static string month_qb(QBasic *interpreter, const vector<string> arg);
	/// 日付取得
	static string day_qb(QBasic *interpreter, const vector<string> arg);
	/// 時間取得
	static string hour_qb(QBasic *interpreter, const vector<string> arg);
	/// 分取得
	static string minute_qb(QBasic *interpreter, const vector<string> arg);
	/// 秒取得
	static string second_qb(QBasic *interpreter, const vector<string> arg);
	/// 曜日取得
	static string week_qb(QBasic *interpreter, const vector<string> arg);
	
private:
	
	/**
	 * 現在日付取得
	 * @return 現在日付
	 */
	static struct tm *getNowDate();

};

#endif /* QBasicDateFunctions_h */
