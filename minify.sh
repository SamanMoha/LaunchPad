#! /bin/sh

INFILE=launchpad_interface.html
OUTFILE=interfaceHTML.h

echo "// !!! FILE GENERATED AUTOMATICALLY FROM index.html AND minify.sh !!!" > $OUTFILE
echo "// !!! DO NOT MODIFY !! \n" >> $OUTFILE

/bin/echo -n "String handleRootHTML = \" " >> $OUTFILE

html-minifier --quote-character "'" \
              --collapse-whitespace \
              --minify-js true \
              --minify-css true \
              $INFILE | sed "s:\":':g" >> $OUTFILE
              # replace double quotes by single quotes

echo " \" ; \n " >> $OUTFILE

echo "Here is the content of the file that was generated:\n"
cat $OUTFILE

