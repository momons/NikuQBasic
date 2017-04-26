//
//  QBasicTypeChangeFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/27.
//
//

#ifndef QBasicTypeChangeFunctions_h
#define QBasicTypeChangeFunctions_h

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト 型変換サブ関数群
class QBasicTypeChangeFunctions final {
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
	static QBasicVariableEntity abs_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	
};

#endif /* QBasicTypeChangeFunctions_h */
