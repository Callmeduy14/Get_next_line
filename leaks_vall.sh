#!/usr/bin/env bash
set -euo pipefail

# Konfigurasi
MAND_SRC="get_next_line.c get_next_line_utils.c"
BONUS_SRC="get_next_line_bonus.c get_next_line_utils_bonus.c"
TESTER="tester_gnl.c"

# Sample data
echo -e "A1\nA2\nA3\n" > a.txt
printf "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n" > b.txt
{ seq 1 200 | sed 's/^/Line /'; } > big.txt
# file tanpa newline terakhir
printf "no-newline-here" > nonl.txt

build() {
  local mode=$1
  local bs=$2
  local out=$3
  if [[ "$mode" == "mand" ]]; then
    cc -g -Wall -Wextra -Werror -D BUFFER_SIZE=$bs $MAND_SRC $TESTER -o "$out"
  else
    cc -g -Wall -Wextra -Werror -D BUFFER_SIZE=$bs $BONUS_SRC $TESTER -o "$out" -DUSE_BONUS
  fi
}

run_vg() {
  local bin=$1; shift
  echo ">> valgrind $bin $*"
  valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=definite --error-exitcode=111 \
    "./$bin" "$@" >/dev/null
  local rc=$?
  if [[ $rc -eq 0 ]]; then
    echo "   ✅ OK (no definite leaks)"
  else
    echo "   ❌ Leak detected or error (rc=$rc)"
  fi
}

# Matrix BUFFER_SIZE
for BS in 1 42 4096; do
  echo "=========================="
  echo "BUFFER_SIZE=$BS (MAND)"
  build mand $BS gnl_m_$BS
  run_vg gnl_m_$BS full a.txt
  run_vg gnl_m_$BS full nonl.txt
  # Early exit (harusnya leak kalau static buffer tidak dibersihkan):
  if ! run_vg gnl_m_$BS early big.txt 3; then
    echo "   (Expected for many GNL: early-exit can reveal static-buffer leak)"
  fi

  echo "--------------------------"
  echo "BUFFER_SIZE=$BS (BONUS)"
  build bonus $BS gnl_b_$BS
  run_vg gnl_b_$BS full a.txt b.txt
  run_vg gnl_b_$BS interleave a.txt b.txt
  if ! run_vg gnl_b_$BS early big.txt 5; then
    echo "   (Expected for many GNL: early-exit can reveal static-buffer leak)"
  fi
done

echo "Done."
