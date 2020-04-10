make: runelection.cpp hashFunctions.cpp bloom.cpp postlist.cpp redblack.cpp
	g++ -o runelection runelection.cpp hashFunctions.cpp bloom.cpp postlist.cpp redblack.cpp

.PHONY: clean

clean:
	rm -f runelection
