create table ingredients (
    ingredient_id integer primary key,
    meal_id integer,
    ingredient_name varchar(255),
    ingredient_amount real,
    ingredient_protein real,
    ingredient_carbs real,
    ingredient_fiber real,
    ingredient_fat real,
    ingredient_calories real
);

create index index_ingredients_meal
on ingredients(meal_id);
