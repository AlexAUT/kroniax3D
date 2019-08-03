#!/bin/zsh

CLIENT_NUMBER=$1

# Stop if a build error occures
set -e

cd "${0%/*}"

SCRIPT_DIR=$(pwd)


mkdir -p /tmp/test
cd /tmp/test
cmake $SCRIPT_DIR -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_SHARED_LIBS=ON

make rocketwars_game rocketwars_server -j

cd $SCRIPT_DIR

# Do not exit if the server or client crashes
set +e

/tmp/test/rocketwars_server &
SERVER_PID=$!

# Start the game CLIENT_NUMBER of times
for i in $(seq 1 $CLIENT_NUMBER); do
  /tmp/test/rocketwars_game &
  pids[${i}]=$!
done
# wait for games to close
for pid in ${pids[*]}; do
    wait $pid
done

# Kill the server
kill $SERVER_PID
