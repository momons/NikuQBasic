//
//  QBasicScene.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/02.
//
//

#include "QBasicScene.h"

/**
 *  初期化
 *  @return 作成可否
 */
bool QBasicScene::init() {

	// タッチ初期化
	initTouch();
	
	// 初期化
	setupNodes = map<int, QBasicSetupNodeEntity>();
	showNodes = map<int, Node*>();
	particles = map<int, string>();
	
	// 実行
	scheduleUpdate();
	
	interpreter = new QBasic(this,
									// 通信
//									"a = net(\"http://yahoo.co.jp/\")\n"
//									"log(a)\n"
									// ブラウザ
//									"browser(\"Yahoo!\",\"http://yahoo.co.jp\")\n"
									// アラート
//									"alert(\"タイトル\",\"メッセージ\",\"OK!\")\n"
									// 確認アラート
//									"a = confirm(\"タイトル\",\"メッセージ\",\"OK\",\"キャンセル\")\n"
//									"log(a)\n"
									// 入力
//									"a = input(\"タイトル\",\"メッセージ\",\"でふぉると！\")\n"
//									"log(a)\n"
									// BGM
//									"loadbgm(\"bgm_game\")\n"
//									"playbgm(1)\n"
									// 効果音
//									"loadse(0,\"se_break\")\n"
//									"playse(0,1)\n"
									
									"loadparticle(0, \"particle_texture.plist\")\n"
									"drawlock(1)\n"
									"drawparticle(0, 0, 300, 300)\n"
									"drawlock(0)\n"
									
//									"linewidth(4)\n"
//									"color(255,0,0,255)\n"
//
									"f = 0\n"
									"drawlock(1)\n"
//									"rect(0,0,0,200,200,0)\n"
//									"drawlock(0)\n"
									"label loop\n"
//
									"a = touchbegincnt\n"
									"if a > 0 and f = 0 then\n"
									"  f = 1\n"
									"  x = touchbeginx(0)\n"
									"  y = touchbeginy(0)\n"
									"  drawlock(1)\n"
									"  move(0,x,y)\n"
									"  drawlock(0)\n"
									"endif\n"
//									"a = touchmovecnt\n"
//									"if a > 0 and f = 1 then\n"
//									"  x = touchmovex(0)\n"
//									"  y = touchmovey(0)\n"
//									"  drawlock(1)\n"
//									"  move(0,x,y)\n"
//									"  drawlock(0)\n"
//									"endif\n"
									"a = touchendcnt\n"
									"if a > 0 and f = 1 then\n"
									"  f = 0\n"
									"endif\n"
//
									"goto \"loop\"\n"
									
//									"drawlock(1)\n"
//									"color(255,0,0,255)\n"
//									"rect(0,200,200,200,200,0)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									"drawlock(1)\n"
//									"move(0,400,400)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									"drawlock(1)\n"
//									"scale(0,1.5,1.5)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									
//									"drawlock(1)\n"
//									"color(0,0,255,255)\n"
//									"circle(1,300,300,200,200,0)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									"drawlock(1)\n"
//									"move(1,400,400)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									"drawlock(1)\n"
//									"scale(1,1.5,1.5)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									
//									"drawlock(1)\n"
//									"color(0,255,0,255)\n"
//									"triangle(2,200,200,300,400,400,200,0)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									"drawlock(1)\n"
//									"move(2,400,367)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									"drawlock(1)\n"
//									"scale(2,1.5,1.5)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									
//									"drawlock(1)\n"
//									"color(255,0,255,255)\n"
//									"line(3,200,200,400,400)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									"drawlock(1)\n"
//									"move(3,400,400)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
//									"drawlock(1)\n"
//									"scale(3,1.5,1.5)\n"
//									"drawlock(0)\n"
//									"wait(2000)\n"
									
//									"stopbgm\n"
//									"stopse(0)\n"
									,
									"a"
									);
	auto t1 = interpreter->backgroundRun();
//	t1.join();
	t1.detach();
	
	return true;
}


