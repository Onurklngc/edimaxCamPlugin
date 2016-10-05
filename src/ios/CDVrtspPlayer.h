#import <Cordova/CDV.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import "MediaStreamingLib/ViewController.h"


@interface CDVrtspPlayer : CDVPlugin {

}
- (void)playRTSP:(CDVInvokedUrlCommand*)command;

@end
