//
//  QBasicVariableEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/12.
//
//

#ifndef QBasicVariableEntity_h
#define QBasicVariableEntity_h

#include "picojson.h"

using namespace std;

/// int→enum変換用マクロ
#define VARIABLE_TYPE(value) static_cast<VariableType>(value)
/// enum→int変換用マクロ
#define VARIABLE_TYPE_RAWVALUE(value) static_cast<int>(value)

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
	
	/// タイプ (配列、連想配列用は複数)
	vector<VariableType> types;
	
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
	/// 定数フラグ
	bool isConst = false;
	
	/**
	 * コンストラクタ
	 */
	QBasicVariableEntity();
	
	/**
	 * コンストラクタ
	 * @param name  変数名
	 * @param types 変数タイプ
	 * @param value 値のポインタ
	 */
	QBasicVariableEntity(const string &name, const vector<VariableType> &types, void *value);

	/**
	 * コンストラクタ
	 * @param name  変数名
	 * @param value 値の文字列
	 */
	QBasicVariableEntity(const string &name, const string &value);

	/**
	 * コンストラクタ 配列用
	 * @param name   変数名
	 * @param types  値変数タイプ群
	 * @param values 値
	 */
	QBasicVariableEntity(const string &name, const vector<VariableType> &types, const vector<QBasicVariableEntity> &values);

	/**
	 * コンストラクタ 連想配列用
	 * @param name   変数名
	 * @param types  値変数タイプ群
	 * @param values 値
	 */
	QBasicVariableEntity(const string &name, const vector<VariableType> &types, const map<string, QBasicVariableEntity> &values);
	
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
	 * @param types 変数タイプ
	 * @param value 値
	 * @return 結果
	 */
	QBasicVariableEntity mul(const vector<VariableType> types, const double value);

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

#pragma mark - 要素操作
	
	/**
	 * 要素追加
	 * @param entity 変数entity
	 * @return 結果entity
	 */
	QBasicVariableEntity append(const QBasicVariableEntity &entity);
	

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

	/**
	 * QBasicVariableEntity→JSONオブジェクト変換
	 * @return JSONオブジェクト
	 */
	picojson::object toJsonObject();

	/**
	 * QBasicVariableEntity→JSON配列変換
	 * @return JSON配列
	 */
	picojson::array toJsonArray();
	
	/**
	 * QBasicVariableEntity→JSON文字列
	 * @return JSON文字列
	 */
	string toJsonString();

	/**
	 * QBasicVariableEntity→保存用JSONオブジェクト変換
	 * @return JSONオブジェクト
	 */
	picojson::object toStorageJsonObject();
	
	/**
	 * JSONオブジェクト→QBasicVariableEntity変換
	 * @param object JSONオブジェクト
	 * @return QBasicVariableEntity
	 */
	static QBasicVariableEntity buildForJsonObject(picojson::object &object);

	/**
	 * JSON配列→QBasicVariableEntity変換
	 * @param object JSONオブジェクト
	 * @return QBasicVariableEntity
	 */
	static QBasicVariableEntity buildForJsonArray(picojson::array &object);
	
	/**
	 * 保存用JSONオブジェクト→QBasicVariableEntity変換
	 * @param object JSONオブジェクト
	 * @return QBasicVariableEntity
	 */
	static QBasicVariableEntity buildForStorageJsonObject(picojson::object &object);

#pragma mark - その他
	
	/**
	 *  変数タイプを文字列に変換
	 *  @param types  タイプ
	 *  @return 文字列
	 */
	static string toString(const vector<VariableType> &types);
	
	/**
	 *  定数化設定
	 *  @param isConst  true:定数、false:変数
	 */
	void setConst(const bool isConst);

private:

	/**
	 *  変数タイプを文字列に変換
	 *  @param name  変数名
	 *  @param types 変数タイプ
	 *  @param value 値のポインタ
	 */
	void inline configureEntity(const string &name, const vector<VariableType> &types, void *value);
	
	/**
	 * 値なしコピー
	 * @return コピーEntity
	 */
	QBasicVariableEntity copyNotValue();
	
};

#endif /* QBasicVariableEntity_h */
