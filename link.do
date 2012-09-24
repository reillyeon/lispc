redo-ifchange config.sh
. ./config.sh
exec > $3
cat <<-EOF
  set -e
  OUT="\$1"
  shift
  $CXX $LDFLAGS -o "\$OUT" "\$@"
EOF
chmod a+x $3
