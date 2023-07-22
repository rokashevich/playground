#!/bin/bash
set -euE -o pipefail
function exit_handler() 
{
  echo exit_code=$?
#  trap - EXIT
}
trap exit_handler ERR EXIT
echo 111
echo 222
echo 33
d
