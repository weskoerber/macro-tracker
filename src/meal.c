#include "meal.h"
#include <stdio.h>
#include <string.h>

struct linkedlist_t *meals_internal = NULL;

int select_callback(void *, int, char **, char **);

int meals_all(sqlite3 *db, struct linkedlist_t **meals) {
  const char *sql = "select * from meals;";
  char *err_msg = NULL;
  int records = -1;

  printf("\nQUERY: %s\n\n", sql);

  ll_create(&meals_internal, sizeof(struct meal_t));

  struct meal_t tmp;

  int result = sqlite3_exec(db, sql, select_callback, (void *)&tmp, &err_msg);

  if (result != SQLITE_OK) {
    fprintf(stderr, "Failed to select data\n");
    fprintf(stderr, "SQL error (%d): %s\n", result, err_msg);

    int code = sqlite3_extended_errcode(db);
    fprintf(stderr, "Extended error (%d): %s\n", code, sqlite3_errstr(code));

    sqlite3_free(err_msg);
    sqlite3_close(db);

    return 0;
  }

  *meals = meals_internal;
  return ll_count(*meals);
}

void meal_print_all(struct linkedlist_t *meals) {
  if (!meals) {
    fprintf(stderr, "parameter was a NULL pointer\n");
    return;
  }

  struct meal_t *meal;
  while (ll_next(meals, (void **)&meal)) {
    meal_print(meal);
    printf("\n");
  }
}

void meal_print(struct meal_t *meal) {
  if (!meal) {
    fprintf(stderr, "parameter was a NULL pointer\n");
    return;
  }

  printf("meal_id => %ld\n", meal->meal_id);
  printf("meal_date => %ld\n", meal->meal_date);
  printf("meal_name => %s\n", meal->meal_name);
  printf("meal_servings => %ld\n", meal->meal_servings);
}

int select_callback(void *buffer, int count, char **data, char **columns) {
  struct meal_t *tmp = (struct meal_t *)buffer;

  for (int i = 0; i < count; i++) {
    const char *column = columns[i];
    const char *value = data[i];

    if (!strcmp(column, "meal_id")) {
      long id = strtol(value, NULL, 10);
      tmp->meal_id = id;
    } else if (!strcmp(column, "meal_name")) {
      unsigned long len = strlen(value) + 1;
      tmp->meal_name = malloc(len);
      strncpy(tmp->meal_name, value, len);
      tmp->meal_name[len] = '\0';
    } else if (!strcmp(column, "meal_date")) {
      long date = strtol(value, NULL, 10);
      tmp->meal_date = date;
    } else if (!strcmp(column, "meal_servings")) {
      long servings = strtol(value, NULL, 10);
      tmp->meal_servings = servings;
    }
  }

  ll_append(meals_internal, tmp);

  return 0;
}
