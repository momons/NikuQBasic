//
//  QBInterpreterScene.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/02.
//
//

#ifndef __NikuQBasic__QBInterpreterScene__
#define __NikuQBasic__QBInterpreterScene__

#include "cocos2d.h"
#include <vector>
#include <map>

#include "QBInterpreter.h"
#include "QBInterpreterSetupNodeEntity.h"

using namespace std;
USING_NS_CC;

class QBInterpreterScene final: public Scene {
public:

	virtual bool init();
	
	// a selector callback
	void menuCloseCallback(Ref* pSender);
	
	// implement the "static create()" method manually
	CREATE_FUNC(QBInterpreterScene);
	
	/** 描画ロックフラグ */
	bool drawLock;
	
	/** パーティクル */
	map<int, string> particles;
	
	/** タッチ開始座標 */
	vector<Vec2> touchBegin;
	/** タッチ移動座標 */
	vector<Vec2> touchMove;
	/** タッチ移動座標 */
	vector<Vec2> touchEnd;
	
	/**
	 *  nodeを追加
	 *  @param index インデックス
	 *  @param node  追加するnode
	 */
	void addNode(int index, QBInterpreterSetupNodeEntity node);
	
	/**
	 *  ノード取得
	 *  @param index インデックス
	 *  @return Entity
	 */
	QBInterpreterSetupNodeEntity * getSetupNode(int index);
	
private:
	
	/** インタプリタ */
	QBInterpreter *interpreter;

	/** 表示設定するnode情報 */
	map<int, QBInterpreterSetupNodeEntity> setupNodes;
	
	/** 表示中ノード */
	map<int, Node*> showNodes;

	/** タッチ終了情報を削除するカウント **/
	int removeTouchEndCount;

	/**
	 *  メイン処理
	 *  @param delta デルタ
	 */
	virtual void update(float delta);
	
	/**
	 *  ノードを設定
	 */
	void setupNode();

	/**
	 *  ノードを設定
	 *  @param index インデックス
	 *  @param node  ノード
	 */
	void createNode(int index, QBInterpreterSetupNodeEntity *node);
	
	/**
	 *  ノードを移動
	 *  @param index     インデックス
	 */
	void moveNode(int index);
	
	/**
	 *  ノードを追加移動
	 *  @param index     インデックス
	 */
	void moveAddNode(int index);
	
	/**
	 *  ノードを拡大
	 *  @param index     インデックス
	 */
	void scaleNode(int index);
	
	/**
	 *  ノードを回転
	 *  @param index     インデックス
	 */
	void rotationNode(int index);
	
	/**
	 *  ノード移動
	 *  @param index     インデックス
	 *  @param node      ノード
	 */
	void setLocateNode(int index);
	
#pragma mark - タッチ
	
	/**
	 *  タッチ初期化
	 */
	void initTouch();
	
	/**
	 *  タッチクリア処理
	 */
	void clearTouch();
};


#endif /* defined(__NikuQBasic__QBInterpreterScene__) */
