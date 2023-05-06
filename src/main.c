#include "main.h"
#include <sqlite3.h>
#include <stdio.h>

int callback(void *, int, char **, char **);

int main(int argc, char **argv) {
  if (argc < 1) {
    fprintf(stderr, "No database provided");
    return 1;
  }

  printf("sqlite3 version: %s\n", sqlite3_libversion());

  sqlite3 *db;
  char *err_msg = NULL;

  int result = sqlite3_open(argv[1], &db);
  sqlite3_extended_result_codes(db, 1);

  if (result != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));

    sqlite3_close(db);

    return 1;
  }

  char *sql = "select * from meals;";
  result = sqlite3_exec(db, sql, callback, NULL, &err_msg);

  if (result != SQLITE_OK) {
    fprintf(stderr, "Failed to select data\n");
    fprintf(stderr, "SQL error (%d): %s\n", result, err_msg);

    int code = sqlite3_extended_errcode(db);
    fprintf(stderr, "Extended error (%d): %s\n", code, sqlite3_errstr(code));

    sqlite3_free(err_msg);
    sqlite3_close(db);

    return 1;
  }

  sqlite3_close(db);
  return 0;
}

int callback(void *_, int argc, char **argv, char **azColName) {
  _ = NULL;

  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf("\n");

  return 0;
}
