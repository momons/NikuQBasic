//
//  QBasicListFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/10.
//
//

#ifndef QBasicListFunctions_h
#define QBasicListFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト 配列操作サブ関数群
class QBasicListFunctions final {
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
	/// 要素数取得
	static inline vector<QBasicVariableEntity> count_params();
	static inline QBasicVariableEntity count_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	static inline void count_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset);
	/// 要素追加
	static inline vector<QBasicVariableEntity> append_params();
	static inline QBasicVariableEntity append_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	static inline void append_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset);
	/// 配列連結
//	static inline vector<QBasicVariableEntity> extend_params();
//	static inline QBasicVariableEntity extend_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
//	static inline void extend_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset);
	/// 要素取得
//	static inline vector<QBasicVariableEntity> at_params();
//	static inline QBasicVariableEntity at_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
//	static inline void at_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset);
};

#endif /* QBasicListFunctions_h */