void QBasicScene::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif
	
	Director::getInstance()->end();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

#pragma mark - メイン

/**
 *  メイン処理
 *  @param delta デルタ
 */
void QBasicScene::update(float delta) {
	
	// 表示設定
	setupNode();
	
	// タッチ終了クリア処理
	clearTouch();
}

#pragma mark - 画像、図形、文字列

/**
 *  nodeを追加
 *  @param index インデックス
 *  @param node  追加するnode
 */
void QBasicScene::addNode(int index, QBasicSetupNodeEntity node) {
	// 追加
	setupNodes[index] = node;
}

/**
 *  ノード取得
 *  @param index インデックス
 *  @return Entity
 */
QBasicSetupNodeEntity * QBasicScene::getSetupNode(int index) {
	auto node = setupNodes.find(index);
	if (node == setupNodes.end()) {
		return nullptr;
	}
	return &((*node).second);
}

/**
 *  ノードを設定
 */
void QBasicScene::setupNode() {
	
	// ロック中なので何もしない
	if (drawLock) {
		return;
	}

	for (auto it = setupNodes.begin();it != setupNodes.end();it++) {
		
		auto index = (*it).first;
		auto setupNode = &(*it).second;
		
		// 特に何もなし
		if (setupNode->setupTypes.size() <= 0) {
			continue;
		}
		
		// 作成
		for (auto it2 = setupNode->setupTypes.begin();it2 != setupNode->setupTypes.end();it2++) {
			auto setupType = SETUP_TYPE_RAW_VALUE(*it2);
			switch (setupType) {
				case QBasicSetupType::Hidden:{
					auto showIt = showNodes.find(index);
					if (showIt == showNodes.end()) {
						break;
					}
					// 表示から削除
					showNodes[index]->removeFromParent();
					// 要素から削除
					showNodes.erase(showIt);
					break;
				}
				case QBasicSetupType::Create:{
					createNode(index, setupNode);
					break;
				}
				case QBasicSetupType::Move:
					moveNode(index);
					break;
				case QBasicSetupType::MoveAdd:
					moveAddNode(index);
					break;
				case QBasicSetupType::Scale:
				case QBasicSetupType::ScaleAdd:
					scaleNode(index);
					break;
				case QBasicSetupType::Rotation:
				case QBasicSetupType::RotationAdd:
					rotationNode(index);
					break;
				case QBasicSetupType::Mirror:
					break;
			}
			// 要素から削除
			setupNode->setupTypes.erase(it2);
			it2--;
		}
	}
}

/**
 *  ノードを設定
 *  @param index インデックス
 *  @param node  ノード
 */
