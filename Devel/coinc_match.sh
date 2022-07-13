#!/bin/bash

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-$0}"; )" &> /dev/null && pwd 2> /dev/null; )";

{ Output=$($SCRIPT_DIR/CoincMatchProc $1 2>&1 1>&3-) ;} 3>&1

echo "Return/Erorrs: " $Output

echo $Output > .ret_val_dpe.txt
