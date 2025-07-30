#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_next_line(int fd);

void assert_equal(const char *expected, const char *actual, const char *msg) {
    if ((expected == NULL && actual != NULL) ||
        (expected != NULL && actual == NULL) ||
        (expected && actual && strcmp(expected, actual) != 0)) {
        printf("❌ Test failed: %s\nExpected: [%s]\nActual: [%s]\n", msg, expected, actual);
        exit(1);
    } else {
        printf("✅ Passed: %s\n", msg);
    }
}

void test_get_next_line_simple_file() {
    int fd = open("test_file.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    char *line;

    line = get_next_line(fd);
    assert_equal("Hello, world!\n", line, "First line");

    free(line);
    line = get_next_line(fd);
    assert_equal("This is a test.\n", line, "Second line");

    free(line);
    line = get_next_line(fd);
    assert_equal("Last line.", line, "Third line (no newline)");

    free(line);
    line = get_next_line(fd);
    assert_equal(NULL, line, "EOF");

    close(fd);
}

int main() {
    test_get_next_line_simple_file();
    printf("🎉 All tests passed!\n");
    return 0;
}
