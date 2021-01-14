//ͨ����ȡ/proc/stat (CPU)��/proc/meminfo(�ڴ��Ӳ��)�ļ���Ϣ  
//proc/meminfo�ļ��ṹ  
//MemTotal:       515164 kB  
//MemFree:         15024 kB  
//Buffers:         13740 kB  
//Cached:         248824 kB  
//SwapCached:    960 kB  
//Active:         309980 kB  
//Inactive:       63420 kB  
//#include <cstdio>
//
//
//typedef struct MEMPACKED         //����һ��mem occupy�Ľṹ��  
//{
//    char name1[20];      //����һ��char���͵�������name��20��Ԫ��  
//    unsigned long MemTotal;
//    char name2[20];
//    unsigned long MemFree;
//    char name3[20];
//    unsigned long Buffers;
//    char name4[20];
//    unsigned long Cached;
//    char name5[20];
//    unsigned long SwapCached;
//}MEM_OCCUPY;
//
////proc/stat�ļ��ṹ  
////cpu  633666 46912 249878 176813696 782884 2859 19625 0  
////cpu0 633666 46912 249878 176813696 782884 2859 19625 0  
////intr 5812844  
////ctxt 265816063  
////btime 1455203832  
////processes 596625  
////procs_running 1  
////procs_blocked 0  
//
//typedef struct CPUPACKED         //����һ��cpu occupy�Ľṹ��  
//{
//    char name[20];      //����һ��char���͵�������name��20��Ԫ��  
//    unsigned int user; //����һ���޷��ŵ�int���͵�user  
//    unsigned int nice; //����һ���޷��ŵ�int���͵�nice  
//    unsigned int system;//����һ���޷��ŵ�int���͵�system  
//    unsigned int idle; //����һ���޷��ŵ�int���͵�idle  
//    unsigned int lowait;
//    unsigned int irq;
//    unsigned int softirq;
//}CPU_OCCUPY;
//
//
//static void get_memoccupy(MEM_OCCUPY* mem) //��������get��������һ���βνṹ����Ū��ָ��O  
//{
//    FILE * fd;
//    char buff[256];
//    MEM_OCCUPY * m;
//    m = mem;
//
//    fd = fopen("/proc/meminfo", "r");
//    //MemTotal: 515164 kB  
//        //MemFree: 7348 kB  
//        //Buffers: 7892 kB  
//        //Cached: 241852  kB  
//        //SwapCached: 0 kB  
//        //��fd�ļ��ж�ȡ����Ϊbuff���ַ����ٴ浽��ʼ��ַΪbuff����ռ���   
//        fgets(buff, sizeof(buff), fd);
//    sscanf(buff, "%s %lu ", m->name1, &m->MemTotal);
//    fgets(buff, sizeof(buff), fd);
//    sscanf(buff, "%s %lu ", m->name2, &m->MemFree);
//    fgets(buff, sizeof(buff), fd);
//    sscanf(buff, "%s %lu ", m->name3, &m->Buffers);
//    fgets(buff, sizeof(buff), fd);
//    sscanf(buff, "%s %lu ", m->name4, &m->Cached);
//    fgets(buff, sizeof(buff), fd);
//    sscanf(buff, "%s %lu", m->name5, &m->SwapCached);
//
//    fclose(fd);     //�ر��ļ�fd  
//}
//
//
//static int get_cpuoccupy(CPU_OCCUPY* cpust) //��������get��������һ���βνṹ����Ū��ָ��O  
//{
//    FILE * fd;
//    char buff[256];
//    CPU_OCCUPY * cpu_occupy;
//    cpu_occupy = cpust;
//
//    fd = fopen("/proc/stat", "r");
//    fgets(buff, sizeof(buff), fd);
//
//    sscanf(buff, "%s %u %u %u %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, &cpu_occupy->nice, &cpu_occupy->system, &cpu_occupy->idle, &cpu_occupy->lowait, &cpu_occupy->irq, &cpu_occupy->softirq);
//
//
//    fclose(fd);
//
//    return 0;
//}
//
//
//static int cal_cpuoccupy(CPU_OCCUPY* o, CPU_OCCUPY* n)
//{
//    unsigned long od, nd;
//    double cpu_use = 0;
//
//    od = (unsigned long)(o->user + o->nice + o->system + o->idle + o->lowait + o->irq + o->softirq);//��һ��(�û�+���ȼ�+ϵͳ+����)��ʱ���ٸ���od  
//    nd = (unsigned long)(n->user + n->nice + n->system + n->idle + n->lowait + n->irq + n->softirq);//�ڶ���(�û�+���ȼ�+ϵͳ+����)��ʱ���ٸ���od  
//    double sum = nd - od;
//    double idle = n->idle - o->idle;
//    cpu_use = idle / sum;
//    printf("cpu_use1(idle) = %f\r\n", cpu_use);
//    idle = n->user + n->system + n->nice - o->user - o->system - o->nice;
//    cpu_use = idle / sum;
//    printf("cpu_use2(user+system+nice) = %f\r\n", cpu_use);
//    return 0;
//}
//static void getcpuuserlv(CPU_OCCUPY* cpu_last)
//{
//    MEM_OCCUPY mem_stat;
//    CPU_OCCUPY cpu_stat;  
//
//    //��ȡ�ڴ�  
//    get_memoccupy((MEM_OCCUPY*)&mem_stat);
//    printf(" [MemTotal] = %lu \n [MemFree] = %lu \n [Buffers] = %lu \n [Cached] = %lu \n [SwapCached] = %lu \n", mem_stat.MemTotal, mem_stat.MemFree, mem_stat.Buffers, mem_stat.Cached, mem_stat.SwapCached);
//    get_cpuoccupy((CPU_OCCUPY*)&cpu_stat);
//   
// 
//    //����cpuʹ����  
//     cal_cpuoccupy((CPU_OCCUPY*)&cpu_last, (CPU_OCCUPY*)&cpu_stat);
//
//     cpu_last = &cpu_stat;
//
//}