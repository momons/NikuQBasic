//
//  QBasicErrorEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/17.
//
//

#ifndef QBasicErrorEntity_h
#define QBasicErrorEntity_h

using namespace std;

/// enum→数値変換用マクロ
#define ERROR_TYPE(value) static_cast<ErrorType>(value)

/// エラータイプ
enum class ErrorType {
	/// なし
	Nothing,
	/// 必要なものがない
	MissingFound,
	/// 変数型が不正
	BadVariableType,
	/// 戻り値がvoid
	ReturnTypeVoid,
	/// 該当関数なし
	UnknownFunction,
	/// 不明なシンボル
	UnknownSymbol,
};

/**
 * エラーEntity
 */
class QBasicErrorEntity final {
public:
	
	/// シンボルインデックス
	int symbolIndex = 0;
	/// エラータイプ
	ErrorType type = ErrorType::Nothing;
	/// エラーメッセージ
	string message = "";
	
	/**
	 * コンストラクタ
	 */
	QBasicErrorEntity();
	
	/**
	 * コンストラクタ
	 * @param symbolIndex  シンボルインデックス
	 * @param type         エラータイプ
	 * @param message      メッセージ
	 */
	QBasicErrorEntity(const int symbolIndex, const ErrorType type, const string &message);
	
	/**
	 * デストラクタ
	 */
	~QBasicErrorEntity();
	
};

#endif /* QBasicErrorEntity_h */
