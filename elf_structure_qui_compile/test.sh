#!/bin/bash
if [[ $# < 2 ]]; then
  echo "Usage :"
  echo " ./test.sh -h [FILE_NAME] : teste l'affichage de l'en-tête du fichier elf spécifié"
  echo " ./test.sh -S [FILE_NAME]: teste l'affichage de la table des sections du fichier elf spécifié"
  echo " ./test.sh -x [SECTION_NB] [FILE_NAME]: teste l'affichage du contenu de la section n°[SECTION_NB] du fichier elf spécifié"
  echo " ./test.sh -x [SECTION_NAME] [FILE_NAME]: teste l'affichage du contenu de la section de nom [SECTION_NAME] du fichier elf spécifié"
  echo " ./test.sh -s [FILE_NAME]: teste l'affichage de la table des symboles du fichier elf spécifié"
  echo " ./test.sh -r [FILE_NAME]: teste l'affichage des tables de réimplantation du fichier elf spécifié"
elif [[ $1 = "-s" ]]; then
  if [[ -e test_files/symtab_$2.txt ]]; then
    rm test_files/symtab_$2.txt
  fi
  if [[ -e test_files/ref_symtab_$2.txt ]]; then
    rm test_files/ref_symtab_$2.txt
  fi
  ./readelf -s $2 >> test_files/symtab_$2.txt
  readelf -s $2 >> test_files/ref_symtab_$2.txt
  different=$(diff -w test_files/ref_symtab_$2.txt test_files/symtab_$2.txt)
  if [[ $different = "" ]]; then
    echo "Test de l'affichage de la table des symboles réussi"
  else
    diff -w -c test_files/ref_symtab_$2.txt test_files/symtab_$2.txt
    echo "Test de l'affichage de la table des symboles échoué, les lignes commençant par ! sont celles qui diffèrent"
  fi
elif [[ $1 = "-h" ]]; then
  if [[ -e test_files/header_$2.txt ]]; then
    rm test_files/header_$2.txt
  fi
  if [[ -e test_files/ref_header_$2.txt ]]; then
    rm test_files/ref_header_$2.txt
  fi
  ./readelf -h $2 >> test_files/header_$2.txt
  readelf -h $2 >> test_files/ref_header_$2.txt
  different=$(diff -w test_files/ref_header_$2.txt test_files/header_$2.txt)
  if [[ $different = "" ]]; then
    echo "Test de l'affichage du header réussi"
  else
    diff -w -c test_files/ref_header_$2.txt test_files/header_$2.txt
    echo "Test de l'affichage du header échoué, les lignes commençant par ! sont celles qui diffèrent"
  fi
elif [[ $1 = "-S" ]]; then
  if [[ -e test_files/sections_tab_$2.txt ]]; then
    rm test_files/sections_tab_$2.txt
  fi
  if [[ -e test_files/ref_sections_tab_$2.txt ]]; then
    rm test_files/ref_sections_tab_$2.txt
  fi
  ./readelf -S $2 >> test_files/sections_tab_$2.txt
  readelf -S $2 >> test_files/ref_sections_tab_$2.txt
  different=$(diff -w test_files/ref_sections_tab_$2.txt test_files/sections_tab_$2.txt)
  if [[ $different = "" ]]; then
    echo "Test de l'affichage de la table des sections réussi"
  else
    diff -w -c test_files/ref_sections_tab_$2.txt test_files/sections_tab_$2.txt
    echo "Test de l'affichage de la table des sections échoué, les lignes commençant par ! sont celles qui diffèrent"
  fi
elif [[ $1 = "-x" && $2 != "" ]]; then
  if [[ -e test_files/section_"$2"_content_"$3".txt ]]; then
    rm test_files/section_"$2"_content_"$3".txt
  fi
  if [[ -e test_files/ref_section_"$2"_content_"$3".txt ]]; then
    rm test_files/ref_section_"$2"_content_"$3".txt
  fi
  ./readelf -x $2 $3 >> test_files/section_"$2"_content_"$3".txt
  readelf -x $2 $3 >> test_files/ref_section_"$2"_content_"$3".txt
  different=$(diff -w test_files/ref_section_"$2"_content_"$3".txt test_files/section_"$2"_content_"$3".txt)
  if [[ $different = "" ]]; then
    echo "Test de l'affichage du contenu d'une section réussi"
  else
    diff -w -c test_files/ref_section_"$2"_content_"$3".txt test_files/section_"$2"_content_"$3".txt
    echo "Test de l'affichage du contenu d'une section échoué, les lignes commençant par ! sont celles qui diffèrent"
  fi
elif [[ $1 = "-r" && $2 != "" ]]; then
  if [[ -e test_files/relocation_tab_$2.txt ]]; then
    rm test_files/relocation_tab_$2.txt
  fi
  if [[ -e test_files/ref_relocation_tab_$2.txt ]]; then
    rm test_files/ref_relocation_tab_$2.txt
  fi
  ./readelf -r $2 >> test_files/relocation_tab_$2.txt
  readelf -r $2 >> test_files/ref_relocation_tab_$2.txt
  different=$(diff -w test_files/ref_relocation_tab_$2.txt test_files/relocation_tab_$2.txt)
  if [[ $different = "" ]]; then
    echo "Test de l'affichage des tables de relocation réussi"
  else
    diff -w -c test_files/ref_relocation_tab_$2.txt test_files/relocation_tab_$2.txt
    echo "Test de l'affichage des tables de relocation échoué, les lignes commençant par ! sont celles qui diffèrent"
  fi
fi
