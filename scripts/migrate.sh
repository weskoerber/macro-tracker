#!/usr/bin/env bash

DIR=$(dirname $0)
DBNAME=$1

FILES=$(find $DIR/../migrations/ -name "*.sql" -type f)

for file in $FILES; do
    echo "Migrating $(basename $file)"
    cat $file | sqlite3 $DIR/../$DBNAME
done
