#include "KittyMemory/MemoryPatch.h"

typedef unsigned long DWORD;
static bool Drive;

  [[noreturn]] void *maps_thread(void *) {
        while (true) {
            auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

//void Bypass() {
    char buff[256];
    FILE *fp;
    fp = fopen("/proc/self/maps", "r");
    DWORD *baddr = NULL, *eaddr = NULL;
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "[anon:libc_malloc]")) {
            sscanf(buff, "%lx-%lx ", &baddr, &eaddr);
            while (baddr < eaddr - 1){
                baddr++;
                if (*(int *)baddr == 117440528){
                    *(int *)baddr = 1073741824;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 117440528){
                    *((int *)baddr + 1) = 1073741824;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 855638022){
                    *(int *)baddr = 1073741824;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 855638022){
                    *((int *)baddr + 1) = 1073741824;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 534752){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 534752){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 735948){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 735948){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 473880){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 473880){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 473880){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 473880){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 1158823830){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 1158823830){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 1073691099){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 1073691099){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 10772480){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 10772480){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 9723904){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 9723904){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 5304320){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 5304320){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 142933568){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 142933568){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 142934208){
                    *(int *)baddr = 0;
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 142934208){
                    *((int *)baddr + 1) = 0;
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
            }
        }
    fclose(fp);
}
auto td = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t1;
            std::this_thread::sleep_for(std::chrono::milliseconds(std::max(std::min(0LL, SLEEP_TIME - td), SLEEP_TIME)));
        }
       return 0;
    }

  [[noreturn]] void *maps1_thread(void *) {
        while (true) {
            auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            
    char buff[256];
    int *modify = 0;
    FILE *fp;
    fp = fopen("/proc/self/maps", "r");
    DWORD *baddr = NULL, *eaddr = NULL;
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);
        if (strstr(buff, "r-xp") != NULL && !feof(fp) && strstr(buff,"/data/app/")) {
            sscanf(buff, "%lx-%lx ", &baddr, &eaddr);
            while (baddr < eaddr - 1){
                baddr++;
                if (*(int *)baddr == 3670080){
                    KittyMemory::memWrite(reinterpret_cast<void *>((int *)baddr), &modify, 4);
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 3670080){
                    KittyMemory::memWrite(reinterpret_cast<void *>(((int *)baddr) + 1), &modify, 4);
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 4194311){
                    KittyMemory::memWrite(reinterpret_cast<void *>((int *)baddr), &modify, 4);
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 4194311){
                    KittyMemory::memWrite(reinterpret_cast<void *>(((int *)baddr) + 1), &modify, 4);
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 139568){
                    KittyMemory::memWrite(reinterpret_cast<void *>((int *)baddr), &modify, 4);
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 139568){
                    KittyMemory::memWrite(reinterpret_cast<void *>(((int *)baddr) + 1), &modify, 4);
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 144,387;133634){
                    KittyMemory::memWrite(reinterpret_cast<void *>((int *)baddr), &modify, 4);
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 144,387;133634){
                    KittyMemory::memWrite(reinterpret_cast<void *>(((int *)baddr) + 1), &modify, 4);
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 134,658;134,658){
                    KittyMemory::memWrite(reinterpret_cast<void *>((int *)baddr), &modify, 4);
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 134,658;134,658){
                    KittyMemory::memWrite(reinterpret_cast<void *>(((int *)baddr) + 1), &modify, 4);
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 134658){
                    KittyMemory::memWrite(reinterpret_cast<void *>((int *)baddr), &modify, 4);
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 134658){
                    KittyMemory::memWrite(reinterpret_cast<void *>(((int *)baddr) + 1), &modify, 4);
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 196864;16842753){
                    KittyMemory::memWrite(reinterpret_cast<void *>((int *)baddr), &modify, 4);
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 196864;16842753){
                    KittyMemory::memWrite(reinterpret_cast<void *>(((int *)baddr) + 1), &modify, 4);
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 133378;144387){
                    KittyMemory::memWrite(reinterpret_cast<void *>((int *)baddr), &modify, 4);
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 133378;144387){
                    KittyMemory::memWrite(reinterpret_cast<void *>(((int *)baddr) + 1), &modify, 4);
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
               if (*(int *)baddr == 133378){
                    KittyMemory::memWrite(reinterpret_cast<void *>((int *)baddr), &modify, 4);
                    LOGE("x8搜索到%lx-%lx", baddr, eaddr);
                }
                if (*((int *)baddr + 1) == 133378){
                    KittyMemory::memWrite(reinterpret_cast<void *>(((int *)baddr) + 1), &modify, 4);
                    LOGE("x4搜索到%lx-%lx", baddr, eaddr);
                }
            }
        }
    fclose(fp);
}
auto td = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t1;
            std::this_thread::sleep_for(std::chrono::milliseconds(std::max(std::min(0LL, SLEEP_TIME - td), SLEEP_TIME)));
        }
       return 0;
    }
    
