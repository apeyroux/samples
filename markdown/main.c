#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mkdio.h>

#define MKD_EXEMPLE "My title\n---\n\nUne *intro* ? pour _quoi_ ?"
#define CUTE "\n---- 8< ---- 8< ---- 8< ---- 8< ---- 8< ----\n"

int main(void) {
	char *out = NULL;
	int sizeout;

	MMIOT *doc = mkd_string(MKD_EXEMPLE, strlen(MKD_EXEMPLE)+1, 0);

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
	
	fprintf(stdout, "document size:%d\n", sizeout);	
	fprintf(stdout, "%s\n", CUTE);	
	fprintf(stdout, "%s\n", out);
	fprintf(stdout, "%s\n", CUTE);	

	return EXIT_SUCCESS;
}
