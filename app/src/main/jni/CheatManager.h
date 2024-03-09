#pragma once

// Created by SPraditya

struct MAPS
{
    long int addr;
    long int taddr;
    int type;
    struct MAPS *next;
};
typedef struct MAPS *PMAPS;
#define LEN sizeof(struct MAPS)

enum S_PRA_API TYPES
{
    TYPE_DWORD,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_WORD,
    TYPE_BYTE,
    TYPE_QWORD,
};
enum Range
{
    ALL,
    B_BAD,
    V,
    C_ALLOC,
    C_BSS,
    CODE_APP,
    C_DATA,
    C_HEAP,
    JAVA_HEAP,
    A_ANONMYOUS,
    CODE_SYSTEM,
    STACK,
    ASHMEM
};

int handle = -1;
int count = -1;
int searchRange = 0;
int resCount = 0;
PMAPS res = NULL;

enum LogPriority {
        TraceP, DebugP, InfoP, WarnP, ErrorP, FatalP, CriticalP, Succes
};

class BasicLogger
{
  public:
      static LogPriority verbosity;
      static const char* filepath;
      
      static void SetVerbosity(LogPriority new_priority) {
          verbosity = new_priority;
      }
      
      static void Log(LogPriority priority, const char* message) 
      {
          if (priority >= verbosity) {
              std::ofstream FILE(filepath, std::ios_base::app);
              switch (priority) {
                  case TraceP:
                      FILE << "Trace:\t";
                      break;
                  case DebugP:
                      FILE << "Debug:\t";
                      break;
                  case InfoP: 
                      FILE << "Info:\t"; 
                      break;
                  case WarnP: 
                      FILE << "Warn:\t"; 
                      break;
                  case ErrorP: 
                      FILE << "Error:\t"; 
                      break;
                  case CriticalP: 
                      FILE << "Critical:\t"; 
                      break;
                  case Succes: 
                      FILE << "Successfully:\t"; 
                      break;
             }
              FILE << message << "\n";
              FILE.close();
          }
     }
};
LogPriority BasicLogger::verbosity = TraceP;
const char* BasicLogger::filepath = "";

S_PRA_API void InitMemory();
S_PRA_API int GetResultCount();
S_PRA_API void ClearResults();
S_PRA_API int SetSearchRange(int type);
S_PRA_API PMAPS readmaps(int type);
S_PRA_API PMAPS readmaps_all();
S_PRA_API PMAPS readmaps_bad();
S_PRA_API PMAPS readmaps_v();
S_PRA_API PMAPS readmaps_c_alloc();
S_PRA_API PMAPS readmaps_c_bss();
S_PRA_API PMAPS readmaps_code_app();
S_PRA_API PMAPS readmaps_c_data();
S_PRA_API PMAPS readmaps_c_heap();
S_PRA_API PMAPS readmaps_java_heap();
S_PRA_API PMAPS readmaps_a_anonmyous();
S_PRA_API PMAPS readmaps_code_system();
S_PRA_API PMAPS readmaps_stack();
S_PRA_API PMAPS readmaps_ashmem();

S_PRA_API void MemorySearch(char *value, int TYPE);
S_PRA_API PMAPS MemorySearch_DWORD(DWORD value, PMAPS pMap);
S_PRA_API PMAPS MemorySearch_FLOAT(FLOAT value, PMAPS pMap);
S_PRA_API PMAPS MemorySearch_DOUBLE(DOUBLE value, PMAPS pMap);
S_PRA_API PMAPS MemorySearch_WORD(WORD value, PMAPS pMap);
S_PRA_API PMAPS MemorySearch_BYTE(BYTE value, PMAPS pMap);
S_PRA_API PMAPS MemorySearch_QWORD(QWORD value, PMAPS pMap);

S_PRA_API void MemoryOffset(char *value, long int offset, int type);
S_PRA_API PMAPS MemoryOffset_DWORD(DWORD value, long int offset, PMAPS pBuff);
S_PRA_API PMAPS MemoryOffset_FLOAT(FLOAT value, long int offset, PMAPS pBuff);
S_PRA_API PMAPS MemoryOffset_DOUBLE(DOUBLE value, long int offset, PMAPS pBuff);
S_PRA_API PMAPS MemoryOffset_WORD(WORD value, long int offset, PMAPS pBuff);
S_PRA_API PMAPS MemoryOffset_BYTE(BYTE value, long int offset, PMAPS pBuff);
S_PRA_API PMAPS MemoryOffset_QWORD(QWORD value, long int offset, PMAPS pBuff);

