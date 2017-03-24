//
//  QBAlertViewLauncher.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/06/04.
//
//

#ifndef __NikuQBasic__QBAlertViewLauncher__
#define __NikuQBasic__QBAlertViewLauncher__

#include <string>

using namespace std;

/**
 *  AlertView起動クラス
 */
class QBAlertViewLauncher final
{
public:
	
	/** 表示中フラグ */
	static bool isShow;
	
	/** 戻り値 */
	static string retValue;
	
	/**
	 *  アラート画面起動
	 *  @param title  タイトル
	 *  @param msg    メッセージ
	 *  @param button ボタン
	 */
	static void show(
					 const char *title,
					 const char *msg,
					 const char *button
					 );
	
	
	/**
	 *  確認アラート画面起動
	 *  @param title   タイトル
	 *  @param msg     メッセージ
	 *  @param button1 ボタン
	 *  @param button2 ボタン
	 */
	static void showConfirm(
							const char *title,
							const char *msg,
							const char *button1,
							const char *button2
							);
	
	/**
	 *  入力アラート画面起動
	 *  @param title       タイトル
	 *  @param msg         メッセージ
	 *  @param defaultText デフォルトテキスト
	 */
	static void showInput(
						  const char *title,
						  const char *msg,
						  const char *defaultText
						  );

};

#endif /* defined(__NikuQBasic__QBAlertViewLauncher__) */
