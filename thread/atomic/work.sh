set -x
make clean

option=$1

make ${option}
set +x
while true
do
    ./${option}.out
done