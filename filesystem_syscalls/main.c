#include <stdlib.h>
#include <sys/mount.h>

int main(void) {
	
	mount("/dev/sdb1", "/mnt", "vfat", 0, NULL);
	system("lsblk | grep sdb1");

	umount("/mnt");
	system("lsblk | grep sdb1");

	return 0;
}
