#import <Cordova/CDV.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import "lib/ViewController.h"

@interface CDVrtspPlayer : CDVPlugin{

}

@property (nonatomic, retain) ViewController* streamViewController;
@property (nonatomic, weak) CDVInvokedUrlCommand* lastCommand;

- (void)playRTSP:(CDVInvokedUrlCommand*)command;

- (void)showStreamPlayer:(NSString*)url;


@end
