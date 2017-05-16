//
//  QBasicVariableTests.mm
//  QBasicVariableTests
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// スクリプト 変数テスト
@interface QBasicVariableTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicVariableTests

- (void)setUp {
    [super setUp];

	NSString *script = [TestFileUtils loadFile:@"variable" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
    [super tearDown];
}

/// 英字のみ宣言
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 英数字で宣言
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 記号を混ぜるとコンパイルエラー
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 頭が数字はコンパイルエラー
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 基本ステートメント名と被っているとコンパイルエラー
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// ステートメント名と被っているとコンパイルエラー
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 数値を入れて取り出せるか 1
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 計算式を入れて取り出せるか 15
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 15);
}

/// 違う変数から値を設定できる
- (void)test8 {
	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 変数を判定できるか
- (void)test9 {
	interpreter = new QBasic(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 変数同士の判定ができるか
- (void)test10 {
	interpreter = new QBasic(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 変数の２重定義はコンパイルエラー
- (void)test11 {
	interpreter = new QBasic(nullptr, [scripts[11] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// func内に２重定義すれば大丈夫
- (void)test12 {
	interpreter = new QBasic(nullptr, [scripts[12] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// func内の２重定義はダメ
- (void)test13 {
	interpreter = new QBasic(nullptr, [scripts[13] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// funcの引数名とグローバル変数が２重定義はOK
- (void)test14 {
	interpreter = new QBasic(nullptr, [scripts[14] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// funcの引数名で２重定義はダメ
- (void)test15 {
	interpreter = new QBasic(nullptr, [scripts[15] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

@end