S_PRA_API void MemoryWrite(char *value, long int offset, int type);
S_PRA_API int MemoryWrite_DWORD(DWORD value, PMAPS pBuff, long int offset);
S_PRA_API int MemoryWrite_FLOAT(FLOAT value, PMAPS pBuff, long int offset);
S_PRA_API int MemoryWrite_DOUBLE(DOUBLE value, PMAPS pBuff, long int offset);
S_PRA_API int MemoryWrite_WORD(WORD value, PMAPS pBuff, long int offset);
S_PRA_API int MemoryWrite_BYTE(BYTE value, PMAPS pBuff, long int offset);
S_PRA_API int MemoryWrite_QWORD(QWORD value, PMAPS pBuff, long int offset);

char *GetAddressValue(ADDRESS addr, int type);
DWORD GetAddressValue_DWORD(ADDRESS addr);
FLOAT GetAddressValue_FLOAT(ADDRESS addr);
DOUBLE GetAddressValue_DOUBLE(ADDRESS addr);
WORD GetAddressValue_WORD(ADDRESS addr);
BYTE GetAddressValue_BYTE(ADDRESS addr);
QWORD GetAddressValue_QWORD(ADDRESS addr);

void GlobalAntiCheatManager()
{
    pstring path = app_instance->GetAppFileDir().string();
    path << "Anogs.log";
    BasicLogger::filepath = path.c_str();
    
    pid_t game_pid = getpid();
    if (game_pid == 0) {
        BasicLogger::Log(ErrorP, "Gagal mendapatkan proses!");
        return;
    }
    
    char filename[64];
    sprintf(filename, "/proc/%d/mem", game_pid);
    handle = open(filename, O_RDWR);
    if (handle == -1) {
        BasicLogger::Log(ErrorP, "Gagal mendapatkan memory! ");
        sprintf(filename, "/proc/self/mem");
        handle = open(filename, O_RDWR);
        if (handle == -1) {
            BasicLogger::Log(ErrorP, "Gagal mendapatkan self memory! ");
            return;
        }
    }
    lseek(handle, 0, SEEK_SET);
    
    SetSearchRange(C_ALLOC);
    MemorySearch("349,525", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch("134658", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch("134914", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch("721,158", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch("16384;196,870", TYPES::TYPE_DWORD);
    MemoryWrite("67109633", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch("786,694", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch(":libanogs.so", TYPES::TYPE_BYTE);
    MemoryWrite("136", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch(":anticheatexpert.com", TYPES::TYPE_BYTE);
    MemoryWrite("136", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch(":61.151.168.203", TYPES::TYPE_BYTE);
    MemoryWrite("136", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch(":FooGameClientIPC", TYPES::TYPE_BYTE);
    MemoryWrite("136", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch(":.jpg", TYPES::TYPE_BYTE);
    MemoryWrite("136", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch(":libtprt.so", TYPES::TYPE_BYTE);
    MemoryWrite("136", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch(":.so", TYPES::TYPE_BYTE);
    MemoryWrite("136", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch(":.log", TYPES::TYPE_BYTE);
    MemoryWrite("136", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch(":/tss", TYPES::TYPE_BYTE);
    MemoryWrite("136", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch(":MidasOversea", TYPES::TYPE_BYTE);
    MemoryWrite("136", 0, TYPES::TYPE_DWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch(":QTAudioEngine", TYPES::TYPE_BYTE);
    MemoryWrite(":136", 0, TYPES::TYPE_BYTE);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch(":backups", TYPES::TYPE_BYTE);
    MemoryWrite(":136", 0, TYPES::TYPE_BYTE);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch(":user_agent", TYPES::TYPE_BYTE);
    MemoryWrite(":136", 0, TYPES::TYPE_BYTE);
    ClearResults();
    SetSearchRange(C_ALLOC);
    MemorySearch("1.86902387e-40~1.87261119e-40::5", TYPES::TYPE_FLOAT);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP | C_ALLOC);
    MemorySearch("8,070,450,536,542,896,128", TYPES::TYPE_QWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("2,621,448", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("2,721,15897,2721,1584", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("65,793", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("227,116", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("8,756", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("29,124", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("227,116", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("229,721,15864", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("233,16721,158", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("213,224", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("232,252", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("236,348", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("25,685", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("72721,158,914", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("25,289", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("213,224", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("7721,1584,96721,158", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("65,793", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("7721,158721,158,864", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("24,944", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("28,992", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
    ClearResults();
    SetSearchRange(CODE_APP);
    MemorySearch("14,645", TYPES::TYPE_DWORD);
    MemoryWrite("361418272505074178", 0, TYPES::TYPE_QWORD);
	ClearResults();
    BasicLogger::Log(Succes, "Protection has been activated!");
}


int GetResultCount() {
    return count;
}

void ClearResults() {
    PMAPS pHead = res;
    PMAPS pTemp = pHead;
    int i;
    for (i = 0; i < resCount; i++) {
        pTemp = pHead;
        pHead = pHead->next;
        free(pTemp);
    }
}

void MemorySearch(char *value, int type) {
    PMAPS pHead = NULL;
    PMAPS pMap = NULL;
    count = 0;
    switch (searchRange) {
        case ALL:
            pMap = readmaps(ALL);
            break;
        case B_BAD:
            pMap = readmaps(B_BAD);
            break;
            case V:
            pMap = readmaps(V);
            break;
        case C_ALLOC:
            pMap = readmaps(C_ALLOC);
            break;
        case C_BSS:
            pMap = readmaps(C_BSS);
            break;
        case CODE_APP:
            pMap = readmaps(CODE_APP);
            break;
        case C_DATA:
            pMap = readmaps(C_DATA);
            break;
        case C_HEAP:
            pMap = readmaps(C_HEAP);
            break;
        case JAVA_HEAP:
            pMap = readmaps(JAVA_HEAP);
            break;
        case A_ANONMYOUS:
            pMap = readmaps(A_ANONMYOUS);
            break;
        case CODE_SYSTEM:
            pMap = readmaps(CODE_SYSTEM);
            break;
        case STACK:
            pMap = readmaps(STACK);
            break;
        case ASHMEM:
            pMap = readmaps(ASHMEM);
            break;
        default:
            printf("\033[32;1mYou Select A NULL Type!\n");
            break;
    }
    if (pMap == NULL) {
        puts("map error");
        return (void)0;
    }
    switch (type) {
        case TYPE_DWORD:
            pHead = MemorySearch_DWORD(atoi(value), pMap);
            break;
        case TYPE_FLOAT:
            pHead = MemorySearch_FLOAT(atof(value), pMap);
            break;
        case TYPE_DOUBLE:
            pHead = MemorySearch_DOUBLE(atof(value), pMap);
            break;
        case TYPE_WORD:
            pHead = MemorySearch_WORD(atoi(value), pMap);
            break;
        case TYPE_BYTE:
            pHead = MemorySearch_BYTE(atoi(value), pMap);
            break;
        case TYPE_QWORD:
            pHead = MemorySearch_QWORD(atoi(value), pMap);
            break;
        default:
            printf("\033[32;1mYou Select A NULL Type!\n");
            break;
    }
    if (pHead == NULL) {
        puts("搜索内存失败!");
        return;
    }
    resCount = count;
    res = pHead;
}

PMAPS MemorySearch_DWORD(DWORD value, PMAPS pMap) {
    pid_t pid = getpid();
    if (pid == 0) {
        puts("获取进程失败!");
        return NULL;
    }
    
    PMAPS pTemp = NULL;
    pTemp = pMap;
    PMAPS n, e;
    e = n = (PMAPS) malloc(LEN);
    PMAPS pBuff;
    pBuff = n;
    int iCount = 0;
    int c;
    DWORD buff[1024] = { 0 };
    
    while (pTemp != NULL) { 
        c = (pTemp->taddr - pTemp->addr) / 4096;
        for (int j = 0; j < c; j++) {
            pread64(handle, buff, 0x1000, pTemp->addr + j * 4096);
            for (int i = 0; i < 1024; i++) {
                if (buff[i] == value) {
                    iCount++;
                    count += 1;
                    n->addr = (pTemp->addr) + (j * 4096) + (i * 4);
                    n->type = TYPE_DWORD;
                    
                    if (iCount == 1) {
                        n->next = NULL;
                        e = n;
                        pBuff = n;
                    } else {
                        n->next = NULL;
                        e->next = n;
                        e = n;
                    }
                    n = (PMAPS) malloc(LEN);
                }
            }
        }
        pTemp = pTemp->next;
    }
    free(n);
    return pBuff;
}

PMAPS MemorySearch_FLOAT(FLOAT value, PMAPS pMap) {
    pid_t pid = getpid();
    if (pid == 0) {
        puts("获取进程失败!");
        return NULL;
    }
    
    PMAPS pTemp = NULL;
    pTemp = pMap;
    PMAPS n, e;
    e = n = (PMAPS) malloc(LEN);
    PMAPS pBuff;
    pBuff = n;
    int iCount = 0;             
    int c;
    FLOAT buff[1024] = { 0 };   
    while (pTemp->next != NULL) {
        c = (pTemp->taddr - pTemp->addr) / 4096;
        for (int j = 0; j < c; j += 1) {
            pread64(handle, buff, 0x1000, pTemp->addr + (j * 4096));
            for (int i = 0; i < 1024; i += 1) {
                if (buff[i] == value) {
                    iCount++;
                    count += 1;
                    n->addr = (pTemp->addr) + (j * 4096) + (i * 4);
                    n->type = TYPE_FLOAT;
                    if (iCount == 1) {
                        n->next = NULL;
                        e = n;
                        pBuff = n;
                    } else {
                        n->next = NULL;
                        e->next = n;
                        e = n;
                    }
                    n = (PMAPS) malloc(LEN);
                }
                
            }
            
        }
        pTemp = pTemp->next;
    }
    free(n);
    return pBuff;
}

PMAPS MemorySearch_DOUBLE(DOUBLE value, PMAPS pMap) {
    pid_t pid = getpid();
    if (pid == 0) {
        puts("获取进程失败!");
        return NULL;
    }
    
    PMAPS pTemp = NULL;
    pTemp = pMap;
    PMAPS n, e;
    e = n = (PMAPS) malloc(LEN);
    PMAPS pBuff;
    pBuff = n;
    int iCount = 0;             
    int c;
    DOUBLE buff[1024] = { 0 };  
    while (pTemp->next != NULL) {
        c = (pTemp->taddr - pTemp->addr) / 4096;
        for (int j = 0; j < c; j += 1) {
            pread64(handle, buff, 0x1000, pTemp->addr + (j * 4096));
            for (int i = 0; i < 1024; i += 1) {
                if (buff[i] == value) {
                    iCount++;
                    count += 1;
                    n->addr = (pTemp->addr) + (j * 4096) + (i * 4);
                    n->type = TYPE_DOUBLE;
                    if (iCount == 1) {
                        n->next = NULL;
                        e = n;
                        pBuff = n;
                    } else {
                        n->next = NULL;
                        e->next = n;
                        e = n;
                    }
                    n = (PMAPS) malloc(LEN);
                }
                
            }
            
        }
        pTemp = pTemp->next;
    }
    free(n);
    return pBuff;
}

PMAPS MemorySearch_WORD(WORD value, PMAPS pMap) {
    pid_t pid = getpid();
    if (pid == 0) {
        puts("获取进程失败!");
        return NULL;
    }
    
    PMAPS pTemp = NULL;
    pTemp = pMap;
    PMAPS n, e;
    e = n = (PMAPS) malloc(LEN);
    PMAPS pBuff;
    pBuff = n;
    int iCount = 0;             
    int c;
    WORD buff[1024] = { 0 };    
    while (pTemp->next != NULL) {
        c = (pTemp->taddr - pTemp->addr) / 4096;
        for (int j = 0; j < c; j += 1) {
            pread64(handle, buff, 0x1000, pTemp->addr + (j * 4096));
            n->type = TYPE_WORD;
            for (int i = 0; i < 1024; i += 1) {
                if (buff[i] == value) {
                    iCount++;
                    count += 1;
                    n->addr = (pTemp->addr) + (j * 4096) + (i * 4);
                    if (iCount == 1) {
                        n->next = NULL;
                        e = n;
                        pBuff = n;
                    } else {
                        n->next = NULL;
                        e->next = n;
                        e = n;
                    }
                    n = (PMAPS) malloc(LEN);
                }
                
            }
            
        }
        pTemp = pTemp->next;
    }
    free(n);
    return pBuff;
}

PMAPS MemorySearch_BYTE(BYTE value, PMAPS pMap) {
    pid_t pid = getpid();
    if (pid == 0) {
        puts("获取进程失败!");
        return NULL;
    }
    
    PMAPS pTemp = NULL;
    pTemp = pMap;
    PMAPS n, e;
    e = n = (PMAPS) malloc(LEN);
    PMAPS pBuff;
    pBuff = n;
    int iCount = 0;             
    int c;
    BYTE buff[1024] = { 0 };    
    while (pTemp->next != NULL) {
        c = (pTemp->taddr - pTemp->addr) / 4096;
        for (int j = 0; j < c; j += 1) {
            pread64(handle, buff, 0x1000, pTemp->addr + (j * 4096));
            for (int i = 0; i < 1024; i += 1) {
                if (buff[i] == value) {
                    iCount++;
                    count += 1;
                    n->addr = (pTemp->addr) + (j * 4096) + (i * 4);
                    n->type = TYPE_BYTE;
                    if (iCount == 1) {
                        n->next = NULL;
                        e = n;
                        pBuff = n;
                    } else {
                        n->next = NULL;
                        e->next = n;
                        e = n;
                    }
                    n = (PMAPS) malloc(LEN);
                }
                
            }
            
        }
        pTemp = pTemp->next;
    }
    free(n);
    return pBuff;
}

PMAPS MemorySearch_QWORD(QWORD value, PMAPS pMap) {
    pid_t pid = getpid();
    if (pid == 0) {
        puts("获取进程失败!");
        return NULL;
    }
    
    PMAPS pTemp = NULL;
    pTemp = pMap;
    PMAPS n, e;
    e = n = (PMAPS) malloc(LEN);
    PMAPS pBuff;
    pBuff = n;
    int iCount = 0;             
    int c;
    QWORD buff[1024] = { 0 };   
    while (pTemp->next != NULL) {
        c = (pTemp->taddr - pTemp->addr) / 4096;
        for (int j = 0; j < c; j += 1) {
            pread64(handle, buff, 0x1000, pTemp->addr + (j * 4096));
            for (int i = 0; i < 1024; i += 1) {
                if (buff[i] == value) {
                    iCount++;
                    count += 1;
                    n->addr = (pTemp->addr) + (j * 4096) + (i * 4);
                    n->type = TYPE_QWORD;
                    if (iCount == 1) {
                        n->next = NULL;
                        e = n;
                        pBuff = n;
                    } else {
                        n->next = NULL;
                        e->next = n;
                        e = n;
                    }
                    n = (PMAPS) malloc(LEN);
                }
            }
        }
        pTemp = pTemp->next;
    }
    free(n);
    return pBuff;
}

void MemoryOffset(char *value, long int offset, int type) {
    PMAPS pHead = NULL;
    count = 0;
    switch (type) {
        case TYPE_DWORD:
            pHead = MemoryOffset_DWORD(atoi(value), offset, res);
            break;
        case TYPE_FLOAT:
            pHead = MemoryOffset_FLOAT(atof(value), offset, res);
            break;
        case TYPE_DOUBLE:
            pHead = MemoryOffset_DOUBLE(atof(value), offset, res);
            break;
        case TYPE_WORD:
            pHead = MemoryOffset_WORD(atoi(value), offset, res);
            break;
        case TYPE_BYTE:
            pHead = MemoryOffset_BYTE(atoi(value), offset, res);
            break;
        case TYPE_QWORD:
            pHead = MemoryOffset_QWORD(atoi(value), offset, res);
            break;
        default:
            printf("\033[32;1mYou Select A NULL Type!\n");
            break;
    }
    if (pHead == NULL) {
        puts("偏移失败!");
        return (void)0;
    }
    resCount = count;
    ClearResults();
    res = pHead;
}

PMAPS MemoryOffset_DWORD(DWORD value, long int offset, PMAPS pBuff) {
    PMAPS pEnd = NULL;
    PMAPS pNew = NULL;
    PMAPS pTemp = pBuff;
    PMAPS BUFF = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    BUFF = pNew;
    int iCount = 0;     
    long int all;               
    DWORD *buf = (DWORD *)malloc(sizeof(DWORD));
    int jg;
    while (pTemp != NULL) {
        all = pTemp->addr + offset;
        pread64(handle, buf, 4, all);
        jg = *buf;
        if (jg == value) {
            iCount++;
            count += 1;
            pNew->addr = pTemp->addr;
            pNew->type = TYPE_DWORD;
            if (iCount == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                BUFF = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN);
            if (resCount == 1) {
                free(pNew);
                close(handle);
                return BUFF;
            }
        }
        
        pTemp = pTemp->next;    
    }
    free(pNew);
    return BUFF;
}

PMAPS MemoryOffset_FLOAT(FLOAT value, long int offset, PMAPS pBuff) {
    
                        
    PMAPS pEnd = NULL;
    PMAPS pNew = NULL;
    PMAPS pTemp = pBuff;
    PMAPS BUFF = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    BUFF = pNew;
    int iCount = 0;     
    long int all;               
    FLOAT *buf = (FLOAT *)malloc(sizeof(FLOAT));    

    FLOAT jg;
    while (pTemp != NULL) {
        all = pTemp->addr + offset; 
        
        pread64(handle, buf, 4, all);
        jg = *buf;
        if (jg == value) {
            iCount++;
            count += 1;
            
            pNew->addr = pTemp->addr;
            pNew->type = TYPE_FLOAT;
            if (iCount == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                BUFF = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN);
            if (resCount == 1) {
                free(pNew);
                close(handle);
                return BUFF;
            }
        }
        
        pTemp = pTemp->next;    
    }
    free(pNew);
    return BUFF;
}

PMAPS MemoryOffset_DOUBLE(DOUBLE value, long int offset, PMAPS pBuff) {
    
                        
    PMAPS pEnd = NULL;
    PMAPS pNew = NULL;
    PMAPS pTemp = pBuff;
    PMAPS BUFF = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    BUFF = pNew;
    int iCount = 0;     
    long int all;               
    DOUBLE *buf = (DOUBLE *)malloc(sizeof(DOUBLE)); // 缓冲区
    
    DOUBLE jg;
    while (pTemp != NULL) {
        all = pTemp->addr + offset; 
        pread64(handle, buf, 4, all);
        jg = *buf;
        if (jg == value) {
            iCount++;
            count += 1;
            
            pNew->addr = pTemp->addr;
            pNew->type = TYPE_DOUBLE;
            if (iCount == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                BUFF = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN);
            if (resCount == 1) {
                free(pNew);
                close(handle);
                return BUFF;
            }
        }
        
        pTemp = pTemp->next;    
    }
    free(pNew);
    return BUFF;
}

PMAPS MemoryOffset_WORD(WORD value, long int offset, PMAPS pBuff) {
    
                        
    PMAPS pEnd = NULL;
    PMAPS pNew = NULL;
    PMAPS pTemp = pBuff;
    PMAPS BUFF = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    BUFF = pNew;
    int iCount = 0;     
    long int all;               
    WORD *buf = (WORD *)malloc(sizeof(WORD));   
    
    WORD jg;
    while (pTemp != NULL) {
        all = pTemp->addr + offset; 
        pread64(handle, buf, 4, all);
        jg = *buf;
        if (jg == value) {
            iCount++;
            count += 1;
            
            pNew->addr = pTemp->addr;
            pNew->type = TYPE_WORD;
            if (iCount == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                BUFF = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN);
            if (resCount == 1) {
                free(pNew);
                close(handle);
                return BUFF;
            }
        }
        /* else { printf("jg:%e,value:%e\n",jg,value); } */
        pTemp = pTemp->next;    // 指向下一个节点读取数据
    }
    free(pNew);
    return BUFF;
}

PMAPS MemoryOffset_BYTE(BYTE value, long int offset, PMAPS pBuff) {
    
                        // 初始个数为0
    PMAPS pEnd = NULL;
    PMAPS pNew = NULL;
    PMAPS pTemp = pBuff;
    PMAPS BUFF = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    BUFF = pNew;
    int iCount = 0;     // 个数与句柄
    long int all;               // 总和
    BYTE *buf = (BYTE *)malloc(sizeof(BYTE));   // 缓冲区
    // int buf[16]; //出现异常使用
    BYTE jg;
    while (pTemp != NULL) {
        all = pTemp->addr + offset; // 偏移后的地址
        pread64(handle, buf, 4, all);
        jg = *buf;
        if (jg == value) {
            iCount++;
            count += 1;
            // printf("偏移成功,addr:%lx\n",all);
            pNew->addr = pTemp->addr;
            pNew->type = TYPE_BYTE;
            if (iCount == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                BUFF = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN);
            if (resCount == 1) {
                free(pNew);
                close(handle);
                return BUFF;
            }
        }
        /* else { printf("jg:%e,value:%e\n",jg,value); } */
        pTemp = pTemp->next;    // 指向下一个节点读取数据
    }
    free(pNew);
    return BUFF;
}

PMAPS MemoryOffset_QWORD(QWORD value, long int offset, PMAPS pBuff) {
    
                        // 初始个数为0
    PMAPS pEnd = NULL;
    PMAPS pNew = NULL;
    PMAPS pTemp = pBuff;
    PMAPS BUFF = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    BUFF = pNew;
    int iCount = 0;     // 个数与句柄
    long int all;               // 总和
    QWORD *buf = (QWORD *)malloc(sizeof(QWORD));    // 缓冲区
    // int buf[16]; //出现异常使用
    QWORD jg;
    while (pTemp != NULL) {
        all = pTemp->addr + offset; // 偏移后的地址
        pread64(handle, buf, 4, all);
        jg = *buf;
        if (jg == value) {
            iCount++;
            count += 1;
            // printf("偏移成功,addr:%lx\n",all);
            pNew->addr = pTemp->addr;
            pNew->type = TYPE_QWORD;
            if (iCount == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                BUFF = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN);
            if (resCount == 1) {
                free(pNew);
                close(handle);
                return BUFF;
            }
        }
        /* else { printf("jg:%e,value:%e\n",jg,value); } */
        pTemp = pTemp->next;    // 指向下一个节点读取数据
    }
    free(pNew);
    return BUFF;
}


void MemoryWrite(char *value, long int offset, int type) {
    switch (type) {
        case TYPE_DWORD:
            MemoryWrite_DWORD(atoi(value), res, offset);
            break;
        case TYPE_FLOAT:
            MemoryWrite_FLOAT(atof(value), res, offset);
            break;
        case TYPE_DOUBLE:
            MemoryWrite_DOUBLE(atof(value), res, offset);
            break;
        case TYPE_WORD:
            MemoryWrite_WORD(atoi(value), res, offset);
            break;
        case TYPE_BYTE:
            MemoryWrite_BYTE(atoi(value), res, offset);
            break;
        case TYPE_QWORD:
            MemoryWrite_QWORD(atoi(value), res, offset);
            break;
        default:
            printf("\033[32;1mYou Select A NULL Type!\n");
            break;
    }
    // ClearResults();//清空list
}

int MemoryWrite_DWORD(DWORD value, PMAPS pBuff, long int offset) {
    
    PMAPS pTemp = NULL;
    pTemp = pBuff;
    int i;
    for (i = 0; i < resCount; i++) {
        pwrite64(handle, &value, 4, pTemp->addr + offset);
        if (pTemp->next != NULL)
            pTemp = pTemp->next;
    }
    return 0;
}

int MemoryWrite_FLOAT(FLOAT value, PMAPS pBuff, long int offset) {
    
    PMAPS pTemp = NULL;
    pTemp = pBuff;
    int i;
    for (i = 0; i < resCount; i++) {
        pwrite64(handle, &value, 4, pTemp->addr + offset);
        if (pTemp->next != NULL)
            pTemp = pTemp->next;
    }
    return 0;
}

int MemoryWrite_DOUBLE(DOUBLE value, PMAPS pBuff, long int offset) {
    
    PMAPS pTemp = NULL;
    int handle;
    pTemp = pBuff;
    int i;
    for (i = 0; i < resCount; i++) {
        pwrite64(handle, &value, 4, pTemp->addr + offset);
        if (pTemp->next != NULL)
            pTemp = pTemp->next;
    }
    return 0;
}

int MemoryWrite_WORD(WORD value, PMAPS pBuff, long int offset) {
    
    PMAPS pTemp = NULL;
    pTemp = pBuff;
    int i;
    for (i = 0; i < resCount; i++) {
        pwrite64(handle, &value, 4, pTemp->addr + offset);
        if (pTemp->next != NULL)
            pTemp = pTemp->next;
    }
    return 0;
}

int MemoryWrite_BYTE(BYTE value, PMAPS pBuff, long int offset) {
    
    PMAPS pTemp = NULL;
    pTemp = pBuff;
    int i;
    for (i = 0; i < resCount; i++) {
        pwrite64(handle, &value, 4, pTemp->addr + offset);
        if (pTemp->next != NULL)
            pTemp = pTemp->next;
    }
    return 0;
}

int MemoryWrite_QWORD(QWORD value, PMAPS pBuff, long int offset) {
    
    PMAPS pTemp = NULL;
    pTemp = pBuff;
    int i;
    for (i = 0; i < resCount; i++) {
        pwrite64(handle, &value, 4, pTemp->addr + offset);
        if (pTemp->next != NULL)
            pTemp = pTemp->next;
    }
    return 0;
}



int SetSearchRange(int type) {
    switch (type) {
        case ALL:
            searchRange = 0;
            break;
        case B_BAD:
            searchRange = 1;
            break;
         case V:
            searchRange = 2;
            break;
        case C_ALLOC:
            searchRange = 3;
            break;
        case C_BSS:
            searchRange = 4;
            break;
        case CODE_APP:
            searchRange = 5;
            break;
        case C_DATA:
            searchRange = 6;
            break;
        case C_HEAP:
            searchRange = 7;
            break;
        case JAVA_HEAP:
            searchRange = 8;
            break;
        case A_ANONMYOUS:
            searchRange = 9;
            break;
        case CODE_SYSTEM:
            searchRange = 10;
            break;
        case STACK:
            searchRange = 11;
            break;
        case ASHMEM:
            searchRange = 12;
            break;
        default:
            printf("\033[32;1mYou Select A NULL Type!\n");
            break;
    }
    return 0;
}

PMAPS readmaps(int type) {
    PMAPS pMap = NULL;
    switch (type) {
        case ALL:
            pMap = readmaps_all();
            break;
        case B_BAD:
            pMap = readmaps_bad();
            break;
            case V:
            pMap = readmaps_v();
            break;
        case C_ALLOC:
            pMap = readmaps_c_alloc();
            break;
        case C_BSS:
            pMap = readmaps_c_bss();
            break;
        case CODE_APP:
            pMap = readmaps_code_app();
            break;
        case C_DATA:
            pMap = readmaps_c_data();
            break;
        case C_HEAP:
            pMap = readmaps_c_heap();
            break;
        case JAVA_HEAP:
            pMap = readmaps_java_heap();
            break;
        case A_ANONMYOUS:
            pMap = readmaps_a_anonmyous();
            break;
        case CODE_SYSTEM:
            pMap = readmaps_code_system();
            break;
        case STACK:
            pMap = readmaps_stack();
            break;
        case ASHMEM:
            pMap = readmaps_ashmem();
            break;
        default:
            printf("\033[32;1mYou Select A NULL Type!\n");
            break;
    }
    if (pMap == NULL) {
        return 0;
    }
    return pMap;
}

PMAPS readmaps_all() {
    PMAPS pHead = NULL;
    PMAPS pNew;
    PMAPS pEnd;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);  // 读取一行
        if (strstr(buff, "rw") != NULL && !feof(fp)) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            // 这里使用lx是为了能成功读取特别长的地址
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); // 分配内存
        }
    }
    free(pNew);                 // 将多余的空间释放
    fclose(fp);                 // 关闭文件指针
    return pHead;
}

PMAPS readmaps_bad() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);  
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "kgsl-3d0")) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); 
        }
    }
    free(pNew);                 
    fclose(fp);                 
    return pHead;
}


PMAPS readmaps_v()
{
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL)
    {
        puts("分析失败");
        return NULL;
    }
    while (!feof(fp))
    {
        fgets(buff, sizeof(buff), fp);  
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "/dev/kgsl-3d0"))
        {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        }
        else
        {
            flag = 0;
        }
        if (flag == 1)
        {
            i++;
            if (i == 1)
            {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            }
            else
            {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); 
        }
    }
    free(pNew);                 
    fclose(fp);                 
    return pHead;
}


PMAPS readmaps_c_alloc() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);  
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "[anon:libc_malloc]")) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN);
        }
    }
    free(pNew);                 
    fclose(fp);                 
    return pHead;
}

PMAPS readmaps_c_bss() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);  
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "[anon:.bss]")) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); 
        }
    }
    free(pNew);                 
    fclose(fp);                 
    return pHead;
}



PMAPS readmaps_code_app() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);  
        if (strstr(buff, "r-xp") != NULL && !feof(fp) && strstr(buff, "/data/app/")) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); 
        }
    }
    free(pNew);                 
    fclose(fp);                 
    return pHead;
}


PMAPS readmaps_c_data() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);  
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "/data/app/")) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); 
        }
    }
    free(pNew);                 
    fclose(fp);                 
    return pHead;
}

