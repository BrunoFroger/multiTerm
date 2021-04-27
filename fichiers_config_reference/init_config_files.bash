#!/bin/bash
# copie des fichiers de configurations dans les bons repertoires

HOME_DIR=/Users/obfe6300

SOURCE_DIR=${HOME_DIR}/fichiers_config_reference
DEST_DIR_CFG=${HOME_DIR}/devBruno/multiTerm/build-multiTerm-Desktop_Qt_6_0_1_clang_64bit-Debug/multiTerm.app/Contents/MacOS
DEST_DIR_CNX=${HOME_DIR}/multiTerm

ln -s ${SOURCE_DIR}/multiTerm.cfg ${DEST_DIR_CFG}
ln -s ${SOURCE_DIR}/multiTerm.cnx ${DEST_DIR_CNX}