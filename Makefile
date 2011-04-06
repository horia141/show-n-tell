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

test-utils: $(UTILS_SRC) test_utils.c
	gcc -g -Wall -o test-utils -DCPU $(UTILS_SRC_C) test_utils.c
	valgrind --leak-check=full ./test-utils

test-color: $(COLOR_SRC) test_color.c
	gcc -g -Wall -o test-color -DCPU $(COLOR_SRC_C) test_color.c
	valgrind --leak-check=full ./test-color

test-image: $(UTILS_SRC) $(COLOR_SRC) $(IMAGE_SRC) test_image.c
	gcc -g -Wall -o test-image -DCPU $(UTILS_SRC_C) $(COLOR_SRC_C) $(IMAGE_SRC_C) test_image.c
	valgrind --leak-check=full ./test-image

test-visuals: $(UTILS_SRC) $(COLOR_SRC) $(VISUALS_SRC) test_visuals.c
	gcc -g -Wall -o test-visuals -DCPU $(VISUALS_LIB) $(UTILS_SRC_C) $(COLOR_SRC_C) $(VISUALS_SRC_C) test_visuals.c
	valgrind --leak-check=full ./test-visuals
