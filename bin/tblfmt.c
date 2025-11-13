#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024
#define MAX_HEADER_COLS  80

static char ***rows;
static int nrows, szrows;
static int ncols;

static void analyzeHeader(char *line);
static void parseRow(char *line);
static void fmt();
static void appendRow(char **cols);
static void skipEmptyLines(char *lineBuffer);
static char *rightPad(char *s, int max);
static char *filled(char c, int len);
static char *trimSpaces(char *s);
static int max(int a, int b);

int
main()
{
	char lineBuffer[LINE_BUFFER_SIZE];
	char *line;

	rows = NULL;
	nrows, szrows = 0;
	ncols = 0;

	skipEmptyLines(lineBuffer);

	line = trimSpaces(lineBuffer);
	if (line[0] != '|') {
		fprintf(stderr, "malformed table header\n");
		return 1;
	}

	analyzeHeader(line);
	fgets(lineBuffer, sizeof(lineBuffer), stdin); /* skip separator */
	while (fgets(lineBuffer, sizeof(lineBuffer), stdin)) {
		line = trimSpaces(lineBuffer);
		parseRow(line);
	}

	fmt();

	return 0;
}

static void
analyzeHeader(char *line)
{
	char **row;
	char *tok;

	row = malloc(MAX_HEADER_COLS * sizeof(*row));
	assert(row);

	for (tok = strtok(line, "|"); tok != NULL; tok = strtok(NULL, "|")) {
		row[ncols++] = trimSpaces(strdup(tok));
	}

	appendRow(row);
}

static void
parseRow(char *line)
{
	char **row;
	char *tok;
	int i;

	row = malloc(ncols * sizeof(*row));
	assert(row);

	i = 0;
	for (tok = strtok(line, "|"); tok != NULL; tok = strtok(NULL, "|")) {
		if (i == ncols) {
			fprintf(stderr, "malformed table\n");
			exit(1);
		}
		row[i++] = trimSpaces(strdup(tok));
	}

	appendRow(row);
}

static void
fmt()
{
	int i, j, len, *colLens;

	colLens = malloc(ncols * sizeof(*colLens));
	assert(colLens);
	memset(colLens, 0, ncols * sizeof(*colLens));

	for (i = 0; i < nrows; i++) {
		for (j = 0; j < ncols; j++) {
			len = strlen(rows[i][j]);
			colLens[j] = max(colLens[j], len);
		}
	}

	for (j = 0; j < ncols; j++) {
		printf("| %s ", rightPad(rows[0][j], colLens[j]));
	}
	printf("|\n");

	for (j = 0; j < ncols; j++) {
		printf("| %s ", filled('-', colLens[j]));
	}
	printf("|\n");

	for (i = 1; i < nrows; i++) {
		for (j = 0; j < ncols; j++) {
			printf("| %s ", rightPad(rows[i][j], colLens[j]));
		}
		printf("|\n");
	}
}

static void
appendRow(char **row)
{
	if (nrows == szrows) {
		szrows += 10; /* 10 is arbitrary */
		rows = realloc(rows, szrows * sizeof(*rows));
	}
	rows[nrows++] = row;
}

static void
skipEmptyLines(char *lineBuffer)
{
	char *line;

	while (fgets(lineBuffer, LINE_BUFFER_SIZE, stdin)) {
		line = trimSpaces(lineBuffer);
		if (strlen(line))
			break;
	}
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
filled(char c, int len)
{
	char *buf;

	buf = malloc(len + 1);
	assert(buf);
	memset(buf, c, len + 1);

	return buf;
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