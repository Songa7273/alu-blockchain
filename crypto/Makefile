CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
AR = ar
ARFLAGS = rcs

SRC = sha256.c ec_create.c ec_to_pub.c ec_from_pub.c \
	ec_save.c ec_load.c ec_sign.c ec_verify.c

OBJ = $(SRC:.c=.o)

libhblk_crypto.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f libhblk_crypto.a

re: fclean libhblk_crypto.a

.PHONY: clean fclean re
