#include "ResourceDirectory.h"
#import <Foundation/Foundation.h>

std::string getResourcePath(void) {
    std::string rpath;
    NSBundle* bundle = [NSBundle mainBundle];
    if (bundle != nil) {
        NSString* path = [bundle resourcePath];
        rpath = [path UTF8String] + std::string("/");
    }
    return rpath;
}
