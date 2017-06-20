//
//  QBScriptInfoManager.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/07/06.
//
//

#ifndef __NikuQBasic__QBScriptInfoManager__
#define __NikuQBasic__QBScriptInfoManager__

#include "cocos2d.h"
#include <string>
#include <map>

class QBasicPlists;

using namespace std;
USING_NS_CC;

/**
 *  スクリプトインフォマネージャ
 */
class QBScriptInfoManager {
public:
	
	/** プロジェクトID */
	string projectId;
	
	/** プロジェクト名 */
	string projectName;
	
	/** 画面の向き */
	int orientation;
	
	/** 画面の幅 */
	int screenWidth;
	
	/** 画面の高さ */
	int screenHeight;
	
	/** コピーライト */
	string copyright;
	
	/** 説明 */
	string comment;
	
	/**
	 *  コンストラクタ
	 *  @param projectId プロジェクトId
	 */
	QBScriptInfoManager(string projectId);
	
	/**
	 *  デストラクタ
	 */
	~QBScriptInfoManager();
	
	/**
	 *  読み込み
	 */
	void read();
	
	/**
	 *  書き込み
	 */
	void write();
	
private:
	
	/** ファイルパス */
	string _filePath;
	
	/** plistマネージャ */
	QBasicPlists *_plistManager;
	
};

#endif /* defined(__NikuQBasic__QBScriptInfoManager__) */
