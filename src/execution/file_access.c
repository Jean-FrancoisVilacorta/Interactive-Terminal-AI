/*
** EPITECH PROJECT, 2025
** B-PSU-200-PAR-2-1-42sh-rayan.ouerdane
** File description:
** file_access
*/

#include "my.h"
#include "shell.h"
#include <elf.h>
#include <fcntl.h>
#include <sys/stat.h>

int check_basic_access(char *path)
{
    struct stat st;

    if (access(path, F_OK) != 0) {
        my_dprintf(STDERR_FD, "%s: Command not found.\n", path);
        return EXIT_FAILURE;
    }
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
        my_dprintf(STDERR_FD, "%s: Permission denied.\n", path);
        return EXIT_FAILURE;
    }
    if (access(path, X_OK) != 0) {
        my_dprintf(STDERR_FD, "%s: Permission denied.\n", path);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int check_elf_header(int fd, char *path)
{
    Elf64_Ehdr elf_header;

    if (read(fd, &elf_header, sizeof(elf_header)) != sizeof(elf_header))
        return EXIT_SUCCESS;
    if (elf_header.e_ident[EI_MAG0] != ELFMAG0 ||
        elf_header.e_ident[EI_MAG1] != ELFMAG1 ||
        elf_header.e_ident[EI_MAG2] != ELFMAG2 ||
        elf_header.e_ident[EI_MAG3] != ELFMAG3) {
            my_dprintf(STDERR_FD, "%s: Exec format error. Binary file not "
                "executable.\n", path);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int check_file_access(char *path)
{
    int fd = 0;
    int result = 0;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return EXIT_FAILURE;
    result = check_elf_header(fd, path);
    close(fd);
    return result;
}
