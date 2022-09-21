include ../config.mak

APP = es20_eglCreatePixmapSurface
all:$(APP)

OBJ=$(patsubst %.c,%.o,$(SAMPLE_SRC))
$(OBJ): %.o: %.c
	$(AT)$(CC) -c  $^ -o $@ $(INC_DIR) $(LIB_DIR) $(LIBS) $(MACRO)

OBJ2=$(patsubst %.c,%.o,$(COMMON_SRC))

OBJ3=$(patsubst %.c,%.o,$(ADP_SRC))

$(OBJ2): %.o: %.c
	$(AT)$(CC) -c $^ -o $@ $(INC_DIR) $(LIB_DIR) $(LIBS) $(MACRO)

$(APP):$(OBJ3) $(OBJ2) $(OBJ)
	$(AT)$(CC) -o $@ $^ $(INC_DIR) $(LIB_DIR) $(LIBS) $(MACRO)

clean:
	-@rm -f $(APP)
	-@rm -f $(OBJ)
	-@rm -f $(OBJ2)
