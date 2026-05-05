/*
 * generate_file.c
 *
 * Generates a file of a specified size filled with predictable data.
 *
 * Usage:
 *   ./generate_file output.txt 5 KB
 *
 * Notes:
 * - Size must be an integer
 * - Maximum size: 1 GB
 * - Writes in 4 KB chunks to mimic page-sized writes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE_BYTES 1073741824ULL   // 1 GB limit
#define CHUNK_SIZE 4096                // Matches typical page size

// Converts unit string to byte multiplier
unsigned long long get_multiplier(const char *unit)
{
    if (strcmp(unit, "B") == 0) return 1ULL;
    if (strcmp(unit, "KB") == 0) return 1024ULL;
    if (strcmp(unit, "MB") == 0) return 1024ULL * 1024ULL;
    if (strcmp(unit, "GB") == 0) return 1024ULL * 1024ULL * 1024ULL;
    return 0;
}

// Validates that input string contains only digits
int is_integer(const char *str)
{
    if (str == NULL || *str == '\0')
        return 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)str[i]))
            return 0;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s output_file size unit\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *size_str = argv[2];
    char *unit = argv[3];

    if (!is_integer(size_str))
    {
        fprintf(stderr, "Error: size must be an integer.\n");
        return 1;
    }

    unsigned long long size = strtoull(size_str, NULL, 10);
    unsigned long long multiplier = get_multiplier(unit);

    if (multiplier == 0)
    {
        fprintf(stderr, "Error: unit must be B, KB, MB, or GB.\n");
        return 1;
    }

    unsigned long long total_bytes = size * multiplier;

    if (total_bytes == 0 || total_bytes > MAX_SIZE_BYTES)
    {
        fprintf(stderr, "Error: file size must be between 1 byte and 1 GB.\n");
        return 1;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("fopen");
        return 1;
    }

    char buffer[CHUNK_SIZE];

    // Fill buffer with random pattern (A-Z)
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        buffer[i] = 'A' +  rand() % 26;
    }

    unsigned long long bytes_written = 0;

    // Write file in chunks to control memory usage
    while (bytes_written < total_bytes)
    {
        unsigned long long remaining = total_bytes - bytes_written;
        size_t bytes_to_write = remaining < CHUNK_SIZE ? remaining : CHUNK_SIZE;

        size_t written = fwrite(buffer, 1, bytes_to_write, fp);

        if (written != bytes_to_write)
        {
            perror("fwrite");
            fclose(fp);
            return 1;
        }

        bytes_written += written;
    }

    fclose(fp);

    printf("Created file: %s\n", filename);
    printf("Size: %llu bytes\n", total_bytes);

    return 0;
}