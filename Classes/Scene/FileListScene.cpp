//
//  FileListScene.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/01/11.
//
//

#include "FileListScene.h"

#include "CustomDirector.h"

/**
 *  初期化
 *  @return 作成可否
 */
bool FileListScene::init() {
	
	// 画面サイズサイズを取得
	windowSize = Director::getInstance()->getWinSize();
	
	// テーブルビュー
	tableView = TableView::create(this, Size(windowSize.width, windowSize.height * 9 / 10));
	tableView->setPosition(Point(0, 0));
	tableView->setDirection(TableView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setDelegate(this);
	addChild(tableView);
	tableView->reloadData();
	
	return true;
}

#pragma mark - TableViewDataSource

/// セルサイズ設定
Size FileListScene::cellSizeForTable(TableView* table) {
	return Size(windowSize.width, 30);
}

/// セル設定
TableViewCell* FileListScene::tableCellAtIndex(TableView* table,ssize_t idx) {
	
	// 行番号
	auto id = StringUtils::format("%zd", idx);
	// 行テキスト
	auto text = StringUtils::format("aa");
	// セル
	TableViewCell *cell = table->dequeueCell();
	
	cell = new TableViewCell();
	cell->autorelease();
	
	// セルの背景は交互に色を変更する
	auto background_color = Color3B::GREEN;
	if (idx%2) {
		background_color = Color3B::BLUE;
	}
	
	// Background
	auto bg = Sprite::create();
	bg->setAnchorPoint(Point(0, 0));
	bg->setTextureRect(Rect(0, 0, windowSize.width, 30));
	bg->setColor(background_color);
	bg->setTag(100);
	cell->addChild(bg);
	
	// ボーダーライン
	auto line = Sprite::create();
	line->setAnchorPoint(Point(0, 0));
	line->setTextureRect(Rect(0, 0, windowSize.width, 1));
	line->setColor(Color3B::WHITE);
	cell->addChild(line);
	
	// 画像
	//	auto imge_1 = Sprite::create("Icon-80.png");
	//	imge_1->setAnchorPoint(Point(0, 0));
	//	imge_1->setPosition(Point(10, 0));
	//	cell->addChild(imge_1);
	
	// IDテキスト部分
	auto label_1 = Label::createWithSystemFont(id, "HiraKakuProN", 30);
	label_1->setAnchorPoint(Point(0, 0));
	label_1->setPosition(Point(110, 0));
	label_1->setColor(Color3B::WHITE);
	cell->addChild(label_1);
	
	// テキスト部分
	auto label_2 = Label::createWithSystemFont(text, "HiraKakuProN", 30);
	label_2->setAnchorPoint(Point(0, 0));
	label_2->setPosition(Point(140, 0));
	label_2->setColor(Color3B::WHITE);
	cell->addChild(label_2);
	
	return cell;
}

/// 行数設定
ssize_t FileListScene::numberOfCellsInTableView(TableView* table) {
	return 60;
}

#pragma mark - TableViewDelegate

/// タッチイベント
void FileListScene::tableCellTouched(TableView* table,TableViewCell* cell) {
	CCLOG("%ziのセルがタッチされました", cell->getIdx());
	
	CustomDirector *director = (CustomDirector *)Director::getInstance();
	director->popSceneWithTransition<TransitionSlideInL>(0.5);
}
