#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/queue.h>

struct user_s {
	char *name;
	int age;
	LIST_ENTRY(user_s) users;
};

typedef struct user_s user_t;

void freeuser(user_t *u) {
	free(u->name);
	free(u);
	u = NULL;
}

int main(int ac, char **av) {

	user_t *u1 = NULL;
	user_t *u2 = NULL;
	user_t *np = NULL;

	if(NULL == (u1  = (user_t *) malloc(sizeof(user_t))))
		return EXIT_FAILURE;

	if(NULL == (u2 = (user_t *) malloc(sizeof(user_t))))
		return EXIT_FAILURE;

	if(NULL == (np = (user_t *) malloc(sizeof(user_t))))
		return EXIT_FAILURE;

	u1->name = strdup("j4");
	u1->age = 31;

	u2->name = strdup("Angel");
	u2->age = 30;

	LIST_HEAD(listusers, user_s) head;

	fprintf(stdout, "--- Add to list ---\n");

	fprintf(stdout, "Add name: %s to list.\n", u1->name);
	LIST_INSERT_HEAD(&head, u1, users);

	fprintf(stdout, "Add name: %s to list.\n", u2->name);
	LIST_INSERT_HEAD(&head, u2, users);

	fprintf(stdout, "--- Read list ---\n");
	
	for(np = head.lh_first; np != NULL; np = np->users.le_next)
		fprintf(stdout, "Read %s\n", np->name);

	fprintf(stdout, "--- Delete list ---\n");

	while (head.lh_first != NULL) {
		fprintf(stdout, "Delete %s\n", head.lh_first->name);
		LIST_REMOVE(head.lh_first, users);
	}

	freeuser(u1);
	freeuser(u2);

	return EXIT_SUCCESS;
}
