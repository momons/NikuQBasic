//
//  QBasicQueries.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/21.
//
//

#ifndef QBasicQueries_h
#define QBasicQueries_h

using namespace std;

class QBasicVariableEntity;

/**
 *  クエリを扱うクラス
 */
class QBasicQueries final {
public:
	
	/**
	 *  オブジェクト変換
	 *
	 *  @param jsonValue  出力オブジェクト
	 *  @param error      エラー
	 *  @param jsonString JSON文字列
	 */
//	static void toObject(picojson::value &jsonValue, string *error, const string &jsonString);
	
	/**
	 *  クエリ文字列変換
	 *  @param value 値
	 */
	static string toQueryString(QBasicVariableEntity &value);
	
private:
	
	/**
	 *  コンストラクタ
	 */
	QBasicQueries() {}
	
	/**
	 *  デストラクタ
	 */
	~QBasicQueries() {}
};

#endif /* QBasicQueries_h */
