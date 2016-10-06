#import <Cordova/CDV.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import "MediaStreamingLib/ViewController.h"


@interface rtspPlayer : CDVPlugin


@property (nonatomic, retain) UIViewController* streamViewController;
@property (readwrite, assign) BOOL hasPendingOperation;
@property (nonatomic, weak) CDVInvokedUrlCommand* lastCommand;

- (void)playRTSP:(CDVInvokedUrlCommand*)command;

@end
