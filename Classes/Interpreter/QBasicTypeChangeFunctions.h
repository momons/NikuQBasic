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
	/// int変換
	static inline vector<QBasicVariableEntity> toInt_params();
	static inline QBasicVariableEntity toInt_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	static inline void toInt_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset);
	/// float変換
	static inline vector<QBasicVariableEntity> toFloat_params();
	static inline QBasicVariableEntity toFloat_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	static inline void toFloat_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset);
	/// str変換
	static inline vector<QBasicVariableEntity> toStr_params();
	static inline QBasicVariableEntity toStr_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	static inline void toStr_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset);
	/// bool変換
	static inline vector<QBasicVariableEntity> toBool_params();
	static inline QBasicVariableEntity toBool_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	static inline void toBool_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset);
	
};

#endif /* QBasicTypeChangeFunctions_h */
