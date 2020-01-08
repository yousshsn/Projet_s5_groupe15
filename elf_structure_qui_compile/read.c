#include "read.h"

/* ouvre et renvoie le fichier de nom elf_file passé en paramètre
   paramètres : const char* elf_file
               const char* mode */
FILE* open_file(const char* elf_file, const char* mode) {
  FILE* file = fopen(elf_file, mode);
  return file;
}

/* récupère les données du fichier de nom elf_file passé en paramètre
   paramètre : const char* elf_file */
uint8_t* getData(const char* elf_file) {
  uint8_t* data = malloc(sizeof(uint8_t));
  int fd = open(elf_file, O_RDONLY);
  data = mmap(NULL, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED, fd, 0);
  close(fd);
  return data;
}

/* lit et affecte le header depuis le fichier file passée en paramètre
   paramètres : Elf64_Ehdr* header
                FILE* file */
void read_header(Elf64_Ehdr* header, FILE* file) {
  int r = 0;
  if (file) {
    fseek(file, 0, SEEK_SET);
    int r = fread(header, sizeof(Elf64_Ehdr), 1, file);
    if (!r) {
      printf("Erreur de lecture\n");
    }
  } else {
    printf("Le fichier spécifié est introuvable\n");
  }
  // pour éviter l'erreur de compilation
  r = r + 0;
}

/* lit et affecte les headers de section depuis le fichier file passée en paramètre
   paramètres : Elf64_Ehdr* header
                Elf64_Shdr* sections_tab
                FILE* file */
void read_section_header(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, FILE* file) {
  int r = 0;
  if (file) {
    fseek(file, header->e_shoff, SEEK_SET);
    r = fread(sections_tab, sizeof(Elf64_Shdr)*header->e_shnum, 1, file);
    if (!r) {
      printf("Erreur de lecture\n");
    }
  } else {
    printf("Le fichier spécifié est introuvable\n");
  }
  // pour éviter l'erreur de compilation
  r = r + 0;
}

/* lit et renvoie la table des symboles depuis le fichier file passé en paramètre
   paramètres : Elf64_Ehdr* header
                Elf64_Shdr* sections_tab
                int* nb_symbols
                FILE* file */
Elf32_Sym* read_symbol_table(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, int* nb_symbols, FILE* file) {
  Elf32_Sym* symbols_table = NULL;
  int r = 0;
  if (file) {
    for (int i = 0; i < header->e_shnum; i++) {
      if (sections_tab[i].sh_type == SHT_SYMTAB || sections_tab[i].sh_type == SHT_DYNSYM) {
        fseek(file, sections_tab[i].sh_offset, SEEK_SET);
        *nb_symbols = sections_tab[i].sh_size / sections_tab[i].sh_entsize;
        symbols_table = malloc(sizeof(Elf32_Sym)*(*nb_symbols));
        for(int j = 0; j < *nb_symbols; j++){
          r = fread(&symbols_table[j].st_name, sizeof(Elf32_Word), 1, file);
          r = fread(&symbols_table[j].st_value, sizeof(Elf32_Addr), 1, file);
          r = fread(&symbols_table[j].st_size, sizeof(Elf32_Word), 1, file);
          r = fread(&symbols_table[j].st_info, sizeof(unsigned char), 1, file);
          r = fread(&symbols_table[j].st_other, sizeof(unsigned char), 1, file);
          r = fread(&symbols_table[j].st_shndx, sizeof(Elf32_Half), 1, file);
        }
      }
    }
  } else {
    printf("Le fichier spécifié est introuvable\n");
    // pour éviter l'erreur de compilation
    r = r + 0;
  }
  return symbols_table;
}

/* lit et affecte les tables de réimplantation depuis le fichier file passé en paramètre
   paramètres : Elf64_Shdr* sections_tab
                Elf32_Rel* relocation_table
                int i
                FILE* file */
void read_relocation_table(Elf64_Shdr* sections_tab, Elf32_Rel* relocation_table, int i, FILE* file) {
  int r = 0;
  if (file) {
    fseek(file, sections_tab->sh_offset + sections_tab->sh_addr + sizeof(Elf32_Rel)*i, SEEK_SET);
    r = fread(relocation_table, sizeof(Elf32_Rel), 1, file);
  } else {
    printf("Le fichier spécifié est introuvable\n");
    // pour éviter l'erreur de compilation
    r = r + 0;
  }
}

/* lit et renvoie la table des strings depuis le descripteur de fichier fd passé en paramètre
   paramètres : int32_t fd
                Elf64_Shdr* section_header */
char* read_str_tab(int32_t fd, Elf64_Shdr* section_header) {
  char* buffer = malloc(section_header->sh_size);
	if (!buffer) {
	   printf("erreur d'allocation pour la table des str");
	}

	if (!(lseek(fd, (off_t) section_header->sh_offset, SEEK_SET) == (off_t) section_header->sh_offset)) {
		printf("erreur alignement ou decalage (str_tab)");
	}

	if (!(read(fd, (void *) buffer, section_header->sh_size) == section_header->sh_size)) {
		printf("erreur taille (str_tab)");
	}
	return buffer;
}

/* lit et renvoie la section depuis le descripteur de fichier fd passé en paramètre
   paramètres : int32_t fd
                Elf64_Shdr* section_header */
char* read_section(int32_t fd, Elf64_Shdr* section_header) {
  char* buffer = malloc(section_header->sh_size);
	if (!buffer) {
	printf("erreur d'allocation pour la section");
	}

	if (!(lseek(fd, (off_t) section_header->sh_offset, SEEK_SET) == (off_t) section_header->sh_offset)) {
		printf("erreur alignement ou decalage (read_section)");
	}

	if (!(read(fd, (void*) buffer, section_header->sh_size) == section_header->sh_size)) {
		printf("erreur taille (read_section)");
	}
	return buffer;
}
