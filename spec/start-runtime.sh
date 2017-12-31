#!/bin/bash -e
SERIALFILE=test.microflo
OPTIONS="--port 3333 --baudrate 115200 --serial $SERIALFILE"

# Make sure we clean up
trap 'kill $(jobs -p)' EXIT

./build/tests/runtime $SERIALFILE &
sleep 2
./node_modules/.bin/microflo runtime $OPTIONS --componentmap build/tests/runtime.component.map.json
