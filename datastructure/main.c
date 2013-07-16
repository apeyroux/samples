#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/queue.h>

struct user_s {
	char *name;
	uint age;
	LIST_ENTRY(user_s) users;
};

typedef struct user_s user_t;

user_t *newuser(char *name, uint age) {
	user_t *u = NULL;
	if(NULL == (u = (user_t *) malloc(sizeof(user_t))))
		return NULL;

	u->name = strdup(name);
	u->age = age;

	fprintf(stdout, "new %s p:%p\n", u->name, u);
	return u;
}

void freeuser(user_t *u) {
	fprintf(stdout, "free %s p:%p\n", u->name, u);
	free(u->name);
	free(u);
	u = NULL;
}

int main(int ac, char **av) {

	user_t *u1 = NULL;
	user_t *u2 = NULL;
	user_t *np = NULL;

	if(NULL == (u1  = newuser("J4", 31)))
		return EXIT_FAILURE;

	if(NULL == (u2 = newuser("Angel", 30)))
		return EXIT_FAILURE;

	if(NULL == (np = (user_t *) malloc(sizeof(user_t))))
		return EXIT_FAILURE;

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
		freeuser(head.lh_first);
		LIST_REMOVE(head.lh_first, users);
	}

	return EXIT_SUCCESS;
}
