//
//  main.m
//  Test5
//
//  Created by Brandon Fogerty on 8/23/13.
//  Copyright (c) 2013 Brandon Fogerty. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "Engine.h"

NSApplication *app;
NSWindow *window;

int main(int argc, char *argv[])
{
    app = [NSApplication sharedApplication];
    
    NSRect windowRect = NSMakeRect(10.0f, 10.0f, 800.0f, 600.0f);
    window = [[NSWindow alloc] initWithContentRect:windowRect styleMask:( NSResizableWindowMask | NSClosableWindowMask | NSTitledWindowMask) backing:NSBackingStoreBuffered defer:NO];
    
    [window makeKeyAndOrderFront:nil];
    [window setTitle:@"xdpixelengine"];
    
    
    if ([app respondsToSelector:@selector(run)])
	{
		[app
         performSelectorOnMainThread:@selector(run)
         withObject:nil
         waitUntilDone:YES];
	}
    
    
    return 0;
}

void run()
{
    //	[self finishLaunching];
	[[NSNotificationCenter defaultCenter]
     postNotificationName:NSApplicationWillFinishLaunchingNotification
     object:NSApp];
	[[NSNotificationCenter defaultCenter]
     postNotificationName:NSApplicationDidFinishLaunchingNotification
     object:NSApp];
	
	do
	{
		NSEvent *event =
        [app
         nextEventMatchingMask:NSAnyEventMask
         untilDate:[NSDate distantFuture]
         inMode:NSDefaultRunLoopMode
         dequeue:YES];
		
		[app sendEvent:event];
		[app updateWindows];
	} while (1==1);
}
