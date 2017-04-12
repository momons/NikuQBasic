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
	float floatValue = 0;
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
	int compare(const float floatValue);
	
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
};

#endif /* QBasicVariableEntity_h */
