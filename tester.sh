#!/bin/bash

make re
if [ $? -eq 0 ]; then
	echo "Build successful"
else
	echo "Build failed"
fi

test() {
	IS_BIN="$2"
	INPUT="$1"
	HASH1="$(./ft_ssl $3 -q -s "$INPUT")"
	HASH2="$(echo -n "$INPUT" | $4 | awk '{print $1}')"
	if [ "$HASH1" == "$HASH2" ]; then
		if [ "$IS_BIN" == "1" ]; then
			echo "✅ | $HASH1 (0x$(echo -n "$INPUT" | xxd -p -c 0))"
		else
			echo "✅ | $HASH1 ('$INPUT')"
		fi
	else
		if [ "$IS_BIN" == "1" ]; then
			echo "❌ | $HASH1 != $HASH2 (0x$(echo -n "$INPUT" | xxd -p -c 0))"
		else
			echo "❌ | $HASH1 != $HASH2 ('$INPUT')"
		fi
		exit 1
	fi
}

testMD5() {
	test "$1" "$2" "md5" "md5sum"
}

testSHA256() {
	test "$1" "$2" "sha256" "sha256sum"
}

testMD5 "Hello, World!"
testMD5 "42"
testMD5 ""
for i in {1..65}; do
	testMD5 "$(openssl rand $i | sed -e 's/\x00/\xff/g')" 1
done

testSHA256 "Hello, World!"
testSHA256 "42"
testSHA256 ""
for i in {1..257}; do
	testSHA256 "$(openssl rand $i | sed -e 's/\x00/\xff/g')" 1
done
