#import "CDVrtspPlayer.h"

@implementation CDVrtspPlayer

@synthesize viewController;

- (void)showStreamPlayer:(NSString*)url
{
    self.hasPendingOperation = YES;
    
    
    UIStoryboard *sb = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    
    self.streamViewController = [sb instantiateViewControllerWithIdentifier:@"ViewController"];
    
    [self.streamViewController setStreamUrl:url];
    
    [self.viewController presentViewController:self.streamViewController animated:YES completion:nil];
    
}

- (void)playRTSP:(CDVInvokedUrlCommand*) command
{
    CDVPluginResult* pluginResult = nil;
    NSString* streamURL = [command.arguments objectAtIndex:0];
    
    if (streamURL != nil) {
        [self showStreamPlayer:streamURL];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Arg was null"];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

@end
