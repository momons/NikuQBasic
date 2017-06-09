//
//  QBasicTypeIsFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/10.
//
//

#ifndef QBasicTypeIsFunctions_h
#define QBasicTypeIsFunctions_h

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト 型判別サブ関数群
class QBasicTypeIsFunctions final {
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
	/// int判定
	static inline vector<QBasicVariableEntity> isInt_params();
	static inline QBasicVariableEntity isInt_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// float判定
	static inline vector<QBasicVariableEntity> isFloat_params();
	static inline QBasicVariableEntity isFloat_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// str判定
	static inline vector<QBasicVariableEntity> isStr_params();
	static inline QBasicVariableEntity isStr_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// bool判定
	static inline vector<QBasicVariableEntity> isBool_params();
	static inline QBasicVariableEntity isBool_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// list判定
	static inline vector<QBasicVariableEntity> isList_params();
	static inline QBasicVariableEntity isList_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// dict判定
	static inline vector<QBasicVariableEntity> isDict_params();
	static inline QBasicVariableEntity isDict_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
};

#endif /* QBasicTypeIsFunctions_h */
