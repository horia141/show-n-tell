UTILS_SRC_C = utils.c
UTILS_SRC_H = utils.h
UTILS_SRC = $(UTILS_SRC_C) $(UTILS_SRC_H)

COLOR_SRC_C = color.c
COLOR_SRC_H = color.h
COLOR_SRC = $(COLOR_SRC_C) $(COLOR_SRC_H)

IMAGE_SRC_C = image.c
IMAGE_SRC_H = image.h
IMAGE_SRC = $(IMAGE_SRC_C) $(IMAGE_SRC_H)

VISUALS_SRC_C = visuals.c
VISUALS_SRC_H = visuals.h
VISUALS_SRC = $(VISUALS_SRC_C) $(VISUALS_SRC_H)
VISUALS_LIB = -lglut

SRC = $(UTILS_SRC) $(COLOR_SRC) $(IMAGE_SRC) $(VISUALS_SRC)
LIB = $(UTILS_LIB) $(COLOR_LIB) $(IMAGE_LIB) $(VISUALS_LIB)

test-utils: dirs $(UTILS_SRC) test_utils.c
	gcc -g -Wall -o ./out/test/utils -DCPU $(UTILS_SRC_C) test_utils.c
	valgrind --leak-check=full ./out/test/utils

test-color: dirs $(COLOR_SRC) test_color.c
	gcc -g -Wall -o ./out/test/color -DCPU $(COLOR_SRC_C) test_color.c
	valgrind --leak-check=full ./out/test/color

test-image: dirs $(UTILS_SRC) $(COLOR_SRC) $(IMAGE_SRC) test_image.c
	gcc -g -Wall -o ./out/test/image -DCPU $(UTILS_SRC_C) $(COLOR_SRC_C) $(IMAGE_SRC_C) test_image.c
	valgrind --leak-check=full ./out/test/image

test-visuals: dirs $(UTILS_SRC) $(COLOR_SRC) $(VISUALS_SRC) test_visuals.c
	gcc -g -Wall -o ./out/test/visuals -DCPU $(VISUALS_LIB) $(UTILS_SRC_C) $(COLOR_SRC_C) $(VISUALS_SRC_C) test_visuals.c
	valgrind --leak-check=full ./out/test/visuals

dist: dirs $(SRC)
	mkdir -p ./out/dist
	gcc -g -Wall -shared -Wl,-soname,libsnt.so -o ./out/dist/libsnt.so $(LIB) $(SRC)
	cp utils.h ./out/dist
	cp color.h ./out/dist
	cp image.h ./out/dist
	cp visuals.h ./out/dist

dirs:
	mkdir -p ./out
	mkdir -p ./out/test
	mkdir -p ./out/dist
	mkdir -p ./out/tmp
