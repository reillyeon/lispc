redo-ifchange config.sh
. ./config.sh
exec > $3
cat <<-EOF
  redo-ifchange \$2.cpp
  $CXX $CXXFLAGS -MD -MF \$3.deps.tmp -o \$3 -c \$2.cpp
  DEPS=\$(sed -e "s/^\$3://" -e 's/\\\\//g' <\$3.deps.tmp)
  rm -f \$3.deps.tmp
  redo-ifchange \$DEPS
EOF
chmod a+x $3
