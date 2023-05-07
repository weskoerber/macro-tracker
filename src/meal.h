#ifndef MEAL_H
#define MEAL_H

#include "linkedlist.h"
#include "main.h"

struct meal_t {
  long meal_id;
  char *meal_name;
  long meal_date;
  long meal_servings;
};

int meals_all(sqlite3 *db, struct linkedlist_t **meals);

void meal_print_all(struct linkedlist_t *meals);
void meal_print(struct meal_t *meal);

#endif // MEAL_H
