//
//  QBInterpreterVariableTests.mm
//  QBInterpreterVariableTests
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBInterpreter.h"

/// スクリプト 変数テスト
@interface QBInterpreterVariableTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBInterpreter *interpreter;
}
@end

@implementation QBInterpreterVariableTests

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
	interpreter = new QBInterpreter(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 英数字で宣言
- (void)test1 {
	interpreter = new QBInterpreter(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 記号を混ぜるとコンパイルエラー
- (void)test2 {
	interpreter = new QBInterpreter(nullptr, [scripts[2] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 頭が数字はコンパイルエラー
- (void)test3 {
	interpreter = new QBInterpreter(nullptr, [scripts[3] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 基本ステートメント名と被っているとコンパイルエラー
- (void)test4 {
	interpreter = new QBInterpreter(nullptr, [scripts[4] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// ステートメント名と被っているとコンパイルエラー
- (void)test5 {
	interpreter = new QBInterpreter(nullptr, [scripts[5] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 数値を入れて取り出せるか 1
- (void)test6 {
	interpreter = new QBInterpreter(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 計算式を入れて取り出せるか 15
- (void)test7 {
	interpreter = new QBInterpreter(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "15");
}

/// 違う変数から値を設定できる
- (void)test8 {
	interpreter = new QBInterpreter(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 変数を判定できるか
- (void)test9 {
	interpreter = new QBInterpreter(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 変数同士の判定ができるか
- (void)test10 {
	interpreter = new QBInterpreter(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 変数の２重定義はコンパイルエラー
- (void)test11 {
	interpreter = new QBInterpreter(nullptr, [scripts[11] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

@end
