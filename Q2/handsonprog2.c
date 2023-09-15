/*
=======================================================================================================================================================================================
Name : handsonprog2.c
Author : H Anarghya
Description : Write a simple program to execute in an infinite loop at the background. 
	      Go to /proc directory and identify all the process related information in the corresponding proc directory.
Date: 10th Aug, 2023.
=======================================================================================================================================================================================

=======================================================================================================================================================================================
Sample Output:
dell@dell-Inspiron-3576:~/sslab/Q2$ ./h2 &
[1] 3549
dell@dell-Inspiron-3576:~/sslab/Q2$ cd /proc/3549
dell@dell-Inspiron-3576:/proc/3549$ ls
arch_status  cgroup      coredump_filter     environ  gid_map            limits     mem         net        oom_score      personality  schedstat  smaps_rollup  status          timers
attr         clear_refs  cpu_resctrl_groups  exe      io                 loginuid   mountinfo   ns         oom_score_adj  projid_map   sessionid  stack         syscall         timerslack_ns
autogroup    cmdline     cpuset              fd       ksm_merging_pages  map_files  mounts      numa_maps  pagemap        root         setgroups  stat          task            uid_map
auxv         comm        cwd                 fdinfo   ksm_stat           maps       mountstats  oom_adj    patch_state    sched        smaps      statm         timens_offsets  wchan
dell@dell-Inspiron-3576:/proc/3549$ ls -l fd
total 0
lrwx------ 1 dell dell 64 Sep 10 11:57 0 -> /dev/pts/0
lrwx------ 1 dell dell 64 Sep 10 11:57 1 -> /dev/pts/0
lrwx------ 1 dell dell 64 Sep 10 11:57 2 -> /dev/pts/0
=======================================================================================================================================================================================
*/

#include<stdio.h>

int main(){
	for(;;){}
}
