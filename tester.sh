#!/bin/bash

make re
if [ $? -eq 0 ]; then
	echo "Build successful"
else
	echo "Build failed"
fi

ERR_COUNT=0

test() {
	IS_BIN="$2"
	INPUT="$1"
	HASH1="$(echo -n "$INPUT" | ./ft_ssl $3 -q)"
	HASH2="$(echo -n "$INPUT" | bash -c "$4")"
	if [ "$HASH1" == "$HASH2" ]; then
		if [ "$IS_BIN" == "1" ]; then
			echo "✅ | $3 | $HASH1 (0x$(echo -n "$INPUT" | xxd -p -c 0))"
		else
			echo "✅ | $3 | $HASH1 ('$INPUT')"
		fi
	else
		if [ "$IS_BIN" == "1" ]; then
			echo "❌ | $3 | $HASH1 != $HASH2 (0x$(echo -n "$INPUT" | xxd -p -c 0))"
		else
			echo "❌ | $3 | $HASH1 != $HASH2 ('$INPUT')"
		fi
		ERR_COUNT=$((ERR_COUNT + 1))
	fi
}

testMD5() {
	test "$1" "$2" "md5" 'md5sum | awk '\''{print $1}'\'''
}

testSHA256() {
	test "$1" "$2" "sha256" 'sha256sum | awk '\''{print $1}'\'''
}

testWhirlpool() {
	test "$1" "$3" "whirlpool" "echo '$2'"
}

LOREM_IPSUM="Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam sapien nibh, porta ac ante eu, eleifend tempus enim. Maecenas posuere velit et sapien malesuada malesuada. Sed non tempus dui. Duis aliquet risus sed ante vulputate suscipit. Etiam justo purus, tempor sed risus at, ornare vehicula odio. Donec mollis rutrum quam sit amet facilisis. Suspendisse urna felis, luctus nec viverra vitae, egestas vel dui. In ut interdum ante, pretium consectetur massa. In tempor lobortis egestas. Sed ut nunc neque. Nulla facilisi. Morbi in ligula fringilla, ultrices nisi vitae, vulputate eros. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed egestas hendrerit nunc, vel rhoncus felis tempus sit amet. Aliquam vulputate, velit quis molestie condimentum, metus mi tristique sem, a tristique urna turpis id tortor. Duis mattis purus non libero varius consequat.
Sed vitae mauris quis justo feugiat bibendum. Sed sodales vel leo at accumsan. Sed eu diam nec libero tempor ultrices quis sit amet nisl. Cras gravida turpis id tincidunt maximus. Vestibulum congue purus non gravida ullamcorper. Integer vestibulum odio eget urna ornare venenatis. Maecenas ac luctus est. Maecenas blandit pretium turpis vitae fringilla. Nam pharetra, justo ut placerat rutrum, justo est fringilla tellus, eget ultricies urna est nec nisi. Phasellus viverra accumsan nibh sed molestie.
Sed nec erat libero. Curabitur et diam urna. Quisque eu malesuada ex, vitae pellentesque sapien. Quisque vel scelerisque velit, lacinia faucibus arcu. Praesent non urna in ante dapibus maximus sed ut mi. Mauris ultricies neque vitae ultricies vestibulum. Aliquam venenatis tortor ut fringilla iaculis. Praesent sed viverra lacus, quis fermentum enim. Duis sit amet posuere est, vel scelerisque nisi. Suspendisse finibus, magna tempus fermentum sagittis, metus odio luctus sapien, vitae mattis risus mauris vitae nibh. Quisque at ante iaculis metus blandit consectetur. Nullam tincidunt suscipit iaculis."

testMD5 "Hello, World!"
testMD5 "42"
testMD5 ""
for i in {1..65}; do
	testMD5 "$(openssl rand $i | sed -e 's/\x00/\xff/g')" 1
done
testMD5 "$LOREM_IPSUM"

testSHA256 "Hello, World!"
testSHA256 "42"
testSHA256 ""
for i in {1..257}; do
	testSHA256 "$(openssl rand $i | sed -e 's/\x00/\xff/g')" 1
done
testSHA256 "$LOREM_IPSUM"

testWhirlpool "Hello, World!" "3D837C9EF7BB291BD1DCFC05D3004AF2EEB8C631DD6A6C4BA35159B8889DE4B1EC44076CE7A8F7BFA497E4D9DCB7C29337173F78D06791F3C3D9E00CC6017F0B"
testWhirlpool "42" "FEE32BE7C00E73EAB97A39549D79AF73AEC87B6FA22A0B56867A4975FE82344CD9776C6D6DFF419E0F2E415C492340BB8329BBFAC0C872934DF66466C2E0E5D3"
testWhirlpool "" "19FA61D75522A4669B44E39C1D2E1726C530232130D407F89AFEE0964997F7A73E83BE698B288FEBCF88E3E03C4F0757EA8964E59B63D93708B138CC42A66EB3"
testWhirlpool "abc" "4E2448A4C6F486BB16B6562C73B4020BF3043E3A731BCE721AE1B303D97E6D4C7181EEBDB6C57E277D0E34957114CBD6C797FC9D95D8B582D225292076D4EEF5"
testWhirlpool "The quick brown fox jumps over the lazy dog" "B97DE512E91E3828B40D2B0FDCE9CEB3C4A71F9BEA8D88E75C4FA854DF36725FD2B52EB6544EDCACD6F8BEDDFEA403CB55AE31F03AD62A5EF54E42EE82C3FB35"
testWhirlpool "$LOREM_IPSUM" "7EC87B9D40E6267498741516FBB726A9C84EE2FCCDB263D2CB4FEAF8E81E924F486CAA6F5360351FD6A0C6F0098CBE220BBF553C729267E4A09B1A2D23914D65"

exit $ERR_COUNT
