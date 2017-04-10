//
//  QBInterpreterFuncTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/11.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBInterpreter.h"

@interface QBInterpreterFuncTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBInterpreter *interpreter;
}
@end

@implementation QBInterpreterFuncTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"func" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// 引数なし
- (void)test0 {
	interpreter = new QBInterpreter(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 引数あり
- (void)test1 {
	interpreter = new QBInterpreter(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 関数名に予約語を使用
- (void)test2 {
	interpreter = new QBInterpreter(nullptr, [scripts[2] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 変数名がかぶっている
- (void)test3 {
	interpreter = new QBInterpreter(nullptr, [scripts[3] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 引数の変数名がかぶっている
- (void)test4 {
	interpreter = new QBInterpreter(nullptr, [scripts[4] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// funcの中にfunc
- (void)test5 {
	interpreter = new QBInterpreter(nullptr, [scripts[5] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 同一funcを二重定義
- (void)test6 {
	interpreter = new QBInterpreter(nullptr, [scripts[6] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

@end
