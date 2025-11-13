#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct row {
	char **vals;
	int nvals, szvals;
};

static struct row *rows;
static int nrows, szrows;

static void appendRow(struct row row);
static void appendValue(struct row *row, char *val);
static char *rightPad(char *s, int max);
static char *trimSpaces(char *s);
static int max(int a, int b);

int
main(int argc, char **argv)
{
	char *c, lineBuffer[1024], *line, *tok;
	int i, j, colLens[1024];
	struct row row;

	rows = NULL;
	nrows = 0;
	szrows = 0;

	argc--;
	argv++;

	if (argc != 1) {
		fprintf(stderr, "usage: align <character>\n");
		return 1;
	}

	if (strlen(argv[0]) != 1) {
		fprintf(stderr, "usage: align <character>\n");
		return 1;
	}

	c = argv[0];

	while (fgets(lineBuffer, sizeof(lineBuffer), stdin)) {
		memset(&row, 0, sizeof(row));

		line = strdup(trimSpaces(lineBuffer));
		for (tok = strtok(line, c); tok != NULL; tok = strtok(NULL, c)) {
			tok = trimSpaces(tok);
			appendValue(&row, tok);
		}

		appendRow(row);
	}

	for (i = 0; i < nrows; i++) {
		row = rows[i];
		for (j = 0; j < row.nvals; j++) {
			colLens[j] = max(colLens[j], strlen(row.vals[j]));
		}
	}

	for (i = 0; i < nrows; i++) {
		row = rows[i];
		for (j = 0; j < row.nvals; j++) {
			printf("%s", rightPad(row.vals[j], colLens[j]));
			if (j < row.nvals - 1) {
				printf(" %s ", c);
			}
		}
		printf("\n");
	}
}

static void
appendRow(struct row row)
{
	if (nrows == szrows) {
		szrows += 10; /* 10 is arbitrary */
		rows = realloc(rows, szrows * sizeof(*rows));
	}
	rows[nrows++] = row;
}

static void
appendValue(struct row *row, char *val)
{
	if (row->nvals == row->szvals) {
		row->szvals += 10; /* 10 is arbitrary */
		row->vals = realloc(row->vals, row->szvals * sizeof(*row->vals));
	}
	row->vals[row->nvals++] = val;
}

static char *
rightPad(char *s, int max)
{
	char *buf;

	buf = malloc(max + 1);
	assert(buf);
	memset(buf, ' ', max + 1);

	return memcpy(buf, s, strlen(s));
}

static char *
trimSpaces(char *s)
{
	int len;

	while (isspace(*s) && *s != '\0')
		s++;
	if (*s == '\0')
		return s;

	len = strlen(s);
	while (len && isspace(s[len - 1]))
		len--;

	s[len] = '\0';
	return s;
}

static int
max(int a, int b)
{
	if (a < b) {
		return b;
	}
	return a;
}