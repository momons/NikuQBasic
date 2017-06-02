//
//  QBasicFunctionTypeChangeTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/03.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "StringUtil.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

@interface QBasicFunctionTypeChangeTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicFunctionTypeChangeTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"function_type_change" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// float2int
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
	XCTAssertEqual(interpreter->variables["b"].intValue, 2);
}

/// str2int
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 10);
	XCTAssertEqual(interpreter->variables["b"].intValue, 0);
}

/// bool2int
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
	XCTAssertEqual(interpreter->variables["b"].intValue, 0);
}

/// int2float
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 10.0);
	XCTAssertEqual(interpreter->variables["b"].floatValue, 5.0);
}

/// str2float
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 10.0);
	XCTAssertEqual(interpreter->variables["b"].floatValue, 0.0);
}

/// bool2float
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 1.0);
	XCTAssertEqual(interpreter->variables["b"].floatValue, 0.0);
}

/// int2str
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "10");
	XCTAssertEqual(interpreter->variables["b"].strValue, "20");
}

/// float2str
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "10.5");
	XCTAssertEqual(interpreter->variables["b"].strValue, "20.4");
}

/// bool2str
- (void)test8 {
	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "true");
	XCTAssertEqual(interpreter->variables["b"].strValue, "false");
}

/// int2bool
- (void)test9 {
	interpreter = new QBasic(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
	XCTAssertEqual(interpreter->variables["b"].boolValue, false);
}

/// float2bool
- (void)test10 {
	interpreter = new QBasic(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
	XCTAssertEqual(interpreter->variables["b"].boolValue, false);
}

/// str2bool
- (void)test11 {
	interpreter = new QBasic(nullptr, [scripts[11] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
	XCTAssertEqual(interpreter->variables["b"].boolValue, false);
	XCTAssertEqual(interpreter->variables["c"].boolValue, false);
}

@end