void QBasicScene::createNode(int index, QBasicSetupNodeEntity *node) {

	// まだある場合は消去
	auto showIt = showNodes.find(index);
	if (showIt != showNodes.end()) {
		// 表示から削除
		showNodes[index]->removeFromParent();
		// 要素から削除
		showNodes.erase(showIt);
	}
	
	// 表示設定
	switch (node->type) {
		case QBasicSetupNodeType::Text: {
			auto text = Label::createWithSystemFont(node->text, node->fontName, node->fontSize);
			text->setPosition(Point(node->x1, node->y1));
			text->setColor(Color3B((GLubyte)(255 * node->color.r), (GLubyte)(255 * node->color.g), (GLubyte)(255 * node->color.b)));
			text->setOpacity((GLubyte)(255 * node->color.a));
			addChild(text);
			showNodes[index] = text;
			break;
		}
		case QBasicSetupNodeType::Image: {
			break;
		}
		case QBasicSetupNodeType::Particle: {
			// 設定されていない
			auto it = particles.find(node->index);
			if (it == particles.end()) {
				break;
			}
			auto particle = ParticleSystemQuad::create(particles[node->index]);
			particle->resetSystem();
			particle->setPosition(Vec2(node->x1, node->y1));
			addChild(particle);
			showNodes[index] = particle;
			break;
		}
		case QBasicSetupNodeType::Line: {
			auto draw = DrawNode::create();
			draw->drawSegment(
							  Vec2(node->x1, node->y1),
							  Vec2(node->x2, node->y2),
							  node->lineWidth, node->color
							  );
			addChild(draw);
			showNodes[index] = draw;
			break;
		}
		case QBasicSetupNodeType::Rect: {
			Vec2 points[] = {
				Vec2(node->x1, node->y1),
				Vec2(node->x1 + node->width, node->y1),
				Vec2(node->x1 + node->width, node->y1 + node->height),
				Vec2(node->x1, node->y1 + node->height),
			};
			auto draw = DrawNode::create();
			if (node->isFill) {
				draw->drawPolygon(points, 4, node->color, node->lineWidth, node->color);
			} else {
				draw->drawPolygon(points, 4, Color4F(0, 0, 0, 0), node->lineWidth, node->color);
			}
			addChild(draw);
			showNodes[index] = draw;
			break;
		}
		case QBasicSetupNodeType::Circle: {
			vector<Vec2> points;
			for (int i = 0;i < CIRCLE_POINT_COUNT;i++) {
				points.push_back(
								 Vec2(node->x1 + node->width * cos(M_PI / 180 * (90 + 360 * i / CIRCLE_POINT_COUNT)),
									  node->y1 + node->height * sin(M_PI / 180 * (90 + 360 * i / CIRCLE_POINT_COUNT))
									  )
								 );
			}
			auto draw = DrawNode::create();
			if (node->isFill) {
				draw->drawPolygon(&points[0], CIRCLE_POINT_COUNT, node->color, node->lineWidth, node->color);
			} else {
				draw->drawPolygon(&points[0], CIRCLE_POINT_COUNT, Color4F(0, 0, 0, 0), node->lineWidth, node->color);
			}
			addChild(draw);
			showNodes[index] = draw;
			break;
		}
		case QBasicSetupNodeType::Triangle: {
			Vec2 points[] = {
				Vec2(node->x1, node->y1),
				Vec2(node->x2, node->y2),
				Vec2(node->x3, node->y3),
			};
			auto draw = DrawNode::create();
			if (node->isFill) {
				draw->drawPolygon(points, 3, node->color, node->lineWidth, node->color);
			} else {
				draw->drawPolygon(points, 3, Color4F(0, 0, 0, 0), node->lineWidth, node->color);
			}
			addChild(draw);
			showNodes[index] = draw;
			break;
		}
	}
}

/**
 *  ノードを移動
 *  @param index     インデックス
 */
void QBasicScene::moveNode(int index) {
	
	auto nodeEntity = setupNodes[index];
	auto nodeEntityBk = nodeEntity;
	switch (nodeEntity.type) {
		case QBasicSetupNodeType::Text:
		case QBasicSetupNodeType::Image:
		case QBasicSetupNodeType::Circle:
		case QBasicSetupNodeType::Particle:
			nodeEntity.x1 = nodeEntity.moveX;
			nodeEntity.y1 = nodeEntity.moveY;
			nodeEntity.centerX = nodeEntity.x1;
			nodeEntity.centerY = nodeEntity.y1;
			break;
		case QBasicSetupNodeType::Rect:
			nodeEntity.centerX = nodeEntity.moveX;
			nodeEntity.centerY = nodeEntity.moveY;
			nodeEntity.x1 = nodeEntity.centerX - (nodeEntity.width / 2);
			nodeEntity.y1 = nodeEntity.centerY - (nodeEntity.height / 2);
			break;
		case QBasicSetupNodeType::Line:{
			nodeEntity.centerX = nodeEntity.moveX;
			nodeEntity.centerY = nodeEntity.moveY;
			double subX = (nodeEntityBk.centerX - nodeEntity.moveX);
			double subY = (nodeEntityBk.centerY - nodeEntity.moveY);
			nodeEntity.x1 -= subX;
			nodeEntity.y1 -= subY;
			nodeEntity.x2 -= subX;
			nodeEntity.y2 -= subY;
			break;
		}
		case QBasicSetupNodeType::Triangle:{
			nodeEntity.centerX = nodeEntity.moveX;
			nodeEntity.centerY = nodeEntity.moveY;
			double subX = (nodeEntityBk.centerX - nodeEntity.moveX);
			double subY = (nodeEntityBk.centerY - nodeEntity.moveY);
			nodeEntity.x1 -= subX;
			nodeEntity.y1 -= subY;
			nodeEntity.x2 -= subX;
			nodeEntity.y2 -= subY;
			nodeEntity.x3 -= subX;
			nodeEntity.y3 -= subY;
			break;
		}
	}
	setupNodes[index] = nodeEntity;
	
	// 位置設定
	setLocateNode(index);
}

