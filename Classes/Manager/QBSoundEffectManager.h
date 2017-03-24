//
//  QBSoundEffectManager.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/30.
//
//

#ifndef __NikuQBasic__QBSoundEffectManager__
#define __NikuQBasic__QBSoundEffectManager__

#include "cocos2d.h"
#include "QBUserDefaultsManager.h"
#include "map"

USING_NS_CC;
using namespace std;

/**
 *  効果音マネージャ
 */
class QBSoundEffectManager
{
public:
	
	/**
	 *  デストラクタ
	 */
	~QBSoundEffectManager();
	
	/**
	 *  インスタンスシェア
	 *  @return インスタンス変数
	 */
	static QBSoundEffectManager *sharedInstance();

	/**
	 *  プリロード
	 *  @param index    インデックス
	 *  @param fileName ファイル名
	 *  @return エフェクトID
	 */
	void preload(int index, const char *fileName);
	
	/**
	 *  すべて破棄
	 */
	void unload();

	/**
	 *  再生
	 *  @param index    インデックス
	 *  @param loop     ループ可否
	 *  @return 再生可否
	 */
	bool play(int index, bool loop);

	/**
	 *  停止
	 *  @param index    インデックス
	 */
	void stop(int index);

	/**
	 *  一時停止
	 *  @param index    インデックス
	 */
	void pause(int index);
	
	/**
	 *  再開
	 *  @param index    インデックス
	 */
	void resume(int index);
	
	/**
	 *  ボリューム(別にいらないけど)
	 *  @param effectVolume エフェクト音量 0〜1
	 */
	void volume(float effectVolume);
	
private:
	
    /** インスタンス変数 */
	static QBSoundEffectManager *_QBSoundEffectManagerInstance;
	
	/** ユーザーデフォルツマネージャー */
	QBUserDefaultsManager *_userDefaultsManager;
	
	/** ファイル名郡 */
	map<int, string> _fileName;
	
	/** 再生ID郡 */
	map<int, unsigned int> _soundID;
	
	/**
	 *  初期化
	 */
	static void initialize();
	
	/**
	 *  コンストラクタ
	 */
	QBSoundEffectManager();

	/**
	 *  ファイル名を変換
	 *  @param fileName 元ファイル名
	 *  @return 変換ファイル名
	 */
	string editFileName(const char *fileName);
};

#endif /* defined(__NikuQBasic__QBSoundEffectManager__) */
