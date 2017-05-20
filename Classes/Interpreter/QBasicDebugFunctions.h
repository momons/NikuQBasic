//
//  QBasicDebugFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#ifndef QBasicDebugFunctions_h
#define QBasicDebugFunctions_h

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト デバッグサブ関数群
class QBasicDebugFunctions final {
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
	/// ウエイトを入れる
	static inline vector<QBasicVariableEntity> wait_params();
	static inline QBasicVariableEntity wait_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 標準出力
	static inline vector<QBasicVariableEntity> print_params();
	static inline QBasicVariableEntity print_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// エラーを発生させる
	static inline vector<QBasicVariableEntity> error_params();
	static inline QBasicVariableEntity error_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);

};

#endif /* QBasicDebugFunctions_h */