/**
 *  ノードを追加移動
 *  @param index     インデックス
 */
void QBasicScene::moveAddNode(int index) {
	
	auto nodeEntity = setupNodes[index];
	auto nodeEntityBk = nodeEntity;
	switch (nodeEntity.type) {
		case QBasicSetupNodeType::Text:
		case QBasicSetupNodeType::Image:
		case QBasicSetupNodeType::Circle:
		case QBasicSetupNodeType::Particle:
			nodeEntity.x1 += nodeEntity.moveX;
			nodeEntity.y1 += nodeEntity.moveY;
			nodeEntity.centerX = nodeEntity.x1;
			nodeEntity.centerY = nodeEntity.y1;
			break;
		case QBasicSetupNodeType::Rect:
			nodeEntity.centerX += nodeEntity.moveX;
			nodeEntity.centerY += nodeEntity.moveY;
			nodeEntity.x1 = nodeEntity.centerX - (nodeEntity.width / 2);
			nodeEntity.y1 = nodeEntity.centerY - (nodeEntity.height / 2);
			break;
		case QBasicSetupNodeType::Line:
			nodeEntity.centerX += nodeEntity.moveX;
			nodeEntity.centerY += nodeEntity.moveY;
			nodeEntity.x1 += nodeEntity.moveX;
			nodeEntity.y1 += nodeEntity.moveY;
			nodeEntity.x2 += nodeEntity.moveX;
			nodeEntity.y2 += nodeEntity.moveY;
			break;
		case QBasicSetupNodeType::Triangle:
			nodeEntity.centerX += nodeEntity.moveX;
			nodeEntity.centerY += nodeEntity.moveY;
			nodeEntity.x1 += nodeEntity.moveX;
			nodeEntity.y1 += nodeEntity.moveY;
			nodeEntity.x2 += nodeEntity.moveX;
			nodeEntity.y2 += nodeEntity.moveY;
			nodeEntity.x3 += nodeEntity.moveX;
			nodeEntity.y3 += nodeEntity.moveY;
			break;
	}
	setupNodes[index] = nodeEntity;

	// 位置設定
	setLocateNode(index);
}

/**
 *  ノードを拡大
 *  @param index     インデックス
 */
