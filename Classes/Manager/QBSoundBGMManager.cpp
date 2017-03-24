//
//  QBSoundBGMManager.cpp
//  ALotOfB
//
//  Created by Hara Kazunari on 2013/10/28.
//
//

#include "QBSoundBGMManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

/** インスタンス変数 */
QBSoundBGMManager * QBSoundBGMManager::_soundBGMManagerInstance = NULL;

/**
 *  インスタンスシェア
 *  @return インスタンス変数
 */
QBSoundBGMManager * QBSoundBGMManager::sharedInstance() {
	
	static once_flag flag;
	
	// 一度だけコール
	call_once(flag, initialize);
	
	return _soundBGMManagerInstance;
}

/**
 *  初期化
 */
void QBSoundBGMManager::initialize() {
	_soundBGMManagerInstance = new QBSoundBGMManager();
}

/**
 *  コンストラクタ
 */
QBSoundBGMManager::QBSoundBGMManager() {
}

/**
 *  デストラクタ
 */
QBSoundBGMManager::~QBSoundBGMManager() {
	// 破棄
	unload();
	
	_soundBGMManagerInstance = NULL;
}

/**
 *  プリロード
 *  @param fileName ファイル名
 */
void QBSoundBGMManager::preload(const char *fileName) {
	// ファイル名退避
	_fileName = fileName;
	
	// ファイルをロード
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(editFileName(_fileName.c_str()).c_str());
}

/**
 *  すべて破棄
 */
void QBSoundBGMManager::unload() {
	// 前の情報を削除
	_fileName = "";
}

/**
 *  再生
 *  @param loop ループ可否
 *  @return 再生可否
 */
bool QBSoundBGMManager::play(bool loop) {
	
	// サウンドOFF
//	if(!_userDefaultsManager->entity->soundOnOff){
//		return false;
//	}
	
	// 範囲外
	if(_fileName.empty()){
		return false;
	}
	
	// 再生
	SimpleAudioEngine::getInstance()->playBackgroundMusic(editFileName(_fileName.c_str()).c_str(), loop);
	
	return true;
}

/**
 *  停止
 */
void QBSoundBGMManager::stop() {
	
	// 範囲外
	if(_fileName.empty()){
		return;
	}
	
	// 停止
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
}

/**
 *  一時停止
 */
void QBSoundBGMManager::pause() {
	
	// 範囲外
	if(_fileName.empty()){
		return;
	}
	
	// 停止
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

/**
 *  再開
 */
void QBSoundBGMManager::resume() {
	
	// サウンドOFF
//	if(!_userDefaultsManager->entity->soundOnOff){
//		return;
//	}
	
	// 範囲外
	if(_fileName.empty()){
		return;
	}
	
	// 再生してなければ再生
	if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
		// 再生
		play(true);
	}else {
		// 再再生
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

/**
 *  ボリューム設定(別にいらないけど)
 *  @param bgmVolume エフェクト音量 0〜1
 */
void QBSoundBGMManager::volume(float bgmVolume) {
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(bgmVolume);
}

/**
 *  ファイル名を変換
 *  @param fileName 元ファイル名
 *  @return 変換ファイル名
 */
string QBSoundBGMManager::editFileName(const char *fileName) {
	string returnFileName;
	Application::Platform platform = Application::getInstance()->getTargetPlatform();
	if (platform == Application::Platform::OS_IPHONE || platform == Application::Platform::OS_IPAD){
		returnFileName = StringUtils::format("%s.m4a",fileName);
	}else {
		returnFileName = StringUtils::format("%s.ogg",fileName);
	}
	return returnFileName;
}
