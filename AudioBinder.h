//
//  Copyright (c) 2009, Oleksandr Tymoshenko <gonzo@bluezbox.com>
//  All rights reserved.
// 
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//  1. Redistributions of source code must retain the above copyright
//     notice unmodified, this list of conditions, and the following
//     disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
// 
//  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  SUCH DAMAGE.
//

#import <Cocoa/Cocoa.h>

#include <AudioToolbox/AudioFormat.h>
#include <AudioToolbox/ExtendedAudioFile.h>

@protocol AudioBinderDelegate

-(void) updateStatus: (NSString *)filename handled:(UInt64)handledFrames total:(UInt64)totalFrames;
-(void) conversionStart: (NSString*)filename 
                 format: (AudioStreamBasicDescription*)format
      formatDescription: (NSString*)description
                 length: (UInt64)frames;
-(BOOL) continueFailedConversion:(NSString*)filename reason:(NSString*)reason;
-(void) conversionFinished: (NSString*)filename;
-(void) audiobookReady: (NSString*)filename duration: (UInt32)seconds;

@end


@interface AudioBinder : NSObject {
    NSMutableArray *_inFiles;
    NSString *_outFileName;
    ExtAudioFileRef _outAudioFile;
    UInt32 _outFileLength;
    id _delegate;
}

-(id) init;
-(void) setDelegate: (id <AudioBinderDelegate>)delegate;
-(void) addInputFile: (NSString*)fileName;
-(void) setOutputFile: (NSString*)outFileName;
-(BOOL) convert;
-(BOOL) openOutFile;
-(void) closeOutFile;
-(BOOL) convertOneFile: (NSString*)inFileName reason: (NSString**)reason;

@end

