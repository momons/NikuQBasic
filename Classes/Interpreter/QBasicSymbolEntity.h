//
//  QBasicSymbolEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/02.
//
//

#ifndef QBasicSymbolEntity_h
#define QBasicSymbolEntity_h

using namespace std;

/// シンボルタイプ
enum class symbolType {
	Plus,
	Comment,
	Int,
	Float,
	Str,
	Bool,
	Other,
};


/**
 * シンボルEntity
 */
class QBasicSymbolEntity final {
public:

	/// シンボル
	string symbol;
	/// 行
	int row;
	/// 項
	int col;

	/**
	 * コンストラクタ
	 */
	QBasicSymbolEntity();
	
	/**
	 * コンストラクタ
	 * @param symbol  シンボル
	 * @param row     行
	 * @param col     項
	 */
	QBasicSymbolEntity(const string &symbol, int row, int col);
	
	/**
	 * デストラクタ
	 */
	~QBasicSymbolEntity();

};

#endif /* QBasicSymbolEntity_h */
