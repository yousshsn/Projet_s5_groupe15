#include "print.h"
#include "read.h"

// e_machine
#define EM_M32 1
#define EM_SPARC 2
#define EM_386 3
#define EM_68K 4
#define EM_88K 5
#define EM_860 7
#define EM_MIPS 8
#define EM_MIPS_RS4_BE 10
#define EM_FIRST_RESERVED 11
#define EM_LAST_RESERVED 16

/* affiche le header passé en paramètre
  paramètre : Elf64_Ehdr* header */
void print_header(Elf64_Ehdr* header) {
  printf("ELF Header : \n");
  //----MAGIC----
  if (header->e_ident[EI_MAG0]== 0x7f &&
    header->e_ident[EI_MAG1] == 'E' &&
    header->e_ident[EI_MAG2] == 'L' &&
    header->e_ident[EI_MAG3] == 'F') {
      printf("\tMagic\t:\t");
      for (int i = 0; i<16; i++) {
        if (header->e_ident[i] <= 0x0f) {
          printf("0");
        }
        printf("%x ", header->e_ident[i]);
      }
      printf("\n");
      //----CLASS----
      printf("\tClass\t:\t");
      switch (header->e_ident[EI_CLASS]) {
        case ELFCLASSNONE:
        printf("Invalid class\n");
        break;
        case ELFCLASS32:
        printf("ELF32\n");
        break;
        case ELFCLASS64:
        printf("ELF64\n");
        break;
      }
      //----DATA----
      printf("\tData\t:\t");
      switch (header->e_ident[EI_DATA]) {
        case ELFDATANONE:
        printf("Invalid data format\n");
        break;
        case ELFDATA2LSB:
        printf("2's complement, little endian\n");
        break;
        case ELFDATA2MSB:
        printf("2's complement, big endian\n");
        break;
      }
      //----VERSION----
      printf("\tVersion\t:\t");
      if (header->e_ident[EI_VERSION] == 0) {
        printf("0 (invalid)\n");
      } else if (header->e_ident[EI_VERSION] == EV_CURRENT) {
        printf("%d (current)\n", header->e_ident[EI_VERSION]);
      } else if (header->e_ident[EI_VERSION] > EV_CURRENT) {
        #ifdef EV_CURRENT
        #undef EV_CURRENT
        #endif
        #define EV_CURRENT header->e_ident[EI_VERSION]
        printf("%d (new version)\n",header->e_ident[EI_VERSION]);
      } else {
        printf("%d (old version)\n",header->e_ident[EI_VERSION]);
      }

      //----OS/ABI-----
      printf("\tOS/ABI\t:\t");
      switch (header->e_ident[EI_OSABI]) {
        case ELFOSABI_NONE:
        printf("Unspecified\n");
        break;
        case ELFOSABI_HPUX:
        printf("Hewlett-Packard HP-UX\n");
        break;
        case ELFOSABI_NETBSD:
        printf("NetBSD\n");
        break;
        case ELFOSABI_LINUX:
        printf("Linux\n");
        break;
        case ELFOSABI_SOLARIS:
        printf("Sun Solaris\n");
        break;
        case ELFOSABI_AIX:
        printf("AIX\n");
        break;
        case ELFOSABI_IRIX:
        printf("IRIX\n");
        break;
        case ELFOSABI_FREEBSD:
        printf("FreeBSD\n");
        break;
        case ELFOSABI_TRU64:
        printf("Compaq TRU64 UNIX\n");
        break;
        case ELFOSABI_MODESTO:
        printf("Novell Modesto\n");
        break;
        case ELFOSABI_OPENBSD:
        printf("Open BSD\n");
        break;
        default:
        printf("Architecture-specific value range\n");
        break;
      }

      //----ABI VERSION----
      printf("\tABI Version\t:\t");
      printf("%d\n", header->e_ident[EI_ABIVERSION]);

      //----TYPE-------
      printf("\tType\t:\t");
      switch (header->e_type) {
        case ET_NONE:
        printf("Invalid type\n");
        break;
        case ET_REL:
        printf("REL (Relocatable file)\n");
        break;
        case ET_EXEC:
        printf("EXEC (Executable file)\n");
        break;
        case ET_DYN:
        printf("DYN (Shared object file)\n");
        break;
        case ET_CORE:
        printf("CORE (Core file)\n");
        break;
        case ET_HIOS:
        printf("HIOS (Operating system-specific)\n");
        break;
        case ET_LOOS:
        printf("LOOS (Operating system-specific)\n");
        break;
        case ET_LOPROC:
        printf("LOPROC (Processor-specific)\n");
        break;
        case ET_HIPROC:
        printf("HIPROC (Processor-specific)\n");
        break;
        default:
        printf("Type non spécifié (erreur)\n");
        break;
      }
      //----MACHINE----
      printf("\tMachine\t:\t");
      switch (header->e_machine) {
        case ET_NONE:
        printf("No machine\n");
        break;
        case EM_M32:
        printf("AT&T WE 32100\n");
        break;
        case EM_SPARC:
        printf("SPARC\n");
        break;
        case EM_386:
        printf("Inter Architecture\n");
        break;
        case EM_68K:
        printf("Motorola 68000\n");
        break;
        case EM_88K:
        printf("Motorola 88000\n");
        break;
        case EM_860:
        printf("Intel 80860\n");
        break;
        case EM_MIPS:
        printf("MIPS RS3000 Big-Endian\n");
        break;
        case EM_MIPS_RS4_BE:
        printf("MIPS RS4000 Big-Endian\n");
        break;
        default:
        printf("Unspecified or reserved\n");
        break;
      }
      //----ENTRY POINT----
      printf("\tEntry point address\t:\t0x");
      printf("%lx\n", header->e_entry);

      //----START PROGRAM HEADER----
      printf("\tStart of program headers\t:\t");
      printf("%ld (bytes into file)\n", header->e_phoff);

      //----START SECTION HEADER----
      printf("\tStart of section headers\t:\t");
      printf("%ld (bytes into file)\n", header->e_shoff);

      //----FLAGS----
      printf("\tFlags\t:\t0x");
      printf("%x \n", header->e_flags);

      //----HEADER SIZE----
      printf("\tSize of this header\t:\t");
      printf("%d (bytes) \n", header->e_ehsize);

      //----PROGRAM HEADER----
      printf("\tSize of program headers\t:\t");
      printf("%d (bytes) \n", header->e_phentsize);

      printf("\tNumber of program headers\t:\t");
      printf("%d \n", header->e_phnum);

      //----SECTION HEADER----
      printf("\tSize of section headers\t:\t");
      printf("%d (bytes) \n", header->e_shentsize);

      printf("\tNumber of section headers\t:\t");
      printf("%d \n", header->e_shnum);

      //----INDEX TABLE----
      printf("\tSection header string table index:\t");
      printf("%d \n", header->e_shstrndx);
    } else {
      printf("Le fichier n'est pas au format ELF\n");
    }
  }

  /* affiche la table des sections passée en paramètre
    paramètres : Elf64_Ehdr* header
                 Elf64_Shdr* sections_tab
                 char* sh_str */
  void print_sections_tab(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, char* sh_str) {
    printf("There are %d section headers, starting at offset 0x%lx :\n",header->e_shnum, header->e_shoff);
    printf("\nSection Headers:\n");
    printf("[Nr]\tType\t\tAdress\t\tOffset\tSize\t\tEntsize\tFlags\tLink  Info\tAlign\tName\n" );
    for(int i = 0; i < header->e_shnum; i++){
      // Nr
      printf("[%d]\t",i);
      // TYPE
      switch (sections_tab[i].sh_type) {
        case SHT_NULL:
        printf("NULL\t\t");
        break;
        case SHT_PROGBITS:
        printf("PROGBITS\t");
        break;
        case SHT_SYMTAB:
        printf("SYMTAB\t\t");
        break;
        case SHT_STRTAB:
        printf("STRTAB\t\t");
        break;
        case SHT_RELA:
        printf("RELA\t\t");
        break;
        case SHT_HASH:
        printf("HASH\t\t");
        break;
        case SHT_DYNAMIC:
        printf("DYNAMIC\t");
        break;
        case SHT_NOTE:
        printf("NOTE\t\t");
        break;
        case SHT_NOBITS:
        printf("NOBITS\t\t");
        break;
        case SHT_REL:
        printf("REL\t\t");
        break;
        case SHT_SHLIB:
        printf("SHLIB\t\t");
        break;
        case SHT_DYNSYM:
        printf("DYNMISM\t");
        break;
        case SHT_NUM:
        printf("NUM\t\t");
        break;
        case SHT_LOPROC:
        printf("LOPROC\t");
        break;
        case SHT_HIPROC:
        printf("HIPROC\t");
        break;
        case SHT_LOUSER:
        printf("LOUSER\t");
        break;
        case SHT_HIUSER:
        printf("HIUSER\t");
        break;
        default:
        printf("ERR\t\t");
        break;
      }

      // ADDRESS
      printf("0x%08lx\t",sections_tab[i].sh_addr);

      // OFFSET
      printf("0x%08lx\t", sections_tab[i].sh_offset);

      // SIZE
      printf("0x%08lx\t",sections_tab[i].sh_size);

      // ENTSIZE
      printf("0x%08lx\t",sections_tab[i].sh_entsize);


      // FLAGS
      uint32_t flag=sections_tab[i].sh_flags;
      char* buffer ="WAXLMSIOGTCxoElp";
      // contient plusieurs characteres pour differents flags
      // la validité n'est testé que pour les flags W,A,X,M,S,I
      // L est très incertain

      for(int i=0;i<strlen(buffer);i++){
        if(flag%2){
          printf("%c",buffer[i]);
        }
        flag=flag>>1;
      }
      printf("\t");

      // LINK
      printf("%d\t",sections_tab[i].sh_link);
      // INFO
      printf("%d\t",sections_tab[i].sh_info);

      // ALIGN
      printf("%08lx\t",sections_tab[i].sh_addralign);

      // NAME
      printf("%s", (sh_str + sections_tab[i].sh_name));
      printf("\n");

    }
    printf("\nKey to Flags : \n");
    printf("W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\nL (link order), O (extra OS processing required), G (group), T (TLS),\nC (compressed), x (unknown), o (OS specific), E (exclude),\nl (large), p (processor specific)\n");
  }

  /* affiche le contenu d'une section à partir de son numéro passé en paramètre
    paramètres : Elf64_Ehdr* header
                 Elf64_Shdr* sections_tab
                 char* sh_str
                 uint8_t* data
                 int* section_nb */
  void print_section_content_from_nb(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, char* sh_str, uint8_t* data, int* section_nb) {
    for (int i = 0; i < header->e_shnum; i++) {
      size_t k;
      if (i == *section_nb) {
        printf("Hex dump of section %s\n", sh_str + sections_tab[i].sh_name);
        int h = 0;
        for (k = sections_tab[i].sh_offset; k < sections_tab[i].sh_offset + sections_tab[i].sh_size; k = k+4) {
          size_t tmp = k;
          printf("0x%07x %x%x%x%x", h, data[k], data[k+1], data[k+2], data[k+3]);
          k = k+4;
          printf(" %x%x%x%x", data[k], data[k+1], data[k+2], data[k+3]);
          k = k+4;
          printf(" %x%x%x%x", data[k], data[k+1], data[k+2], data[k+3]);
          k = k+4;
          printf(" %x%x%x%x ", data[k], data[k+1], data[k+2], data[k+3]);

          printf("%c%c%c%c", data[tmp], data[tmp+1], data[tmp+2], data[tmp+3]);
          tmp = tmp+4;
          printf("%c%c%c%c", data[tmp], data[tmp+1], data[tmp+2], data[tmp+3]);
          tmp = tmp+4;
          printf("%c%c%c%c", data[tmp], data[tmp+1], data[tmp+2], data[tmp+3]);
          tmp = tmp+4;
          printf("%c%c%c%c", data[tmp], data[tmp+1], data[tmp+2], data[tmp+3]);
          h++;
          printf("\n");
        }
      }
    }
    printf("\n");
  }

  /* affiche le contenu d'une section à partir de son nom passé en paramètre
     paramètres : Elf64_Ehdr* header
                  Elf64_Shdr* sections_tab
                  char* sh_str, uint8_t* data
                  const char* section_name */
  void print_section_content_from_name(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, char* sh_str, uint8_t* data, const char* section_name) {
    char* name_tmp;
    for(int i = 0; i < header->e_shnum; i++) {
      size_t k;
      name_tmp = sh_str + sections_tab[i].sh_name;
      if (strcmp (section_name, name_tmp) == 0) {
        printf("Hex dump of section %s\n", sh_str + sections_tab[i].sh_name);
        int h = 0;
        for (k = sections_tab[i].sh_offset; k < sections_tab[i].sh_offset + sections_tab[i].sh_size; k=k+4) {
          size_t tmp = k;
          printf("0x%07x %x%x%x%x", h, data[k],data[k+1],data[k+2],data[k+3]);
          k = k+4;
          printf(" %x%x%x%x", data[k],data[k+1],data[k+2],data[k+3]);
          k = k+4;
          printf(" %x%x%x%x", data[k],data[k+1],data[k+2],data[k+3]);
          k = k+4;
          printf(" %x%x%x%x ", data[k],data[k+1],data[k+2],data[k+3]);
          printf("%c%c%c%c", data[tmp],data[tmp+1],data[tmp+2],data[tmp+3]);
          tmp = tmp+4;
          printf("%c%c%c%c", data[tmp],data[tmp+1],data[tmp+2],data[tmp+3]);
          tmp = tmp+4;
          printf("%c%c%c%c", data[tmp],data[tmp+1],data[tmp+2],data[tmp+3]);
          tmp = tmp+4;
          printf("%c%c%c%c", data[tmp],data[tmp+1],data[tmp+2],data[tmp+3]);
          h++;
          printf("\n");
        }
      }
    }
    printf("\n");
  }

  /* affiche la table des symboles passée en paramètre
    paramètres : Elf32_Sym* symbols_table
                 int* nb_symbols */
  void print_symbols_table(Elf32_Sym* symbols_table, int* nb_symbols) {
    printf("Symbol table '.symtab' contains %d entries\n", *nb_symbols);
    printf("Num:\tValue\tSize\tType\tBind\tNdx\tName\n");
    for (int k = 0; k < *nb_symbols; k++) {
      /*
      switch (symbols_table[k].st_name) {
      case 0x0:
      printf("none\n");
      break;
      case 0x1:
      printf("name\n");
      break;
      case 0x7:
      printf("variable\n");
      break;
      case 0x11:
      printf("able\n");
      break;
      case 0x16:
      printf("able\n");
      break;
      case 0x24:
      printf("null string\n");
      break;
    }
    */

    printf("%3d: ", k);
    printf("%8x\t", symbols_table[k].st_value);
    printf("%3d\t", symbols_table[k].st_size);
    switch(ELF32_ST_TYPE(symbols_table[k].st_info)) {
      case 0:
      printf("NOTYPE\t");
      break;
      case 1:
      printf("OBJECT\t");
      break;
      case 2:
      printf("FUNC\t");
      break;
      case 3:
      printf("SECTION\t");
      break;
      case 4:
      printf("FILE\t");
      break;
      case 13:
      printf("LOPROC\t");
      break;
      case 15:
      printf("HIPROC\t");
      break;
    }
    switch(ELF32_ST_BIND(symbols_table[k].st_info)) {
      case 0:
      printf("LOCAL\t");
      break;
      case 1:
      printf("GLOBAL\t");
      break;
      case 2:
      printf("WEAK\t");
      break;
      case 13:
      printf("LOPROC\t");
      break;
      case 15:
      printf("HIPROC\t");
      break;
    }
    switch(symbols_table[k].st_shndx) {
      default:
      printf("%3d\t", symbols_table[k].st_shndx);
      break;
      case SHN_UNDEF:
      printf("UND\t");
      break;
      case SHN_ABS:
      printf("ABS\t");
      break;
    }
    printf("\n");
  }
}

