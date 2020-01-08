#ifndef __READ_H__
#define __READ_H__

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

/* ouvre et renvoie le fichier de nom elf_file passé en paramètre
   paramètres : const char* elf_file
               const char* mode */
FILE* open_file(const char* elf_file, const char* mode);

/* récupère les données du fichier de nom elf_file passé en paramètre
   paramètre : const char* elf_file */
uint8_t* getData(const char* elf_file);

/* lit et affecte le header depuis le fichier file passée en paramètre
   paramètres : Elf64_Ehdr* header
                FILE* file */
void read_header(Elf64_Ehdr* header, FILE* file);

/* lit et affecte les headers de section depuis le fichier file passée en paramètre
   paramètres : Elf64_Ehdr* header
                Elf64_Shdr* sections_tab
                FILE* file */
void read_section_header(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, FILE* file);

/* lit et renvoie la table des symboles depuis le fichier file passé en paramètre
   paramètres : Elf64_Ehdr* header
                Elf64_Shdr* sections_tab
                int* nb_symbols
                FILE* file */
Elf32_Sym* read_symbol_table(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, int* nb_symbols, FILE* file);

/* lit et affecte les tables de réimplantation depuis le fichier file passé en paramètre
   paramètres : Elf64_Shdr* sections_tab
                Elf32_Rel* relocation_table
                int i
                FILE* file */
void read_relocation_table(Elf64_Shdr* sections_tab, Elf32_Rel* relocation_table, int i, FILE* file);

/* lit et renvoie la table des strings depuis le descripteur de fichier fd passé en paramètre
   paramètres : int32_t fd
                Elf64_Shdr* section_header */
char* read_str_tab(int32_t fd, Elf64_Shdr* section_header);

/* lit et renvoie la section depuis le descripteur de fichier fd passé en paramètre
   paramètres : int32_t fd
                Elf64_Shdr* section_header */
char* read_section(int32_t fd, Elf64_Shdr* section_header);

#endif
