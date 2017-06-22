//
//  QBasicUrlEncodeTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/22.
//
//

#import <XCTest/XCTest.h>

#import "QBasicUrlEncode.h"

/// QBasicUrlEncodeTestsクラスのテスト
@interface QBasicUrlEncodeTests : XCTestCase

@end

@implementation QBasicUrlEncodeTests

- (void)setUp {
    [super setUp];
}

- (void)tearDown {
    [super tearDown];
}

/// URLエンコードして、デコードして同じ文字かをチェック
- (void)test0 {
	string value = "あいうえおかきくえこさしすせそたちつてと";
	auto encode = QBasicUrlEncode::encode(value);
	auto decode = QBasicUrlEncode::decode(encode);
	XCTAssertEqual(value, decode);
}

@end
