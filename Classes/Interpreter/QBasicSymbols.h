//
//  QBasicSymbols.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/02.
//
//

#ifndef QBasicSymbols_h
#define QBasicSymbols_h

using namespace std;

class QBasicSymbolEntity;

/**
 * シンボル制御用クラス
 */
class QBasicSymbols final {
public:

	/**
	 *  コンストラクタ
	 *  @param source プログラムソース
	 */
	QBasicSymbols(const string &source);
	
	/**
	 *  デストラクタ
	 */
	~QBasicSymbols();

private:
	
	/// プログラムソース
	string source;
	
	/// 解析実行オフセット
	int execOffset;
	/// 行数
	int row;
	/// 項数
	int col;
	
	/// シンボル群
	vector<QBasicSymbolEntity> symbols;
	
	/**
	 *  シンボルをビルド
	 *  @param source プログラムソース
	 */
	void buildSymbols(const string &source);
	
	/**
	 * 単語取得
	 * @param symbolEntity 単語Entity
	 */
	void getSymbol(QBasicSymbolEntity &symbolEntity);

	/**
	 *  行項アップデート
	 *  @param ch 文字
	 */
	void updateRowCol(char ch);

};

#endif /* QBasicSymbols_h */
