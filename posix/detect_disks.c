#include <mntent.h>
#include <stdio.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <sys/types.h>
int main() {
  FILE *mount_table;
  mount_table = setmntent("/proc/mounts", "r");
  struct mntent *e;
  while ((e = getmntent(mount_table)) != NULL) {
    struct statvfs s;

    // Фильтрация:
    if (statfs(e->mnt_dir, &s) != 0) continue;
    // if (strcmp(e->mnt_type, "aufs") != 0 && strcmp(e->mnt_type, "ext4") != 0)
    //  continue;
    // if (s.f_fsid[0] == 0 && strcmp(e->mnt_fsname, "aufs") != 0) continue;

    printf("statvfs.f_fsid=%lu ", s.f_fsid);
    printf("statvfs.f_flag=%d ", s.f_flag);
    printf("mntent.mnt_dir=%s ", e->mnt_dir);
    printf("mntent.mnt_fsname=%s ", e->mnt_fsname);
    printf("mntent.mnt_type=%s ", e->mnt_type);
    printf("mntent.mnt_opts=%s ", e->mnt_opts);
    printf("mntent.mnt_freq=%d ", e->mnt_freq);
    printf("\n");
  }
  endmntent(mount_table);
  return 0;
}