void QBasicScene::scaleNode(int index) {

	auto nodeEntity = setupNodes[index];
	auto showNode = showNodes[index];
	switch (nodeEntity.type) {
		case QBasicSetupNodeType::Text:
		case QBasicSetupNodeType::Image:
		case QBasicSetupNodeType::Particle:
			showNode->setScaleX(nodeEntity.scaleX);
			showNode->setScaleY(nodeEntity.scaleY);
			break;
		case QBasicSetupNodeType::Rect:
			nodeEntity.width *= nodeEntity.scaleX;
			nodeEntity.height *= nodeEntity.scaleY;
			nodeEntity.x1 = nodeEntity.centerX - (nodeEntity.width / 2);
			nodeEntity.y1 = nodeEntity.centerY - (nodeEntity.height / 2);
			break;
		case QBasicSetupNodeType::Circle:
			nodeEntity.width *= nodeEntity.scaleX;
			nodeEntity.height *= nodeEntity.scaleY;
			break;
		case QBasicSetupNodeType::Line:{
			nodeEntity.x1 *= nodeEntity.scaleX;
			nodeEntity.y1 *= nodeEntity.scaleY;
			nodeEntity.x2 *= nodeEntity.scaleX;
			nodeEntity.y2 *= nodeEntity.scaleY;
			double subX = ((nodeEntity.x1 + nodeEntity.x2) / 2 - nodeEntity.centerX);
			double subY = ((nodeEntity.y1 + nodeEntity.y2) / 2 - nodeEntity.centerY);
			nodeEntity.x1 -= subX;
			nodeEntity.y1 -= subY;
			nodeEntity.x2 -= subX;
			nodeEntity.y2 -= subY;
			break;
		}
		case QBasicSetupNodeType::Triangle:{
			nodeEntity.x2 = nodeEntity.x1 + (nodeEntity.x2 - nodeEntity.x1) * nodeEntity.scaleX;
			nodeEntity.y2 = nodeEntity.y1 + (nodeEntity.y2 - nodeEntity.y1) * nodeEntity.scaleY;
			nodeEntity.x3 = nodeEntity.x1 + (nodeEntity.x3 - nodeEntity.x1) * nodeEntity.scaleX;
			nodeEntity.y3 = nodeEntity.y1 + (nodeEntity.y3 - nodeEntity.y1) * nodeEntity.scaleY;
			double subX = ((nodeEntity.x1 + nodeEntity.x2 + nodeEntity.x3) / 3 - nodeEntity.centerX);
			double subY = ((nodeEntity.y1 + nodeEntity.y2 + nodeEntity.y3) / 3 - nodeEntity.centerY);
			nodeEntity.x1 -= subX;
			nodeEntity.y1 -= subY;
			nodeEntity.x2 -= subX;
			nodeEntity.y2 -= subY;
			nodeEntity.x3 -= subX;
			nodeEntity.y3 -= subY;
			break;
		}
	}
	
	if (nodeEntity.type != QBasicSetupNodeType::Text &&
		nodeEntity.type != QBasicSetupNodeType::Image &&
		nodeEntity.type != QBasicSetupNodeType::Particle) {
		setupNodes[index] = nodeEntity;
		// 位置設定
		setLocateNode(index);
	}
}

/**
 *  ノードを回転
 *  @param index     インデックス
 */
void QBasicScene::rotationNode(int index) {
	
	auto nodeEntity = setupNodes[index];
	auto showNode = showNodes[index];
	switch (nodeEntity.type) {
		case QBasicSetupNodeType::Text:
		case QBasicSetupNodeType::Image:
		case QBasicSetupNodeType::Particle:
			showNode->setRotation(nodeEntity.rotation);
			break;
		case QBasicSetupNodeType::Rect:
			
			
			break;
		case QBasicSetupNodeType::Circle:
		case QBasicSetupNodeType::Line:
		case QBasicSetupNodeType::Triangle:
			break;
	}
}

/**
 *  ノードの座標を設定
 *  @param index     インデックス
 */
