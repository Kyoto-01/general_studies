#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
	
	int s;

	umask(0);

	// mount

	s = mount("/dev/sdb1", "/mnt", "ext4", 0, NULL);
	if (s == -1) {
		perror("Fail while mount.\n");
		return errno;
	}
	printf("=== MOUNT - /dev/sdb1 in /mnt ===\n");
	system("lsblk | grep sdb1");
	printf("=================================\n");

	// mkdir

	s = mkdir("/mnt/bob", 0777);
	if (s == -1) {
		perror("Fail while mkdir.\n");
		return errno;
	}
	printf("=== MKDIR - /mnt/bob ===\n");
	system("ls -ld /mnt/bob");
	printf("========================\n");

	// open

	s = open("/mnt/fs_sys_test.txt", O_CREAT | O_RDWR, 0644);
	if (s == -1) {
		perror("Fail while open.\n");
		return errno;
	}
	close(s);
	printf("=== OPEN - /mnt/fs_sys_test.txt ===\n");
	system("ls -ld /mnt/fs_sys_test.txt");
	printf("===================================\n");

	// link
	
	s = link("/mnt/fs_sys_test.txt", "/mnt/bob/my_fs.txt");
	if (s == -1) {
		perror("Fail while link.\n");
		return errno;
	}
	printf("=== link - /mnt/fs_sys_test.txt to /mnt/bob/my_fs.txt ===\n");
	system("ls -ld /mnt/bob/my_fs.txt");
	printf("=========================================================\n");

	// unlink
	
	s = unlink("/mnt/bob/my_fs.txt");
	if (s == -1) {
		perror("Fail while unlink.\n");
		return errno;
	}
	printf("=== unlink - /mnt/bob/my_fs.txt ===\n");
	system("tree /mnt/bob");
	system("ls -ld /mnt/fs_sys_test.txt");
	printf("===================================\n");

	s = unlink("/mnt/fs_sys_test.txt");
	if (s == -1) {
		perror("Fail while unlink.\n");
		return errno;
	}
	printf("=== unlink - /mnt/fs_sys_test.txt ===\n");
	system("tree /mnt");
	printf("=====================================\n");

	// rmdir
	
	s = rmdir("/mnt/bob");
	if (s == -1) {
		perror("Fail while rmdir.\n");
		return errno;
	}
	printf("=== rmdir - /mnt/bob ===\n");
	system("tree /mnt");
	printf("========================\n");
	
	// umount

	s = umount("/mnt");
	if (s == -1) {
		perror("Fail while umount.\n");
		return errno;
	}
	printf("=== UMOUNT - /dev/sdb1 from /mnt ===\n");
	system("lsblk | grep sdb1");
	printf("====================================\n");

	return 0;
}
