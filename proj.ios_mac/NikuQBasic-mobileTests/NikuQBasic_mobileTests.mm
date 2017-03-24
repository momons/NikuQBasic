//
//  NikuQBasic_mobileTests.m
//  NikuQBasic-mobileTests
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#import <XCTest/XCTest.h>

#import "QBInterpreter.h"

@interface NikuQBasic_mobileTests : XCTestCase

@end

@implementation NikuQBasic_mobileTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
	
	auto interpreter = new QBInterpreter(nullptr, ";sas;alog(\"abc\")", "");

	try {
		interpreter->run();
	} catch(const exception e) {
		NSLog(@"%s", e.what());
	}
	
	delete interpreter;
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
