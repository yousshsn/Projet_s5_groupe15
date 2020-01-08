#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>

/* affiche le header passé en paramètre
  paramètre : Elf64_Ehdr* header */
void print_header(Elf64_Ehdr* header);

/* affiche la table des sections passée en paramètre
  paramètres : Elf64_Ehdr* header
               Elf64_Shdr* sections_tab
               char* sh_str */
void print_sections_tab(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, char* sh_str);

/* affiche le contenu d'une section à partir de son numéro passé en paramètre
  paramètres : Elf64_Ehdr* header
               Elf64_Shdr* sections_tab
               char* sh_str
               uint8_t* data
               int* section_nb */
void print_section_content_from_nb(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, char* sh_str, uint8_t* data, int* section_nb);

/* affiche le contenu d'une section à partir de son nom passé en paramètre
   paramètres : Elf64_Ehdr* header
                Elf64_Shdr* sections_tab
                char* sh_str, uint8_t* data
                const char* section_name */
void print_section_content_from_name(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, char* sh_str, uint8_t* data, const char* section_name);

/* affiche la table des symboles passée en paramètre
  paramètres : Elf32_Sym* symbols_table
               int* nb_symbols */
void print_symbols_table(Elf32_Sym* symbols_table, int* nb_symbols);

/* affiche les tables de réimplantation passées en paramètre
   paramètres : Elf64_Ehdr* header
                Elf64_Shdr* sections_tab
                Elf64_Shdr* header_reloc_tab
                Elf32_Rel* relocation_table
                FILE* file */
void print_relocation_table(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, Elf64_Shdr* header_reloc_tab, Elf32_Rel* relocation_table, FILE* file);

#endif
