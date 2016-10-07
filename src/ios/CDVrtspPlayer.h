#import <Cordova/CDV.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>


@interface CDVrtspPlayer : CDVPlugin{

}

@property (readwrite, assign) BOOL hasPendingOperation;
@property (nonatomic, weak) CDVInvokedUrlCommand* lastCommand;

- (void)playRTSP:(CDVInvokedUrlCommand*)command;

- (void)showStreamPlayer:(NSString*)url;


@end
