//
//  main.c
//  Toplogincal
//
//  Created by zyq on 2018/1/23.
//  Copyright © 2018年 hgl. All rights reserved.
//

#include <stdio.h>
#include "custom.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    struct Graph g=init();
    tpcSort(g);
    return 0;
}