void QBasicScene::setLocateNode(int index) {
	
	auto nodeEntity = setupNodes[index];
	auto node = showNodes[index];
	
	// 表示設定
	switch (nodeEntity.type) {
		case QBasicSetupNodeType::Text:
		case QBasicSetupNodeType::Image:
		case QBasicSetupNodeType::Particle:{
			node->setPosition(Vec2(nodeEntity.x1, nodeEntity.y1));
			break;
		}
		case QBasicSetupNodeType::Line: {
			auto draw = (DrawNode*)node;
			draw->clear();
			draw->drawSegment(
							  Vec2(nodeEntity.x1, nodeEntity.y1),
							  Vec2(nodeEntity.x2, nodeEntity.y2),
							  nodeEntity.lineWidth, nodeEntity.color
							  );
			break;
		}
		case QBasicSetupNodeType::Rect: {
			auto draw = (DrawNode*)node;
			Vec2 points[] = {
				Vec2(nodeEntity.x1, nodeEntity.y1),
				Vec2(nodeEntity.x1 + nodeEntity.width, nodeEntity.y1),
				Vec2(nodeEntity.x1 + nodeEntity.width, nodeEntity.y1 + nodeEntity.height),
				Vec2(nodeEntity.x1, nodeEntity.y1 + nodeEntity.height),
			};
			draw->clear();
			if (nodeEntity.isFill) {
				draw->drawPolygon(points, 4, nodeEntity.color, nodeEntity.lineWidth, nodeEntity.color);
			} else {
				draw->drawPolygon(points, 4, Color4F(0, 0, 0, 0), nodeEntity.lineWidth, nodeEntity.color);
			}
			break;
		}
		case QBasicSetupNodeType::Circle: {
			auto draw = (DrawNode*)node;
			vector<Vec2> points;
			for (int i = 0;i < CIRCLE_POINT_COUNT;i++) {
				points.push_back(
								 Vec2(nodeEntity.x1 + nodeEntity.width * cos(M_PI / 180 * (90 + 360 * i / CIRCLE_POINT_COUNT)),
									  nodeEntity.y1 + nodeEntity.height * sin(M_PI / 180 * (90 + 360 * i / CIRCLE_POINT_COUNT))
									  )
								 );
			}
			draw->clear();
			if (nodeEntity.isFill) {
				draw->drawPolygon(&points[0], CIRCLE_POINT_COUNT, nodeEntity.color, nodeEntity.lineWidth, nodeEntity.color);
			} else {
				draw->drawPolygon(&points[0], CIRCLE_POINT_COUNT, Color4F(0, 0, 0, 0), nodeEntity.lineWidth, nodeEntity.color);
			}
			break;
		}
		case QBasicSetupNodeType::Triangle: {
			auto draw = (DrawNode*)node;
			Vec2 points[] = {
				Vec2(nodeEntity.x1, nodeEntity.y1),
				Vec2(nodeEntity.x2, nodeEntity.y2),
				Vec2(nodeEntity.x3, nodeEntity.y3),
			};
			draw->clear();
			if (nodeEntity.isFill) {
				draw->drawPolygon(points, 3, nodeEntity.color, nodeEntity.lineWidth, nodeEntity.color);
			} else {
				draw->drawPolygon(points, 3, Color4F(0, 0, 0, 0), nodeEntity.lineWidth, nodeEntity.color);
			}
			break;
		}
	}
}

#pragma mark - タッチ

/**
 *  タッチ初期化
 */
void QBasicScene::initTouch() {

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->setEnabled(true);
	
	// タッチ開始
	listener->onTouchesBegan =  [this](vector<Touch*> touches, Event *event){
		
		// 初期化
		touchBegin.clear();
		touchMove.clear();
		touchEnd.clear();
		
		// 情報を退避
		for (auto it = touches.begin();it != touches.end();it++) {
			touchBegin.push_back((*it)->getLocation());
		}
		
	};
	// タッチ移動
	listener->onTouchesMoved = [this](vector<Touch*> touches, Event *event){
		
		// 初期化
		touchBegin.clear();
		touchMove.clear();
		touchEnd.clear();
		
		// 情報を退避
		for (auto it = touches.begin();it != touches.end();it++) {
			touchMove.push_back((*it)->getLocation());
		}
		
	};
	// タッチ終了
	listener->onTouchesEnded = [this](vector<Touch*> touches, Event *event){
		
		// 初期化
		touchBegin.clear();
		touchMove.clear();
		touchEnd.clear();
		
		// 情報を退避
		removeTouchEndCount = 0;
		for (auto it = touches.begin();it != touches.end();it++) {
			touchEnd.push_back((*it)->getLocation());
		}
		
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

/**
 *  タッチ終了クリア処理
 */
void QBasicScene::clearTouch() {
	// タッチ終了カウント
	if (touchEnd.size() > 0) {
		removeTouchEndCount++;
		// 0.5秒でクリア
		if (removeTouchEndCount >= 30) {
			touchEnd.clear();
			removeTouchEndCount = 0;
		}
	}
}
