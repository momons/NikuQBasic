//
//  QBSoundEffectManager.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/30.
//
//

#include "QBSoundEffectManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

/** インスタンス変数 */
QBSoundEffectManager * QBSoundEffectManager::_QBSoundEffectManagerInstance = NULL;

/**
 *  インスタンスシェア
 *  @return インスタンス変数
 */
QBSoundEffectManager * QBSoundEffectManager::sharedInstance() {
	
	static once_flag flag;
	
	// 一度だけコール
	call_once(flag, initialize);
	
	return _QBSoundEffectManagerInstance;
}

/**
 *  初期化
 */
void QBSoundEffectManager::initialize() {
	_QBSoundEffectManagerInstance = new QBSoundEffectManager();
}

/**
 *  コンストラクタ
 */
QBSoundEffectManager::QBSoundEffectManager() {
}

/**
 *  デストラクタ
 */
QBSoundEffectManager::~QBSoundEffectManager() {
	// 破棄
	unload();
	
	_QBSoundEffectManagerInstance = NULL;
}

/**
 *  プリロード
 *  @param index    インデックス
 *  @param fileName ファイル名
 *  @return エフェクトID
 */
void QBSoundEffectManager::preload(int index, const char *fileName) {
	
	// 既存にあるかチェック
	auto findFile = _fileName.find(index);
	if (findFile != _fileName.end()) {
		if (_fileName[index].compare(fileName) == 0) {
			// ファイル名も一緒なのでスルー
			return;
		}
	}
	
	// ファイルをロード
	SimpleAudioEngine::getInstance()->preloadEffect(editFileName(fileName).c_str());
	
	// ファイルを追加
	_fileName[index] = fileName;
	_soundID[index] = 0;
}

/**
 *  すべて破棄
 */
void QBSoundEffectManager::unload() {
	// 特に追加なし
	if(_fileName.empty()){
		return;
	}

	// 破棄する
	for (auto it = _fileName.begin();it != _fileName.end();it++) {
		string oneFileName = (*it).second;
		SimpleAudioEngine::getInstance()->unloadEffect(editFileName(oneFileName.c_str()).c_str());
	}
	
	// 解放
	_fileName.clear();
	_soundID.clear();
}

/**
 *  再生
 *  @param index    インデックス
 *  @param loop     ループ可否
 *  @return 再生可否
 */
bool QBSoundEffectManager::play(int index, bool loop) {
	
	// 既存にあるかチェック
	auto findFile = _fileName.find(index);
	if (findFile == _fileName.end()) {
		return false;
	}
	
	// 再生
	string oneFileName = _fileName[index];
	unsigned int soundID = SimpleAudioEngine::getInstance()->playEffect(editFileName(oneFileName.c_str()).c_str(),loop);
	
	// サウンドIDを退避
	_soundID[index] = soundID;
	
	return true;
}

/**
 *  停止
 *  @param index    インデックス
 */
void QBSoundEffectManager::stop(int index) {
	
	// 既存にあるかチェック
	auto findFile = _soundID.find(index);
	if (findFile == _soundID.end()) {
		return;
	}

	// 停止
	SimpleAudioEngine::getInstance()->stopEffect(_soundID[index]);
}

/**
 *  一時停止
 *  @param index    インデックス
 */
void QBSoundEffectManager::pause(int index) {
	
	// 既存にあるかチェック
	auto findFile = _soundID.find(index);
	if (findFile == _soundID.end()) {
		return;
	}
	
	// 停止
	SimpleAudioEngine::getInstance()->stopEffect(_soundID[index]);
}

/**
 *  再開
 *  @param index    インデックス
 */
void QBSoundEffectManager::resume(int index) {
	
	// 既存にあるかチェック
	auto findFile = _soundID.find(index);
	if (findFile == _soundID.end()) {
		return;
	}
	
	// 停止
	SimpleAudioEngine::getInstance()->resumeEffect(_soundID[index]);
}

/**
 *  ボリューム(別にいらないけど)
 *  @param effectVolume エフェクト音量 0〜1
 */
void QBSoundEffectManager::volume(float effectVolume) {
	SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
}

/**
 *  ファイル名を変換
 *  @param fileName 元ファイル名
 *  @return 変換ファイル名
 */
string QBSoundEffectManager::editFileName(const char *fileName) {
	
	string returnFileName;
	Application::Platform platform = Application::getInstance()->getTargetPlatform();
	if (platform == Application::Platform::OS_IPHONE || platform == Application::Platform::OS_IPAD) {
		returnFileName = StringUtils::format("%s.m4a",fileName);
	} else {
		returnFileName = StringUtils::format("%s.ogg",fileName);
	}
	return returnFileName;
}