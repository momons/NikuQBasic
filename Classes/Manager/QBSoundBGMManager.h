//
//  QBSoundBGMManager.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/30.
//
//

#ifndef __NikuQBasic__QBSoundBGMManager__
#define __NikuQBasic__QBSoundBGMManager__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

/**
 *  BGMマネージャ
 */
class QBSoundBGMManager
{
public:
	
	/**
	 *  デストラクタ
	 */
	~QBSoundBGMManager();
	
	/**
	 *  インスタンスシェア
	 *  @return インスタンス変数
	 */
	static QBSoundBGMManager *sharedInstance();
	
	/**
	 *  プリロード
	 *  @param fileName ファイル名
	 */
	void preload(const char *fileName);
	
	/**
	 *  すべて破棄
	 */
	void unload();
	
	/**
	 *  再生
	 *  @param loop ループ可否
	 *  @return 再生可否
	 */
	bool play(bool loop);
	
	/**
	 *  停止
	 */
	void stop();
	
	/**
	 *  一時停止
	 */
	void pause();
	
	/**
	 *  再開
	 */
	void resume();
	
	/**
	 *  ボリューム設定(別にいらないけど)
	 *  @param bgmVolume エフェクト音量 0〜1
	 */
	void volume(float bgmVolume);
	
private:
	
    /** インスタンス変数 */
	static QBSoundBGMManager *_soundBGMManagerInstance;
	
	/** ファイル名 */
	string _fileName;
	
	/**
	 *  初期化
	 */
	static void initialize();
	
	/**
	 *  コンストラクタ
	 */
	QBSoundBGMManager();
	
	/**
	 *  ファイル名を変換
	 *  @param fileName 元ファイル名
	 *  @return 変換ファイル名
	 */
	string editFileName(const char *fileName);
};

#endif