/* affiche les tables de réimplantation passées en paramètre
   paramètres : Elf64_Ehdr* header
                Elf64_Shdr* sections_tab
                Elf64_Shdr* header_reloc_tab
                Elf32_Rel* relocation_table
                FILE* file */
void print_relocation_table(Elf64_Ehdr* header, Elf64_Shdr* sections_tab, Elf64_Shdr* header_reloc_tab, Elf32_Rel* relocation_table, FILE* file) {
  int nb_entries = header_reloc_tab->sh_size / header_reloc_tab->sh_entsize;
  char* sh_str = read_str_tab(fileno(file), sections_tab);
  char* name_tmp = sh_str + header_reloc_tab->sh_name;
  printf("Relocation section '%s' at offset 0x%lx contains %d entries\n", name_tmp, header_reloc_tab->sh_offset, nb_entries);
  printf("Offset\t\tInfo\t\tType\t\tSym. Value\t\tSym. Name + Addend\n");
  for (int i = 0; i < nb_entries; i++) {
    read_relocation_table(sections_tab, relocation_table, i, file);
    printf("%-.8x\t",relocation_table->r_offset);
    printf("%-.8x\t",relocation_table->r_info);
    switch (ELF32_R_TYPE(relocation_table->r_info)) {
      case 0:
      printf("R_ARM_NONE");
      break;
      case 1:
      printf("R_ARM_PC24");
      break;
      case 2:
      printf("R_ARM_ABS32");
      break;
      case 3:
      printf("R_ARM_REL32");
      break;
      case 4:
      printf("R_ARM_PC13");
      break;
      case 5:
      printf("R_ARM_ABS16");
      break;
      case 6:
      printf("R_ARM_ABS12");
      break;
      case 7:
      printf("R_ARM_THM_ABS5");
      break;
      case 8:
      printf("R_ARM_ABS8");
      break;
      case 9:
      printf("R_ARM_SBREL32");
      break;
      case 10:
      printf("R_ARM_THM_PC22");
      break;
      case 11:
      printf("R_ARM_THM_PC8");
      break;
      case 12:
      printf("R_ARM_AMP_VCALL9");
      break;
      case 13:
      printf("R_ARM_TLS_DESC");
      break;
      case 14:
      printf("R_ARM_THM_SWI8");
      break;
      case 15:
      printf("R_ARM_XPC25");
      break;
      case 16:
      printf("R_ARM_THM_XPC22");
      break;
      case 17:
      printf("R_ARM_TLS_DTPMOD32");
      break;
      case 18:
      printf("R_ARM_TLS_DTPOFF32");
      break;
      case 19:
      printf("R_ARM_TLS_TPOFF32");
      break;
      case 20:
      printf("R_ARM_COPY");
      break;
      case 21:
      printf("R_ARM_GLOB_DAT");
      break;
      case 22:
      printf("R_ARM_JUMP_SLOT");
      break;
      case 23:
      printf("R_ARM_RELATIVE");
      break;
      case 24:
      printf("R_ARM_GOTOFF");
      break;
      case 25:
      printf("R_ARM_GOTPC");
      break;
      case 26:
      printf("R_ARM_GOT32");
      break;
      case 27:
      printf("R_ARM_PLT32");
      break;
      case 28:
      printf("R_ARM_CALL");
      break;
      case 29:
      printf("R_ARM_JUMP24");
      break;
      case 30:
      printf("R_ARM_THM_JUMP24");
      break;
      case 31:
      printf("R_ARM_BASE_ABS");
      break;
      case 32:
      printf("R_ARM_ALU_PCREL_7_0");
      break;
      case 33:
      printf("R_ARM_ALU_PCREL_15_8");
      break;
      case 34:
      printf("R_ARM_ALU_PCREL_23_15");
      break;
      case 35:
      printf("R_SBREL_11_0");
      break;
      case 36:
      printf("R_ARM_ALU_SBREL_19_12");
      break;
      case 37:
      printf("R_ARM_ALU_SBREL_27_20");
      break;
      case 38:
      printf("R_ARM_TARGET1");
      break;
      case 39:
      printf("R_ARM_SBREL31");
      break;
      case 40:
      printf("R_ARM_V4BX");
      break;
      case 41:
      printf("R_ARM_TARGET2");
      break;
      case 42:
      printf("R_ARM_PREL31");
      break;
      case 43:
      printf("R_ARM_MOVW_ABS_NC");
      break;
      case 44:
      printf("R_ARM_MOVT_ABS");
      break;
      case 45:
      printf("R_ARM_MOVW_PREL_NC");
      break;
      case 46:
      printf("R_ARM_MOVT_PREL");
      break;
      case 47:
      printf("R_ARM_THM_MOVW_ABS_NC");
      break;
      case 48:
      printf("R_ARM_THM_MOVT_ABS");
      break;
      case 49:
      printf("R_ARM_THM_MOVW_PREL_NC");
      break;
      case 50:
      printf("R_ARM_THM_MOVT_PREL");
      break;
      case 51:
      printf("R_ARM_THM_JUMP19");
      break;
      case 52:
      printf("R_ARM_THM_JUMP6");
      break;
      case 53:
      printf("R_ARM_THM_ALU_PREL_11_0");
      break;
      case 54:
      printf("R_ARM_THM_PC12");
      break;
      case 55:
      printf("R_ARM_ABS32_NOI");
      break;
      case 56:
      printf("R_ARM_REL32_NOI");
      break;
      case 57:
      printf("R_ARM_ALU_PC_G0_NC");
      break;
      case 58:
      printf("R_ARM_ALU_PC_G0");
      break;
      case 59:
      printf("R_ARM_ALU_PC_G1_NC");
      break;
      case 60:
      printf("R_ARM_ALU_PC_G1");
      break;
      case 61:
      printf("R_ARM_ALU_PC_G2");
      break;
      case 62:
      printf("R_PC_G1");
      break;
      case 63:
      printf("R_PC_G2");
      break;
      case 64:
      printf("R_ARM_LDRS_PC_G0");
      break;
      case 65:
      printf("R_ARM_LDRS_PC_G1");
      break;
      case 66:
      printf("R_ARM_LDRS_PC_G2");
      break;
      case 67:
      printf("R_ARM_LDC_PC_G0");
      break;
      case 68:
      printf("R_ARM_LDC_PC_G1");
      break;
      case 69:
      printf("R_ARM_LDC_PC_G2");
      break;
      case 70:
      printf("R_ARM_ALU_SB_G0_NC");
      break;
      case 71:
      printf("R_ARM_ALU_SB_G0");
      break;
      case 72:
      printf("R_ARM_ALU_SB_G1_NC");
      break;
      case 73:
      printf("R_ARM_ALU_SB_G1");
      break;
      case 74:
      printf("R_ARM_ALU_SB_G2");
      break;
      case 75:
      printf("R_SB_G0");
      break;
      case 76:
      printf("R_SB_G1");
      break;
      case 77:
      printf("R_SB_G2");
      break;
      case 78:
      printf("R_ARM_LDRS_SB_G0");
      break;
      case 79:
      printf("R_ARM_LDRS_SB_G1");
      break;
      case 80:
      printf("R_ARM_LDRS_SB_G2");
      break;
      case 81:
      printf("R_ARM_LDC_SB_G0");
      break;
      case 82:
      printf("R_ARM_LDC_SB_G1");
      break;
      case 83:
      printf("R_ARM_LDC_SB_G2");
      break;
      case 84:
      printf("R_ARM_MOVW_BREL_NC");
      break;
      case 85:
      printf("R_ARM_MOVT_BREL");
      break;
      case 86:
      printf("R_ARM_MOVW_BREL");
      break;
      case 104:
      printf("R_ARM_TLS_GD32");
      break;
      case 105:
      printf("R_ARM_TLS_LDM32");
      break;
      case 106:
      printf("R_ARM_TLS_LDO32");
      break;
      case 107:
      printf("R_ARM_TLS_IE32");
      break;
      case 108:
      printf("R_ARM_TLS_LE32");
      break;
      case 109:
      printf("R_ARM_TLS_LDO12");
      break;
      case 110:
      printf("R_ARM_TLS_LE12");
      break;
      case 111:
      printf("R_ARM_TLS_IE12GP");
      break;
      case 128:
      printf("R_ARM_ME_TOO");
      break;
      case 129:
      printf("R_ARM_THM_TLS_DESCSEQ");
      break;
      case 130:
      printf("R_ARM_THM_TLS_DESCSEQ32");
      break;
      case 131:
      printf("R_ARM_THM_GOT_BREL12");
      break;
      case 160:
      printf("R_ARM_IRELATIVE");
      break;
      case 249:
      printf("R_ARM_RXPC25");
      break;
      case 250:
      printf("R_ARM_RSBREL32");
      break;
      case 251:
      printf("R_ARM_THM_RPC22");
      break;
      case 252:
      printf("R_ARM_RREL32");
      break;
      case 253:
      printf("R_ARM_RABS22");
      break;
      case 254:
      printf("R_ARM_RPC24");
      break;
      case 255:
      printf("R_ARM_RBASE");
      break;
      case 256:
      printf("R_ARM_NUM");
      break;

    }
    printf("\t%10.16x\n",(ELF32_R_SYM(relocation_table->r_info)));
  }
}
