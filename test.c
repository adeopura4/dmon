#include <stdio.h>

#define DMON_IMPL
#include "dmon.h"

#if DMON_OS_LINUX
#include "dmon_extra.h"
#endif

/*
adeopura: This code can be ignored for now/
struct pre_signed_request_data {
    char * filename;
    int fileSize;
    char folderToken[512];
};

static void onCreate(const char* rootdir, const char* filepath) {
    char test[512];
    strcpy(test, filepath);

    struct pre_signed_request_data requestData = {test, 44,"token"};

    printf("creating: %s\n", requestData.filename);
}
*/

static void watch_callback(dmon_watch_id watch_id, dmon_action action, const char* rootdir,
                           const char* filepath, const char* oldfilepath, void* user)
{
    (void)(user);
    (void)(watch_id);

    switch (action) {
    case DMON_ACTION_CREATE:
        printf("CREATE: [%s]%s\n", rootdir, filepath);
        //onCreate(rootdir, filepath);
        break;
    case DMON_ACTION_DELETE:
        printf("DELETE: [%s]%s\n", rootdir, filepath);
        break;
    case DMON_ACTION_MODIFY:
        printf("MODIFY: [%s]%s\n", rootdir, filepath);
        break;
    case DMON_ACTION_MOVE:
        printf("MOVE: [%s]%s -> [%s]%s\n", rootdir, oldfilepath, rootdir, filepath);
        break;
    }
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        dmon_init();
        puts("waiting for changes ..");
        dmon_watch(argv[1], watch_callback, DMON_WATCHFLAGS_RECURSIVE, NULL);
        getchar();
        dmon_deinit();
    } else {
        puts("usage: test dirname");
    }
    return 0;
}
