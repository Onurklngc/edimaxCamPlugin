//
//  ViewController.m
//  LifeLibExample
//
//  Created by HikaruBB on 2016/6/8.
//  Copyright © 2016年 HikaruBB. All rights reserved.
//

#import "ViewController.h"
#include "LifeLibrary.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)callbackFailWithErrorCode:(int)errorCode job:(int)job jobType:(int)jobType
{
    NSLog(@"Error code:%d, Job:%d, JobType:%d", errorCode, job, jobType);
    
    //=================================================
    // Error code : see //Return Code// in LifeLibrary.h
    //=================================================
    
    //=================================================
    // Job : see //Jobs// in LifeLibrary.h
    //=================================================
    
    //=================================================
    // Job Type : CustomCGI likes LifeLibrary_CustomJobType
    //=================================================
}

- (void)callbackCommandData:(int)job jobType:(int)jobType data:(char *)data dataSize:(int)dataSize
{
    NSString *str = [[NSString alloc] initWithUTF8String:data];
    
    str = [str stringByReplacingOccurrencesOfString:@"\r" withString:@""];
    str = [str stringByReplacingOccurrencesOfString:@"\n" withString:@""];
    str = [str stringByReplacingOccurrencesOfString:@"\t" withString:@""];
    
    if (job == LIFE_JOB_CONNECT || job == LIFE_JOB_SEARCH)
    {
        NSData *data = [str dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *jsonDictionary = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:nil];
        
        if (job == LIFE_JOB_SEARCH)
            jsonDictionary = [jsonDictionary objectForKey:@"search"];
        
        NSLog(@"%@", jsonDictionary);
    }
    else if (job == LIFE_JOB_LOGIN)
    {
        ////Data format -> XML
        lib.state = State_LoginOK;
        NSLog(@"%@", str);
        
        //=================================================
        // Path and port -> Parse from str
        //=================================================
        lib.rtspPath = @"ipcam_h264.sdp";
        lib.rtspPort = [NSNumber numberWithInt:554];
        [lib connectWithLifeAPI:LIFE_JOB_START_RTSP connectType:TUNNEL_RULE_AUTO jobType:0 command:nil];
    }
}

- (void)callbackAudioIn:(unsigned char *)audioData dataSize:(int)dataSize format:(int)format
{
    NSLog(@"Audio in");
}

- (IBAction)initLib:(id)sender
{
    lib = [[LifeLibrary alloc] init];
    lib.delegate = self;
    [lib initWithCloudIP:@"122.248.252.67"];
    
    _label.numberOfLines = 0;
}

- (IBAction)doSeatch:(id)sender
{
    [lib doSearch];
}
- (IBAction)connectDevice:(id)sender
{
  //  lib.macAddress = @"74DA38629873";
    lib.username = @"admin";
    lib.password = @"1234";
    
    [lib addObserver:self forKeyPath:@"state" options:NSKeyValueObservingOptionNew context:NULL];
    [lib addObserver:self forKeyPath:@"image" options:NSKeyValueObservingOptionNew context:NULL];
    
    [lib connectWithLifeAPI:LIFE_JOB_CONNECT connectType:TUNNEL_RULE_AUTO jobType:0 command:nil];
    
    //=================================================
    //  You can order the following job by connectWithLifeAPI
    //    LIFE_JOB_CONNECT
    //    LIFE_JOB_DISCONNECT
    //    LIFE_JOB_LOGIN
    //    LIFE_JOB_GET_SNAPSHOT
    //    LIFE_JOB_START_RTSP
    //    LIFE_JOB_STOP_RTSP
    //    LIFE_JOB_START_READ_AVI_FILE
    //    LIFE_JOB_STOP_READ_AVI_FILE
    //    LIFE_JOB_PAN_TILT
    
    //  You also can order other command by connectWithLifeAPI
    //    LIFE_JOB_CUSTOM_CGI
    //    [lib connectWithLifeAPI:LIFE_JOB_CUSTOM_CGI connectType:TUNNEL_RULE_AUTO jobType:Job_DoEvent command:@"/camera-cgi/getEventJPEG.cgi"];
    //=================================================
}

- (void)setStreamUrl:(NSString *)url{
    if (url == nullable || url = @"") {
        lib.macAddress = @"74DA38629873";
    } else lib.macAddress = url;
}


- (IBAction)sendAudio:(id)sender
{
    //=================================================
    // Send Audio
    // 1. You need to collect sound and ensure format.
    // 2. [lib prepareToSendAudio:LIFE_AUDIO_OUT_FORAMT_PCM_16000_1_TO_ADPCM buffer:buf bufferSize:size] in first time.
    // 3. [lib sendAudio:buf bufferSize:size];
    //=================================================
}

- (IBAction)stopAuido:(id)sender
{
    [lib stopAudio];
}

- (IBAction)pantilt:(id)sender
{
    //=================================================
    // Job : see //PanTilt_Direction// in LifeLibrary.h
    //=================================================
    
    UIButton *btn = (UIButton *)sender;
    [lib connectWithLifeAPI:LIFE_JOB_PAN_TILT connectType:TUNNEL_RULE_AUTO jobType:(int)btn.tag command:nil];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    if ([keyPath isEqualToString:@"state"])
    {
        dispatch_async(dispatch_get_main_queue(), ^
        {
            LifeLibrary *obj = object;
            
            NSString *str;
            
            switch (obj.state)
            {
                case State_Connecting:
                    str = @"Connecting";
                    break;
                case State_Connected:
                    str = @"Connect OK";
                    break;
                case State_LoginOK:
                    str = @"Login OK";
                    break;
                case State_DoRTSP:
                    str = @"Start RTSP";
                    break;
                case State_Teardown:
                    str = @"Stop RTSP";
                    break;
                    
                default:
                    break;
            }
            
            _label.text = str;
        });
    }
    else if ([keyPath isEqualToString:@"image"])
    {
        LifeLibrary *obj = object;
        _imgview.image = obj.image;
    }
}

@end
