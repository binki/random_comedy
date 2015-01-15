#include <stdio.h>
#include <string.h>

static int do_column(char *line, const char *column_name, const char *print_and_suffix, char **lasts)
{
  char *tok;
  const char separator[] = { (char)0xb5, '\0', };

  char *quotes_lasts;
  const char *quotes_separators = "'";

  tok = strtok_r(line, separator, lasts);
  if (!tok)
    {
      fprintf(stderr, "Unable to read field %s\n", column_name);
      return 1;
    }
  if (!print_and_suffix)
    return 0;

  fputs("'", stdout);
  /* print out escaped (doubled) quotes. */
  tok = strtok_r(tok, quotes_separators, &quotes_lasts);
  while (tok)
    {
      fputs(tok, stdout);
      if ((tok = strtok_r(NULL, quotes_separators, &quotes_lasts)))
        fputs("''", stdout);
    }
  printf("'%s", print_and_suffix);
  return 0;
}

int main(int argc, const char *const argv[])
{
  char *line = NULL;
  size_t line_n;
  ssize_t line_len;

  char *tok_lasts;

  const int batch_size = 32;
  int batch_i = 0;
  short first = 1;

  while ((line_len = getline(&line, &line_n, stdin)) != (ssize_t)-1)
    {
      if (batch_i == 0)
        {
          if (!first)
            fputs(";\n", stdout);
          fputs("  INSERT INTO lrb_quotes VALUES\n", stdout);
        }
      else
        if (!first)
          fputs(",\n", stdout);
      first = 0;
      batch_i = (batch_i + 1) % batch_size;

      fputs("(", stdout);
      if (0
          || do_column(line, "id", ",", &tok_lasts)
          || do_column(NULL, "submitter", NULL, &tok_lasts)
          || do_column(NULL, "quote", ")", &tok_lasts))
        return 1;
    }
  fputs(";\n", stdout);
  return 0;
}
