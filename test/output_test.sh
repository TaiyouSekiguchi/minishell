function test () {
	eval ./output_test ${1}
}


commands=(
	"cat \-e \<.gitignore"
)

for cmd in "${commands[@]}";
do
	echo "${cmd}"
	BASH=`echo "${cmd}" | tr -d '\\'`
	test "$cmd" $BASH
	echo $BASH
	$BASH
	#echo $BASH
done