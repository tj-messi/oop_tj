common：公共文件
	注意：class_aat.cpp - 部分给出，需要自行补充完整

include：公共头文件
	注意：class_aat.h - 部分给出，需要自行补充完整
              lib_aat_tools.h - 不准改动

lib：公共库文件
	注意：lib_common_tools.lib已给出，需要打开 class_aat.h 中的 ENABLE_LIB_COMMON_TOOLS 才能用
              lib_common_tools.pdb不要改动，仅为了去除编译警告

test_args_analyse_tools：class_aat工具集测试函数
	注意：test_args_analyses_tools.cpp - 已完整给出，建议的命令行测试在.cpp最后的注释中

my_ping：ping工具参数模拟程序
	注意：my_ping.cpp - 有一个条件编译选项需要置0/1后分别测试，有一个函数需要实现

my_convert：Windows和Linux格式的文本文件互转工具
	注意：my_convert.cpp - 有一个条件编译选项需要置0/1后分别测试，其他不需要改动
