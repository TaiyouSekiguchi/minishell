#!/bin/bash

function test () {
	echo "==============================================="
	echo "TEST COMMAND :" "${1}"
	echo ""

	MINI=`../minishell -c "${1}" 2>&1`
	MINI_STATUS=`echo $?`

	REAL=`bash -c "${1}" 2>&1`
	REAL_STATUS=`echo $?`

	if [ "$MINI" == "$REAL" ]; then
		echo "[ OUTPUT is EQUAL ]."
		echo $MINI
	else
		echo "[ OUTPUT is DIFFERENT. ]"
		echo "<<< minishell output >>>"
		echo $MINI
		echo ""

		echo "<<< bash output >>>"
		echo $REAL
	fi

	echo ""
	if [ "$MINI_STATUS" = "$REAL_STATUS" ]; then
		echo "[ STATUS is EQUAL. ]"
		echo $MINI_STATUS
	else
		echo "[ STATUS is DIFFERENT. ]"
		echo "MINISHELL :" $MINI_STATUS
		echo "BASH      :" $REAL_STATUS
	fi
	echo "==============================================="
	echo ""
	echo ""
}


function result () {
	echo "==============================================="
	RESULT=`../minishell -c "$1" "$2" "$3" "$4" "$5"`
	echo -n $RESULT
	echo "==============================================="
	echo ""
}

result "ls -al"
result "cd .." "pwd"
result "export TEST=taiyou" "export" "unset TEST" "env"


