//
//  QBasicErrors.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/17.
//
//

#ifndef QBasicErrors_h
#define QBasicErrors_h

using namespace std;

class QBasicSymbols;
class QBasicErrorEntity;
enum class ErrorType;
class QBasicVariableEntity;
enum class VariableType;

/**
 * エラー制御用クラス
 */
class QBasicErrors final {
public:
	
	/**
	 *  コンストラクタ
	 *  @param source プログラムソース
	 */
	QBasicErrors(QBasicSymbols *symbols);
	
	/**
	 *  デストラクタ
	 */
	~QBasicErrors();

	/**
	 *  エラー追加
	 *  @param errorType エラータイプ
	 *  @param message   メッセージ
	 */
	void addError(const ErrorType errorType, const string &message);

	/**
	 *  エラー追加
	 *  @param symbolIndex シンボルインデックス
	 *  @param errorType   エラータイプ
	 *  @param message     メッセージ
	 */
	void addError(const int symbolIndex, const ErrorType errorType, const string &message);

	/**
	 *  エラー取得
	 *  @param index インデックス
	 *  @return エラー情報
	 */
	QBasicErrorEntity *operator [] (const int index);
	
	/**
	 *  エラークリア
	 */
	void clear();
	
	/**
	 *  エラーの個数
	 *  @return エラーの個数
	 */
	int size();

	/**
	 *  エラー有無
	 *  @return true: エラーあり、false: エラーなし
	 */
	bool hasError();

	/**
	 *  エラータイプMissingFoundのメッセージ作成
	 *  @param trueSymbol  正しいシンボル
	 *  @param falseSymbol 間違ったシンボル
	 *  @return メッセージ
	 */
	static string buildMissingFound(const string &trueSymbol, const string &falseSymbol);

	/**
	 *  エラータイプBadVariableTypeのメッセージ作成
	 *  @param trueVariable  正しいタイプ
	 *  @param falseVariable 間違ったタイプ
	 *  @return メッセージ
	 */
	static string buildBadVariableType(const QBasicVariableEntity &trueVariable, const QBasicVariableEntity &falseVariable);

	/**
	 *  エラータイプBadVariableTypeのメッセージ作成
	 *  @param trueTypes     正しいタイプ
	 *  @param falseVariable 間違ったタイプ
	 *  @return メッセージ
	 */
	static string buildBadVariableType(const vector<VariableType> &trueTypes, const QBasicVariableEntity &falseVariable);

private:
	
	/// シンボルクラス
	QBasicSymbols *symbols;
	
	/// エラー群
	vector<QBasicErrorEntity> errors;
};

#endif /* QBasicErrors_h */
