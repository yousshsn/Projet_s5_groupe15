#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "print.h"

void print_elf_header(const char* elf_file) {
  FILE* file = open_file(elf_file, "rb");
  Elf64_Ehdr* header = malloc(sizeof(Elf64_Ehdr));
  read_header(header, file);
  print_header(header);
  free(header);
}

void print_elf_sections_tab(const char* elf_file) {
  FILE* file = open_file(elf_file, "rb");
  Elf64_Ehdr* header = malloc(sizeof(Elf64_Ehdr));
  read_header(header, file);
  Elf64_Shdr* sections_tab = malloc(sizeof(Elf64_Shdr)*header->e_shnum);
  read_section_header(header, sections_tab, file);
  char* sh_str = read_str_tab(fileno(file), &sections_tab[header->e_shstrndx]);
  print_sections_tab(header, sections_tab, sh_str);
  free(header);
  free(sections_tab);
}

void print_elf_section_content_from_nb(const char* elf_file, int* section_nb) {
  FILE* file = open_file(elf_file, "rb");
  Elf64_Ehdr* header = malloc(sizeof(Elf64_Ehdr));
  read_header(header, file);
  Elf64_Shdr* sections_tab = malloc(sizeof(Elf64_Shdr)*header->e_shnum);
  read_section_header(header, sections_tab, file);
  char* sh_str = read_str_tab(fileno(file), &sections_tab[header->e_shstrndx]);
  uint8_t* data = malloc(sizeof(uint32_t));
  data = getData(elf_file);
  print_section_content_from_nb(header, sections_tab, sh_str, data, section_nb);
  free(header);
  free(sections_tab);
}

void print_elf_section_content_from_name(const char* elf_file, const char* section_name) {
  FILE* file = open_file(elf_file, "rb");
  Elf64_Ehdr* header = malloc(sizeof(Elf64_Ehdr));
  read_header(header, file);
  Elf64_Shdr* sections_tab = malloc(sizeof(Elf64_Shdr)*header->e_shnum);
  read_section_header(header, sections_tab, file);
  char* sh_str = read_str_tab(fileno(file), &sections_tab[header->e_shstrndx]);
  uint8_t* data = malloc(sizeof(uint32_t));
  data = getData(elf_file);
  print_section_content_from_name(header, sections_tab, sh_str, data, section_name);
  free(header);
  free(sections_tab);
}

void print_elf_symbols_table(const char* elf_file) {
  FILE* file = open_file(elf_file, "rb");
  Elf64_Ehdr* header = malloc(sizeof(Elf64_Ehdr));
  read_header(header, file);
  Elf64_Shdr* sections_tab = malloc(sizeof(Elf64_Shdr)*header->e_shnum);
  read_section_header(header, sections_tab, file);
  int* nb_symbols = malloc(sizeof(int));
  Elf32_Sym* symbols_table = read_symbol_table(header, sections_tab, nb_symbols, file);
  print_symbols_table(symbols_table, nb_symbols);
  free(header);
  free(sections_tab);
  free(nb_symbols);
}

void print_elf_relocation_table(const char* elf_file) {
  FILE* file = open_file(elf_file, "rb");
  Elf64_Ehdr* header = malloc(sizeof(Elf64_Ehdr));
  read_header(header, file);
  Elf64_Shdr* sections_tab = malloc(sizeof(Elf64_Shdr)*header->e_shnum);
  read_section_header(header, sections_tab, file);
  Elf64_Shdr* header_reloc_tab = malloc(sizeof(Elf64_Shdr));
  for (int i = 0; i < header->e_shnum; i++) {
    if (sections_tab[i].sh_type == SHT_RELA) {
      *header_reloc_tab = sections_tab[i];
    }
  }
  Elf32_Rel* relocation_table = malloc(sizeof(Elf32_Rel));
  print_relocation_table(header, sections_tab, header_reloc_tab, relocation_table, file);
  free(header);
  free(sections_tab);
  free(header_reloc_tab);
}

int main(int argc, char const *argv[]) {
  if (argc > 2) {
    if (!strcmp(argv[1], "-h")) {
      print_elf_header(argv[2]);
    } else if (!strcmp(argv[1], "-S")) {
      print_elf_sections_tab(argv[2]);
    } else if (!strcmp(argv[1], "-x")) {
      int section_nb = atoi(argv[2]);
      if (section_nb != 0) {
        print_elf_section_content_from_nb(argv[3], &section_nb);
      } else {
        print_elf_section_content_from_name(argv[3], argv[2]);
      }
    } else if (!strcmp(argv[1], "-s")) {
      print_elf_symbols_table(argv[2]);
    } else if (!strcmp(argv[1], "-r")) {
      print_elf_relocation_table(argv[2]);
    }
  }
  return 0;
}
