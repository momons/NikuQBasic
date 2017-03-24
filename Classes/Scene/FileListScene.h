//
//  FileListScene.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/01/11.
//
//

#ifndef FileListScene_h
#define FileListScene_h

#include "cocos2d.h"
#include <extensions/cocos-ext.h>

using namespace std;
USING_NS_CC;
using namespace extension;

/// ファイルリストシーンクラス
class FileListScene final: public Scene, public TableViewDataSource, public TableViewDelegate {
public:
	
	/**
	 *  初期化
	 *  @return 作成可否
	 */
	virtual bool init() override;
	
	CREATE_FUNC(FileListScene);
	
#pragma mark - TableViewDataSource
	
	virtual Size cellSizeForTable(TableView* table) override;
	virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx) override;
	virtual ssize_t numberOfCellsInTableView(TableView* table) override;
	
#pragma mark - TableViewDelegate
	
	virtual void tableCellTouched(TableView* table,TableViewCell* cell) override;
	virtual void scrollViewDidScroll(ScrollView* view) override {};
	virtual void scrollViewDidZoom(ScrollView* view) override {};
	
private:
	
	/// テーブルビュー
	TableView *tableView;
	
	/// 画面サイズ
	Size windowSize;
	
};

#endif /* FileListScene_h */