PMAPS readmaps_c_heap() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);  
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "[heap]")) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); 
        }
    }
    free(pNew);                 
    fclose(fp);                 
    return pHead;
}

PMAPS readmaps_java_heap() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);  
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "/dev/ashmem/")) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); 
        }
    }
    free(pNew);                 
    fclose(fp);                 
    return pHead;
}

PMAPS readmaps_a_anonmyous() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);  
        if (strstr(buff, "rw") != NULL && !feof(fp) && (strlen(buff) < 42)) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); 
        }
    }
    free(pNew);                 
    fclose(fp);                 
    return pHead;
}

PMAPS readmaps_code_system() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "/system")) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN);
        }
    }
    free(pNew);
    fclose(fp);
    return pHead;
}

PMAPS readmaps_stack() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "[stack]")) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); 
        }
    }
    free(pNew);                 
    fclose(fp);                 
    return pHead;
}

PMAPS readmaps_ashmem() {
    PMAPS pHead = NULL;
    PMAPS pNew = NULL;
    PMAPS pEnd = NULL;
    pEnd = pNew = (PMAPS) malloc(LEN);
    FILE *fp;
    int i = 0, flag = 1;
    char lj[64], buff[256];
    int pid = getpid();
    sprintf(lj, "/proc/%d/maps", pid);
    fp = fopen(lj, "r");
    if (fp == NULL) {
        puts("内存读取失败!");
        return NULL;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);
        if (strstr(buff, "rw") != NULL && !feof(fp) && strstr(buff, "/dev/ashmem/")
                && !strstr(buff, "dalvik")) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
            
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = NULL;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = NULL;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN);
        }
    }
    free(pNew);
    fclose(fp);
    return pHead;
}

