//
//  QBasicVariableEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/12.
//
//

#ifndef QBasicVariableEntity_h
#define QBasicVariableEntity_h

using namespace std;

/// enum→数値変換用マクロ
#define VARIABLE_TYPE(value) static_cast<VariableType>(value)

/// 変数タイプ
enum class VariableType {
	/// なし
	Void,
	/// 整数
	Int,
	/// 小数
	Float,
	/// 文字
	Str,
	/// ブール
	Bool,
	/// 配列
	List,
	/// 連想配列
	Dict,
	/// 不明
	Unknown,
};

/**
 * 変数Entity
 */
class QBasicVariableEntity final {
public:
	
	/// 名前
	string name;
	
	/// タイプ
	VariableType type;
	
	/// 整数値
	int intValue = 0;
	/// 小数値
	double floatValue = 0;
	/// 文字列
	string strValue = "";
	/// ブール値
	bool boolValue = false;
	/// 配列
	vector<QBasicVariableEntity> listValue;
	/// 連想配列
	map<string, QBasicVariableEntity> dictValue;
	
	/**
	 * コンストラクタ
	 */
	QBasicVariableEntity();
	
	/**
	 * コンストラクタ
	 * @param name  変数名
	 * @param type  変数タイプ
	 * @param value 値のポインタ
	 */
	QBasicVariableEntity(const string &name, const VariableType type, const void *value);

	/**
	 * コンストラクタ
	 * @param name  変数名
	 * @param value 値の文字列
	 */
	QBasicVariableEntity(const string &name, const string &value);

	/**
	 * デストラクタ
	 */
	~QBasicVariableEntity();

	/**
	 * entityと比較
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	int compare(const QBasicVariableEntity &entity);
				
	/**
	 * intと比較
	 * @param intValue int値
	 * @return 比較結果
	 */
	int compare(const int intValue);
	
	/**
	 * floatと比較
	 * @param floatValue float値
	 * @return 比較結果
	 */
	int compare(const double floatValue);
	
	/**
	 * stringと比較
	 * @param strValue string値
	 * @return 比較結果
	 */
	int compare(const string strValue);
	
	/**
	 * boolと比較
	 * @param boolValue bool値
	 * @return 比較結果
	 */
	int compare(const bool boolValue);
	
#pragma mark - 四則演算

	/**
	 * 足し算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity add(const QBasicVariableEntity &entity);

	/**
	 * 引き算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity sub(const QBasicVariableEntity &entity);

	/**
	 * 掛け算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity mul(const QBasicVariableEntity &entity);

	/**
	 * 割り算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity div(const QBasicVariableEntity &entity);

	/**
	 * 余り
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity mod(const QBasicVariableEntity &entity);
	
#pragma mark - 論理演算

	/**
	 * And論理演算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity expressionAnd(const QBasicVariableEntity &entity);

	/**
	 * OR論理演算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity expressionOr(const QBasicVariableEntity &entity);

	/**
	 * XOR論理演算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity expressionXor(const QBasicVariableEntity &entity);

	/**
	 * NOT論理演算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity expressionNot();
	
private:
	
	/**
	 * 値なしコピー
	 * @return コピーEntity
	 */
	QBasicVariableEntity copyNotValue();
	
};

#endif /* QBasicVariableEntity_h */
