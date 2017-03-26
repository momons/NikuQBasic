//
//  QBInterpreterIfTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/25.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBInterpreter.h"

@interface QBInterpreterIfTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBInterpreter *interpreter;
}
@end

@implementation QBInterpreterIfTests

- (void)setUp {
    [super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"if" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
    [super tearDown];
}

/// イコール
- (void)test0 {
	interpreter = new QBInterpreter(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// ノットイコール
- (void)test1 {
	interpreter = new QBInterpreter(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 小なり
- (void)test2 {
	interpreter = new QBInterpreter(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 小なりイコール
- (void)test3 {
	interpreter = new QBInterpreter(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 大なり
- (void)test4 {
	interpreter = new QBInterpreter(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 大なりイコール
- (void)test5 {
	interpreter = new QBInterpreter(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// and
- (void)test6 {
	interpreter = new QBInterpreter(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// or
- (void)test7 {
	interpreter = new QBInterpreter(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// xor
- (void)test8 {
	interpreter = new QBInterpreter(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// not
- (void)test9 {
	interpreter = new QBInterpreter(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// else
- (void)test10 {
	interpreter = new QBInterpreter(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// elseif
- (void)test11 {
	interpreter = new QBInterpreter(nullptr, [scripts[11] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// elseifその２
- (void)test12 {
	interpreter = new QBInterpreter(nullptr, [scripts[12] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 文字比較イコール
- (void)test13 {
	interpreter = new QBInterpreter(nullptr, [scripts[13] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 文字比較ノットイコール
- (void)test14 {
	interpreter = new QBInterpreter(nullptr, [scripts[14] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 文字比較小なり
- (void)test15 {
	interpreter = new QBInterpreter(nullptr, [scripts[15] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 文字比較小なりイコール
- (void)test16 {
	interpreter = new QBInterpreter(nullptr, [scripts[16] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 文字比較大なり
- (void)test17 {
	interpreter = new QBInterpreter(nullptr, [scripts[17] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// 文字比較大なりイコール
- (void)test18 {
	interpreter = new QBInterpreter(nullptr, [scripts[18] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// if文の中にif文
- (void)test19 {
	interpreter = new QBInterpreter(nullptr, [scripts[19] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

/// else２個でコンパイルエラー
- (void)test20 {
	interpreter = new QBInterpreter(nullptr, [scripts[20] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// elseの後にelseifでコンパイルエラー
- (void)test21 {
	interpreter = new QBInterpreter(nullptr, [scripts[21] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

@end
