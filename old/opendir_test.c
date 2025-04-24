#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

int	main(void)
{
	DIR *test = NULL;
	struct dirent *testing = NULL;
	test = opendir(".");
//	test = opendir("test_symlink");
	if (!test)
	{
		perror("open: ");
		exit (errno);
	}
	else
		printf("Success reading ?\n");
	testing = readdir(test);
	while (testing)
	{
		if (!test)
		{
			perror("readdir: ");
			closedir(test);
			exit (errno);
		}
		else
		{
			printf("dir_name: %s\n", testing->d_name);
			printf("type: %d, %d, %d, %d\n", testing->d_type, DT_LNK, DT_UNKNOWN, DT_DIR);

		}
		testing = readdir(test);
	}
	closedir(test);
}
