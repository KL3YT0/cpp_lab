build:
	g++ ./BinaryHeap/BinaryHeap.cpp ./IsPowerOfTwo/IsPowerOfTwo.cpp app.cpp -o app -Wall

run:
	./app

run_vg:
	valgrind ./app

run_vg_full:
	valgrind --leak-check=full ./app

run_cg:
	valgrind --tool=callgrind ./app