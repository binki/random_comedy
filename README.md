To test:

    DBFILE=database.sqlite3
    rm -f "${DBFILE}"
    gcc -o comedy4sqlite{,.c}
    { cat bot_schema.sql; ./comedy4sqlite < random_comedy.txt; echo 'SELECT * FROM lrb_quotes;'; } | sqlite3 "${DBFILE}" | wc -l
    wc -l random_comedy.txt

The `random_comedy.txt` originates from
http://beige-box.com/random_comedy.txt.
