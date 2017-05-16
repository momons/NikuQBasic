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
	/// float→int変換
	static vector<QBasicVariableEntity> float2int_params();
	static QBasicVariableEntity float2int_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// str→int変換
	static vector<QBasicVariableEntity> str2int_params();
	static QBasicVariableEntity str2int_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// bool→int変換
	static vector<QBasicVariableEntity> bool2int_params();
	static QBasicVariableEntity bool2int_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// int→float変換
	static vector<QBasicVariableEntity> int2float_params();
	static QBasicVariableEntity int2float_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// str→float変換
	static vector<QBasicVariableEntity> str2float_params();
	static QBasicVariableEntity str2float_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// bool→float変換
	static vector<QBasicVariableEntity> bool2float_params();
	static QBasicVariableEntity bool2float_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// int→str変換
	static vector<QBasicVariableEntity> int2str_params();
	static QBasicVariableEntity int2str_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// float→str変換
	static vector<QBasicVariableEntity> float2str_params();
	static QBasicVariableEntity float2str_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// bool→str変換
	static vector<QBasicVariableEntity> bool2str_params();
	static QBasicVariableEntity bool2str_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// int→bool変換
	static vector<QBasicVariableEntity> int2bool_params();
	static QBasicVariableEntity int2bool_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// float→bool変換
	static vector<QBasicVariableEntity> float2bool_params();
	static QBasicVariableEntity float2bool_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// str→bool変換
	static vector<QBasicVariableEntity> str2bool_params();
	static QBasicVariableEntity str2bool_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	
};

#endif /* QBasicTypeChangeFunctions_h */
