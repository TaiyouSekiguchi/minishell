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
result "cd .." "pwd"
result "export TEST=taiyou" "export" "unset TEST" "env"
