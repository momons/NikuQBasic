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
	/// 該当変数なし
	UnknownVariable,
	/// 該当関数なし
	UnknownFunction,
	/// 不明なシンボル
	UnknownSymbol,
	/// 配列範囲外
	ListIndexOutOfBounds,
	/// 連想配列不正キー
	DictUnknownKey,
	/// 変数二重定義
	OverlapVariableName,
	/// 変数名が不正
	BadVariableName,
	/// 関数二重定義
	OverlapFunctionName,
	/// 関数名が不正
	BadFunctionName,
	/// 不正なelseif
	BadElseif,
	/// 不正なelse
	BadElse,
	/// endifがない
	NothingEndif,
	/// nextがない
	NothingNext,
	/// 関数内に関数
	FunctionOverFunction,
	/// 戻り値がない
	NothingReturnValue,
	/// 定数に値を設定していない
	NothingConstValue,
	/// 定数は値を変更できない
	NoChangeConstValue,
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
