//
//  CustomDirector.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/01/11.
//
//

#ifndef CustomDirector_h
#define CustomDirector_h

/// カスタムディレクター
class CustomDirector: public Director {
public:
	template<class T> void popSceneWithTransition(float duration) {
		CCASSERT(_runningScene != NULL, "running scene should not null");
		
		_scenesStack.popBack();
		ssize_t c = _scenesStack.size();
		if (c == 0) {
			end();
			return;
		}
		
		Scene *scene = (Scene *)T::create(duration, (Scene *)_scenesStack.at(c - 1));
		_scenesStack.replace(c - 1, scene);
		_sendCleanupToScene = true;
		_nextScene = (Scene*)_scenesStack.at(c - 1);
	}
};

#endif /* CustomDirector_h */
