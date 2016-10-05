#import "CDVrtspPlayer.h"

@implementation CDVrtspPlayer

@synthesize viewController;



- (void)playRTSP:(CDVInvokedUrlCommand*) command
{
	CDVPluginResult* pluginResult = nil;
	NSString* streamURL = [command.arguments objectAtIndex:0];
	
	if (streamURL != nil) {
		pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
	} else {
		pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Arg was null"];
	}
	[self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

@end
