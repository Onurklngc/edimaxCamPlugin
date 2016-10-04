//
//  LifeLibrary.h
//  LifeLibrary
//
//  Created by HikaruBB on 2016/6/7.
//  Copyright © 2016年 HikaruBB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

@protocol LifeLibraryDelegate <NSObject>

@optional
- (void)callbackFailWithErrorCode:(int)errorCode job:(int)job jobType:(int)jobType;
- (void)callbackCommandData:(int)job jobType:(int)jobType data:(char *)data dataSize:(int)dataSize;
- (void)callbackAudioIn:(unsigned char *)audioData dataSize:(int)dataSize format:(int)format;

@end

typedef enum
{
    State_Unknow,
    State_Connecting,
    State_Connected,
    State_LoginOK,
    State_DoRTSP,
    State_Teardown,
    State_Dissconnect,
    State_TunnelClose,
    State_TunnelOpening,
    State_TunnelOpened,
    State_ConnectionError,
    State_UserPasswordError,
    State_TooManyUser
} LifeLibrary_State;

typedef enum
{
    DirectionUp,
    DirectionDown,
    DirectionLeft,
    DirectionRight,
    DirectionLeftUp,
    DirectionLeftDown,
    DirectionRightUp,
    DirectionRightDown
} PanTilt_Direction;

typedef enum
{
    TUNNEL_RULE_AUTO,       // LAN + Cloud
    TUNNEL_RULE_CLOUD_ONLY, // P2P or Relay
    TUNNEL_RULE_P2P_ONLY,	// P2P
    TUNNEL_RULE_RELAY_ONLY,	// Relay
    TUNNEL_RULE_LAN_P2P,	// LAN or P2P
    TUNNEL_RULE_LAN_RELAY,	// LAN or Relay
    TUNNEL_RULE_LAN_ONLY,	// LAN
} LifeLibrary_ConnectType;

typedef enum
{
    AUDIO_FORMAT_PCM_8000_1,  // PCM
    AUDIO_FORMAT_PCM_16000_2, // AAC
    AUDIO_FORMAT_PCM_16000_1  // ADPCM
} Audio_In_Format;

typedef enum
{
    AUDIO_OUT_FORAMT_PCM_8000_1_TO_GSM,
    AUDIO_OUT_FORAMT_PCM_16000_1_TO_ADPCM,
    AUDIO_OUT_FORAMT_PCM_8000_1_TO_MULAW
} Audio_Out_Format;

//=================================================
// Jobs
//=================================================
#define	LIFE_JOB_NONE					0
#define	LIFE_JOB_CONNECT				1
#define	LIFE_JOB_DISCONNECT				2
#define	LIFE_JOB_RELEASE				3

#define	LIFE_JOB_LOGIN					10
#define	LIFE_JOB_CUSTOM_CGI				11
#define	LIFE_JOB_GET_ALL_INFO			12
#define	LIFE_JOB_GET_WIFI_LIST			13

#define	LIFE_JOB_SET_TIMEZONE			20
#define	LIFE_JOB_SET_WIFI_CONFIG		21

#define	LIFE_JOB_SEARCH					90
#define	LIFE_JOB_KEEP_ALIVE				91

// IP Camera
#define	LIFE_JOB_GET_SNAPSHOT  			100
#define	LIFE_JOB_START_RTSP  			101
#define	LIFE_JOB_STOP_RTSP				102

#define	LIFE_JOB_PAN_TILT 				110
#define	LIFE_JOB_GET_EVENT_LIST			111
#define	LIFE_JOB_GET_EVENT_FILE			112

#define	LIFE_JOB_START_SEND_AUDIO		150
#define	LIFE_JOB_SEND_AUDIO				151
#define	LIFE_JOB_STOP_SEND_AUDIO		152

#define	LIFE_JOB_START_READ_AVI_FILE	160
#define	LIFE_JOB_STOP_READ_AVI_FILE		161

//smart plug
#define	LIFE_JOB_SET_POWER_SWITCH		200
#define	LIFE_JOB_GET_CURRENT_METER		201
#define	LIFE_JOB_GET_POWER_STATUS		202

//=================================================
// Return Code
//=================================================
#define LIFE_ERR_SUCCESS				0

#define LIFE_ERR_RELEASE				-1
#define LIFE_ERR_INVLIDE_JOB			-2
#define LIFE_ERR_SIZE					-3
#define LIFE_ERR_INDEX					-4
#define LIFE_ERR_PARSER					-5
#define LIFE_ERR_FORMAT					-6
#define LIFE_ERR_PNV_V1					-7

#define LIFE_ERR_DEVICE_NOT_FOUND		-10
#define LIFE_ERR_CLOUD_NOT_FOUND		-11
#define LIFE_ERR_CLOUD_NO_RESPONSE		-12
#define LIFE_ERR_DEVICE_FW_OLD			-13
#define LIFE_ERR_CLIENT_FW_OLD			-14
#define LIFE_ERR_DEVICE_FW_UPGRADING	-15

#define LIFE_ERR_TUNNEL_CLOSED			-20
#define LIFE_ERR_TUNNEL_OPENED			-21
#define LIFE_ERR_TUNNEL_OPENING			-22
#define LIFE_ERR_TUNNEL_CLOSING			-23
#define LIFE_ERR_CONNECTION_FAILED		-24
#define LIFE_ERR_TIMEOUT				-25

#define LIFE_ERR_PASSWORD				-30
#define LIFE_ERR_CMD_NOT_SUPPORT		-31
#define LIFE_ERR_TOO_MANY				-32
#define LIFE_ERR_DIGEST					-33
#define LIFE_ERR_JOB_RUNNING			-34

#define LIFE_ERR_OPEN_FILE				-40
#define LIFE_ERR_FILE_INFO				-41

@interface LifeLibrary : NSObject
{
    
@private
    NSString *cloudIP;
    Audio_Out_Format audioOutFormat, audioInFormat;
    NSMutableArray *_camsArray;
}

@property (nonatomic, assign) LifeLibrary_State state;
@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *macAddress;
@property (nonatomic, retain) NSString *username;
@property (nonatomic, retain) NSString *password;
@property (nonatomic, retain) NSString *hostname;
@property (nonatomic, retain) NSNumber *port;
@property (nonatomic, retain) NSNumber *rtspPort;
@property (nonatomic, retain) NSString *rtspPath;
@property (nonatomic, retain) NSNumber *model;
@property (weak, nonatomic) UIImage *image;

@property (nonatomic, assign) id<LifeLibraryDelegate> delegate;

- (void)doSearch;
- (void)initWithCloudIP:(NSString *)cloudServeIP;
- (void)connectWithLifeAPI:(int)job connectType:(int)connectType jobType:(int)jobType command:(NSString *)command;

- (void)returnCommandData:(int)job jobType:(int)jobType data:(char *)data dataSize:(int)dataSize;
- (void)replaceImage:(UIImage*)image;
- (void)returnFailWithErrorCode:(int)errorCode job:(int)job jobType:(int)jobType;
- (void)getAudioIn:(unsigned char *)audioData dataSize:(int)dataSize format:(int)format;

- (void)prepareToSendAudio:(Audio_Out_Format)format buffer:(unsigned char)buffer bufferSize:(int)bufferSize;
- (void)sendAudio:(unsigned char)buffer bufferSize:(int)bufferSize;
- (void)stopAudio;

@end
