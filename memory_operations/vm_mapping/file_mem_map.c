#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define PAGE_SIZE 4096

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s inpput_file output_file\n", argv[0]);
        return 1;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];
    
    int fd = open(input_filename, O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    struct stat file_info;

    if (fstat(fd, &file_info) == -1)
    {
        perror("fstat");
        close(fd);
        return 1;
    }

    size_t file_size = file_info.st_size;

    if (file_size == 0)
    {
        fprintf(stderr, "Error: input file is empty.\n");
        close(fd);
        return 1;
    }

    char *data = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

    if (data == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    FILE *out = fopen(output_filename, "w");

    if (out == NULL)
    {
        perror("fopen");
        munmap(data, file_size);
        close(fd);
        return 1;
    }

    fprintf(out, "Input file: %s\n", input_filename);
    fprintf(out, "File size: %zu bytes\n", file_size);
    fprintf(out, "Mapped file starts at virtual address: %p\n\n", (void *)data);

    fprintf(out, "Reading file every %d bytes:\n\n", PAGE_SIZE);

    for (size_t i = 0; i < file_size; i += PAGE_SIZE)
    {
        fprintf(out,
                "data[%5zu] address = %p, value = %02X\n",
                i,
                (void *)&data[i],
                (unsigned char)data[i]);
    }

    fclose(out);
    munmap(data, file_size);
    close(fd);

    printf("Output written to: %s\n", output_filename);

    return 0;
}