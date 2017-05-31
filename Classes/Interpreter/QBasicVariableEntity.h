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
	/// バリュータイプ 配列、連想配列用
	vector<VariableType> valueTypes;
	
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
	
	/// nilフラグ
	bool isNil = true;
	
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
	QBasicVariableEntity(const string &name, const VariableType type, void *value);

	/**
	 * コンストラクタ
	 * @param name        変数名
	 * @param type        変数タイプ
	 * @param valueTypes  値変数タイプ群
	 * @param value       値のポインタ
	 */
	QBasicVariableEntity(const string &name, const VariableType type, const vector<VariableType> &valueTypes, void *value);
	
	/**
	 * コンストラクタ
	 * @param name  変数名
	 * @param value 値の文字列
	 */
	QBasicVariableEntity(const string &name, const string &value);

	/**
	 * コンストラクタ 配列用
	 * @param name        変数名
	 * @param valueTypes  値変数タイプ群
	 * @param values      値
	 */
	QBasicVariableEntity(const string &name, const vector<VariableType> &valueTypes, const vector<QBasicVariableEntity> &values);

	/**
	 * コンストラクタ 連想配列用
	 * @param name        変数名
	 * @param valueTypes  値変数タイプ群
	 * @param values      値
	 */
	QBasicVariableEntity(const string &name, const vector<VariableType> &valueTypes, const map<string, QBasicVariableEntity> &values);
	
	/**
	 * デストラクタ
	 */
	~QBasicVariableEntity();

	/**
	 * 値取得
	 * @return 値のポインタ
	 */
	void *getValue();
	
#pragma mark - 比較

	/**
	 * entityと比較
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	int compare(const QBasicVariableEntity &entity);
	
	/**
	 * ==比較
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	bool operator == (const QBasicVariableEntity &entity);

	/**
	 * !=比較
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	bool operator != (const QBasicVariableEntity &entity);
	
	/**
	 * >比較
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	bool operator > (const QBasicVariableEntity &entity);
	
	/**
	 * <比較
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	bool operator < (const QBasicVariableEntity &entity);
	
	/**
	 * >=比較
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	bool operator >= (const QBasicVariableEntity &entity);
	
	/**
	 * <=比較
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	bool operator <= (const QBasicVariableEntity &entity);
	
#pragma mark - 四則演算

	/**
	 * 代入
	 * @param entity 変数entity
	 */
	void set(const QBasicVariableEntity &entity);

	/**
	 * int代入
	 * @param value 値
	 */
	void set(const int value);

	/**
	 * float代入
	 * @param value 値
	 */
	void set(const double value);

	/**
	 * str代入
	 * @param value 値
	 */
	void set(const string &value);

	/**
	 * bool代入
	 * @param value 値
	 */
	void set(const bool value);

	/**
	 * 足し算
	 * @param entity 変数entity
	 * @return 結果
	 */
	QBasicVariableEntity operator + (const QBasicVariableEntity &entity);

	/**
	 * 引き算
	 * @param entity 変数entity
	 * @return 結果
	 */
	QBasicVariableEntity operator - (const QBasicVariableEntity &entity);

	/**
	 * 掛け算
	 * @param entity 変数entity
	 * @return 結果
	 */
	QBasicVariableEntity operator * (const QBasicVariableEntity &entity);

	/**
	 * 掛け算 数値
	 * @param type  変数タイプ
	 * @param value 値
	 * @return 結果
	 */
	QBasicVariableEntity mul(VariableType type, double value);

	/**
	 * 割り算
	 * @param entity 変数entity
	 * @return 結果
	 */
	QBasicVariableEntity operator / (const QBasicVariableEntity &entity);

	/**
	 * 余り
	 * @param entity 変数entity
	 * @return 結果
	 */
	QBasicVariableEntity operator % (const QBasicVariableEntity &entity);
	
#pragma mark - 論理演算

	/**
	 * And論理演算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity operator & (const QBasicVariableEntity &entity);

	/**
	 * And比較論理演算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity operator && (const QBasicVariableEntity &entity);

	/**
	 * OR論理演算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity operator | (const QBasicVariableEntity &entity);

	/**
	 * OR比較論理演算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity operator || (const QBasicVariableEntity &entity);
	
	/**
	 * XOR論理演算
	 * @param entity 変数entity
	 * @return 比較結果
	 */
	QBasicVariableEntity operator ^ (const QBasicVariableEntity &entity);

	/**
	 * NOT論理演算
	 * @return 比較結果
	 */
	QBasicVariableEntity operator ! ();

#pragma mark - チェック
	
	/**
	 *  変数タイプの取得
	 *  @param str 文字
	 *  @return 変数タイプ
	 */
	static VariableType getVariableType(const string &str);
	
	/**
	 *  変数タイプ文字の取得
	 *  @param variableType 変数タイプ
	 *  @return 文字
	 */
	static string getVariableTypeString(const VariableType variableType);
	
	/**
	 *  変数タイプの取得 階層
	 *  @param entity 変数entity
	 *  @return 変数タイプ群
	 */
	static vector<VariableType> getVariableTypes(const QBasicVariableEntity &entity);

#pragma mark - 変換
	
	/**
	 * Intへ変換
	 * @return 結果
	 */
	QBasicVariableEntity toInt();

	/**
	 * Floatへ変換
	 * @return 結果
	 */
	QBasicVariableEntity toFloat();

	/**
	 * Strへ変換
	 * @return 結果
	 */
	QBasicVariableEntity toStr();

	/**
	 * Boolへ変換
	 * @return 結果
	 */
	QBasicVariableEntity toBool();

#pragma mark - その他
	
	/**
	 *  変数タイプを文字列に変換
	 *  @param type      メインタイプ
	 *  @param subTypes  サブタイプ
	 *  @return 文字列
	 */
	static string toString(const VariableType type, const vector<VariableType> &subTypes);

private:
	
	/**
	 * 値なしコピー
	 * @return コピーEntity
	 */
	QBasicVariableEntity copyNotValue();
	
};

#endif /* QBasicVariableEntity_h */
