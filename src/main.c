#include "main.h"
#include "linkedlist.h"
#include "meal.h"
#include <sqlite3.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Missing positional argument\n");
    exit(1);
  }

  printf("sqlite3 version: %s\n", sqlite3_libversion());

  sqlite3 *db;

  int result = sqlite3_open(argv[1], &db);
  sqlite3_extended_result_codes(db, 1);

  if (result != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));

    sqlite3_close(db);

    return 1;
  }

  struct linkedlist_t *meals;
  int records = meals_all(db, &meals);
  meal_print_all(meals);

  sqlite3_close(db);
  return 0;
}
