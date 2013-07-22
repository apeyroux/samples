#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mkdio.h>

void usage() {
	fprintf(stdout, "uage -i file.mkd\n");
	exit(0);
}

int main(int ac, char **av) {
	char *out, *pathin;
	FILE *fin;
	int sizeout, ch;

	while(-1 != (ch = getopt(ac, av, "i:"))) {
		switch(ch) {
			case 'i':
				pathin = optarg;
				break;
			default:
				break;
		}
	}

	if(!pathin)
		usage();

	if(NULL == (fin = fopen(pathin, "r"))) {
		fprintf(stderr, "error: can't fopen on %s\n", pathin);
		return EXIT_FAILURE;
	}

	MMIOT *doc = mkd_in(fin, 0);

	if(!doc) {
		fprintf(stderr, "error: init mkd_string\n");
		return EXIT_FAILURE;
	}

	if(!mkd_compile(doc, 0)) {
		free(doc);
		fprintf(stderr, "error: mkd_compile\n");
		return EXIT_FAILURE;
	}

	if(-1 == (sizeout = mkd_document(doc, &out))) {
		free(doc);
		fprintf(stderr, "error: mkd_outument\n");
		return EXIT_FAILURE;
	}
	
	fprintf(stdout, "%s\n", out);

	return EXIT_SUCCESS;
}
