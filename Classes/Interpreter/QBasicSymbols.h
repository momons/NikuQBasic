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

	/**
	 *  次のシンボルへ
	 *  @return シンボル
	 */
	string nextSymbol();
	
	/**
	 *  一個前のシンボルを取得
	 *  @return シンボル
	 */
	QBasicSymbolEntity *beforeSymbolEntity();
	
	/**
	 * シンボル情報取得
	 * @param offset オフセット
	 * @return シンボル情報のポインタ
	 */
	QBasicSymbolEntity *operator [] (const int offset);
	
	/**
	 *  オフセット設定
	 *  @param offset オフセット
	 */
	void jumpOffset(const int offset);
	
	/**
	 *  オフセット一つ下げる
	 */
	void popBack();

	/**
	 *  現在のオフセット取得
	 *  @return 現在のオフセット
	 */
	int offset();
	
	/**
	 *  オフセットをスナップショットする
	 */
	void snapshot();
	
	/**
	 *  スナップショットオフセット取得
	 *  @return スナップショットオフセット
	 */
	int snapshotOffset();
	
private:
	
	/// プログラムソース
	string source;
	
	/// 解析実行オフセット
	int execOffset;
	/// 行数
	int row;
	/// 項数
	int col;
	
	/// スナップショットオフセット
	int snapshotExecOffset;

	/// シンボル群
	vector<QBasicSymbolEntity> symbols;
	
	/**
	 *  シンボルをビルド
	 *  @param source プログラムソース
	 */
	void inline buildSymbols(const string &source);
	
	/**
	 * 単語取得
	 * @param symbolEntity 単語Entity
	 */
	void inline getSymbol(QBasicSymbolEntity &symbolEntity);

	/**
	 *  行項アップデート
	 *  @param ch 文字
	 */
	void updateRowCol(char ch);

};

#endif /* QBasicSymbols_h */
