find . -type f -name \*.o -print0 | xargs -0 rm -f
rm -f main
rm -f compile link
