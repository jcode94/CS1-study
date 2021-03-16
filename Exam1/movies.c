#include <stdio.h>
#include <string.h>

#define LEN_TITLE 21

typedef struct movie movie;
typedef struct actor actor;
struct movie {
   int num_actors;
   char * title;
   actor * actor_array;
};
struct actor {
   char * name;
   int birth_year;
   int salary;
};
movie * readMovies() {
	int M, A, birth_year, salary;
	char name[LEN_TITLE], char title[LEN_TITLE];
	scanf("%d", &M);
	
	movie * movieList = calloc(M, sizeof(movie));
	
	// Setting up movie info
	for (int i = 0; i < M; ++i) {
		scanf("%d", &A);
		movieList[i]->num_actors = A;
		scanf("%s", title);
		movieList[i]->title = calloc(strlen(title) + 1, sizeof(char));
		strcpy(movieList[i]->title, title);
		movieList[i]->actor_array = calloc(movieList[i]->num_actors, sizeof(actor));
		// Filling in actor info
		for (int j = 0; j < A; ++j) {
			scanf("%s", name);
			movieList[i]->actor_array[i]->name = calloc(strlen(name) + 1, sizeof(char));
			strcpy(movieList[i]->actor_array[i]->name, name);
			scanf("%d", &birth_year);
			scanf("%d", &salary);
			movieList[i]->actor_array->birth_year = birth_year;
			movieList[i]->actor_array->salary = salary;
		}
	}
	
	
	return movieList;
}