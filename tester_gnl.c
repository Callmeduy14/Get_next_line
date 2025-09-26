
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef USE_BONUS
# include "get_next_line_bonus.h"
#else
# include "get_next_line.h"
#endif

static void print_usage(const char *p)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "  %s full <file1> [file2 ...]\n", p);
	fprintf(stderr, "  %s interleave <file1> <file2>\n", p);
	fprintf(stderr, "  %s early <file> <nline>\n", p);
}

int main(int argc, char **argv)
{
	char *line;
	int   fd1, fd2;
	size_t i;

	if (BUFFER_SIZE <= 0) {
		fprintf(stderr, "[INFO] BUFFER_SIZE=%d -> get_next_line() selalu return NULL\n", BUFFER_SIZE);
		return 0;
	}
	if (argc < 3) { print_usage(argv[0]); return 1; }

	/* Mode: full -> baca setiap file sampai EOF */
	if (argv[1][0]=='f' && argv[1][1]=='u' && argv[1][2]=='l' && argv[1][3]=='l') {
		for (int a = 2; a < argc; ++a) {
			fd1 = open(argv[a], O_RDONLY);
			if (fd1 < 0) { perror("open"); continue; }
			i = 0;
			while ((line = get_next_line(fd1)) != NULL) {
				(void)write(1, line, ft_strlen(line));
				free(line);
				i++;
			}
			close(fd1);
			fprintf(stderr, "\n[full] %s -> %zu lines read\n", argv[a], i);
		}
		return 0;
	}

	/* Mode: interleave -> bonus test, dua file dibaca bergantian */
	if (argv[1][0]=='i') {
		if (argc < 4) { print_usage(argv[0]); return 1; }
		fd1 = open(argv[2], O_RDONLY);
		fd2 = open(argv[3], O_RDONLY);
		if (fd1 < 0 || fd2 < 0) { perror("open"); if (fd1>=0) close(fd1); if (fd2>=0) close(fd2); return 1; }
		char *l1, *l2;
		int done1 = 0, done2 = 0;
		while (!done1 || !done2) {
			if (!done1) {
				l1 = get_next_line(fd1);
				if (l1) { (void)write(1, l1, ft_strlen(l1)); free(l1); }
				else done1 = 1;
			}
			if (!done2) {
				l2 = get_next_line(fd2);
				if (l2) { (void)write(1, l2, ft_strlen(l2)); free(l2); }
				else done2 = 1;
			}
		}
		close(fd1); close(fd2);
		fprintf(stderr, "\n[interleave] done\n");
		return 0;
	}

	/* Mode: early -> baca nline lalu keluar (tanpa menghabiskan file) */
	if (argv[1][0]=='e') {
		if (argc < 4) { print_usage(argv[0]); return 1; }
		long nline = strtol(argv[3], NULL, 10);
		if (nline < 0) nline = 0;
		fd1 = open(argv[2], O_RDONLY);
		if (fd1 < 0) { perror("open"); return 1; }
		for (long k = 0; k < nline; ++k) {
			line = get_next_line(fd1);
			if (!line) break;
			(void)write(1, line, ft_strlen(line));
			free(line);
		}
		/* Intentionally NOT draining file. Tutup fd lalu exit. */
		close(fd1);
		fprintf(stderr, "\n[early] read %ld lines then exited early\n", nline);
		return 0;
	}

	print_usage(argv[0]);
	return 1;
}
