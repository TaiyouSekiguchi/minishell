#!/bin/bash

function test () {
	echo "================================================"
	echo "TEST COMMAND :" ["${1}"]
	echo ""

	MINI=`../minishell -c "${1}" 2>&1`
	MINI_STATUS=`echo $?`

	REAL=`bash -c "${1}" 2>&1`
	REAL_STATUS=`echo $?`

	if [ "$MINI" == "$REAL" ]; then
		echo "[ OUTPUT is EQUAL. ]"
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
	echo ""
}

commands=(
	'""'
	"''"
	'.'
	'..'
	'/'
	'/Users'
	'/no_exist_dir'
	'/bin/ls'
	'/bin/ls -l'
	'/usr/bin/file ./minishell'
	'/usr/bin/wc -l ./minishell'
	'echo'
	'echo hello'
	'echo -n-n-n 42'
	'echo 42 -n'
	'echo -n'
	'echo -n 42'
	'echo -n 42-n'
	'echo -n aaa -n bbb -n ccc'
	'exit'
	'exit "      42"'
	'exit +123'
	'exit -456'
	'exit 1111111111'
	'exit 9223372036854775807'
	'exit -9223372036854775808'
	'exit 9223372036854775808'
	'exit -9223372036854775809'
	'exit a'
	'exit ++1'
	'exit ft 42'
	'exit 12345abc'
	'exit 1 2 3'
	'exit 42 ft'
	'/usr/bin/grep notexist Makefile'
	'/bin/ls -3'
	'/usr/bin/grep a filenotexist'
	'cmdnotexist'
	'echo ||||||'
	'echo a >>'
	'echo "" "" "" | cat -e'
	'"/bin/ls" srcs'
	'"/bin/ls srcs"'
	'"/bi"n/ls srcs'
	'""/bin/ech"o" "test"'
	'"/bin/echo -n hello"'
	'"/bin/ls" ">" "test"'
	"echo 'Hello, world'"
	"echo '\$USER'"
	"echo '\"'"
	"echo ''\$USER''"
	"echo '''\$USER'''"
	'env | sort'
	'export'
	'export TEST=hoge'
	'export aaa'
	'export 42="42"'
	'export _42="42"'
	'cd .'
	'cd ..'
	'cd ../'
	'cd ""'
	'cd /'
	'cd aaa'
	'cd //'
	'cd ../../../../..///../.././../../'
	'cd /tmp/..'
	'cd /tmp/../'
	'pwd'
	'/../bin/ls'
	'/../bin/ls/'
	'/tmp/../bin/ls'
	'ls -al'
	'cat .gitignore'
	'<notexist'
	'cat Makefile | grep .c | grep fclean'
	'echo $'
	'echo $$'
	'echo " $"'
	'echo "\$"'
	'echo "$USER"'
	"echo '\$USER'"
	"echo \"'\$USER'\""
	"echo \"'hoge-\$USER-hoge'\""
)

echo -n>simple.log
for (( i = 0; i < ${#commands[@]}; ++i))
do
	test "${commands[$i]}" >> simple.log
done

echo 'test finished.'
