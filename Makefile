# 编译器设置
CC := gcc

# 添加 include 路径 和 ***新的依赖生成选项***
CFLAGS := -g -Wall -Iinclude -MMD -MP

# 目录定义
SRCDIR := src
BUILDDIR := build

# 目标文件
TARGET := $(BUILDDIR)/main

# 自动查找所有 .c 文件
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
DEPS := $(OBJS:.o=.d) # ***新增：定义依赖文件的变量***
# 默认目标
all: $(TARGET)

# 链接
$(TARGET): $(OBJS)
	@echo "Linking..."
	@$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "Build finished: $(TARGET)"

# 编译
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# 创建 build 目录
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

# 清理
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILDDIR)

# ***新增：包含所有自动生成的依赖文件***
# 这一行告诉 make 去读取那些 .d 文件，了解头文件依赖
-include $(DEPS)

.PHONY: all clean
