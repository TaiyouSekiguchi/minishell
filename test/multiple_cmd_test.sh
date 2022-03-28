#!/bin/bash

function result () {
	echo "================    START    ====================="
	echo [COMMAND] : ["$1"] ["$2"] ["$3"] ["$4"] ["$5"] ["$6"] ["$7"] ["$8"] ["$9"]
	echo ""
	../minishell -c "$1" "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9"
	echo "================    FINISH   ====================="
	echo ""
	read Wait
}

result "ls -al"
result 'export TEST=hoge' 'export TEST=HOGE' 'export TEST=' 'export TEST=LOVE' 'echo $TEST'
result "export TEST=hoge" "export" "unset TEST" "env"
result "export TEST=hoge" "export" "unset TEST TEST TEST TEST" 'echo $TEST'
result "export TEST" "unset TEST" "export"
result "unset TEST"
result "cd .." "pwd"
result "cd /tmp/" "pwd"
result "cd" "cd .." "cd /" "cd //" "cd .." "cd ."
result "cd /../../..////../..//./..//" "pwd"
result "cd /tmp/.."  "pwd"
result "cd /tmp/../../../../tmp/" "pwd"
result "cd /////tmp/../../../../tmp/" "pwd"