char *GetAddressValue(ADDRESS addr,int type) {
    char *str = (char *)malloc(sizeof(char));
    DWORD i;
    FLOAT f;
    DOUBLE d;
    WORD w;
    BYTE b;
    QWORD q;
    switch (type) {
        case TYPE_DWORD:
            i = GetAddressValue_DWORD(addr);
            sprintf(str,"%d",i);
            break;
        case TYPE_FLOAT:
            f = GetAddressValue_FLOAT(addr);
            sprintf(str,"%e",f);
            break;
        case TYPE_DOUBLE:
            d = GetAddressValue_DOUBLE(addr);
            sprintf(str,"%e",d);
            break;
        case TYPE_WORD:
            w = GetAddressValue_WORD(addr);
            sprintf(str,"%d",w);
            break;
        case TYPE_BYTE:
            b = GetAddressValue_BYTE(addr);
            sprintf(str,"%d",b);
            break;
        case TYPE_QWORD:
            q = GetAddressValue_QWORD(addr);
            sprintf(str,"%ld",q);
            break;
        default:
            sprintf(str,"%s","");
            printf("\033[32;1m你选择了一个未知类型!\n");
            break;
    }
    return str;
}


DWORD GetAddressValue_DWORD(ADDRESS addr) {
    DWORD buf;
    pread64(handle, &buf, sizeof(DWORD), addr);
    return buf;
}

FLOAT GetAddressValue_FLOAT(ADDRESS addr) {
    FLOAT buf;
    pread64(handle, &buf, sizeof(FLOAT), addr);
    return buf;
}

DOUBLE GetAddressValue_DOUBLE(ADDRESS addr) {
    DOUBLE buf;
    pread64(handle, &buf, sizeof(DOUBLE), addr);
    return buf;
}

WORD GetAddressValue_WORD(ADDRESS addr) {
    WORD buf;
    pread64(handle, &buf, sizeof(WORD), addr);
    return buf;
}

BYTE GetAddressValue_BYTE(ADDRESS addr) {
    BYTE buf;
    pread64(handle, &buf, sizeof(BYTE), addr);
    return buf;
}

QWORD GetAddressValue_QWORD(ADDRESS addr) {
    QWORD buf;
    pread64(handle, &buf, sizeof(QWORD), addr);
    return buf;
}
