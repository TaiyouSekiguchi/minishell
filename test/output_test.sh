#!/bin/bash

function test () {
	echo =================== ${3} ======================
	echo "<<<<< input >>>>>"
	echo ${2}
	echo " "
	echo "== minishell =="
	eval ./output_test ${1} > ./test/minishell_out.txt
	echo "==   bash    =="
	echo " "
	eval ${2} > ./test/bash_out.txt
	echo "<<<<< outcome >>>>>"
	diff -L MINISHELL -L BASH -q -u -s ./test/minishell_out.txt ./test/bash_out.txt
	echo " "
	echo " " >> ./test/test.log
	echo =================== ${3} ====================== >> ./test/test.log
	echo "< input >" >> ./test/test.log
	echo ${2} >> ./test/test.log
	#echo " " >> ./test/test.log
	echo "< outcome >" >> ./test/test.log
	diff -L MINISHELL -L BASH -q -s ./test/minishell_out.txt ./test/bash_out.txt >> ./test/test.log
	diff -L MINISHELL -L BASH -u ./test/minishell_out.txt ./test/bash_out.txt >> ./test/test.log
}

commands=(
	'echo $HOME'
	"pwd"
	"ls"
	"cat \-e \<.gitignore"
	"cat .\/test\/big_file \| wc \-l"
	"cat .\/test\/big_file \| cat \<.gitignore"
	"cat .\/test\/big_file \| cat \<.gitignore \| wc \-l"
	"cat .\/test\/big_file \| cat \<.gitignore \| wc \-l \| cat \-e"
	#"echo \"\" \"\" \"\" \| cat \-e"
	"pwd \| wc \-l"
	#"\"/bin/ls srcs\""
	#"\"/bi\"n/ls srcs"
	"\"\"/bin/ech\"o\" \"test\""
)

rm -rf ./test/test.log
echo " "
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "                         start                           "
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
cnt=0
for cmd in "${commands[@]}"
do
	MINI=$cmd
	BASH=`echo "${cmd}" | tr -d '\\'`
	test "$MINI" "$BASH" $cnt
	cnt=`echo "$cnt+1" | bc`
done
rm -rf ./test/bash_out.txt
rm -rf ./test/minishell_out.txt
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "                         finish                           "
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "For more information, please see \"./test/test.log\" file."
echo " "
