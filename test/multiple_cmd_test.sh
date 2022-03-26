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
result "export TEST=taiyou" "export" "unset TEST" "env"
result "export A B=b C D=d E F=f" "export" "env" "unset A D" "export" "env"
result 'export A="ho -n"' "ec\$A hoge"
result 'export A="c"' 'export B=h' 'export C=o' 'export HOGE=HOME' "e\$A\$B\$C \$HOGE"
result 'export A="c"' 'export B=h' 'export C=o' 'export HOGE=HOME' "e\$A\$B\$C \$\$HOGE"
result "cd" "cd --" "pwd" "echo \$PWD"
result "cd .." "pwd"
result "cd" "cd .." "cd /" "cd //" "cd .." "cd ." "pwd" "echo $PWD"
result "cd /../../..////../..//./..//" "pwd"
result "cd /tmp/.."  "pwd"
result "cd /tmp/../../../../tmp/" "pwd"
result "cd /////tmp/../../../../tmp/" "pwd"
result "cat <../.gitignore | wc -l > outfile" "cat outfile" "rm outfile"
result ">out1 >>out2 <no1 >out3 >> out4"
result "<../.gitignore > out1 > out2 >out3 >out4" "ls -al | grep out" "rm out1 out2 out3 out4"