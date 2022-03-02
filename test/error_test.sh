#!/bin/bash

function test () {
	echo =================== ${3} ======================
	echo "----------------- command --------------------"
	echo ${2}
	echo "----------------------------------------------"
	echo "== minishell =="
	eval ./error_test ${1}
	echo "== bash =="
	eval ${2}
}

commands=(
	#cmdが存在しない
	"hoge_cmd"
	#infileが存在しない
	"cat \-e \<hoge_file"
	#コマンド, infile なし
	"hoge \-e hoge_file \| wc \-l"
	#いろいろ
	"cat \<.gitignore \| hoge_cmd \| cat \-hoge \> outfile"
)

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
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "                         finish                           "
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo " "